#include "CustomPixmapButtonCtr.h"
#include "custompixmapbutton.h"

CustomPixmapButtonCtr::CustomPixmapButtonCtr(QObject *parent)
    :QObject(parent)
{
}

void CustomPixmapButtonCtr::addButton2List(CustomPixmapButton * button)
{
    if(button == NULL)
        return;

    m_buttonList.append(button);
    connect(button,SIGNAL(sig_choose(int)),this,SLOT(slot_chooseButton(int)));
}

void CustomPixmapButtonCtr::delButtonFromList(CustomPixmapButton * button)
{
    if(button == NULL)
        return;

    QList<CustomPixmapButton *>::iterator ci;
    CustomPixmapButton * tmp = NULL;
    for(ci=m_buttonList.begin(); ci!=m_buttonList.end(); ++ci)
    {
        if((*ci) == button)
        {
            tmp = *ci;
            m_buttonList.erase(ci);
            break;
        }
    }

    if(tmp != NULL)
    {
        delete tmp;
        tmp = NULL;
    }
}

void CustomPixmapButtonCtr::delButtonFromList(int id)
{
    QList<CustomPixmapButton *>::iterator ci;
    CustomPixmapButton * tmp = NULL;
    for(ci=m_buttonList.begin(); ci!=m_buttonList.end(); ++ci)
    {
        if((*ci)->getID() == id)
        {
            tmp = *ci;
            m_buttonList.erase(ci);
            break;
        }
    }

    if(tmp != NULL)
    {
        delete tmp;
    }
}

void CustomPixmapButtonCtr::clearButtonList()
{
    QList<CustomPixmapButton *>::iterator ci;
    for(ci=m_buttonList.begin(); ci!=m_buttonList.end(); ++ci)
    {
        delete *ci;
        *ci = NULL;
    }

    m_buttonList.clear();
}

void CustomPixmapButtonCtr::slot_chooseButton(int id)
{
    QList<CustomPixmapButton *>::const_iterator ci;
    for(ci=m_buttonList.constBegin(); ci!=m_buttonList.constEnd(); ++ci)
    {
        if((*ci)->getSlectType() == STATE::SELECT_SINGLE)
        {
            if((*ci)->getID() != id)
            {
                (*ci)->setStateType(STATE::UNCHOOSE);
            }
        }
        else
        {

        }

    }
    emit sig_chooseThisButton(id);  // 选择按钮后发信号
}

CustomPixmapButtonCtr::~CustomPixmapButtonCtr()
{
    clearButtonList();
    m_buttonList.clear();
}

bool CustomPixmapButtonCtr::setDefaultChooseButtons(int* arr, int len)
{
    if(m_buttonList.size() < len)
        return false;

    QList<CustomPixmapButton *>::const_iterator ci;
    for(ci=m_buttonList.constBegin(); ci!=m_buttonList.constEnd(); ++ci)
    {
        int id = (*ci)->getID();
        for(int i=0;i<len;i++)
        {
            if( id == arr[i])
            {
                (*ci)->setStateType(STATE::CHOOSE);
            }
        }
    }
    return true;
}

int CustomPixmapButtonCtr::getCurrentChooseButton()
{
    QList<CustomPixmapButton *>::const_iterator ci;
    for(ci=m_buttonList.constBegin(); ci!=m_buttonList.constEnd(); ++ci)
    {
        if( (*ci)->getStateType() == STATE::CHOOSE)
        {
            return (*ci)->getID();
        }
    }
}

CustomPixmapButton *CustomPixmapButtonCtr::getOneButton(int id)
{
    QList<CustomPixmapButton *>::const_iterator ci;
    for(ci=m_buttonList.constBegin(); ci!=m_buttonList.constEnd(); ++ci)
    {
        if( (*ci)->getID() == id )
        {
            return *ci;
        }
    }
    return NULL;
}

