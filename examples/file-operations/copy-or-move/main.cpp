#include "mainwindow.h"

#include <QApplication>

/*!
 * \title File Operation
 * Peony provides a complex file operation frameworks, including
 * copy, move, rename, trash, delete, link untrash. The frameworks
 * also designed to enable undo/redo, and error handling.
 *
 * This example doesn't show the high-level usage of file operation.
 * The undo/redo and error handling is provided by FileOperationManager.
 * Use FileOperationManager to start/manage operation is recommend,
 * and you can also implement your own manager through the interface
 * Peony provied.
 *
 * \see FileOperationManager, FileOperationErrorHandler, FileOperationWizzard,
 * FileOperationErrorDialog
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
