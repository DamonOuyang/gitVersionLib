#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    /*
    QSlider::groove:horizontal {
              height: 6px;
              background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: , stop: 0 rgb(124, 124, 124), stop: 1.0 rgb(72, 71, 71));
     }
      QSlider::handle:horizontal {
              width: 1px;
              background: rgb(0, 160, 230);
              margin: -6px 0px -6px 0px;
              border-radius: 9px;
     }
     */

    int nMin = 0;
    int nMax = 200;
    int nSingleStep = 10;

    // 微调框
    QSpinBox *pSpinBox = new QSpinBox(this);
    pSpinBox->setMinimum(nMin);  // 最小值
    pSpinBox->setMaximum(nMax);  // 最大值
    pSpinBox->setSingleStep(nSingleStep);  // 步长

    // 滑动条
    QSlider *pSlider = new QSlider(this);
    pSlider->setOrientation(Qt::Horizontal);  // 水平方向
    pSlider->setMinimum(nMin);  // 最小值
    pSlider->setMaximum(nMax);  // 最大值
    pSlider->setSingleStep(nSingleStep);  // 步长
    pSlider->move(100,100);
    pSlider->setStyleSheet("QPushButton{background-image: url(:/images/call_up.bmp);}"
                           "QPushButton:hover{background-image: url(:/images/call_hov.bmp);}"
                           "QPushButton:pressed{background-image: url(:/images/call_down.bmp);}");

    // 连接信号槽（相互改变）
    connect(pSpinBox, SIGNAL(valueChanged(int)), pSlider, SLOT(setValue(int)));
    connect(pSlider, SIGNAL(valueChanged(int)), pSpinBox, SLOT(setValue(int)));

    pSpinBox->setValue(10);
}

Widget::~Widget()
{

}
