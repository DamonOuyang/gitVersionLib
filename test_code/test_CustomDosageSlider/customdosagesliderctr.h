#ifndef CUSTOMDOSAGESSLIDERCTR_H
#define CUSTOMDOSAGESSLIDERCTR_H

#include <QObject>
#include <QList>

class CustomDosageSlider;
class CustomDosagesSliderCtr : public QObject
{
    Q_OBJECT

public:
    CustomDosagesSliderCtr(QObject *parent = 0);
    ~CustomDosagesSliderCtr();

public:
    void setDefaultChooseButton(int id);
    int  getCurrentChooseButton();
    void addButton2List(CustomDosageSlider * button);
    void clearButtonList();
    CustomDosageSlider * getOneButton(int id);


    void delButtonFromList(CustomDosageSlider * button);
    void delButtonFromList(int id);
    inline QList<CustomDosageSlider *> getButtonList(){return m_buttonList;}

public slots:
    void slot_chooseButton(int id);

signals:
    void sig_chooseThisButton(int id);

protected:


private:
    QList<CustomDosageSlider *> m_buttonList;

};

#endif // CUSTOMDOSAGESSLIDERCTR_H
