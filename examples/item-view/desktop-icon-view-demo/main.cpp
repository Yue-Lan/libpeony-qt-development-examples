#include "dialog.h"
#include "desktop-stacked-widget.h"
#include <QApplication>
#include <QPixmap>
#include <QMessageBox>

#include <QDebug>

/*!
 * \brief
 * this demo provide a simple way to realize a linux 'desktop'.
 *
 * the desktop is divided into two parts, the background and the icon view.
 * the background is a QLabel instance (actually 2 labels), and the icon view is a background-transparent
 * folder view.
 *
 * there are some small techinques i'll show you how to change the background with fade in/out
 * effect, and how to use stack widget superimposed the background and icon view (stack all mode & transparent).
 *
 * of course the window instance which represent the desktop is not so simple at all.
 * in qt5, the QApplication provide a set of apis to help us archive more
 * complex interaction with our devices about the 'desktop'. This demo
 * doesn't show that.
 */

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    QMessageBox::question(nullptr, QObject::tr("Hint"), QObject::tr("selecte the picture file and change the window background"));

    DesktopStackedWidget d;
    d.show();

    w.connect(&w, &QFileDialog::currentChanged, [&](const QString &file){
        qDebug()<<file;
        if (file.endsWith(".jpg") || file.endsWith(".png")) {
            QPixmap p(file);
            d.setBg(p);
        }
    });

    w.connect(&w, &QFileDialog::rejected, [=]{
        qApp->quit();
    });

    w.connect(&w, &QFileDialog::accepted, [=]{
        qApp->quit();
    });

    w.show();

    return a.exec();
}
