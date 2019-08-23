#include "mainwindow.h"
#include <QApplication>

#include <PeonyFileInfo>

#include <PeonyFileItem>
#include <PeonyFileItemModel>
#include <QTreeView>
#include <QHeaderView>

#include <QLineEdit>
#include <QToolBar>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QLineEdit *line = new QLineEdit("computer:///", &w);
    QToolBar *toolbar = new QToolBar(&w);
    toolbar->addWidget(line);
    w.addToolBar(Qt::TopToolBarArea, toolbar);

    QTreeView *v = new QTreeView(&w);
    v->header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    w.setCentralWidget(v);

    Peony::FileItemModel *model = new Peony::FileItemModel(v);
    v->setModel(model);

    line->connect(line, &QLineEdit::returnPressed, [=](){
        /// it is not convenient, i will add setRootUri() method.
        /// note that never use a exsited FileItem instance in model
        /// as new root item.
        auto info = Peony::FileInfo::fromUri(line->text());
        auto item = new Peony::FileItem(info, nullptr, model);
        model->setRootItem(item);
    });

    v->connect(v, &QTreeView::expanded, [=](const QModelIndex &index){
        auto expandedItem = model->itemFromIndex(index);
        expandedItem->findChildrenAsync();
    });

    v->connect(v, &QTreeView::collapsed, [=](const QModelIndex &index){
        auto collapsedItem = model->itemFromIndex(index);
        collapsedItem->clearChildren();
    });

    w.show();

    return a.exec();
}
