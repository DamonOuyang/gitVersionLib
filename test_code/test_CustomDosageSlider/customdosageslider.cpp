#include "customdosageslider.h"
#include <QGraphicsSceneMouseEvent>

CustomDosageSlider::CustomDosageSlider(int id,QGraphicsWidget * parent)
    : QGraphicsWidget(parent), m_btnRect(QRect(0,0,0,0)),m_state(STATE::UNCHOOSE),m_id(id),m_sliderPoint(QPoint(0,0))
{
    setCacheMode(DeviceCoordinateCache);
    this->resize(453,94);
}

CustomDosageSlider::~CustomDosageSlider()
{

}

void CustomDosageSlider::resetPixmap()
{
    update();
}

void CustomDosageSlider::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    setStateType(STATE::CHOOSE);

    update();
    emit sig_choose(m_id);
}

void CustomDosageSlider::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
    if(getStateType() == STATE::CHOOSE)
    {
        if( boundingRect().contains( event->pos() ))
        {
            //emit sig_mouse_released();
        }
    }
    else
    {

    }

}

void CustomDosageSlider::mouseMoveEvent( QGraphicsSceneMouseEvent * event )
{
    QRect  frameRect = boundingRect().toRect();
    QPoint currPoint = event->pos().toPoint();
    m_sliderPoint.setX(currPoint.x() - SLIDERWIDTH  / 2);
    m_sliderPoint.setY(currPoint.y() - SLIDERHEIGHT / 2);

    if(getStateType() == STATE::CHOOSE)
    {
        if( !frameRect.contains( currPoint, true ) )
        {

        }
    }
    else
    {

    }
    update();
}

void CustomDosageSlider::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0,0,m_bgImg);
    if(this->m_state == STATE::UNCHOOSE)
    {
       painter->drawPixmap(0 ,0  ,m_bgImg );
    }
    else
    {
        //painter->drawPixmap(0 ,0 ,m_sliderImg);
    }
    painter->drawPixmap(m_sliderPoint,m_sliderImg);
}

void CustomDosageSlider::setImageFile( const QString& bgImg, const QString& sliderImg )
{
    m_bgImg = QPixmap( bgImg );
    m_sliderImg  = QPixmap( sliderImg );
}

