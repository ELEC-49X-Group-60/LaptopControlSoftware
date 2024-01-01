#ifndef CONTROLWINDOW_H
#define CONTROLWINDOW_H

#include <QMainWindow>
#include "Server.h"

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
    Server server;
    bool serverOn = false;
    int driveData = 0;  // Think in terms of bits: W - bit 0, A - bit 1, S - bit 2, D - bit 3
                    // If W and S are pressed, value is 0101 = 5
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private slots:
    void on_start_server_button_clicked();
    void on_close_server_button_clicked();

private:
    Ui::ControlWindow *ui;
};
#endif // CONTROLWINDOW_H
