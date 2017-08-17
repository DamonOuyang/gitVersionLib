#ifndef CUSTOMPIXMAPBUTTON_H
#define CUSTOMPIXMAPBUTTON_H

#include <QPixmap>
#include <QGraphicsWidget>
#include <QPainter>
#include <QPoint>

namespace STATE {
    typedef enum
      {
        CHOOSE=0,
        UNCHOOSE
      } CLICK_STATE_TYPE;
    typedef enum
      {
        SELECT_SINGLE=0,
        SELECT_MULT
      }SELECT_STATE_TYPE;
}

class CustomPixmapButton : public QGraphicsWidget
{
	Q_OBJECT

public:
    CustomPixmapButton(int id,QPoint posPoint = QPoint(0,0)
            ,const QString& unchooseImg = NULL
            ,const QString& chooseImg = NULL
            ,STATE::SELECT_STATE_TYPE state=STATE::SELECT_SINGLE
            ,QGraphicsWidget * parent = NULL
            );

	~CustomPixmapButton();

    void setImageFile(  const QString& unchooseImg, const QString& chooseImg  );

    inline void setStateType( STATE::CLICK_STATE_TYPE state ){ m_clickState = state; update();}
    inline STATE::CLICK_STATE_TYPE getStateType(){return m_clickState;}
    inline void setID(int id){m_id = id;}
    inline int  getID(){return m_id;}
    inline void setSlectStateType( STATE::SELECT_STATE_TYPE state ){ m_slectState = state; update();}
    inline STATE::SELECT_STATE_TYPE getSlectType(){return m_slectState;}
    inline int getBntWidth();
    inline int getBntHeight();

Q_SIGNALS:
    //void sig_mouse_pressed(int id);
    //void sig_mouse_released();

    void sig_choose(int id);

protected: 		
	virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
	virtual void mouseReleaseEvent( QGraphicsSceneMouseEvent * event );
	virtual void mouseMoveEvent( QGraphicsSceneMouseEvent * event );
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:

    QRectF					         m_btnRect;
    QPixmap                          m_unchooseImg;
    QPixmap					         m_chooseImg;
    STATE::CLICK_STATE_TYPE          m_clickState;
    STATE::SELECT_STATE_TYPE         m_slectState;
    int                              m_id;
    QPoint                           m_posPiont;

};

#endif // CUSTOMPIXMAPBUTTON_H
