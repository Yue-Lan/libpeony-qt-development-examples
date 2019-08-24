#include "mainwindow.h"
#include <QApplication>
#include <PeonyFileInfoJob>
#include <PeonyFileInfo>

#include <QTextEdit>
#include <QDebug>

/// you should use a info-querying like this, especially in ui-thread.
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QTextEdit t;
    w.setCentralWidget(&t);

    Peony::FileInfoJob *job = new Peony::FileInfoJob("computer:///");
    job->setAutoDelete();
    job->connect(job, &Peony::FileInfoJob::queryAsyncFinished, [&](){
        auto info = job->getInfo();
        t.append(info->displayName());
        t.append(info->fileSize());
        t.append(info->fileType());
        t.append(info->iconName());

        qDebug()<<info->displayName()<<
                  info->fileSize()<<
                  info->fileType()<<
                  info->iconName();
    });
    job->queryAsync();

    w.show();

    return a.exec();
}
