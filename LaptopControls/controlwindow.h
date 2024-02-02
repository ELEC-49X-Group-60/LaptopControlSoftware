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

     int sgn(int val);

protected:
    Client client;
    bool serverOn = false;
    int x = 0;
    int y = 0;
    int speed = 1;
    int motorFR = 128;    // For the motors, speed is on a scale from 0 to 255
    int motorRR = 128;    // 0-127 is counter-clockwise rotation. 128-255 is clockwise rotation (double check this)
    int motorFL = 128;    // valid range for motors is 84 - 171
    int motorRL = 128;    // Right side is +, left side is - for going forward
    void adjustMotors();
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void on_start_client_button_clicked();
    void on_close_client_button_clicked();

private:
    Ui::ControlWindow *ui;
};
#endif // CONTROLWINDOW_H
