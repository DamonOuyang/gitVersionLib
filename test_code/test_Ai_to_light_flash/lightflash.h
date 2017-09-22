#ifndef LIGHTFLASH_H
#define LIGHTFLASH_H

#include <QGraphicsWidget>
#include <QTimer>
#include "singleton.h"

class CoffeeProductItem;
enum { ITEM_COUNT_TO_LIGHT = 10 };

enum LIGHT_TYPE
{
    ZERO = 0,
    ONE,
    TWO,
    TREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    NINE,
    TEN
};

typedef struct LIGHT_FLASH_STATE
{
    LIGHT_TYPE _runType;  // 2
    int _loop;            // 2
    int _time_offset;     // 300
    int _itemArr[ITEM_COUNT_TO_LIGHT]={0};

}Light_Flash_State;

class LightFlash : public QObject
{

    Q_OBJECT

    friend class singleton<LightFlash>;

private:
    LightFlash(QObject* parent = NULL);
    ~LightFlash();

public:
    static LightFlash * getInstance();
    static void releaseInstance();
    void init(QList<CoffeeProductItem*> productItemList,Light_Flash_State flshSate = NULL);
private:
    static LightFlash * m_instance;

public:
    void run();
    void stop();

    inline void setFlashState(Light_Flash_State* flshSate){m_flshSate = flshSate;}
    inline Light_Flash_State getFlashState(){return m_flshSate;}

signals:
    void sig_stop_this_light_type(int);

public slots:
    void slot_reflesh();

protected:
    void initProductItemState();
    void initFlashState(Light_Flash_State flshSate);
    void updateProductItemList();
    static void resetProductItemState_1();
    static void resetProductItemState_2();
    static void resetProductItemState_3();
    static void resetProductItemState_4();
    static void resetProductItemState_5();
    static void resetProductItemState_6();
    static void resetProductItemState_7();
    static void resetProductItemState_8();
    static void resetProductItemState_9();
    static void resetProductItemState_10();
    static void resetStateAll();
    static void resetStaticTypeVar();
    void ctrlLoopCount();

private:
    QTimer*             m_OffsetTimer;
    QList<CoffeeProductItem*> m_productItemList;
    Light_Flash_State*  m_flshSate;

    static int m_stateCount;
    static int m_ctrlLoop;

private:
    LightFlash(const LightFlash &rhs){}
    LightFlash& operator=(const LightFlash &rhs){}

};

//public:
//    LightFlash(QList<CoffeeProductItem*> productItemList,Light_Flash_State flshSate = NULL,QObject* parent = NULL);
//    ~LightFlash();

#endif // LIGHTFLASH_H
