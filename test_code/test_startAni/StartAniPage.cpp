#include "StartAniPage.h"
#include "pixloaled.h"

const int       POINT_X   = 900;
const int       POINT_Y   = 700;

StartAniPage::StartAniPage(QGraphicsWidget * parent)
    :QGraphicsWidget(parent)
    ,m_changePointTimer(NULL)
    ,m_curPointID(0)
{
//    if(!m_changePointTimer)
//        m_changePointTimer = new QTimer;
//    connect(m_changePointTimer , SIGNAL(timeout()) , this , SLOT(slot_changePoint()));
//    m_changePointTimer->start(1000);
}

void StartAniPage::slot_changePoint()
{
    ++m_curPointID;
    if(m_curPointID >= m_pointPixs.size())
        m_curPointID = 0;
    update();
}

QSizeF StartAniPage::getScreenSize()
{
    QSizeF screenSize;

    QGraphicsWidget* pParentView = dynamic_cast<QGraphicsWidget *>( parentItem());
    screenSize = pParentView ? pParentView->size() : size();
    return screenSize;
}

void StartAniPage::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF viewRect( 0, 0, getScreenSize().width(), getScreenSize().height());
    if( !m_pointPixs[m_curPointID]->isNull())
    {
        painter->drawPixmap(viewRect, *(m_pointPixs[m_curPointID]), QRectF(0, 0, m_pointPixs[m_curPointID]->width(), m_pointPixs[m_curPointID]->height()));
    }
    else
    {
        painter->fillRect( viewRect, QBrush(QColor(0,0,0)));
    }
}

StartAniPage::~StartAniPage()
{

}

