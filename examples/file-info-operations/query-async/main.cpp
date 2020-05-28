#include <QCoreApplication>

#include <PeonyFileInfo>
#include <PeonyFileInfoJob>

#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto info = Peony::FileInfo::fromUri("computer:///");
    Peony::FileInfoJob job(info);
    QObject::connect(&job, &Peony::FileInfoJob::infoUpdated, [&](){
        qDebug()<<"display name:"<<info->displayName();
    });
    job.queryAsync();
    qDebug()<<"display name:"<<info->displayName();

    return a.exec();
}
