#include "widget.h"
#include "StartAniPage.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>
#include "pixloaled.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    StartAniPage *star = new StartAniPage;

    if(!pixLoaled::getInstance()->loalStateViewPage())
    {
        printf("%s\n","loalStateViewPage()");
        return;
    }
    QVector<QPixmap*> tmp = pixLoaled::getInstance()->getPointPixs();
    star->setPointPixVet(tmp);




    QGraphicsScene *scene = new QGraphicsScene(this);
    //scene->addItem(star);
    QGraphicsView *view = new QGraphicsView(scene);
    view->resize(1000, 500);
    view->show();
}

Widget::~Widget()
{

}

void Widget::slot_testBnt(int id)
{
    qDebug() << id << endl;
}
