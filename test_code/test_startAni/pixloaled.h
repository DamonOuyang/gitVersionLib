#ifndef PIXLOALED_H
#define PIXLOALED_H

#include <QObject>
#include <QVector>
#include <QPixmap>

class PixmapMgr;
class pixLoaled : public QObject
{
    Q_OBJECT

public:
    static pixLoaled * getInstance();
    static void releaseInstance();

    bool loalCoffeeProgressPage();
	bool loalStateViewPage();
	bool loalPixforAni(int count);

    inline QVector<QPixmap*> getBgs(){return m_bgs;}
    inline QVector<QPixmap*> getPointPixs(){return m_pointPixs;}


signals:

public slots:

protected:
    explicit pixLoaled(QObject *parent = 0);
    ~pixLoaled();
    pixLoaled(const pixLoaled& other);
    pixLoaled& operator=(const pixLoaled &other);

private:
    static pixLoaled * m_instance;
    QVector<QPixmap*>   m_bgs;
    QVector<QPixmap*>   m_pointPixs;
};

#endif // PIXLOALED_H
