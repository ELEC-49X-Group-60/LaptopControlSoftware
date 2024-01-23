#include "Client.h"
#include <strings.h>

Client::Client() {

}

bool Client::startConnection(QString hostname, int port){


    clientSocket = new QTcpSocket(this);
    connect(clientSocket, SIGNAL(newConnection()), this, SLOT(newConnection()));

    clientSocket->connectToHost(hostname, port);
    if(!clientSocket->waitForConnected()){
        qDebug() << "Client failed to start";
        return false;
    }
    else{
        qDebug() << "Client started";
    }
    return true;
}

void Client::newConnection(){


    qDebug() << "Client Connected";

    clientSocket->write("Hello server\r\n");
    clientSocket->flush();

    clientSocket->waitForBytesWritten(3000);
}

void Client::closeConnection(){
    clientSocket->write("exit\n");
    clientSocket->flush();

    clientSocket->close();
    qDebug() << "Client closed";
}

void Client::sendDriveData(int data){
    std::string msg = std::to_string(data) + "\n";
    clientSocket->write(msg.c_str());
    clientSocket->flush();
    clientSocket->waitForBytesWritten(3000);
}