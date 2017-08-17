#include "threadloalpix.h"

ThreadLoalPix::ThreadLoalPix(QObject *parent)
    : QObject(parent)
{
    m_threadStopFlag = false;
    m_bgs.clear();
}

ThreadLoalPix::~ThreadLoalPix()
{

}

void ThreadLoalPix::stopThread()
{
    m_threadStopFlag = true;
}

void ThreadLoalPix::slot_loalPix()
{
    for(int  i = 1 ; i< 96 ; ++i)
    {
        QString tmp = "./vendPictures/CoffeeVend/WaitCoffeePic/loading";
        tmp+= QString::number(i);
        tmp+= ".png";

        QPixmap tmpPix;
        bool b =tmpPix.load(tmp);
        if(b)
            m_bgs.push_back(&tmpPix);
    }
    emit sig_loalPixFinished();
}
