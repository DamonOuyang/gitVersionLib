#ifndef DOSAGESLIDER_H
#define DOSAGESLIDER_H

#include <QObject>
#include <QSlider>

class DosageSlider : public QSlider
{
    Q_OBJECT
public:
    DosageSlider(QWidget *parent=0);
    ~DosageSlider();

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

private:



};

#endif // DOSAGESLIDER_H
