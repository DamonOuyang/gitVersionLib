#include "keywidget.h"
#include "softkeylineedit.h"

KeyWidget::KeyWidget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(400 , 300);
    lineEdit = new SoftKeyLineEdit(this);
    lineEdit->setGeometry(QRect(132, 70, 121, 27));
}

KeyWidget::~KeyWidget()
{

}
