#include "reciever.h"

Reciever::Reciever(QObject *parent ) :
    QObject(parent),
    mDisplay("0.0")
{
    mCalc = new Calculator(this) ;
    mServer = new QTcpServer(this);
    connect(mServer, &QTcpServer::newConnection, this, &Reciever::newConnection);
    if (!mServer->listen(QHostAddress::Any, 9009)) {
        qDebug() << "Server could not start!";
    } else {
        qDebug() << "Server started!";
    }
}

void Reciever::readData()
{
    qDebug()<< "Reciever::readData()" ;
    QByteArray data = mSocket->readAll();
    QString input(data);
    qDebug()<< input ;
    // HERE DATA NEEDS TO BE SENT TO A CALCULATOR INSTANCE
    setDisplay(input) ;

}

void Reciever::newConnection()
{
    if(mServer->hasPendingConnections())
        mSocket = mServer->nextPendingConnection() ;
    connect(mSocket , &QTcpSocket::readyRead , this , &Reciever::readData) ;
}

QString Reciever::display() const
{
    return mDisplay;
}

void Reciever::setDisplay(QString newDisplay)
{
    if (display() == newDisplay)
        return;
    mDisplay = newDisplay;
    emit displayChanged();
}
