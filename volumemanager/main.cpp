#include <QCoreApplication>

#include <peony-qt/volume-manager.h>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto volumeManager = Peony::VolumeManager::getInstance();

    QObject::connect(volumeManager, &Peony::VolumeManager::driveConnected, [&](std::shared_ptr<Peony::Drive> drive){
        qInfo()<<drive.get()->name()<<"connected";
    });
    QObject::connect(volumeManager, &Peony::VolumeManager::driveDisconnected, [&](std::shared_ptr<Peony::Drive> drive){
        qInfo()<<drive.get()->name()<<"disconnected";
    });
    QObject::connect(volumeManager, &Peony::VolumeManager::volumeAdded, [&](std::shared_ptr<Peony::Volume> volume){
        qInfo()<<volume.get()->name()<<"volume added";
    });
    QObject::connect(volumeManager, &Peony::VolumeManager::volumeRemoved, [&](std::shared_ptr<Peony::Volume> volume){
        qInfo()<<volume.get()->name()<<"volume removed";
    });
    QObject::connect(volumeManager, &Peony::VolumeManager::mountAdded, [&](std::shared_ptr<Peony::Mount> mount){
        qInfo()<<mount.get()->name()<<"mount added";
    });
    QObject::connect(volumeManager, &Peony::VolumeManager::mountRemoved, [&](std::shared_ptr<Peony::Mount> mount){
        qInfo()<<mount.get()->name()<<"mount removed";
    });

    return a.exec();
}
