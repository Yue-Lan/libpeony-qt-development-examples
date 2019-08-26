#include "mainwindow.h"
#include <QApplication>
#include <PeonyFileItemProxyModel>
#include <PeonyFileItemModel>
#include <PeonyFileItem>

#include "treeview.h"
#include <QHeaderView>

/// FileItemModel do not has sort and fiter function itself
/// the sorting and filtering function is provided by Qt's
/// sort filter proxy model framework.
/// for getting a sorted and filtered model, use PeonyFileItemProxyModel
/// instead.
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Peony::FileItemModel model;
    model.setRootUri("computer:///");

    Peony::FileItemProxyFilterSortModel proxy_model;
    proxy_model.setSourceModel(&model);

    TreeView v;

    /// we have to enable sort for activate the proxy sort function.
    v.setSortingEnabled(true);
    v.header()->setSectionResizeMode(QHeaderView::ResizeToContents);
    v.setModel(&proxy_model);

    v.connect(&v, &TreeView::expanded, [&](const QModelIndex &index){
        auto item = proxy_model.itemFromIndex(index);
        item->findChildrenAsync();
    });
    v.connect(&v, &TreeView::collapsed, [&](const QModelIndex &index){
        auto item = proxy_model.itemFromIndex(index);
        item->clearChildren();
    });

    w.setCentralWidget(&v);
    w.show();

    return a.exec();
}
