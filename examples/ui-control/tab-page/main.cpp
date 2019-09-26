#include "mainwindow.h"
#include <QApplication>

/// you should install the latest package by make install from git.
/// or comment this project to avoid compilation error.
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
