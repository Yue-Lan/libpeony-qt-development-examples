#include <QCoreApplication>

#include <peony-qt/file-info.h>
#include <peony-qt/file-info-job.h>
#include <peony-qt/file-enumerator.h>
#include <peony-qt/file-watcher.h>

#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    printf("input uri:\n");
    char uri[255];
    scanf("%s", uri);

    qInfo()<<"++++++++++query file info++++++++++";
    auto info = Peony::FileInfo::fromUri(uri);
    Peony::FileInfoJob job(info);
    job.querySync();
    qInfo()<<"displayName"<<info.get()->displayName();
    qInfo()<<"contentType"<<info.get()->type();


    qInfo()<<"++++++++++enumerate file children++++++++++";
    Peony::FileEnumerator e;
    e.setEnumerateDirectory(uri);
    e.enumerateSync();

    qInfo()<<"uris of"<<uri<<"{"<<e.getChildrenUris()<<"}";

    qInfo()<<"++++++++++watch file change++++++++++";

    Peony::FileWatcher watcher(uri);
    watcher.setMonitorChildrenChange(true);
    QObject::connect(&watcher, &Peony::FileWatcher::fileCreated, [&](const QString &fileUri){
        qInfo()<<"file created"<<fileUri;
    });
    QObject::connect(&watcher, &Peony::FileWatcher::fileDeleted, [&](const QString &fileUri){
        qInfo()<<"file deleted"<<fileUri;
    });
    QObject::connect(&watcher, &Peony::FileWatcher::fileChanged, [&](const QString &fileUri){
        qInfo()<<"file changed"<<fileUri;
    });
    QObject::connect(&watcher, &Peony::FileWatcher::directoryDeleted, [&](const QString &fileUri){
        qInfo()<<"directory deleted"<<fileUri;
    });
    QObject::connect(&watcher, &Peony::FileWatcher::directoryUnmounted, [&](const QString &fileUri){
        qInfo()<<"directory unmounted"<<fileUri;
    });

    return a.exec();
}
