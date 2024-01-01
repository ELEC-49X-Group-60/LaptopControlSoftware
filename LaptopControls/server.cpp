#include "Server.h"
#include <strings.h>

Server::Server(QObject *parent) : QObject(parent) {

}

bool Server::startConnection(){
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(!server->listen(QHostAddress::Any, 8080))
    {
        qDebug() << "Server failed to start";
        return false;
    }
    else
    {
        qDebug() << "Server started";
    }
    return true;
}

void Server::newConnection(){
    serverSocket = server->nextPendingConnection();

    qDebug() << "Client Connected";

    serverSocket->write("Hello client\r\n");
    serverSocket->flush();

    serverSocket->waitForBytesWritten(3000);
}

void Server::closeConnection(){
    serverSocket->write("exit\n");
    serverSocket->flush();

    serverSocket->close();
    qDebug() << "Server closed";
}

void Server::sendDriveData(int data){
    std::string msg = std::to_string(data) + "\n";
    serverSocket->write(msg.c_str());
    serverSocket->flush();
    serverSocket->waitForBytesWritten(3000);
}
