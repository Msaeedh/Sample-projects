#ifndef RECIEVER_H
#define RECIEVER_H

#include "calculator.h"
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class Reciever: public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString display READ display WRITE setDisplay NOTIFY displayChanged FINAL)

public:
    Reciever(QObject *Parent = nullptr);
    QString display() const;
    void setDisplay(QString newDisplay);

private:
    QTcpSocket *mSocket ;
    QTcpServer *mServer ;
    Calculator *mCalc ;

    QString mDisplay;

signals:
    void displayChanged();

public slots:
    void readData() ;
    void newConnection();

};

#endif // RECIEVER_H
