#include "GraphicsNormalpic.h"
#include "FontManager.h"

GraphicsNormalPic::GraphicsNormalPic(const QString strMainPicPath , int posX , int posY,QGraphicsItem *parent)
: QGraphicsWidget(parent)
,m_bIsResetFont(false)
{
	m_MainPic.load(strMainPicPath);
	m_nWight = m_MainPic.width();
	m_nHeigth = m_MainPic.height();
	m_nPosX = posX;
	m_nPosY = posY;
	m_bIsShow = true;
	setItemRect (m_nPosX , m_nPosY ,m_nWight ,m_nHeigth );
	setfont(FontManager::getOUIFont());
}

GraphicsNormalPic::GraphicsNormalPic( QPixmap& pix , int posX , int posY ,QGraphicsItem *parent /*= 0 */ )
: QGraphicsWidget(parent)
,m_bIsResetFont(false)
{
	m_MainPic = pix;
	m_nWight = m_MainPic.width();
	m_nHeigth = m_MainPic.height();
	m_nPosX = posX;
	m_nPosY = posY;
	m_bIsShow = true;
	setItemRect (m_nPosX , m_nPosY ,m_nWight ,m_nHeigth );
	setfont(FontManager::getOUIFont());
}

GraphicsNormalPic::~GraphicsNormalPic()
{
	m_TextList.clear();
}

void GraphicsNormalPic::setShow(bool isShow)
{
	m_bIsShow = isShow;
}
bool GraphicsNormalPic::changeText(int num ,QString str)
{
	if ((int)m_TextList.size() <= num)
	{
		return false;
	}
	m_TextList[num].str = str;
	update();
	return true;
}

void GraphicsNormalPic::setItemRect( int posX,int posY , int picW,int picH )
{
	m_itemRt.setRect(posX,posY,picW,picH);
	moveBy(m_nPosX , m_nPosY);
	resize(m_nWight ,m_nHeigth);
}

void GraphicsNormalPic::paint(QPainter * painter,  const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	if (m_bIsShow == false)
	{
		return;
	}
	painter->setRenderHint(QPainter::Antialiasing);
	painter->drawPixmap(0 ,0 ,m_MainPic);

	QRectF rt;
	rt.setRect(0,0,m_nWight,m_nHeigth);

	vector<textShow>::iterator it = m_TextList.begin();
	for (;it!= m_TextList.end(); it++)
	{
		painter->setPen((*it).color);
		if (!m_bIsResetFont)
			painter->setFont((*it).font);
		else
			painter->setFont(m_font);
		if ((*it).isuseRt == false)
		{
			painter->drawText(QPointF((*it).posX , (*it).posY) , (*it).str);
		}
		else
		{
			painter->drawText((*it).rt, Qt::AlignVCenter | Qt::AlignHCenter | Qt::TextWordWrap, (*it).str);
		}
	}
}

void GraphicsNormalPic::setfont(QFont font)
{
	m_font = font;
	m_bIsResetFont = true;
}

void GraphicsNormalPic::insertText(QString str,int x,int y,QColor color ,int fontSize)
{
	textShow tmp;
	tmp.posX = x;
	tmp.posY = y;
	tmp.str = str;
	tmp.color = color;
	m_font.setPixelSize(fontSize);
	tmp.font = m_font;
	tmp.isuseRt = false;
	m_TextList.push_back(tmp);
	update();
}

void GraphicsNormalPic::insertText(QString str,QRectF rt , QColor color, int fontSize)
{
	textShow tmp;
	tmp.rt = rt;
	tmp.str = str;
	tmp.color = color;
	m_font.setPixelSize(fontSize);
	tmp.font = m_font;
	tmp.isuseRt = true;
	m_TextList.push_back(tmp);
	update();
}

void GraphicsNormalPic::clearList()
{
	m_TextList.clear();
}

int  GraphicsNormalPic::getItemWigth()
{
	return m_nWight;
}

int  GraphicsNormalPic::getItemHeight()
{
	return m_nHeigth;
}

int GraphicsNormalPic::getItemPosX()
{
	return m_nPosX;
}

int GraphicsNormalPic::getItemPosY()
{
	return m_nPosY;
}

QPixmap GraphicsNormalPic::getItemMainPic()
{
	return m_MainPic;
}

QRectF  GraphicsNormalPic::getItemRect()
{
	return m_itemRt;
}

void GraphicsNormalPic::setMianPic(QPixmap pic)
{
	m_MainPic = pic;
}

QFont GraphicsNormalPic::getFont()
{
	return m_font;
}

QPointF GraphicsNormalPic::getpicPos()
{
	return QPointF(getItemPosX(),getItemPosY());
}
void    GraphicsNormalPic::setpicPos(QPointF pos)
{
	setPos(pos);
}

void GraphicsNormalPic::setTextWeight(int weight)
{
	m_font.setWeight(weight);
}