#ifndef CUSTOMPIXMAPBUTTON_H
#define CUSTOMPIXMAPBUTTON_H

#include <QGraphicsPixmapItem>
#include <QPixmap>

namespace STATE {
    typedef enum
      {
        CHOOSE=0,
        UNCHOOSE
      } STATE_TYPE;
}

class CustomPixmapButton : public QObject, public QGraphicsPixmapItem
{
	Q_OBJECT

public:
    CustomPixmapButton(int id,QGraphicsItem * parent = NULL);
	~CustomPixmapButton();
    void setImageFile(  const QString& unchooseImg, const QString& chooseImg  );
    void resetPixmap();

    inline void setStateType( STATE::STATE_TYPE state ){ m_state = state;}
    inline STATE::STATE_TYPE getStateType(){return m_state;}
    inline void setID(int id){m_id = id;}
    inline int  getID(){return m_id;}

Q_SIGNALS:
    //void sig_mouse_pressed(int id);
    //void sig_mouse_released();

    void sig_choose(int id);

protected: 		
	virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
	virtual void mouseReleaseEvent( QGraphicsSceneMouseEvent * event );
	virtual void mouseMoveEvent( QGraphicsSceneMouseEvent * event );

private:
	QRectF					m_btnRect;	
    QPixmap                 m_unchooseImg;
    QPixmap					m_chooseImg;
    STATE::STATE_TYPE       m_state;
    int                     m_id;
};

#endif // CUSTOMPIXMAPBUTTON_H
