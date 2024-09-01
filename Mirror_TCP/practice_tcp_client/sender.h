#ifndef SENDER_H
#define SENDER_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>

class Sender : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString number READ number WRITE setNumber NOTIFY numberChanged )
public:
    explicit Sender(QObject *parent = nullptr);

    void send() ;

    QString number() const;
    void setNumber(QString newNumber);

private:
    QTcpSocket *mSocket ;
    // QTimer timer ;

    QString mNumber;

private slots:
    void makeConnection() ;

signals:
    void numberChanged();
    void sendButtonClicked() ;
    void connectTCP() ;

};

#endif // SENDER_H
