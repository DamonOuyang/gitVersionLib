#include "widget.h"
#include <QLabel>
#include <QMovie>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QLabel *label = new QLabel(this);
    QMovie *movie = new QMovie("C:/WorkSpace/civet1.6_win_newUi/GVMC/vendui/win32/Mock Debug/vendPictures/CoffeeVend/waitPro.gif");
    label->setMovie(movie);
    movie->start();
    label->show();
}

Widget::~Widget()
{

}
