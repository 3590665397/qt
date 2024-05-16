#include "my_lineedit.h"
#include <QDebug>

My_lineEdit::My_lineEdit(QWidget *parent) :
    QLineEdit(parent)
{
    this->setStyleSheet("My_lineEdit{background:rgba(255,0,0,0);}");
}

void My_lineEdit::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit send_show(this->text());

}
