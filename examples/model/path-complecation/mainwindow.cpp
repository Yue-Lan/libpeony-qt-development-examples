#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <PeonyPathCompleter>
#include <PeonyPathBarModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    auto model = new Peony::PathBarModel(this);
    auto completer = new Peony::PathCompleter(this);
    completer->setModel(model);
    ui->lineEdit->setCompleter(completer);
}

MainWindow::~MainWindow()
{
    delete ui;
}
