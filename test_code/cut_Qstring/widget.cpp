#include "widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
   // {"result":true,"data":"http://mkcaffee.chinaeast.cloudapp.chinacloudapi.cn/app/coffees/index.html#/myCoffees/33333"}
    QString str = "http://mkcaffee.chinaeast.cloudapp.chinacloudapi.cn/app/coffees/index.html#/myCoffees/33333";
    QString str1 = str.mid(str.indexOf("http",1));
    QString str = str1.replace("","");

    qDebug() << str1 ;
}

Widget::~Widget()
{

}
