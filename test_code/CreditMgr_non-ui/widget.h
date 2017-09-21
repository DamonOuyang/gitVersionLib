#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class LineEdit;
class PushButton;
class Label;
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

    bool CheckCard();
    void init();

private slots:
     void on_OpnRdr_Btn_clicked();

     void on_ShwName_Btn_clicked();

     void on_ClsRdr_Btn_clicked();

    void on_Intliz_Btn_clicked();

     void on_ChngName_Btn_clicked();

    void on_SrlNmbr_Btn_clicked();

    void on_Charge_Btn_clicked();

    void on_Recharge_Btn_clicked();

    void on_Blnc_Btn_clicked();

    void on_Data_Btn_clicked();

    void slot_check_Card();

private:
    QTimer * m_pCheckCardTimer;

private:
    /*Info*/
    Label      * m_pLabelDevStaMark;
    Label      * m_pLabelDevSta;
    Label      * m_pLabelCardStaMark;
    Label      * m_pLabelCardSta;
    PushButton * m_pShwNmeBtn;
    Label      * m_pLabelShwNme;

    /*2*/
    PushButton * m_pChgNmeBtn;
    LineEdit   * m_pNmLnEdt;
    PushButton * m_pBalnBtn;
    LineEdit   * m_pBalnEdt;

    /*Admi*/
    PushButton * m_pSralNumBtn;
    LineEdit   * m_pSralNumEdt;

    PushButton * m_pDataBtn;
    LineEdit   * m_pDataEdt;

    /*Operation*/
    PushButton * m_pOpnRderBtn;
    PushButton * m_pCloRderBtn;

    PushButton * m_pInitBtn;
    PushButton * m_pRechargeBtn;
    LineEdit   * m_pRechargeEdt;

    PushButton * m_pChargeBtn;
    LineEdit   * m_pChargeEdt;


};

#endif // WIDGET_H
