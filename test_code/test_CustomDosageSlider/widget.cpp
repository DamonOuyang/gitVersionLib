#include "widget.h"
#include "customdosageslider.h"
#include "customdosagesliderCtr.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QList>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    static int count = 0;
    CustomDosagesSliderCtr* ctr = new CustomDosagesSliderCtr(this);

    CustomDosageSlider* Button = new CustomDosageSlider(count++);
    Button->setImageFile("C:\\Users\\AndroidDev\\Desktop\\test_code\\test_CustomDosageSlider\\2left.png",
                         "C:\\Users\\AndroidDev\\Desktop\\test_code\\test_CustomDosageSlider\\2milk.png");

    CustomDosageSlider* Button2 = new CustomDosageSlider(count++);
    Button2->setImageFile("C:\\Users\\AndroidDev\\Desktop\\test_code\\test_CustomDosageSlider\\2left.png",
                         "C:\\Users\\AndroidDev\\Desktop\\test_code\\test_CustomDosageSlider\\2sugar.png");

    ctr->addButton2List(Button);
    ctr->addButton2List(Button2);

    QList<CustomDosageSlider *> ButtonList = ctr->getButtonList();


   QGraphicsScene *scene = new QGraphicsScene;

    QList<CustomDosageSlider *>::iterator i;
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
