#include "widget.h"
#include "baseapi.h"
#include "gameapi.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    GameAPI* game_api = new GameAPI();
    game_api->getGameList(
                [&](bool success, QList<QPair<QString,QString>> games)
    {
        if(success)
        {
            //do something
            qDebug() << "do something";
        }
        if(!success)
        {
            qDebug() << "not do something";
        }
    }
    );
}

Widget::~Widget()
{

}
