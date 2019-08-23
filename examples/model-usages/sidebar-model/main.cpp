#include "mainwindow.h"
#include <QApplication>
#include <QTreeView>
#include <QHeaderView>
#include <PeonySideBarModel>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QTreeView v;
    v.header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    v.header()->setVisible(false);

    Peony::SideBarModel model;
    v.setModel(&model);
    v.setExpandsOnDoubleClick(false);

    w.setCentralWidget(&v);

    v.connect(&v, &QTreeView::expanded, [&](const QModelIndex &index){
        auto item = static_cast<Peony::SideBarAbstractItem*>(index.internalPointer());
        item->findChildrenAsync();
    });
    v.connect(&v, &QTreeView::collapsed, [&](const QModelIndex &index){
        auto item = static_cast<Peony::SideBarAbstractItem*>(index.internalPointer());
        item->clearChildren();
    });
    v.connect(&v, &QTreeView::clicked, [&](const QModelIndex &index){
        if (index.column() == 1) {
            auto item = static_cast<Peony::SideBarAbstractItem*>(index.internalPointer());
            if (item->isMounted()) {
                item->unmount();
            }
        }
    });

    v.expand(model.index(0, 0));
    v.expand(model.index(1, 0));
    v.expand(model.index(2, 0));

    w.show();

    return a.exec();
}
