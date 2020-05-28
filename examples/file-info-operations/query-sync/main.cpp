#include <QCoreApplication>

#include <PeonyFileInfo>
#include <PeonyFileInfoJob>

#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto info = Peony::FileInfo::fromUri("computer:///", false);
    Peony::FileInfoJob job(info);
    job.querySync();
    qDebug()<<info->displayName();

    return a.exec();
}
