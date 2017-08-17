#ifndef CUSTOMDOSAGESLIDER_H
#define CUSTOMDOSAGESLIDER_H

#include <QPixmap>
#include <QGraphicsWidget>
#include <QPainter>
#include <QPoint>

namespace STATE {
    typedef enum
      {
        CHOOSE=0,
        UNCHOOSE
      } STATE_TYPE;
}

enum {BGWIDTH=151 ,BGHEIGHT=94/*30*/ ,SLIDERWIDTH=94 ,SLIDERHEIGHT=94 };

class CustomDosageSlider : public QGraphicsWidget
{
    Q_OBJECT
public:
    CustomDosageSlider(int id,QGraphicsWidget * parent = NULL);
    ~CustomDosageSlider();

    void setImageFile(  const QString& m_bgImg, const QString& m_sliderImg  );
    void resetPixmap();
    inline void setStateType( STATE::STATE_TYPE state ){ m_state = state;}
    inline STATE::STATE_TYPE getStateType(){return m_state;}
    inline void setID(int id){m_id = id;}
    inline int  getID(){return m_id;}

Q_SIGNALS:
    void sig_choose(int id);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent * event);
    virtual void mouseReleaseEvent( QGraphicsSceneMouseEvent * event );
    virtual void mouseMoveEvent( QGraphicsSceneMouseEvent * event );
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QRectF					m_btnRect;

    QPixmap                 m_bgImg;
    QPixmap					m_sliderImg;

    STATE::STATE_TYPE       m_state;
    int                     m_id;
    QPoint                  m_sliderPoint;

};


#endif // CUSTOMDOSAGESLIDER_H
