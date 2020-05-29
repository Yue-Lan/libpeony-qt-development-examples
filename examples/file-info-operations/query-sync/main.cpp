#include <QCoreApplication>

#include <PeonyFileInfo>
#include <PeonyFileInfoJob>

#include <QDebug>

/*!
 * \title FileInfo Querying
 * \brief
 * In Peony, A FileInfo instance represent a file item in file systems.
 * However the file info is not a dynamic instance and it always outdated.
 * To keep the static info's accurency, we have to update it frequently.
 *
 * The task updating the file info is taked over by FileInfoJob. And that
 * means when we construct a file info or a file info is outdated, we both
 * have to start a job to update the info's data. This is a common desgin
 * through most of file manager applications.
 */

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto info = Peony::FileInfo::fromUri("computer:///", false);
    Peony::FileInfoJob job(info);
    job.querySync();
    qDebug()<<info->displayName();

    return a.exec();
}
