#include "widget.h"
#include "custompixmapbutton.h"
#include "CustomPixmapButtonCtr.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    static int count = 0;
    CustomPixmapButtonCtr* ctr = new CustomPixmapButtonCtr(this);

//    CustomPixmapButton* Button = new CustomPixmapButton(count++);
//    Button->setImageFile("C:\\Users\\AndroidDev\\Desktop\\test_button\\unchoose_wei.png",
//                         "C:\\Users\\AndroidDev\\Desktop\\test_button\\choose_wei.png");

//    CustomPixmapButton* Button2 = new CustomPixmapButton(count++);
//    Button2->setImageFile("C:\\Users\\AndroidDev\\Desktop\\test_button\\unchoose_ali.png",
//                         "C:\\Users\\AndroidDev\\Desktop\\test_button\\choose_ali.png");

    CustomPixmapButton* button = new CustomPixmapButton(1,QPixmap("C:\\Users\\AndroidDev\\Desktop\\test_button\\unchoose_wei.png")
                                                        ,QPixmap("C:\\Users\\AndroidDev\\Desktop\\test_button\\choose_wei.png")
                                                        ,QPixmap("C:\\Users\\AndroidDev\\Desktop\\test_button\\unchoose_wei.png"));

    CustomPixmapButton* button2 = new CustomPixmapButton(2,QPixmap("C:\\Users\\AndroidDev\\Desktop\\test_button\\unchoose_ali.png")
                                                         ,QPixmap("C:\\Users\\AndroidDev\\Desktop\\test_button\\choose_ali.png")
                                                         ,QPixmap("C:\\Users\\AndroidDev\\Desktop\\test_button\\unchoose_ali.png"));

    ctr->addButton2List(button);
    ctr->addButton2List(button2);

    QList<CustomPixmapButton *> ButtonList = ctr->getButtonList();


   QGraphicsScene *scene = new QGraphicsScene;

    QList<CustomPixmapButton *>::iterator i;
    for(i=ButtonList.begin(); i!=ButtonList.end(); ++i)
    {
        scene->addItem(*i);
        connect(*i,SIGNAL(sig_choose(int)),ctr,SLOT(slot_chooseButton(int)));
    }
    ctr->setDefaultChooseButton(0);
    button2->setPos(100,200);

    QGraphicsView *view = new QGraphicsView(scene);
    view->resize(500, 500);
    view->setWindowTitle("Graphics View");

    //ctr->delButtonFromList(1);

    view->show();

}

Widget::~Widget()
{

}
