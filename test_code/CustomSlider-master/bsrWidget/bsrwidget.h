#ifndef BSRWIDGET_H
#define BSRWIDGET_H

#include <QWidget>
#include <QSlider>

struct State
{
    bool p;
    bool c;
    bool x;
    bool q;
    bool all;
};


class SliderButton : public QSlider
{
    Q_OBJECT
public:
    explicit SliderButton(QWidget *parent = 0);

signals:

public slots:

};

class BsrWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BsrWidget(QWidget *parent = 0);

signals:

private slots:
    void changeValueP(int);
    void changeValueC(int);
    void changeValueX(int);
    void changeValueQ(int);
    void changeValueAll(int);

private:
    SliderButton *sliderP;
    SliderButton *sliderC;
    SliderButton *sliderX;
    SliderButton *sliderQ;
    SliderButton *sliderAll;

    State state;
};

#endif // BSRWIDGET_H
