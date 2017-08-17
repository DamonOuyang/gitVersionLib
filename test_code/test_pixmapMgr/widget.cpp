#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget()
{

}


PixmapMgr &langMgr = singleton<PixmapMgr>::instance();
