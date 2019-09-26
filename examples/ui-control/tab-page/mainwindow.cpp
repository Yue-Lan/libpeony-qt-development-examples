#include "mainwindow.h"
#include "controls/directory-view/view/icon-view/icon-view.h"
#include "controls/directory-view/view/standard-view-proxy.h"
#include "path-bar-model.h"
#include "path-completer.h"
#include "file-item-model.h"
#include "file-utils.h"

#include <QStandardPaths>
#include <QLineEdit>
#include <QToolBar>
#include <QTabWidget>
#include <QDebug>

/// you should install the latest package by make install from git.
/// or comment this project to avoid compilation error.
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    auto pathBarModel = new Peony::PathBarModel(this);
    auto pathCompleter= new Peony::PathCompleter(this);
    pathCompleter->setModel(pathBarModel);
    auto line = new QLineEdit(this);
    line->setCompleter(pathCompleter);
    line->setText("file://" + QStandardPaths::writableLocation(QStandardPaths::HomeLocation));

    QToolBar *toolbar = new QToolBar(this);
    toolbar->addWidget(line);
    addToolBar(Qt::TopToolBarArea, toolbar);

    m_tab = new QTabWidget;
    m_tab->setUsesScrollButtons(true);
    auto tabbar = m_tab->tabBar();
    tabbar->setElideMode(Qt::ElideRight);
    tabbar->setExpanding(false);
    tabbar->setDocumentMode(true);
    tabbar->setTabsClosable(true);
    tabbar->setMovable(true);
    tabbar->setAutoHide(true);
    setCentralWidget(m_tab);

    connect(tabbar, &QTabBar::tabCloseRequested, [=](int index){
        qDebug()<<"remove"<<index;
        auto view = static_cast<Peony::DirectoryView::IconView*>(m_tab->widget(index));
        m_tab->removeTab(index);
        view->getProxy()->deleteLater();
        view->deleteLater();
    });

    connect(line, &QLineEdit::returnPressed, [=](){
        auto uri = line->text();
        auto iconView = new Peony::DirectoryView::IconView(m_tab);
        iconView->setDirectoryUri(uri);
        iconView->beginLocationChange();
        auto proxy = iconView->getProxy();
        this->connect(proxy, &Peony::DirectoryViewProxyIface::viewDirectoryChanged, [=](){
            this->disconnect(proxy, &Peony::DirectoryViewProxyIface::viewDirectoryChanged, 0, 0);
            m_tab->addTab(iconView, uri.split('/').last());

            proxy->connect(proxy, &Peony::DirectoryViewProxyIface::viewDoubleClicked, [=](const QString &uri){
                qDebug()<<uri;
                if (Peony::FileUtils::getFileIsFolder(Peony::wrapGFile(g_file_new_for_uri(uri.toUtf8().constData())))) {
                    iconView->setDirectoryUri(uri);
                    iconView->beginLocationChange();
                    m_tab->setTabText(m_tab->indexOf(iconView), uri.split("/").last());
                }
            });

        });
    });
}

MainWindow::~MainWindow()
{

}
