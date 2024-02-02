#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QThread>
#include <QTcpSocket>
#include <QDebug>

const int SPEED_MULTIPLIER = 14;

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
    void sendDriveData(uint8_t FR, uint8_t RR, uint8_t FL, uint8_t RL);

private:
    QTcpSocket *clientSocket;

};

#endif // CLIENT_H
