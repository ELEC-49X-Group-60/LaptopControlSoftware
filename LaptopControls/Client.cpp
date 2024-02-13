#include "Client.h"
#include <strings.h>

Client::Client() {
    clientSocket = new QTcpSocket(this);

    connect(clientSocket, SIGNAL(newConnection()), this, SLOT(newConnection()));
}

bool Client::startConnection(QString hostname, int port){

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

void Client::sendDriveData(uint8_t FR, uint8_t RR, uint8_t FL, uint8_t RL){
    //std::string msg = std::to_string(FR) + " " + std::to_string(RR) + " " + std::to_string(FL) + " " + std::to_string(RL) + " " + "\n";

    char msg[] = {FR, RR, FL, RL};

    clientSocket->write(msg);
    clientSocket->flush();
    clientSocket->waitForBytesWritten(3000);
}
