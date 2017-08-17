#ifndef THREADLOALPIX_H
#define THREADLOALPIX_H

#include <QObject>
#include <QVector>
#include <QPixmap>

class ThreadLoalPix : public QObject
{
    Q_OBJECT
public:
    explicit ThreadLoalPix(QObject *parent = 0);
    ~ThreadLoalPix();

    void stopThread();

    inline QVector<QPixmap*> getVecPix(){return m_bgs;}

signals:
    void sig_loalPixFinished();

public slots:
    void slot_loalPix();

private:
    bool m_threadStopFlag;
    QVector<QPixmap*> m_bgs;
};

#endif // THREADLOALPIX_H
