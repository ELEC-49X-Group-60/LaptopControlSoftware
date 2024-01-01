#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    bool startConnection();

signals:

public slots:
    void newConnection();
    void closeConnection();
    void sendDriveData(int data);

private:
    QTcpServer *server;
    QTcpSocket *serverSocket;

};

#endif // SERVER_H
