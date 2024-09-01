#ifndef Communicator_H
#define Communicator_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDateTime>

class Communicator : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged FINAL)
    Q_PROPERTY(QString status READ status WRITE setStatus NOTIFY statusChanged )
    Q_PROPERTY(QString history READ history WRITE setHistory NOTIFY historyChanged )
    Q_PROPERTY(QString message READ message WRITE setMessage NOTIFY messageChanged )
    Q_PROPERTY(QString port READ port WRITE setPort NOTIFY portChanged )
    Q_PROPERTY(QString ip READ ip WRITE setIp NOTIFY ipChanged )
public:
    explicit Communicator(QObject *parent = nullptr);

    QString status() const;
    void setStatus(const QString newStatus);

    QString history() const;
    void setHistory(const QString newHistory);
    void addHistory(QString newHistory) ;

    QString message() const;
    void setMessage(const QString newMessage);

    QString port() const;
    void setPort(const QString &newPort);

    QString ip() const;
    void setIp(const QString &newIp);

    QString name() const;
    void setName(const QString &newName);

    // to write the mMessage throgh the socket
    Q_INVOKABLE void send() ;

    // to start the the server with 5 seconds timeout
    Q_INVOKABLE void waitForConnection() ;

    // to conncet as client
    Q_INVOKABLE void connectTcp() ;

    // to clear history both ways
    Q_INVOKABLE void clearHistory() ;

    // to disconnect the socket
    Q_INVOKABLE void disconnect() ;

private:
    QString mStatus;
    QString mHistory;
    QString mMessage;

    QString mIp ;
    QString mPort;

    QTcpServer *mServer ;
    QTcpSocket *mSocket ;

    void deleteServer();
    bool checkConnection() ;
    QString mName;

signals:
    //Q_PROPERTY SIGNALS
    void statusChanged();
    void historyChanged();
    void messageChanged();
    void portChanged();
    void ipChanged();

    void nameChanged();

private slots:
    void Read() ;
    // void Connected() ;

};

#endif // Communicator_H
