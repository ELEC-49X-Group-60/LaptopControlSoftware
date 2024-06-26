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

    playerSession = new QMediaPlayer(this);
}

ControlWindow::~ControlWindow()
{
    delete ui;
}

ControlWindow::sgn(int val){
    return (0 < val) - (val < 0);
}

void ControlWindow::adjustMotors(){
    motorRL = 128 - (sgn(y) * gear_speed * SPEED_MULTIPLIER) + (spin * gear_speed * SPEED_MULTIPLIER);
    motorFL = 128 - (sgn(x) * gear_speed * SPEED_MULTIPLIER) + (spin * gear_speed * SPEED_MULTIPLIER);
    motorRR = 128 + (sgn(x) * gear_speed * SPEED_MULTIPLIER) + (spin * gear_speed * SPEED_MULTIPLIER);
    motorFR = 128 + (sgn(y) * gear_speed * SPEED_MULTIPLIER) + (spin * gear_speed * SPEED_MULTIPLIER);

    ui->motor_label->setText(QString("FR: %1\nRR: %2\nFL: %3\nRL: %4").arg(motorFR).arg(motorRR).arg(motorFL).arg(motorRL));
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
        else if (ev->text() == "q" || ev->text() == "Q"){
            ui->q_key->setFrameShadow(QFrame::Raised);
            spin += 1;
        }
        else if (ev->text() == "e" || ev->text() == "E"){
            ui->e_key->setFrameShadow(QFrame::Raised);
            spin -= 1;
        }
        else if (ev->text() == "1"){
            ui->one_key->setStyleSheet("color:rgb(252 ,111, 3)");
            ui->two_key->setStyleSheet("color:rgb(23, 201, 255)");
            ui->three_key->setStyleSheet("color:rgb(23, 201, 255)");
            ui->one_key->setFrameShadow(QFrame::Raised);
            gear_speed = 1;
        }
        else if (ev->text() == "2"){
            ui->two_key->setStyleSheet("color:rgb(252 ,111, 3)");
            ui->one_key->setStyleSheet("color:rgb(23, 201, 255)");
            ui->three_key->setStyleSheet("color:rgb(23, 201, 255)");
            ui->two_key->setFrameShadow(QFrame::Raised);
            gear_speed = 2;
        }
        else if (ev->text() == "3"){
            ui->three_key->setStyleSheet("color:rgb(252 ,111, 3)");
            ui->one_key->setStyleSheet("color:rgb(23, 201, 255)");
            ui->two_key->setStyleSheet("color:rgb(23, 201, 255)");
            ui->three_key->setFrameShadow(QFrame::Raised);
            gear_speed = 3;
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
            x += 1;
            y += 1;
        }
        else if (ev->text() == "d" || ev->text() == "D"){
            ui->d_key->setFrameShadow(QFrame::Sunken);
            x -= 1;
            y += 1;
        }
        else if (ev->text() == "q" || ev->text() == "Q"){
            ui->q_key->setFrameShadow(QFrame::Sunken);
            spin -= 1;
        }
        else if (ev->text() == "e" || ev->text() == "E"){
            ui->e_key->setFrameShadow(QFrame::Sunken);
            spin += 1;
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
        serverOn = client.startConnection(ui->textEditAddress->toPlainText(), 8080);

}

void ControlWindow::on_close_client_button_clicked()
{
    client.closeConnection();
    serverOn = false;
}

void ControlWindow::on_start_camera_button_clicked()
{
    playerSession->setSource(QUrl("rtsp://" + ui->textEditAddress->toPlainText() + ":8554/mystream"));
    playerSession->play();
    playerSession->setVideoOutput(ui->robot_cam_widget);
}


void ControlWindow::on_stop_camera_button_clicked()
{
    playerSession->setVideoOutput(nullptr);
}

