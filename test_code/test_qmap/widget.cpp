#include "widget.h"
#include <map>
#include <unistd.h>

using namespace std;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    map<string,string> m;
    m.insert(pair("hehe","haha"));
    m.insert(pair("dddd","haha"));
    m.insert(pair("rrrr","haha"));
    for(int i=0;i<m.size();i++)
    {
        m.at(i);
    }

}

Widget::~Widget()
{

}
