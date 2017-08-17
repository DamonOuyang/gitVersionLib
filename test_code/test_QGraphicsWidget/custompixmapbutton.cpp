#include "custompixmapbutton.h"
#include <QGraphicsSceneMouseEvent>

CustomPixmapButton::CustomPixmapButton(int id,QGraphicsItem * parent)
    : QGraphicsPixmapItem(parent), m_btnRect(QRect(0,0,0,0)),m_state(STATE::UNCHOOSE),m_id(id)
{
    setCacheMode(DeviceCoordinateCache);
}

CustomPixmapButton::~CustomPixmapButton()
{

}

void CustomPixmapButton::resetPixmap()
{
    if(this->m_state == STATE::UNCHOOSE)
    {
        setPixmap(m_unchooseImg);
    }
    else
    {
        setPixmap(m_chooseImg);
    }
}

void CustomPixmapButton::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    setStateType(STATE::CHOOSE);
    setPixmap( m_chooseImg );

    emit sig_choose(m_id);

}

void CustomPixmapButton::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{	
    if(getStateType() == STATE::CHOOSE)
    {
        setPixmap( m_chooseImg );

        if( boundingRect().contains( event->pos() ))
        {
            //emit sig_mouse_released();
        }
    }
    else
    {
        setPixmap( m_unchooseImg );
    }

}

void CustomPixmapButton::mouseMoveEvent( QGraphicsSceneMouseEvent * event ) 
{
    QRect  frameRect = boundingRect().toRect();
    QPoint currPoint = event->pos().toPoint();

    if(getStateType() == STATE::CHOOSE)
    {
        if( !frameRect.contains( currPoint, true ) )
        {
            setPixmap(m_chooseImg );
        }
    }
    else
    {
        setPixmap( m_unchooseImg );
    }
}

void CustomPixmapButton::setImageFile( const QString& unchooseImg, const QString& chooseImg )
{
    m_unchooseImg = QPixmap( unchooseImg );
    m_chooseImg  = QPixmap( chooseImg );
    setPixmap( m_unchooseImg );
}


