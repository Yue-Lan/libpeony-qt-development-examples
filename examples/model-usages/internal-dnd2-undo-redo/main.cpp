#include "mainwindow.h"
#include <QApplication>
#include <PeonyFileItemProxyModel>
#include <PeonyFileItemModel>
#include <PeonyPathBarModel>
#include <PeonyPathCompleter>
#include <PeonyFileItem>

#include <QListView>
#include <QLineEdit>
#include <QToolBar>
#include <QLabel>

#include <QStandardPaths>

#include <QAction>
#include <PeonyFileOperationManager>

#include <QTextEdit>
#include <QPainter>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTextEdit gg;
    gg.setStyleSheet("padding: 10;"
                     "border-color: red");
    QPainter p;
    gg.show();

    MainWindow w;
    QToolBar t;
    QLineEdit e;
    Peony::PathBarModel pm;
    Peony::PathCompleter c;
    c.setModel(&pm);
    e.setCompleter(&c);

    w.addToolBar(Qt::TopToolBarArea, &t);
    t.addWidget(&e);

    QLabel l;
    l.setWordWrap(true);
    l.setMaximumWidth(480);
    l.setText("This example is similar with the example internal-dnd. "
              "The difference from this example to previous one is that "
              "the dnd2 add undo/redo support."
              "\n\n"
              "You can use ctrl-Z and ctrl-Shfit-Z for undo/redo the operation "
              "which cause by example folder views dnd."
              "\n\n"
              "Note that if a operation went error or was cancelled, "
              "the history of undo or redo will be cleared. "
              "This is because the operation safety would be destroyed "
              "if we record an error or cancelled operation into "
              "undo/redo stack.");

    w.setCentralWidget(&l);

    e.setText("file://" + QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
    e.connect(&e, &QLineEdit::returnPressed, [&](){
        QListView *v = new QListView;

        /// set view attribute
        v->setAttribute(Qt::WA_DeleteOnClose);
        v->setWordWrap(true);
        v->setViewMode(QListView::IconMode);
        v->setGridSize(QSize(96, 96));
        v->setResizeMode(QListView::Adjust);

        /// set select action
        v->setSelectionMode(QAbstractItemView::ExtendedSelection);

        /// set dnd actions
        v->setDragDropMode(QAbstractItemView::DragDrop);
        v->setDefaultDropAction(Qt::MoveAction);

        Peony::FileItemModel *model = new Peony::FileItemModel(v);
        model->setRootUri(e.text());
        Peony::FileItemProxyFilterSortModel *proxy_model = new Peony::FileItemProxyFilterSortModel(model);
        proxy_model->setSourceModel(model);

        /// resort when load directory finished
        model->connect(model, &Peony::FileItemModel::findChildrenFinished, [=](){
            proxy_model->sort(0);
        });

        /// re-sort when file(s) moved in/out.
        model->connect(model, &Peony::FileItemModel::updated, [=](){
            proxy_model->sort(0);
        });

        /// double clicked for location change.
        v->setEditTriggers(QListView::EditKeyPressed);
        v->connect(v, &QListView::doubleClicked, [=](const QModelIndex &index){
            auto item = proxy_model->itemFromIndex(index);
            if (item->hasChildren()) {
                model->setRootUri(item->uri());
            }
        });

        /// add undo/redo action short cut to each view
        /// undo stack and redo stack were shared by all views.
        QAction *undoAction = new QAction(v);
        undoAction->setShortcut(QKeySequence::Undo);
        QAction *redoAction = new QAction(v);
        redoAction->setShortcut(QKeySequence::Redo);
        Peony::FileOperationManager *global_op_manager = Peony::FileOperationManager::getInstance();
        v->connect(undoAction, &QAction::triggered,
                   global_op_manager, &Peony::FileOperationManager::undo);
        v->connect(redoAction, &QAction::triggered,
                   global_op_manager, &Peony::FileOperationManager::redo);
        v->addAction(undoAction);
        v->addAction(redoAction);

        v->setModel(proxy_model);
        v->show();
    });

    w.show();

    return a.exec();
}
