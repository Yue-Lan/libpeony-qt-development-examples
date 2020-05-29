#include "mainwindow.h"

#include <QApplication>

/*!
 * \title File Item Model
 * \brief
 * FileItemModel is a core part of peony's model/view frameworks.
 * It created a bridge from FileInfo to graphics UI.
 *
 * This example show the basic usage of file item model.
 * If you do not understand how it works, you might reference Qt's
 * Model/View Programing/Tutorial.
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
