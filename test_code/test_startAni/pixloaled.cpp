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

bool pixLoaled::loalPixforAni(int count)
{
	bool b = false;
	for(int  i = 1 ; i< count ; ++i)
	{
        QString tmp = "C:/WorkSpace/civet1.6_win_newUi/GVMC/vendui/win32/Mock Debug/vendPictures/CoffeeVend/WaitCoffeePic/loading";
		tmp+= QString::number(i);
		tmp+= ".png";

		QPixmap tmpPix;
		b =tmpPix.load(tmp);
		if(b)
            m_bgs.push_back(&tmpPix);
	}
	return b;
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
   return true;
}


bool pixLoaled::loalStateViewPage()
{
	for(int  i = 1 ; i< 6 ; ++i)
	{
        QString tmp = "./point/point";
		tmp+= QString::number(i);
		tmp+= ".png";

		QPixmap tmpPix;
		bool b =tmpPix.load(tmp);
		if(b)
            m_pointPixs.push_back(&tmpPix);
	}
	return true;
}
