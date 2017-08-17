#include "keywidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    KeyWidget w;
    w.show();

    return a.exec();
}
