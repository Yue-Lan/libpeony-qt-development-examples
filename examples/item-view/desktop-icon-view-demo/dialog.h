#ifndef DIALOG_H
#define DIALOG_H

#include <QFileDialog>

class Dialog : public QFileDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();
};

#endif // DIALOG_H
