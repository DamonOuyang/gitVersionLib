#include "lightflash.h"
#include "CoffeeProductItem.h"

int LightFlash::m_stateCount = 0;
int LightFlash::m_ctrlLoop = 0;

LightFlash::LightFlash(QObject* parent)
    :QObject(parent)
{

}

LightFlash::~LightFlash()
{
    if(m_OffsetTimer->isActive())
    {
        m_OffsetTimer->stop();
        m_OffsetTimer->deleteLater();
        m_OffsetTimer = NULL;
    }
}

void LightFlash::initFlashState(Light_Flash_State flshSate)
{
    if(!flshSate)
    {
        int Arr[ITEM_COUNT_TO_LIGHT] = {0,1,2,3,4,5,6,7,8,9};
        m_flshSate->_runType = 1;                // 1
        m_flshSate->_loop    = 10000;            // 2
        m_flshSate->_time_offset = 500;          // 300
        for(int i=0; i < sizeof(Arr)/sizeof(*Arr);++i)
        {
            m_flshSate->_itemArr[i] = Arr[i];
        }
    }
    else
    {
        m_flshSate->_runType     = flshSate._runType;         // 2
        m_flshSate->_loop        = flshSate._loop;            // 2
        m_flshSate->_time_offset = flshSate._time_offset;     // 300
        for(int i=0; i < sizeof(flshSate._itemArr)/sizeof(flshSate._itemArr[0]);++i)
        {
            m_flshSate->_itemArr[i] = flshSate._itemArr[i];
        }
    }
}

void LightFlash::slot_reflesh()
{
    /*set the product item state to unpress*/
    initProductItemState();

    /*reset the product item state to flash*/
    resetStateAll();

    /*update the view*/
    updateProductItemList();
}

void LightFlash::run()
{
    m_OffsetTimer->start(m_flshSate._time_offset);
}

void LightFlash::stop()
{
    m_OffsetTimer->stop();
    resetStaticTypeVar();
}

void LightFlash::resetStaticTypeVar()
{
   m_stateCount = 0;
   m_ctrlLoop = 0;
}

void LightFlash::initProductItemState()
{
    foreach (item, m_productItemList)
    {
        item->setPressState(false);
    }
}

void LightFlash::updateProductItemList()
{
    foreach (item, m_productItemList)
    {
        item->update();
    }
}

void LightFlash::ctrlLoopCount()
{
    if(m_flshSate->_loop != m_ctrlLoop )
        return;
    else
    {
        m_ctrlLoop = 0;
        stop();
        emit sig_stop_this_light_type(m_flshSate->_runType);
    }
}

void LightFlash::resetProductItemState_1()
{
    /*set the product item of state to press state */
    switch (m_stateCount) {
    case ZERO:
        m_productItemList[m_flshSate.itemArr[ZERO]].setPressState(true);
        break;
    case ONE:
        m_productItemList[m_flshSate.itemArr[ONE]].setPressState(true);
        break;
    case TWO:
        m_productItemList[m_flshSate.itemArr[TWO]].setPressState(true);
        break;
    case TREE:
        m_productItemList[m_flshSate.itemArr[TREE]].setPressState(true);

        break;
    case FOUR:
        m_productItemList[m_flshSate.itemArr[FOUR]].setPressState(true);

        break;
    case FIVE:
        m_productItemList[m_flshSate.itemArr[FIVE]].setPressState(true);

        break;
    case SIX:
        m_productItemList[m_flshSate.itemArr[SIX]].setPressState(true);

        break;
    case SEVEN:
        m_productItemList[m_flshSate.itemArr[SEVEN]].setPressState(true);

        break;
    case EIGHT:
        m_productItemList[m_flshSate.itemArr[EIGHT]].setPressState(true);

        break;
    case NINE:
        m_productItemList[m_flshSate.itemArr[NINE]].setPressState(true);

        break;
    default:
        break;
    }

    ++m_stateCount;
    if(m_stateCount == ITEM_COUNT_TO_LIGHT/m_flshSate->_runType)
    {
        ++m_ctrlLoop;
        m_stateCount = 0;
    }

    ctrlLoopCount();
}

void LightFlash::resetProductItemState_2()
{
    /*set the product item of state to press state */
    switch (m_stateCount) {
    case ZERO:
        m_productItemList[m_flshSate.itemArr[ZERO]].setPressState(true);
        m_productItemList[m_flshSate.itemArr [ONE]].setPressState(true);

        break;
    case ONE:
        m_productItemList[m_flshSate.itemArr [TWO]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[TREE]].setPressState(true);

        break;
    case TWO:
        m_productItemList[m_flshSate.itemArr[FOUR]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[FIVE]].setPressState(true);

        break;
    case TREE:
        m_productItemList[m_flshSate.itemArr  [SIX]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[SEVEN]].setPressState(true);

        break;
    case FOUR:
        m_productItemList[m_flshSate.itemArr[EIGHT]].setPressState(true);
        m_productItemList[m_flshSate.itemArr [NINE]].setPressState(true);
        break;

    default:
        break;
    }
    ++m_stateCount;
    if(m_stateCount == ITEM_COUNT_TO_LIGHT/m_flshSate->_runType)
    {
        m_stateCount = 0;
    }
}

void LightFlash::resetProductItemState_3()
{
    /*set the product item of state to press state */
    switch (m_stateCount) {
    case ZERO:
        m_productItemList[m_flshSate.itemArr[ZERO]].setPressState(true);
        m_productItemList[m_flshSate.itemArr [ONE]].setPressState(true);
        m_productItemList[m_flshSate.itemArr [TWO]].setPressState(true);

        break;
    case ONE:
        m_productItemList[m_flshSate.itemArr[TREE]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[FOUR]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[FIVE]].setPressState(true);

        break;
    case TWO:
        m_productItemList[m_flshSate.itemArr  [SIX]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[SEVEN]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[EIGHT]].setPressState(true);
        break;
    case TREE:
        m_productItemList[m_flshSate.itemArr [NINE]].setPressState(true);
        break;

    default:
        break;
    }
    ++m_stateCount;
    if(m_stateCount == ITEM_COUNT_TO_LIGHT/m_flshSate->_runType)
    {
        m_stateCount = 0;
    }
}

void LightFlash::resetProductItemState_4()
{
    /*set the product item of state to press state */
    switch (m_stateCount) {
    case ZERO:
        m_productItemList[m_flshSate.itemArr[ZERO]].setPressState(true);
        m_productItemList[m_flshSate.itemArr [ONE]].setPressState(true);
        m_productItemList[m_flshSate.itemArr [TWO]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[TREE]].setPressState(true);

        break;
    case ONE:
        m_productItemList[m_flshSate.itemArr[FOUR]];
        m_productItemList[m_flshSate.itemArr[FIVE]];
        m_productItemList[m_flshSate.itemArr  [SIX]];
        m_productItemList[m_flshSate.itemArr[SEVEN]];

        break;
    case TWO:
        m_productItemList[m_flshSate.itemArr[EIGHT]];
        m_productItemList[m_flshSate.itemArr [NINE]];
        break;

    default:
        break;
    }
    ++m_stateCount;
    if(m_stateCount == ITEM_COUNT_TO_LIGHT/m_flshSate->_runType)
    {
        m_stateCount = 0;
    }
}

void LightFlash::resetProductItemState_5()
{
    /*set the product item of state to press state */
    switch (m_stateCount) {
    case ZERO:
        m_productItemList[m_flshSate.itemArr[ZERO]].setPressState(true);
        m_productItemList[m_flshSate.itemArr [ONE]].setPressState(true);
        m_productItemList[m_flshSate.itemArr [TWO]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[TREE]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[FOUR]].setPressState(true);

        break;
    case ONE:
        m_productItemList[m_flshSate.itemArr[FIVE]].setPressState(true);
        m_productItemList[m_flshSate.itemArr  [SIX]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[SEVEN]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[EIGHT]].setPressState(true);
        m_productItemList[m_flshSate.itemArr [NINE]].setPressState(true);

        break;

    default:
        break;
    }
    ++m_stateCount;
    if(m_stateCount == ITEM_COUNT_TO_LIGHT/m_flshSate->_runType)
    {
        m_stateCount = 0;
    }
}

void LightFlash::resetProductItemState_6()
{
    /*set the product item of state to press state */
    switch (m_stateCount) {
    case ZERO:
        m_productItemList[m_flshSate.itemArr[ZERO]].setPressState(true);
        m_productItemList[m_flshSate.itemArr [ONE]].setPressState(true);
        m_productItemList[m_flshSate.itemArr [TWO]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[TREE]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[FOUR]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[FIVE]].setPressState(true);

        break;
    case ONE:
        m_productItemList[m_flshSate.itemArr  [SIX]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[SEVEN]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[EIGHT]].setPressState(true);
        m_productItemList[m_flshSate.itemArr [NINE]].setPressState(true);

        break;

    default:
        break;
    }
    ++m_stateCount;
    if(m_stateCount == (ITEM_COUNT_TO_LIGHT/m_flshSate->_runType) + 1 )
    {
        m_stateCount = 0;
    }
}

void LightFlash::resetProductItemState_7()
{
    /*set the product item of state to press state */
    switch (m_stateCount) {
    case ZERO:
        m_productItemList[m_flshSate.itemArr[ZERO]].setPressState(true);
        m_productItemList[m_flshSate.itemArr [ONE]].setPressState(true);
        m_productItemList[m_flshSate.itemArr [TWO]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[TREE]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[FOUR]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[FIVE]].setPressState(true);
        m_productItemList[m_flshSate.itemArr  [SIX]].setPressState(true);

        break;
    case ONE:
        m_productItemList[m_flshSate.itemArr[SEVEN]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[EIGHT]].setPressState(true);
        m_productItemList[m_flshSate.itemArr [NINE]].setPressState(true);

        break;

    default:
        break;
    }
    ++m_stateCount;
    if(m_stateCount == (ITEM_COUNT_TO_LIGHT/m_flshSate->_runType) + 1 )
    {
        m_stateCount = 0;
    }
}

void LightFlash::resetProductItemState_8()
{
    /*set the product item of state to press state */
    switch (m_stateCount) {
    case ZERO:
        m_productItemList[m_flshSate.itemArr[ZERO]].setPressState(true);
        m_productItemList[m_flshSate.itemArr [ONE]].setPressState(true);
        m_productItemList[m_flshSate.itemArr [TWO]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[TREE]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[FOUR]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[FIVE]].setPressState(true);
        m_productItemList[m_flshSate.itemArr  [SIX]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[SEVEN]].setPressState(true);

        break;
    case ONE:

        m_productItemList[m_flshSate.itemArr[EIGHT]].setPressState(true);
        m_productItemList[m_flshSate.itemArr [NINE]].setPressState(true);

        break;

    default:
        break;
    }
    ++m_stateCount;
    if(m_stateCount == (ITEM_COUNT_TO_LIGHT/m_flshSate->_runType) + 1 )
    {
        m_stateCount = 0;
    }
}

void LightFlash::resetProductItemState_9()
{
    /*set the product item of state to press state */
    switch (m_stateCount) {
    case ZERO:
        m_productItemList[m_flshSate.itemArr[ZERO]].setPressState(true);
        m_productItemList[m_flshSate.itemArr [ONE]].setPressState(true);
        m_productItemList[m_flshSate.itemArr [TWO]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[TREE]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[FOUR]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[FIVE]].setPressState(true);
        m_productItemList[m_flshSate.itemArr  [SIX]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[SEVEN]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[EIGHT]].setPressState(true);

        break;
    case ONE:

        m_productItemList[m_flshSate.itemArr [NINE]].setPressState(true);

        break;

    default:
        break;
    }
    ++m_stateCount;
    if(m_stateCount == (ITEM_COUNT_TO_LIGHT/m_flshSate->_runType) + 1 )
    {
        m_stateCount = 0;
    }
}

void LightFlash::resetProductItemState_10()
{
    /*set the product item of state to press state */
    switch (m_stateCount) {
    case ZERO:
        m_productItemList[m_flshSate.itemArr[ZERO]].setPressState(true);
        m_productItemList[m_flshSate.itemArr [ONE]].setPressState(true);
        m_productItemList[m_flshSate.itemArr [TWO]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[TREE]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[FOUR]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[FIVE]].setPressState(true);
        m_productItemList[m_flshSate.itemArr  [SIX]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[SEVEN]].setPressState(true);
        m_productItemList[m_flshSate.itemArr[EIGHT]].setPressState(true);
        m_productItemList[m_flshSate.itemArr [NINE]].setPressState(true);

        break;

    default:
        break;
    }
    ++m_stateCount;
    if(m_stateCount == (ITEM_COUNT_TO_LIGHT/m_flshSate->_runType))
    {
        m_stateCount = 0;
    }
}

void LightFlash::resetStateAll()
{
    switch (m_flshSate->_runType)
    {
    case ONE:
        resetProductItemState_1();

        break;
    case TWO:
        resetProductItemState_2();

        break;
    case TREE:
        resetProductItemState_3();

        break;
    case FOUR:
        resetProductItemState_4();

        break;
    case FIVE:
        resetProductItemState_5();

        break;
    case SIX:
        resetProductItemState_6();

        break;
    case SEVEN:
        resetProductItemState_7();

        break;
    case EIGHT:
        resetProductItemState_8();

        break;
    case NINE:
        resetProductItemState_9();

        break;
    case TEN:
        resetProductItemState_10();

        break;
    default:
        break;
    }
}

void LightFlash::init(QList<CoffeeProductItem*> productItemList,Light_Flash_State flshSate)
{
    m_productItemList = productItemList;
    initFlashState(flshSate);
    m_OffsetTimer = new QTimer(this);
    connect(m_OffsetTimer,SIGNAL(timeout()),this,SLOT(slot_reflesh()));
}

LightFlash * LightFlash::getInstance()
{
    if(NULL == m_instance)
    {
        m_instance = new LightFlash;
    }

    return m_instance;
}

void LightFlash::releaseInstance()
{
    if(NULL != m_instance)
    {
        delete m_instance;
        m_instance = NULL;
    }
}


//LightFlash::LightFlash(QList<CoffeeProductItem*> productItemList,Light_Flash_State flshSate,QObject* parent)
//    :QObject(parent)
//    ,m_productItemList(productItemList)
//{
//    initFlashState(flshSate);
//    m_OffsetTimer = new QTimer(this);
//    connect(m_OffsetTimer,SIGNAL(timeout()),this,SLOT(slot_reflesh()));

//}
