#include "mainwindow.h"
#include <QApplication>
#include <PeonyPathBarModel>
#include <PeonyPathCompleter>

#include <QLineEdit>
#include <QLabel>
#include <QToolBar>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QToolBar t;
    w.addToolBar(Qt::TopToolBarArea, &t);

    QLineEdit e;
    t.addWidget(&e);

    Peony::PathBarModel m;
    Peony::PathCompleter c;
    c.setModel(&m);

    e.setCompleter(&c);
    e.setText("file:///");

    QLabel helpLabel("entry the text in line edit, and then"
                     "it will automaticly complete the possible folder paths.");

    w.setCentralWidget(&helpLabel);

    w.show();

    return a.exec();
}
