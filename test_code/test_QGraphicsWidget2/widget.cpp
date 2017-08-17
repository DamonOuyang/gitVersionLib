#include "widget.h"
#include "custompixmapbutton.h"
#include "CustomPixmapButtonCtr.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    static int count = 0;
    CustomPixmapButtonCtr* ctr = new CustomPixmapButtonCtr(this);
    CustomPixmapButton* Button = new CustomPixmapButton(count++
                                                        ,QPoint(0,100)
                                                        ,"C:\\Users\\AndroidDev\\Desktop\\test_button\\unchoose_wei.png"
                                                        ,"C:\\Users\\AndroidDev\\Desktop\\test_button\\choose_wei.png"
                                                        ,STATE::SELECT_MULT);


    CustomPixmapButton* Button2 = new CustomPixmapButton(count++
                                                         ,QPoint(100,200)
                                                         ,"C:\\Users\\AndroidDev\\Desktop\\test_button\\unchoose_ali.png"
                                                         ,"C:\\Users\\AndroidDev\\Desktop\\test_button\\choose_ali.png"
                                                         ,STATE::SELECT_MULT);


    CustomPixmapButton* Button3 = new CustomPixmapButton(count++
                                                         ,QPoint(200,300)
                                                         ,"C:\\Users\\AndroidDev\\Desktop\\test_button\\unchoose_ali.png"
                                                         ,"C:\\Users\\AndroidDev\\Desktop\\test_button\\choose_ali.png"
                                                         ,STATE::SELECT_MULT);


    CustomPixmapButton* Button4 = new CustomPixmapButton(count++
                                                         ,QPoint(300,400)
                                                         ,"C:\\Users\\AndroidDev\\Desktop\\test_button\\unchoose_wei.png"
                                                         ,"C:\\Users\\AndroidDev\\Desktop\\test_button\\choose_wei.png"
                                                         ,STATE::SELECT_MULT);

//    CustomPixmapButtonCtr* ctr = new CustomPixmapButtonCtr(this);
//    CustomPixmapButton* Button = new CustomPixmapButton(count++
//                                                        ,QPoint(0,100)
//                                                        ,"C:\\Users\\AndroidDev\\Desktop\\cold_unchoose.png"
//                                                        ,"C:\\Users\\AndroidDev\\Desktop\\cold_choose.png"
//                                                        ,STATE::SELECT_SINGLE);


//    CustomPixmapButton* Button2 = new CustomPixmapButton(count++
//                                                         ,QPoint(400,100)
//                                                         ,"C:\\Users\\AndroidDev\\Desktop\\test_button\\unchoose_ali.png"
//                                                         ,"C:\\Users\\AndroidDev\\Desktop\\test_button\\choose_ali.png"
//                                                         ,STATE::SELECT_SINGLE);


//    CustomPixmapButton* Button3 = new CustomPixmapButton(count++
//                                                         ,QPoint(200,300)
//                                                         ,"C:\\Users\\AndroidDev\\Desktop\\test_button\\unchoose_ali.png"
//                                                         ,"C:\\Users\\AndroidDev\\Desktop\\test_button\\choose_ali.png"
//                                                         ,STATE::SELECT_SINGLE);


//    CustomPixmapButton* Button4 = new CustomPixmapButton(count++
//                                                         ,QPoint(300,400)
//                                                         ,"C:\\Users\\AndroidDev\\Desktop\\test_button\\unchoose_wei.png"
//                                                         ,"C:\\Users\\AndroidDev\\Desktop\\test_button\\choose_wei.png"
//                                                         ,STATE::SELECT_SINGLE);


    ctr->addButton2List(Button);
    ctr->addButton2List(Button2);
    ctr->addButton2List(Button3);
    ctr->addButton2List(Button4);


    int arr[2] = {0,3};
    QGraphicsScene *scene = new QGraphicsScene;
    ctr->setDefaultChooseButtons(arr,2);


    QList<CustomPixmapButton *> list = ctr->getButtonList();
    QList<CustomPixmapButton *>::iterator i;
    for(i=list.begin(); i!=list.end(); ++i)
    {
        scene->addItem(*i);
    }

    QGraphicsView *view = new QGraphicsView(scene);
    view->resize(1000, 500);
    view->setWindowTitle("Graphics View");

    //ctr->delButtonFromList(1);

    connect(ctr,SIGNAL(sig_chooseThisButton(int)),this,SLOT(slot_testBnt(int)));

    view->show();

}

Widget::~Widget()
{

}

void Widget::slot_testBnt(int id)
{
    qDebug() << id << endl;
}
