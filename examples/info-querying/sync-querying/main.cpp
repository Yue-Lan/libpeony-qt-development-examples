#include "mainwindow.h"
#include <QApplication>
#include <PeonyFileInfo>
#include "file-info-manager.h"
#include <PeonyFileInfoJob>

#include <QTextEdit>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /// usually we should use the provided construction interface of FileInfo,
    /// FileInfo::fromXXX() return a std smart pointer from global FileInfoManager instance
    /// If you want to use this method getting a file info in your own code,
    /// you should aslo manually release the ref count in global manager when you
    /// do not use it again.
    std::shared_ptr<Peony::FileInfo> info = Peony::FileInfo::fromUri("computer:///");

    qDebug()<<"we print the files display name without any query:"<<info->displayName();

    Peony::FileInfoJob *job = new Peony::FileInfoJob(info);
    job->setAutoDelete();
    job->querySync();

    qDebug()<<"now we print display name again:"<<info->displayName();

    MainWindow w;
    QTextEdit t;
    w.setCentralWidget(&t);

    t.append(info->displayName());
    t.append(info->iconName());
    t.append(info->fileSize());
    t.append(info->fileType());

    /// Remove the ref count in info manager if it do not use again.
    /// If you use you own code with FileInfo::fromXXX(),
    /// you should do it manually.
    /// If you use the peony's api like FileEnumerator, I have do it and
    /// just not care that.
    /// who hold the ref? 1. file info manager, 2. info job, 3. this code stack.
    if (info.use_count() <= 3) {
        Peony::FileInfoManager::getInstance()->remove(info->uri());
    }

    w.show();

    return a.exec();
}
