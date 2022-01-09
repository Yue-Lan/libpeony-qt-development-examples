#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <peony-qt/mount-operation.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_buttonBox_accepted()
{
    auto mountOperation = new Peony::MountOperation(ui->lineEdit->text(), this);
    mountOperation->start();

    connect(mountOperation, &Peony::MountOperation::cancelled, this, [=]{
        qInfo()<<"mount operation cancelled";
    });
    connect(mountOperation, &Peony::MountOperation::finished, this, [=]{
        qInfo()<<"mount operation finished";
    });
}

void MainWindow::on_buttonBox_rejected()
{
    this->close();
}
