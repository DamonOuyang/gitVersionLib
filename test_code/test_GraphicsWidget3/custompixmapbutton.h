#ifndef SHOWBUTTON_H
#define SHOWBUTTON_H


#include <QGraphicsWidget>
#include <QPixmap>

namespace STATE {
    typedef enum
      {
        CHOOSE=0,
        UNCHOOSE
      } STATE_TYPE;
}

class QGraphicsSceneMouseEvent;
class QGraphicsSceneHoverEvent;
class CustomPixmapButton: public QGraphicsWidget
{
    Q_OBJECT
public:
    enum State { NormalState, HoverState, PressedState };
    enum Style { TextOnly, IconOnly, TextBesidesIcon, TextUnderIcon};
public:
    CustomPixmapButton(int id,const QPixmap &, const QPixmap &, const QPixmap &);
    void setText(const QString &, const QFont &, const QColor &);
    void setIcon(const QPixmap& icon);
    void setStyle(Style style);
    QString getText();
    void resetPixmap();

    inline void setStateType( STATE::STATE_TYPE state ){ m_state = state;}
    inline STATE::STATE_TYPE getStateType(){return m_state;}
    inline void setID(int id){m_id = id;}
    inline int  getID(){return m_id;}

signals:
    void clicked();
    void sig_choose(int id);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *e);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *e);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *e);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *);
protected:
    virtual QRectF boundingRect();
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
private:
    void setPixmap(State state);
private:
    int m_cnt;
    int m_id;
    bool m_isPressed;
    bool m_iconOn;
    bool m_textOn;
    QPixmap m_pixmap;
    QPixmap m_normalPixmap;
    QPixmap m_hoverPixmap;
    QPixmap m_pressedPixmap;
    QPixmap m_icon;
    QString m_text;
    QSize m_size;
    QFont m_font;
    QColor m_color;
    Style m_style;

    STATE::STATE_TYPE       m_state;

};
#endif // SHOWBUTTON_H www.it165.net
