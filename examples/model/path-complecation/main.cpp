#include "mainwindow.h"

#include <QApplication>

/*!
 * \title Path Completion
 * \brief
 * Path completion is based on Qt's completion frameworks.
 * It is a small part of model/view frameworks, displaying
 * the flexieble usage of model/view programing.
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
