#include "mainwindow.h"
#include <QApplication>
#include <QTextEdit>
#include <PeonyFileEnumerator>
#include <PeonyFileInfo>
#include <QDebug>

/*!
 * \title Async Enumeration
 * \brief
 * Peony provides a file enumeration class FileEnumerator.
 * There are 2 basic usage for enumerate a directory, sync mode
 * and async mode. This is the async mode version's example.
 *
 * You will see how doing a async enumeration with Peony::FileEnumerator.
 * The async enumeration do not block current thread, and should use signal
 * to handle the result when enumeration job finished.
 *
 * For UI thread we should not block the ui in a long time, so the async method
 * is recommended.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QTextEdit t;
    w.setCentralWidget(&t);

    Peony::FileEnumerator *e = new Peony::FileEnumerator;
    e->setEnumerateDirectory("computer:///");
    e->connect(e, &Peony::FileEnumerator::enumerateFinished, [&](){
        auto infos = e->getChildren();
        for (auto info: infos) {
            qDebug()<<info->uri();
            t.append(info->uri());
        }
        qDebug()<<"aysnc enumeration finished after main window show";
    });
    e->enumerateAsync();

    w.show();
    qDebug()<<"window show at first";

    return a.exec();
}
