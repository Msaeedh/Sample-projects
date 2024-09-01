#include "communicator.h"

Communicator::Communicator(QObject *parent)
    : QObject{parent} ,
    mIp("127.0.0.1") ,
    mPort("9009"),
    mSocket(nullptr),
    mServer(nullptr)
{
    QString date = QDateTime::currentDateTime().toString("ddd MMM dd.MM.yyyy");
    QString time = QDateTime::currentDateTime().toString("hh:mm:ss");

    addHistory("Wellcome\n") ;
    addHistory( date + " " + time + "\n") ;
    setStatus("Not Connected") ;
}


void Communicator::send()
{
    if (checkConnection()) {
        mSocket->write((name()+": "+mMessage).toUtf8());
        mSocket->flush() ;
        QString time = QDateTime::currentDateTime().toString("hh:mm:ss");
        addHistory("\n" +time+ "    --> you: " + mMessage) ;
    } else {
        setStatus("Unable to send , Connection failure") ;
    }
}


void Communicator::Read()
{
    QString msg(mSocket->readAll()) ;

    if(msg == "---Clear---History--->"){
        clearHistory() ;
        msg = "" ;
        return ;
    }

    QString time = QDateTime::currentDateTime().toString("hh:mm:ss");

    msg.remove("---Clear---History--->") ;
    addHistory("\n" +time+ "    --> " + msg) ;
}

void Communicator::waitForConnection()
{
    if(!checkConnection()) {
        setStatus("Waiting for Connection ...") ;
        if(mServer == nullptr)
            mServer = new QTcpServer ;
        else
            mServer->resumeAccepting() ;

        mServer->listen(QHostAddress::Any , mPort.toUShort()) ;
        setStatus("server initialized ") ;
        mServer->waitForNewConnection(5000) ;
        mSocket = mServer->nextPendingConnection() ;
        mServer->pauseAccepting() ;
        if(checkConnection()){
            QObject::connect(mSocket , &QTcpSocket::readyRead , this , &Communicator::Read ) ;
            QObject::connect(mSocket , &QTcpSocket::disconnected , [&]{
                setStatus("Disconnected") ;
            }) ;
            setStatus("Connected") ;
        }else
            setStatus("Connection unsuccessful") ;
    }
}

void Communicator::connectTcp()
{
    if(!checkConnection()) {
        deleteServer();
        setStatus("Connecting to Host ...") ;
        if(mSocket == nullptr)
            mSocket = new QTcpSocket ;

        mSocket->connectToHost(QHostAddress(mIp) , mPort.toUShort() ) ;
        mSocket->waitForConnected(1200) ;
        if(checkConnection() ){
            setStatus("Connected") ;
            QObject::connect(mSocket , &QTcpSocket::readyRead , this , &Communicator::Read ) ;
            QObject::connect(mSocket , &QTcpSocket::disconnected , [&]{
                setStatus("Disconnected") ;
            }) ;
        }
        else
            setStatus("Connection unsuccessful") ;
    }
}

void Communicator::clearHistory()
{
    setHistory("") ;
    if (mSocket && mSocket->state() == QAbstractSocket::ConnectedState) {
        mSocket->write(QString("---Clear---History--->").toUtf8());
    }
}

void Communicator::deleteServer()
{
    if(checkConnection())
        mSocket->abort() ;
    if(mServer != nullptr ){
        delete mServer ;
        mServer = nullptr ;
        delete mSocket ;
        mSocket = nullptr ;
    }
}

bool Communicator::checkConnection()
{
    if(mSocket && mSocket->state() == QAbstractSocket::SocketState::ConnectedState){
        return true ;
    }
    return false ;

}

void Communicator::disconnect()
{
    if(checkConnection()){
        mSocket->abort() ;
        setStatus("Manually Disconnected") ;
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////

QString Communicator::port() const
{
    return mPort;
}

void Communicator::setPort(const QString &newPort)
{
    if (mPort == newPort)
        return;
    mPort = newPort;
    emit portChanged();
}

QString Communicator::ip() const
{
    return mIp;
}

void Communicator::setIp(const QString &newIp)
{
    if (mIp == newIp)
        return;
    mIp = newIp;
    emit ipChanged();
}

QString Communicator::status() const
{
    return mStatus;
}

void Communicator::setStatus(const QString newStatus)
{
    if (mStatus == newStatus)
        return;
    mStatus = newStatus;
    emit statusChanged();
}

QString Communicator::history() const
{
    return mHistory;
}

void Communicator::setHistory(const QString newHistory)
{
    if (mHistory == newHistory)
        return;
    mHistory = newHistory;
    emit historyChanged();
}

void Communicator::addHistory(QString newHistory)
{
    setHistory(history() + newHistory ) ;
}

QString Communicator::message() const
{
    return mMessage;
}

void Communicator::setMessage(const QString newMessage)
{
    if (mMessage == newMessage)
        return;
    mMessage = newMessage;
    emit messageChanged();
}

QString Communicator::name() const
{
    return mName;
}

void Communicator::setName(const QString &newName)
{
    if (mName == newName)
        return;
    mName = newName;
    emit nameChanged();
}
