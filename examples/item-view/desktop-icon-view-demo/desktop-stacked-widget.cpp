#include "desktop-stacked-widget.h"

#include <QLabel>
#include <QApplication>
#include <QScreen>
#include <QGraphicsOpacityEffect>
#include <QPicture>

#include <QDebug>
#include <QTimer>

#include <PeonyFileItemModel>
#include <QListView>
#include <QStandardPaths>

#include <QStackedLayout>

DesktopStackedWidget::DesktopStackedWidget(QWidget *parent) : QStackedWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    QStackedLayout *layout = static_cast<QStackedLayout*>(this->layout());
    layout->setStackingMode(QStackedLayout::StackAll);

    setWindowFlag(Qt::FramelessWindowHint);
    setWindowFlag(Qt::WindowStaysOnBottomHint);

    m_bottom_bg_widget = new QLabel;
    m_bottom_bg_widget->setAttribute(Qt::WA_TranslucentBackground);
    m_bottom_bg_widget->setContentsMargins(0, 0, 0, 0);
    m_bg_widget = new QLabel;
    m_bg_widget->setAttribute(Qt::WA_TranslucentBackground);
    m_bg_widget->setContentsMargins(0, 0, 0, 0);

    m_timer = new QTimer;
    m_effect = new QGraphicsOpacityEffect(m_bg_widget);

    setGeometry(QApplication::primaryScreen()->geometry());

    ///the order is very important
    addWidget(m_bg_widget);
    addWidget(m_bottom_bg_widget);

    QListView *iconView = new QListView(this);

    //transparent the view
    iconView->setAttribute(Qt::WA_TranslucentBackground);
    iconView->setStyleSheet("background-color:transparent");

    iconView->setMovement(QListView::Snap);
    iconView->setGridSize(QSize(96, 96));
    iconView->setWordWrap(true);
    iconView->setViewMode(QListView::IconMode);
    iconView->setFlow(QListView::TopToBottom);

    iconView->setSelectionMode(QListView::ExtendedSelection);

    Peony::FileItemModel *model = new Peony::FileItemModel(iconView);
    model->setRootUri("file://" + QStandardPaths::writableLocation(QStandardPaths::DesktopLocation));

    iconView->setModel(model);

    addWidget(iconView);
    this->setCurrentWidget(iconView);
}

DesktopStackedWidget::~DesktopStackedWidget()
{
    m_timer->stop();
    delete m_timer;
    delete m_bg_widget;
    delete m_bottom_bg_widget;
}

void DesktopStackedWidget::setBg(const QPixmap &pixmap)
{
    m_timer->stop();
    m_timer->disconnect();

    m_opacity = 0.0;
    m_timer->start(100);
    QPixmap p = pixmap.scaled(QApplication::primaryScreen()->geometry().size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    updateOpacity();
    m_bottom_bg_widget->setPixmap(m_bottom_pixmap);
    m_bg_widget->setPixmap(p);
    m_timer->connect(m_timer, &QTimer::timeout, [=](){

        m_opacity += 0.1;
        if (m_opacity > 1) {
            m_timer->stop();
            m_bottom_pixmap = p;
            return ;
        }
        qDebug()<<m_opacity;
        this->updateOpacity();
    });

    m_bg_widget->setGeometry(QApplication::primaryScreen()->geometry());
}

void DesktopStackedWidget::updateBg(const QString &name)
{
    m_bg_uri = name;
    QPixmap p(name);
    setBg(p);
}

void DesktopStackedWidget::updateGeometry()
{

}

void DesktopStackedWidget::updateOpacity()
{
    m_effect->setOpacity(m_opacity);
    m_bg_widget->setGraphicsEffect(m_effect);
}
