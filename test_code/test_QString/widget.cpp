#include "widget.h"
#include "ui_widget.h"
#include <QString>
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    qDebug() << QString() << endl;

}

Widget::~Widget()
{
    delete ui;
}
