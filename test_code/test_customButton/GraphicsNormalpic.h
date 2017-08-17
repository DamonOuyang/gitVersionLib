#ifndef GRAPHICSNORMALPIC_H
#define GRAPHICSNORMALPIC_H

#include <QGraphicsWidget>
#include <QPainter>

#include <vector>
using namespace std;


class GraphicsNormalPic : public QGraphicsWidget
{
	Q_OBJECT

		Q_PROPERTY(QPointF picPos READ getpicPos WRITE setpicPos);
	QPointF getpicPos();
	void         setpicPos(QPointF pos) ;
	struct textShow
	{
		QString str;
		int posX;
		int posY;
		QRectF rt;
		QColor color;
		QFont font;
		bool isuseRt;
	};
public:
	GraphicsNormalPic(const QString strMainPicPath , int posX , int posY ,QGraphicsItem *parent = 0);
	GraphicsNormalPic(QPixmap& pix , int posX , int posY ,QGraphicsItem *parent = 0 );
	~GraphicsNormalPic();

private:
	QPixmap m_MainPic;
	int m_nPosX;
	int m_nPosY;
	int m_nWight;
	int m_nHeigth;
	QRectF m_itemRt;
	QFont m_font;
	vector<textShow> m_TextList;
	bool    m_bIsShow;
	bool    m_bIsResetFont;
public:
	void setShow(bool show);
	int   getItemWigth();
	int   getItemHeight();
	virtual void setItemRect(int posX,int posY , int picW,int picH);
	virtual void paint(QPainter * painter,  const QStyleOptionGraphicsItem * option, QWidget * widget);
	virtual void setfont(QFont font);
	virtual void insertText(QString str,int x,int y , QColor color = QColor(80,80,80), int fontSize = 10 );
	virtual void insertText(QString str,QRectF rt, QColor color = QColor(80,80,80) , int fontSize= 10);
	virtual void setTextWeight(int weight);
	virtual void clearList();

	bool changeText(int num ,QString str);
	int getItemPosX();
	int getItemPosY();
	virtual QPixmap getItemMainPic();
	virtual QRectF getItemRect();
	virtual void setMianPic(QPixmap pic);
	QFont getFont();    
};

#endif // GRAPHICSNORMALPIC_H
