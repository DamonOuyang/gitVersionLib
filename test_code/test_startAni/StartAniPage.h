#ifndef STARTANIPAGE_H
#define STARTANIPAGE_H

#include <QPixmap>
#include <QGraphicsWidget>
#include <QGraphicsPixmapItem>
#include <QPainter>
#include <QPoint>
#include <QTimer>

class StartAniPage : public QGraphicsWidget
{
    Q_OBJECT
public:
    StartAniPage(QGraphicsWidget * parent = NULL);
    ~StartAniPage();

    QSizeF getScreenSize();
    inline void setPointPixVet(QVector<QPixmap*> pointVect){m_pointPixs = pointVect;}

Q_SIGNALS:

public slots:
    void slot_changePoint();

protected:
   virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

private:
    QVector<QPixmap*>                m_pointPixs;
    QTimer*				             m_changePointTimer;
    int                              m_curPointID;
};

#endif // STARTANIPAGE_H
