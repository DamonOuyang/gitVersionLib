#ifndef PIXLOALED_H
#define PIXLOALED_H

#include <QObject>
#include <QVector>
#include <QPixmap>

class pixLoaled : public QObject
{
    Q_OBJECT

public:
    static pixLoaled * getInstance();
    static void releaseInstance();

    bool loalCoffeeProgressPage();


    inline QVector<QPixmap> getBgs(){return m_bgs;}


signals:

public slots:

protected:
    explicit pixLoaled(QObject *parent = 0);
    ~pixLoaled();
    pixLoaled(const pixLoaled& other);
    pixLoaled& operator=(const pixLoaled &other);

private:
    static pixLoaled * m_instance;
    QVector<QPixmap> m_bgs;

};

#endif // PIXLOALED_H
