#include "mainwindow.h"
#include <QApplication>
#include <QTextEdit>
#include <PeonyFileEnumerator>
#include <PeonyFileInfo>
#include <QDebug>

/*!
 * \brief
 * You will see how doing a async enumeration with Peony::FileEnumerator.
 * For UI thread we should not block the ui in a long time, the async method
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
