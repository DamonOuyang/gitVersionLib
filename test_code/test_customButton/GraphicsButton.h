#ifndef QGRAPHICSBUTTON_H
#define QGRAPHICSBUTTON_H

#include "GraphicsNormalpic.h"
#include <QGraphicsSceneMouseEvent>
#include <QTimer>

class GraphicsButton : public GraphicsNormalPic
{
	Q_OBJECT

public:
	GraphicsButton(QString strName ,const QString pixmapNorPath ,const QString pixmapPrsPath , int posX,int posY, QGraphicsItem *parent = 0 );
	~GraphicsButton();

private:
	QPixmap m_imgNormal;
	QPixmap m_imgPress;
	QPixmap m_imgDisable;
	QString m_strButName;
	bool m_bIsPress;
	int m_nId;
	bool m_bIsEnable;
	bool m_bIsColorBush;
	QFont m_font;
	QColor m_bushColor;
	QColor m_textCol;
	QTimer* m_timer;
	bool   m_isPressMode;
	QTimer* m_pressTimer;
public:
	void setColorBush(bool b);
	void setButName(const QString strName);
	void setButtonPic(const QString strNormalPath , const QString  strPressPath);
	void setButtonPic(const QPixmap normalPix , const QPixmap pressPix);
	void paint(QPainter * painter,  const QStyleOptionGraphicsItem * option, QWidget * widget);
	void mousePressEvent(QGraphicsSceneMouseEvent * event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);
	void mouseMoveEvent ( QGraphicsSceneMouseEvent * event );
	void setEnabled(bool enable);
	void setId(int id);
	int getId();
	void setFont(QFont font);
	void getColorBush(QColor color);
	void setTextCol(QColor col);
	void setLongPressMode();
	void setDisableImg(QString path);
	void setPressMode();
	QString getName(){return m_strButName;}
signals:
	void butPressed();
	void butOn();
	void mouseOut();
public slots:
	void slot_check();
	void slot_Pressed();

};
#endif // GRAPHICSBUTTON_H
