#include "controlwindow.h"
#include "ui_controlwindow.h"
#include "Client.h"

#include <QKeyEvent>

ControlWindow::ControlWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ControlWindow)
{
    ui->setupUi(this);

    serverOn = false;
    driveData = 0;
}

ControlWindow::~ControlWindow()
{
    delete ui;
}

void ControlWindow::adjustMotors(){
    switch (driveData){
    case 0:
    case 5:
    case 10:
    case 15:
        motorFR = 128;
        motorRR = 128;
        motorFL = 128;
        motorRL = 128;
        break;
    case 1:
    case 11:
        motorFR = 148;
        motorRR = 148;
        motorFL = 108;
        motorRL = 108;
        break;
    case 2:
    case 7:
        motorFR = 148;
        motorRR = 108;
        motorFL = 148;
        motorRL = 108;
        break;
    case 3:
        motorFR = 148;
        motorRR = 128;
        motorFL = 128;
        motorRL = 108;
        break;
    case 4:
    case 14:
        motorFR = 108;
        motorRR = 108;
        motorFL = 148;
        motorRL = 148;
        break;
    case 6:
        motorFR = 128;
        motorRR = 108;
        motorFL = 148;
        motorRL = 128;
        break;
    case 8:
    case 13:
        motorFR = 108;
        motorRR = 148;
        motorFL = 108;
        motorRL = 148;
        break;
    case 9:
        motorFR = 128;
        motorRR = 148;
        motorFL = 148;
        motorRL = 128;
        break;
    case 12:
        motorFR = 108;
        motorRR = 128;
        motorFL = 128;
        motorRL = 148;
        break;
    default:
        motorFR = 128;
        motorRR = 128;
        motorFL = 128;
        motorRL = 128;
    }
}

void ControlWindow::keyPressEvent(QKeyEvent *ev)
{
    if (!ev->isAutoRepeat()){
        if (ev->text() == "w" || ev->text() == "W"){
            ui->w_key->setFrameShadow(QFrame::Raised);
            driveData += 1;
        }
        else if (ev->text() == "a" || ev->text() == "A"){
            ui->a_key->setFrameShadow(QFrame::Raised);
            driveData += 2;
        }
        else if (ev->text() == "s" || ev->text() == "S"){
            ui->s_key->setFrameShadow(QFrame::Raised);
            driveData += 4;
        }
        else if (ev->text() == "d" || ev->text() == "D"){
            ui->d_key->setFrameShadow(QFrame::Raised);
            driveData += 8;
        }
        else{
            return;
        }

        adjustMotors();

        if (serverOn)
            client.sendDriveData(motorFR, motorRR, motorFL, motorRL);
    }
}

void ControlWindow::keyReleaseEvent(QKeyEvent *ev)
{
    if (!ev->isAutoRepeat()){
        if (ev->text() == "w" || ev->text() == "W"){
            ui->w_key->setFrameShadow(QFrame::Sunken);
            driveData -= 1;
        }
        else if (ev->text() == "a" || ev->text() == "A"){
            ui->a_key->setFrameShadow(QFrame::Sunken);
            driveData -= 2;
        }
        else if (ev->text() == "s" || ev->text() == "S"){
            ui->s_key->setFrameShadow(QFrame::Sunken);
            driveData -= 4;
        }
        else if (ev->text() == "d" || ev->text() == "D"){
            ui->d_key->setFrameShadow(QFrame::Sunken);
            driveData -= 8;
        }
        else{
            return;
        }

        adjustMotors();

        if (serverOn)
            client.sendDriveData(motorFR, motorRR, motorFL, motorRL);
    }
}

void ControlWindow::on_start_client_button_clicked()
{
    if (!serverOn)
        serverOn = client.startConnection("192.168.1.101", 8080);
}

void ControlWindow::on_close_client_button_clicked()
{
    client.closeConnection();
    serverOn = false;
}

