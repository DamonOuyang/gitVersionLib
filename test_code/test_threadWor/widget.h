#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class ThreadLoalPix;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

public slots:
    void slot_ThreadStart();

signals:

private:
    QThread      *       m_thread;
    ThreadLoalPix*       m_threadLoalPic;

};

#endif // WIDGET_H
