#include "sender.h"
#include "QDebug"

Sender::Sender(QObject *parent)
    : QObject{parent},
    mSocket(new QTcpSocket(this))
{
    // mSocket->connectToHost("127.0.0.1" , 9009 ) ;
    connect(this , &Sender::connectTCP ,this , &Sender::makeConnection) ;
}

void Sender::send() {
    qDebug()<< "the number is : " << number() ;
    qDebug()<< "Sender::send()" ;
    // if (mSocket->state() == QAbstractSocket::ConnectedState) {
    mSocket->write(number().toUtf8());
    // }
}

QString Sender::number() const
{
    return mNumber;
}

void Sender::setNumber(QString newNumber)
{
    if (number() == newNumber)
        return;
    mNumber = newNumber;
    emit numberChanged();
}

void Sender::makeConnection()
{
    qDebug()<< "Sender::makeConnection()" ;
    mSocket->connectToHost("127.0.0.1" , 9009 ) ;
    connect(this , &Sender::sendButtonClicked  , this , &Sender::send ) ;
    mSocket->write(QString("Connected").toUtf8()) ;

}


