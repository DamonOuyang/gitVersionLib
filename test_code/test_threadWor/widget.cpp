#include "widget.h"
#include <QThread>
#include <QDebug>
#include "threadloalpix.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    m_thread = new QThread(this);
    m_threadLoalPic = new ThreadLoalPix;
    m_threadLoalPic->moveToThread(m_thread);
    m_thread->start();
    connect(m_thread,SIGNAL(started()),m_threadLoalPic,SLOT(slot_loalPix()));
}

Widget::~Widget()
{
    if(m_thread->isRunning())
    {
        m_threadLoalPic->stopThread();
        m_thread->exit();
        m_thread->wait();
    }
    m_thread->deleteLater();
}

void Widget::slot_ThreadStart()
{
  qDebug() << "Loal finished..." << endl;
}
