#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

#include <peony-qt/file-copy-operation.h>
#include <peony-qt/file-move-operation.h>

QList<QUrl> srcs;
QUrl destDir;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setWordWrap(true);
    ui->label_2->setWordWrap(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    srcs = QFileDialog::getOpenFileUrls();
    QString str;
    for (auto src : srcs) {
        str.append(src.url());
        str.append('\n');
    }
    ui->label->setText(str);
}

void MainWindow::on_pushButton_2_clicked()
{
    destDir = QFileDialog::getExistingDirectoryUrl();
    ui->label_2->setText(destDir.url());
}

void MainWindow::on_pushButton_3_clicked()
{
    QStringList sourceUris;
    for (auto src : srcs) {
        sourceUris<<src.url();
    }
    bool isCopy = ui->comboBox->currentIndex() == 0;
    if (isCopy) {
        Peony::FileCopyOperation op(sourceUris, destDir.url());
        op.run();
    } else {
        Peony::FileMoveOperation op(sourceUris, destDir.url());
        op.run();
    }
}
