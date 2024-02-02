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
}

ControlWindow::~ControlWindow()
{
    delete ui;
}

ControlWindow::sgn(int val){
    return (0 < val) - (val < 0);
}

void ControlWindow::adjustMotors(){
    motorFR = 128 + (sgn(y) * speed * SPEED_MULTIPLIER);
    motorRR = 128 + (sgn(x) * speed * SPEED_MULTIPLIER);
    motorFL = 128 - (sgn(x) * speed * SPEED_MULTIPLIER);
    motorRL = 128 - (sgn(y) * speed * SPEED_MULTIPLIER);
}

void ControlWindow::keyPressEvent(QKeyEvent *ev)
{
    if (!ev->isAutoRepeat()){
        if (ev->text() == "w" || ev->text() == "W"){
            ui->w_key->setFrameShadow(QFrame::Raised);
            x += 1;
            y += 1;
        }
        else if (ev->text() == "a" || ev->text() == "A"){
            ui->a_key->setFrameShadow(QFrame::Raised);
            x -= 1;
            y += 1;
        }
        else if (ev->text() == "s" || ev->text() == "S"){
            ui->s_key->setFrameShadow(QFrame::Raised);
            x -= 1;
            y -= 1;
        }
        else if (ev->text() == "d" || ev->text() == "D"){
            ui->d_key->setFrameShadow(QFrame::Raised);
            x += 1;
            y -= 1;
        }
        else if (ev->text() == "1"){
            ui->one_key->setStyleSheet("color:rgb(252 ,111, 3)");
            ui->two_key->setStyleSheet("color:rgb(23, 201, 255)");
            ui->three_key->setStyleSheet("color:rgb(23, 201, 255)");
            ui->one_key->setFrameShadow(QFrame::Raised);
            speed = 1;
        }
        else if (ev->text() == "2"){
            ui->two_key->setStyleSheet("color:rgb(252 ,111, 3)");
            ui->one_key->setStyleSheet("color:rgb(23, 201, 255)");
            ui->three_key->setStyleSheet("color:rgb(23, 201, 255)");
            ui->two_key->setFrameShadow(QFrame::Raised);
            speed = 2;
        }
        else if (ev->text() == "3"){
            ui->three_key->setStyleSheet("color:rgb(252 ,111, 3)");
            ui->one_key->setStyleSheet("color:rgb(23, 201, 255)");
            ui->two_key->setStyleSheet("color:rgb(23, 201, 255)");
            ui->three_key->setFrameShadow(QFrame::Raised);
            speed = 3;
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
            x -= 1;
            y -= 1;
        }
        else if (ev->text() == "a" || ev->text() == "A"){
            ui->a_key->setFrameShadow(QFrame::Sunken);
            x += 1;
            y -= 1;
        }
        else if (ev->text() == "s" || ev->text() == "S"){
            ui->s_key->setFrameShadow(QFrame::Sunken);
            x -= 1;
            y -= 1;
        }
        else if (ev->text() == "d" || ev->text() == "D"){
            ui->d_key->setFrameShadow(QFrame::Sunken);
            x -= 1;
            y += 1;
        }
        else if (ev->text() == "1"){
            ui->one_key->setFrameShadow(QFrame::Sunken);
        }
        else if (ev->text() == "2"){
            ui->two_key->setFrameShadow(QFrame::Sunken);
        }
        else if (ev->text() == "2"){
            ui->three_key->setFrameShadow(QFrame::Sunken);
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

