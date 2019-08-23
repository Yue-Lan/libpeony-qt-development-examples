#include "mainwindow.h"
#include <QApplication>
#include <PeonyFileInfo>
#include <PeonyFileInfoJob>
#include <PeonyFileEnumerator>
#include "file-info-manager.h"

#include <QDebug>
#include <QTextEdit>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QTextEdit *t = new QTextEdit(&w);
    w.setCentralWidget(t);

    Peony::FileEnumerator *e = new Peony::FileEnumerator;
    e->setEnumerateDirectory("computer:///");
    e->connect(e, &Peony::FileEnumerator::enumerateFinished, [=](){
        auto infos = e->getChildren();
        /// there is a memory leak, you should careful use lambda with smart pointer.
        /// this is a small bug of libpeony-qt memory management.
        for (auto info : infos) {
            Peony::FileInfoJob *job = new Peony::FileInfoJob(info);
            job->setAutoDelete();
            /// do not use smart pointer in this lambda, otherwise the info will not be
            /// released correctly. use info.get() get the internal pointer instead.
            Peony::FileInfo *interanl_data = info.get();
            job->connect(job, &Peony::FileInfoJob::queryAsyncFinished, [=](){
                t->append(interanl_data->displayName()+": "+interanl_data->iconName()+": "+interanl_data->fileType());
            });
            job->queryAsync();
        }
        delete e;
    });
    e->enumerateAsync();

    w.show();

    return a.exec();
}
