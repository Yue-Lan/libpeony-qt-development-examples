#include "treeview.h"
#include <QMouseEvent>
#include <QDebug>

TreeView::TreeView(QWidget *parent) : QTreeView(parent)
{
    setSelectionMode(QTreeView::ExtendedSelection);
}

/*!
 * \brief TreeView::mousePressEvent
 * \param event
 * \details
 * This view override the mousePressEvent for defineing a
 * new kind of selection-clearing action, which is mostly
 * used in many DE's treeview, e.g the windows file-manager.
 *
 * The action details is, when a right button pressed,
 * and then if the clicked postion is "blank",
 * the selections of this view will be cleared.
 *
 * You can see i use the delegate's sizeHint() and view's
 * visualRect() method to implement this extension function.
 * The delegate here is Qt's QStyledItemDelegate by default. If you
 * want to custom your delegate, and you aslo want your treeview
 * support the right-click-clearing-selection function at blank, you
 * should be careful about overriding your delegate's sizeHint()
 * method.
 */
void TreeView::mousePressEvent(QMouseEvent *event)
{
    QTreeView::mousePressEvent(event);

    if (event->button() == Qt::RightButton) {
        QModelIndex index = indexAt(event->pos());
        auto options = viewOptions();
        auto delegate = itemDelegate(index);
        QSize sizeHint = delegate->sizeHint(options, index);
        QRect rect = visualRect(index);
        QRect judgeRect = QRect(rect.x(), rect.y(), sizeHint.width(), sizeHint.height());
        if (!judgeRect.contains(event->pos())) {
            clearSelection();
        }
    }
}
