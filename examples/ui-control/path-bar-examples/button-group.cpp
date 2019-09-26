#include "button-group.h"
#include <PeonyPathBarModel>
#include <file-utils.h>
#include <QUrl>
#include <QMenu>

#include <QMouseEvent>

ButtonGroup::ButtonGroup(QWidget *parent) : QToolBar(parent)
{
    setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    setIconSize(QSize(16, 16));
    qDebug()<<sizePolicy();
    connect(this, &ButtonGroup::groupChangedRequest, this, &ButtonGroup::setRootUri);
}

void ButtonGroup::setRootUri(const QString &uri)
{
    m_current_uri = uri;

    for (auto action : actions()) {
        removeAction(action);
    }

    QStringList uris;
    uris<<uri;
    QString tmp = Peony::FileUtils::getParentUri(uri);
    while (!tmp.isEmpty()) {
        uris.prepend(tmp);
        tmp = Peony::FileUtils::getParentUri(tmp);
    }

    for (auto uri : uris) {
        //addButton(uri, uri != uris.last());
        addButton(uri);
    }
}

void ButtonGroup::addButton(const QString &uri, bool setMenu)
{
    QAction *action = new QAction(this);
    QUrl url = uri;
    QIcon icon = QIcon::fromTheme(Peony::FileUtils::getFileIconName(uri), QIcon::fromTheme("folder"));

    action->setIcon(icon);
    action->setText(url.fileName());
    connect(action, &QAction::triggered, [=](){
        this->setRootUri(uri);
    });

    if (setMenu) {
        Peony::PathBarModel m;
        m.setRootUri(uri);
        m.sort(0);

        auto suburis = m.stringList();
        if (!suburis.isEmpty()) {
            QMenu *menu = new QMenu(this);
            QList<QAction *> actions;
            for (auto uri : suburis) {
                QUrl url = uri;
                QString tmp = uri;
                QAction *action = new QAction(url.fileName(), this);
                actions<<action;
                connect(action, &QAction::triggered, [=](){
                    Q_EMIT groupChangedRequest(tmp);
                });
            }
            menu->addActions(actions);

            action->setMenu(menu);
        }
    }

    addAction(action);
}

void ButtonGroup::mousePressEvent(QMouseEvent *e)
{
    //if you click a toobar button, this event will not be triggered/
    //you can use this event trigger the 'clicked blank' event.
    e->ignore();
    qDebug()<<"mouse presse event";
    QToolBar::mousePressEvent(e);
}
