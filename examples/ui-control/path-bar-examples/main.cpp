#include <QApplication>
#include <QToolBar>
#include <QScrollArea>
#include <QLabel>
#include <QTextEdit>
#include <QStandardPaths>
#include <QGridLayout>
#include "button-group.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QWidget test;

    QGridLayout layout;
    layout.setSpacing(0);
    layout.setContentsMargins(0, 0, 0, 0);
    test.setLayout(&layout);
    test.setContentsMargins(0, 0, 0, 0);
    test.setStyleSheet("padding: 0");

    ButtonGroup g;
    g.setWindowTitle("path bar");
    g.setContentsMargins(0, 0, 0, 0);
    g.setStyleSheet("padding-right: 10px");

    layout.addWidget(&g);

    g.setRootUri("file://" + QStandardPaths::writableLocation(QStandardPaths::HomeLocation));
    g.setMovable(false);

    QTextEdit l;
    l.setText("this example is showing you how to use Peony::PathBarModel for "
              "making a breadcrumb like path bar. I use QToolBar as the basic control.");

    layout.addWidget(&l);
    test.show();

    return a.exec();
}
