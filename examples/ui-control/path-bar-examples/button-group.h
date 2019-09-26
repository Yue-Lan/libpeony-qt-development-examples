#ifndef BUTTONGROUP_H
#define BUTTONGROUP_H

#include <QWidget>
#include <QToolBar>

class ButtonGroup : public QToolBar
{
    Q_OBJECT
public:
    explicit ButtonGroup(QWidget *parent = nullptr);
    const QString getCurentUri() {return m_current_uri;}

Q_SIGNALS:
    void groupChangedRequest(const QString &uri);

public Q_SLOTS:
    void setRootUri(const QString &uri);

protected:
    void addButton(const QString &uri, bool setMenu = true);
    void mousePressEvent(QMouseEvent *e) override;

private:
    QString m_current_uri;
};

#endif // BUTTONGROUP_H
