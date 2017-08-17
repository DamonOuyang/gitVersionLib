#include "widget.h"
#include "pixloaled.h"
#include <QPoint>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    pixLoaled * s  = pixLoaled::getInstance();

}

Widget::~Widget()
{

}
