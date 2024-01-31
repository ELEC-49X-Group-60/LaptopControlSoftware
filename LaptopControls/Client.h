#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>

class Client : public QThread
{
    Q_OBJECT
public:
    explicit Client();
    bool startConnection(QString hostname = "", int port = 8080);

signals:

public slots:
    void newConnection();
    void closeConnection();
    void sendDriveData(int FR, int RR, int FL, int RL);

private:
    QTcpSocket *clientSocket;

};

#endif // CLIENT_H
