#include "widget.h"
#include "network.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    networkWidget w;

    return a.exec();
}
