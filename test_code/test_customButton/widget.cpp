#include "widget.h"
#include "custompixmapbutton.h"
#include "CustomPixmapButtonCtr.h"
#include "GraphicsButton.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    static int count = 0;
    CustomPixmapButtonCtr* ctr = new CustomPixmapButtonCtr(this);

    CustomPixmapButton* Button = new CustomPixmapButton(count++);
    Button->setImageFile("C:\\Users\\AndroidDev\\Desktop\\test_button\\unchoose_wei.png",
                         "C:\\Users\\AndroidDev\\Desktop\\test_button\\choose_wei.png");

    CustomPixmapButton* Button2 = new CustomPixmapButton(count++);
    Button2->setImageFile("C:\\Users\\AndroidDev\\Desktop\\test_button\\unchoose_ali.png",
                         "C:\\Users\\AndroidDev\\Desktop\\test_button\\choose_ali.png");



    ctr->addButton2List(Button);
    ctr->addButton2List(Button2);

    QList<CustomPixmapButton *> ButtonList = ctr->getButtonList();


   QGraphicsScene *scene = new QGraphicsScene;

    QList<CustomPixmapButton *>::iterator i;
    for(i=ButtonList.begin(); i!=ButtonList.end(); ++i)
    {
        scene->addItem(*i);
        connect(*i,SIGNAL(sig_choose(int)),ctr,SLOT(slot_chooseButton(int)));
    }
    ctr->setDefaultChooseButton(0);
    Button2->setPos(100,200);

    QGraphicsView *view = new QGraphicsView(scene);
    view->resize(500, 500);
    view->setWindowTitle("Graphics View");

    //ctr->delButtonFromList(1);

    view->show();

}

Widget::~Widget()
{

}
