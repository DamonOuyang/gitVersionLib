#include "customdosagesliderctr.h"
#include "customdosageslider.h"
CustomDosagesSliderCtr::CustomDosagesSliderCtr(QObject *parent)
    : QObject(parent)
{

}

void CustomDosagesSliderCtr::addButton2List(CustomDosageSlider * button)
{
    if(button == NULL)
    {
        return;
    }
    else
    {
        m_buttonList.append(button);
    }
}

void CustomDosagesSliderCtr::delButtonFromList(CustomDosageSlider * button)
{
    if(button == NULL)
        return;

    QList<CustomDosageSlider *>::iterator ci;
    CustomDosageSlider * tmp = NULL;
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
    }
}

void CustomDosagesSliderCtr::delButtonFromList(int id)
{
    QList<CustomDosageSlider *>::iterator ci;
    CustomDosageSlider * tmp = NULL;
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

void CustomDosagesSliderCtr::clearButtonList()
{
    QList<CustomDosageSlider *>::iterator ci;
    for(ci=m_buttonList.begin(); ci!=m_buttonList.end(); ++ci)
    {
        delete *ci;
        *ci = NULL;
    }

    m_buttonList.clear();
}

void CustomDosagesSliderCtr::slot_chooseButton(int id)
{
    QList<CustomDosageSlider *>::const_iterator ci;
    for(ci=m_buttonList.constBegin(); ci!=m_buttonList.constEnd(); ++ci)
    {
        if( (*ci)->getID() != id)
        {
            (*ci)->setStateType(STATE::UNCHOOSE);
            (*ci)->resetPixmap();
        }
    }

    emit sig_chooseThisButton(id);  // 选择按钮后发信号
}

CustomDosagesSliderCtr::~CustomDosagesSliderCtr()
{
    clearButtonList();
    m_buttonList.clear();
}

void CustomDosagesSliderCtr::setDefaultChooseButton(int id)
{
    QList<CustomDosageSlider *>::const_iterator ci;
    for(ci=m_buttonList.constBegin(); ci!=m_buttonList.constEnd(); ++ci)
    {
        if( (*ci)->getID() == id)
        {
            (*ci)->setStateType(STATE::CHOOSE);
            (*ci)->resetPixmap();
        }
        else
        {
            (*ci)->resetPixmap();
        }
    }
}

int CustomDosagesSliderCtr::getCurrentChooseButton()
{
    QList<CustomDosageSlider *>::const_iterator ci;
    for(ci=m_buttonList.constBegin(); ci!=m_buttonList.constEnd(); ++ci)
    {
        if( (*ci)->getStateType() == STATE::CHOOSE)
        {
            return (*ci)->getID();
        }
    }
}

CustomDosageSlider *CustomDosagesSliderCtr::getOneButton(int id)
{
    QList<CustomDosageSlider *>::const_iterator ci;
    for(ci=m_buttonList.constBegin(); ci!=m_buttonList.constEnd(); ++ci)
    {
        if( (*ci)->getID() == id )
        {
            return *ci;
        }
    }

    return NULL;
}
