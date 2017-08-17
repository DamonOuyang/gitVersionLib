#include "bsrwidget.h"
#include <QDebug>
#include <QPainterPath>
#include <QPainter>
#include <QStylePainter>
#include <QStyleOptionSlider>
#include <QApplication>

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

SliderButton::SliderButton(QWidget *parent) : QSlider(parent)
{
    setOrientation(Qt::Orientation::Horizontal);
    setMaximum(1);
    setMinimumHeight(100);
    setMinimumWidth(200);

    setStyleSheet(

           "QSlider::groove:horizontal {"
            "border: 0px none;"
            "background: white;"
            "height: 50px;"
            "width: 100px;"
            "border-radius: 5px;"
            "}"

            "QSlider::handle:horizontal {"
            "background: #D8D8D8;"
            "border: 0px none;"
            "width: 50px;"
            "border-radius: 5px;"
            "margin: 0px 0;"
            "}"

            "QSlider::add-page:horizontal {"
            "background: #A2C511;"
            "border-radius: 5px;"
            "}"

            "QSlider::sub-page:horizontal {"
            "background: #DD4814;"
            "border-radius: 5px;"
            "}"

        );

}


BsrWidget::BsrWidget(QWidget *parent) : QWidget(parent)
{

    sliderP = new SliderButton;
    sliderC = new SliderButton;
    sliderX = new SliderButton;
    sliderQ = new SliderButton;
    sliderAll = new SliderButton;

    QLabel *labelP = new QLabel("P-диапазон");
    QLabel *labelC = new QLabel("C-диапазон");
    QLabel *labelX = new QLabel("X-диапазон");
    QLabel *labelQ = new QLabel("Q-диапазон");
    QLabel *labelAll = new QLabel("Все");

    QHBoxLayout *layoutP = new QHBoxLayout;
    layoutP->addWidget(sliderP, 0, Qt::AlignCenter);
    layoutP->addWidget(labelP);

    QHBoxLayout *layoutC = new QHBoxLayout;
    layoutC->addWidget(sliderC, 0, Qt::AlignCenter);
    layoutC->addWidget(labelC);

    QHBoxLayout *layoutX = new QHBoxLayout;
    layoutX->addWidget(sliderX, 0, Qt::AlignCenter);
    layoutX->addWidget(labelX);

    QHBoxLayout *layoutQ = new QHBoxLayout;
    layoutQ->addWidget(sliderQ, 0, Qt::AlignCenter);
    layoutQ->addWidget(labelQ);

    QHBoxLayout *layoutAll = new QHBoxLayout;
    layoutAll->addWidget(sliderAll, 0, Qt::AlignCenter);
    layoutAll->addWidget(labelAll);

    QVBoxLayout* layout = new QVBoxLayout;
    layout->addLayout(layoutP);
    layout->addLayout(layoutC);
    layout->addLayout(layoutX);
    layout->addLayout(layoutQ);
    layout->addLayout(layoutAll);

    this->setLayout(layout);

    connect(sliderP,  SIGNAL(valueChanged(int)), this, SLOT(changeValueP(int)));
    connect(sliderC, SIGNAL(valueChanged(int)), this, SLOT(changeValueC(int)));
    connect(sliderX, SIGNAL(valueChanged(int)), this, SLOT(changeValueX(int)));
    connect(sliderQ, SIGNAL(valueChanged(int)), this, SLOT(changeValueQ(int)));
    connect(sliderAll, SIGNAL(valueChanged(int)), this, SLOT(changeValueAll(int)));

}

void BsrWidget::changeValueP(int value)
{
    qDebug() << "changeValueP()";
    state.p = value;
}

void BsrWidget::changeValueC(int value)
{
    state.c = value;
}

void BsrWidget::changeValueX(int value)
{
    state.x = value;
}

void BsrWidget::changeValueQ(int value)
{
    state.q = value;
}

void BsrWidget::changeValueAll(int value)
{
    state.p = value;
    state.c = value;
    state.x = value;
    state.q = value;

    sliderP->setSliderPosition(value);
    sliderC->setSliderPosition(value);
    sliderX->setSliderPosition(value);
    sliderQ->setSliderPosition(value);


}

