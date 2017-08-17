#include "GraphicsButton.h"
#include "FontManager.h"

GraphicsButton::GraphicsButton(const QString strName , const QString pixmapNorPath ,const QString pixmapPrsPath , int posX,int posY,QGraphicsItem *parent)
: GraphicsNormalPic(pixmapNorPath ,posX, posY,parent)
,m_bIsColorBush(false)
,m_isPressMode(false)
,m_textCol(QColor(255,255,255))
,m_pressTimer(NULL)
{
	m_bIsEnable = true;
	m_bIsPress = false;
	m_strButName = strName;
	setButtonPic(pixmapNorPath , pixmapPrsPath);
	m_font = FontManager::getOUIFont(FontManager::OUI_VERY_SMALL);
	m_font.setBold(true);
	m_nId = -1;

	m_timer = new QTimer(this);
	connect(m_timer , SIGNAL(timeout()) , this , SLOT(slot_check()));
}

GraphicsButton::~GraphicsButton()
{

}

void GraphicsButton::setButName(QString strName)
{
	m_strButName = strName;
}

void GraphicsButton::setButtonPic( QString strNormalPath, const QString  strPressPath )
{
	m_imgNormal.load(strNormalPath);
	m_imgPress.load(strPressPath);
}

void GraphicsButton::setButtonPic(const QPixmap normalPix , const QPixmap pressPix)
{
	m_imgNormal = normalPix;
	m_imgPress  = pressPix;
}

void GraphicsButton::paint(QPainter * painter,  const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	if (m_bIsEnable == false)
	{
		if (m_imgDisable.isNull() == false)
		{
			painter->drawPixmap(0 ,0 ,m_imgDisable);
		}
		else
		{
			painter->drawPixmap(0 ,0  ,m_imgNormal );
		}
	}
	else
	{
		if (m_bIsPress)
		{
			painter->drawPixmap(0 ,0  ,m_imgPress );
		}
		else
		{
			painter->drawPixmap(0 ,0 ,m_imgNormal);
		}

		if (m_bIsColorBush)
		{
			painter->setPen(QColor(150, 150, 150));
			painter->drawRect(0,0,m_imgPress.width(), m_imgPress.height());
			painter->fillRect(1,1,m_imgPress.width()-1,m_imgPress.height()-1,m_bushColor);
		}
	}
	QRectF rt;
	rt.setRect(0,0,getItemWigth(),getItemHeight());

	painter->setPen(m_textCol);
	painter->setFont(m_font);
	painter->drawText(rt, Qt::AlignCenter , m_strButName);
}

void GraphicsButton::setFont(QFont font)
{
	m_font = font;
}

void GraphicsButton::mousePressEvent(QGraphicsSceneMouseEvent * event)
{	  	 
	
	if (m_bIsEnable == false)
	{
		return;
	}
	m_bIsPress = true;
	update();
	if (m_isPressMode && m_pressTimer)
	{
		m_pressTimer->start(100);
	}
	emit butOn();
}

void GraphicsButton::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
	if (m_bIsEnable == false)
	{
		return;
	}
	if (m_isPressMode && m_pressTimer)
	{
		m_pressTimer->stop();
	}
	if (m_bIsPress == true)
	{
		m_bIsPress = false;
		update();
		if (QRectF(0,0,getItemWigth(),getItemHeight()).contains(event->pos().x() , event->pos().y()))
		{
			emit butPressed();
		}
	}
}

void GraphicsButton::mouseMoveEvent ( QGraphicsSceneMouseEvent * event )
{
	int posx = event->pos().x();
	int posy = event->pos().y();
	if (!boundingRect().contains(posx , posy))
	{
		emit mouseOut();
		m_bIsPress = false;
		update();
	}
}

void GraphicsButton::setId(int id)
{
	m_nId = id;
}

int GraphicsButton::getId()
{
	return m_nId;
}

void GraphicsButton::setEnabled(bool enable)
{
	m_bIsEnable = enable;
	update();
}

void GraphicsButton::setColorBush(bool b)
{
	m_bIsColorBush = b;
}

void GraphicsButton::setTextCol(QColor col)
{
	m_textCol = col;
}

void GraphicsButton::getColorBush(QColor color)
{
	m_bushColor = color;
}

void GraphicsButton::slot_check()
{
	if (m_bIsPress)
	{
		emit butOn();
	}
}

void GraphicsButton::setLongPressMode()
{
	m_timer->start(50);
}

void GraphicsButton::setDisableImg( QString path )
{
	m_imgDisable.load(path);
	update();
}

void GraphicsButton::setPressMode()
{
	m_isPressMode = true;
	m_pressTimer = new QTimer(this);
	connect(m_pressTimer , SIGNAL(timeout()) , this , SLOT(slot_Pressed()));
}

void GraphicsButton::slot_Pressed()
{
	if (m_bIsPress)
	{
		emit butPressed();
	}
}
