#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>
#include "Client.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ControlWindow;
}
QT_END_NAMESPACE

class ControlWindow : public QMainWindow
{
    Q_OBJECT

public:
     ControlWindow(QWidget *parent = nullptr);
    ~ControlWindow();

protected:
    Client client;
    bool serverOn = false;
    int motorFL = 0;    // For the motors, speed is on a scale from 0 to 255
    int motorRL = 0;    // 0-127 is counter-clockwise rotation. 128-255 is clockwise rotation (double check this)
    int motorFR = 0;
    int motorRR = 0;
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void on_start_client_button_clicked();
    void on_close_client_button_clicked();

private:
    Ui::ControlWindow *ui;
};
#endif // CONTROLWINDOW_H
