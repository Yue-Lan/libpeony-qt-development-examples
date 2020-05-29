#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <PeonyFileItemModel>
#include <PeonyFileItemProxyModel>

#include <QFileDialog>

static Peony::FileItemModel *model = new Peony::FileItemModel;
static Peony::FileItemProxyFilterSortModel *proxyModel = new Peony::FileItemProxyFilterSortModel;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    proxyModel->setSourceModel(model);
    ui->listView->setModel(proxyModel);
    ui->listView->setViewMode(QListView::IconMode);
    ui->listView->setGridSize(QSize(100, 100));
    ui->listView->setSelectionMode(QListView::ExtendedSelection);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    auto url = QFileDialog::getExistingDirectoryUrl();
    if (!url.isEmpty()) {
        model->setRootUri(url.url());
        proxyModel->sort(0);
    }
}
