#include "controlwindow.h"
#include "ui_controlwindow.h"
#include "Server.h"

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

void ControlWindow::keyPressEvent(QKeyEvent *ev)
{
    if (!ev->isAutoRepeat()){
        if (ev->text() == "w" || ev->text() == "W"){
            ui->w_key->setFrameShadow(QFrame::Raised);
            driveData+=1;
        }
        else if (ev->text() == "a" || ev->text() == "A"){
            ui->a_key->setFrameShadow(QFrame::Raised);
            driveData+=2;
        }
        else if (ev->text() == "s" || ev->text() == "S"){
            ui->s_key->setFrameShadow(QFrame::Raised);
            driveData+=4;
        }
        else if (ev->text() == "d" || ev->text() == "D"){
            ui->d_key->setFrameShadow(QFrame::Raised);
            driveData+=8;
        }
        else{
            return;
        }
        if (serverOn)
            server.sendDriveData(driveData);
    }
}

void ControlWindow::keyReleaseEvent(QKeyEvent *ev)
{
    if (!ev->isAutoRepeat()){
        if (ev->text() == "w" || ev->text() == "W"){
            ui->w_key->setFrameShadow(QFrame::Sunken);
            driveData-=1;
        }
        else if (ev->text() == "a" || ev->text() == "A"){
            ui->a_key->setFrameShadow(QFrame::Sunken);
            driveData-=2;
        }
        else if (ev->text() == "s" || ev->text() == "S"){
            ui->s_key->setFrameShadow(QFrame::Sunken);
            driveData-=4;
        }
        else if (ev->text() == "d" || ev->text() == "D"){
            ui->d_key->setFrameShadow(QFrame::Sunken);
            driveData-=8;
        }
        else{
            return;
        }
        if (serverOn)
            server.sendDriveData(driveData);
    }
}

void ControlWindow::on_start_server_button_clicked()
{
    if (!serverOn)
        serverOn = server.startConnection();
}

void ControlWindow::on_close_server_button_clicked()
{
    server.closeConnection();
    serverOn = false;
}

