#ifndef DESKTOPSTACKEDWIDGET_H
#define DESKTOPSTACKEDWIDGET_H

#include <QStackedWidget>

class QGraphicsOpacityEffect;
class QLabel;

class DesktopStackedWidget : public QStackedWidget
{
    Q_OBJECT
public:
    explicit DesktopStackedWidget(QWidget *parent = nullptr);
    ~DesktopStackedWidget() override;

    void setBg(const QPixmap &pixmap);

public Q_SLOTS:
    void updateBg(const QString &uri);
    void updateGeometry();

protected:
    void updateOpacity();

private:
    QLabel *m_bg_widget;
    QLabel *m_bottom_bg_widget;
    QString m_bg_uri;

    QPixmap m_bottom_pixmap;

    qreal m_opacity = 0.0;
    QGraphicsOpacityEffect *m_effect;
    QTimer *m_timer;
};

#endif // DESKTOPSTACKEDWIDGET_H
