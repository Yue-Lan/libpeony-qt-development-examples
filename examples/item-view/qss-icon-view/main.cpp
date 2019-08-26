#include "mainwindow.h"
#include <QApplication>
#include <QListView>
#include <QFile>

#include <QLabel>
#include <QToolBar>
#include <QLineEdit>
#include <QStandardPaths>

#include <PeonyFileItemModel>
#include <PeonyFileItemProxyModel>
#include <PeonyPathBarModel>
#include <PeonyPathCompleter>
#include <PeonyFileItem>
#include <PeonyFileOperationManager>

/*!
 * \brief
 * This example is the variant example of interal-dnd2-undo-redo.
 * It show a different style sheet icon view provided by custom css
 * file.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    /*!
     * \note
     * read the file from qrc.
     */
    QFile qssFile(":/view.css");
    qssFile.open(QFile::ReadOnly);
    QString styleSheet = QString::fromLatin1(qssFile.readAll());
    a.setStyleSheet(styleSheet);

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
    l.setText("You will see the icon view will change a lot compare with "
              "internal-dnd(1 and 2)."
              "\n\n"
              "The view's background is transparent, and there is a item hover "
              "background drawn now.");

    w.setCentralWidget(&l);

    e.setText("file://" + QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
    e.connect(&e, &QLineEdit::returnPressed, [&](){
        QListView *v = new QListView;

        /*!
          \note
          we have to set the Qt::WA_TranslucentBackground attribute if we
          set the view background-color as transparent.
          otherwise the backgournd will be filled blacked.
          */
        v->setAttribute(Qt::WA_TranslucentBackground);

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
