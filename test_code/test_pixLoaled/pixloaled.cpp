#include "pixloaled.h"

pixLoaled * pixLoaled::m_instance = NULL;

pixLoaled::pixLoaled(QObject *parent)
    : QObject(parent)
{

}

pixLoaled::~pixLoaled()
{

}

pixLoaled * pixLoaled::getInstance()
{
    if(m_instance == NULL)
    {
        m_instance = new pixLoaled;
    }
    return m_instance;
}

void pixLoaled::releaseInstance()
{
    if(m_instance != NULL)
    {
        delete m_instance;
        m_instance = NULL;
    }
}

bool pixLoaled::loalCoffeeProgressPage()
{
    for(int  i = 2 ; i< 96 ; ++i)
    {
        QString tmp = "./vendPictures/CoffeeVend/WaitCoffeePic/loading";
        tmp+= QString::number(i);
        tmp+= ".png";

        QPixmap tmpPix;
        bool b =tmpPix.load(tmp);
        if(b)
            m_bgs.push_back(tmpPix);
    }
   return true;
}



























