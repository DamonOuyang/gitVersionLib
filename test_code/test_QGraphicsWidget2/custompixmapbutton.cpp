#include "custompixmapbutton.h"
#include <QGraphicsSceneMouseEvent>

CustomPixmapButton::CustomPixmapButton(int id
                                       ,QPoint posPiont
                                       ,const QString& unchooseImg
                                       ,const QString& chooseImg
                                       ,STATE::SELECT_STATE_TYPE state
                                       ,QGraphicsWidget * parent
                                       )
    : QGraphicsWidget(parent)
    , m_btnRect(QRect(0,0,0,0))
    , m_clickState(STATE::UNCHOOSE)
    , m_id(id)
    , m_posPiont(posPiont)
    , m_slectState(state)
{
    setCacheMode(DeviceCoordinateCache);
    setPos(m_posPiont);
    setImageFile(unchooseImg,chooseImg);
}

CustomPixmapButton::~CustomPixmapButton()
{

}

void CustomPixmapButton::mousePressEvent(QGraphicsSceneMouseEvent * event)
{
    if(m_slectState == STATE::SELECT_SINGLE)
    {
        setStateType(STATE::CHOOSE);
        emit sig_choose(m_id);
    }
    else
    {
        if(this->m_clickState == STATE::UNCHOOSE)
        {
            setStateType(STATE::CHOOSE);
            emit sig_choose(m_id);
        }
        else
        {
            setStateType(STATE::UNCHOOSE);
        }
    }
}

void CustomPixmapButton::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
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

void CustomPixmapButton::mouseMoveEvent( QGraphicsSceneMouseEvent * event )
{
    QRect  frameRect = boundingRect().toRect();
    QPoint currPoint = event->pos().toPoint();

    if(getStateType() == STATE::CHOOSE)
    {
        if( !frameRect.contains( currPoint, true ) )
        {

        }
    }
    else
    {

    }
}

void CustomPixmapButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(this->m_clickState == STATE::UNCHOOSE)
    {
        painter->drawPixmap(0 ,0  ,m_unchooseImg );
    }
    else
    {
        painter->drawPixmap(0 ,0 ,m_chooseImg);
    }
}

void CustomPixmapButton::setImageFile( const QString& unchooseImg, const QString& chooseImg )
{
    m_unchooseImg = QPixmap( unchooseImg );
    m_chooseImg  = QPixmap( chooseImg );
    m_btnRect.setWidth( m_unchooseImg.width() );
    m_btnRect.setHeight( m_unchooseImg.height() );
    resize(m_btnRect.width(),m_btnRect.height());
}

int CustomPixmapButton::getBntWidth()
{
    return m_btnRect.width();
}

int CustomPixmapButton::getBntHeight()
{
    return m_btnRect.height();
}


