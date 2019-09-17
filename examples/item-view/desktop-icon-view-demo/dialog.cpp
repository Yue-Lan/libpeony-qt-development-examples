#include "dialog.h"

Dialog::Dialog(QWidget *parent)
    : QFileDialog(parent)
{
    QStringList l;
    l<<"*.jpg"<<"*.png";
    setNameFilters(l);
}

Dialog::~Dialog()
{

}
