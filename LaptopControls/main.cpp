#include "controlwindow.h"

#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ControlWindow w;
    w.showMaximized();

    return a.exec();
}
