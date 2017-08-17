#ifndef CUSTOMPIXMAPBUTTONCTR_H
#define CUSTOMPIXMAPBUTTONCTR_H

#include <QList>
#include "custompixmapbutton.h"
#include <QGraphicsScene>
class CustomPixmapButtonCtr : public QObject
{
    Q_OBJECT

public:
    CustomPixmapButtonCtr(QObject *parent = 0);
	~CustomPixmapButtonCtr();

public:
    bool setDefaultChooseButtons(int* arr,int len);
    int  getCurrentChooseButton();
	void addButton2List(CustomPixmapButton * button);
	void clearButtonList();
    CustomPixmapButton * getOneButton(int id);


    void delButtonFromList(CustomPixmapButton * button);
    void delButtonFromList(int id);
    inline QList<CustomPixmapButton *> getButtonList(){return m_buttonList;}

public slots:
    void slot_chooseButton(int id);

signals:
    void sig_chooseThisButton(int id);

protected: 		


private:
    QList<CustomPixmapButton *> m_buttonList;

};

#endif 
