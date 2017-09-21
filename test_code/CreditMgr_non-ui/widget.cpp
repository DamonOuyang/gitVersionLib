#include "widget.h"
#include "lineedit.h"
#include "pushbutton.h"
#include "label.h"

#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QTimer>
#include <QThread>
#include <string.h>

extern "C" {
#include "SDT_VC.h"
}

enum {TIME_OUT_TO_CHRCK_CARD = 1000*3};

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->resize(800,800);
    m_pCheckCardTimer = new QTimer(this);
    connect(m_pCheckCardTimer,SIGNAL(timeout()),this,SLOT(slot_check_Card()));
    init();
}

void Widget::init()
{
    /*Info*/
    m_pLabelDevStaMark = new Label();
    m_pLabelDevSta     = new Label();
    m_pLabelDevStaMark->setText("Device Statue: ");
    m_pLabelDevSta->setText("Off");
    m_pLabelDevStaMark->move(20,20);
    m_pLabelDevSta->move(150,20);
    m_pLabelDevStaMark->setParent(this);
    m_pLabelDevSta->setParent(this);

    m_pLabelCardStaMark = new Label();
    m_pLabelCardSta     = new Label();
    m_pLabelCardStaMark->setText("Card Statue/ID: ");
    m_pLabelCardSta->setText("No Card Found");
    m_pLabelCardStaMark->move(20,50);
    m_pLabelCardSta->move(150,50);
    m_pLabelCardStaMark->setParent(this);
    m_pLabelCardSta->setParent(this);

    m_pShwNmeBtn   = new PushButton();
    m_pLabelShwNme = new Label();
    m_pShwNmeBtn->setText("Show Name:");
    m_pLabelShwNme->setText("None");
    m_pShwNmeBtn->move(20,100);
    m_pLabelShwNme->move(150,80);
    m_pShwNmeBtn->setParent(this);
    m_pLabelShwNme->setParent(this);
    connect(m_pShwNmeBtn,SIGNAL(clicked()),this,SLOT(on_ShwName_Btn_clicked()));

    /*2*/
    m_pChgNmeBtn = new PushButton();
    m_pNmLnEdt   = new LineEdit();
    m_pChgNmeBtn->setText("Change Name");
    m_pNmLnEdt->setText("Input name");
    m_pChgNmeBtn->move(20,150);
    m_pNmLnEdt->move(150,150);
    m_pChgNmeBtn->setParent(this);
    m_pNmLnEdt->setParent(this);
    connect(m_pChgNmeBtn,SIGNAL(clicked()),this,SLOT(on_ChngName_Btn_clicked()));


    m_pBalnBtn = new PushButton();
    m_pBalnEdt   = new LineEdit();
    m_pBalnBtn->setText("Balance");
    m_pBalnEdt->setText("");
    m_pBalnBtn->move(20,200);
    m_pBalnEdt->move(150,200);
    m_pBalnBtn->setParent(this);
    m_pBalnEdt->setParent(this);
    connect(m_pBalnBtn,SIGNAL(clicked()),this,SLOT(on_Blnc_Btn_clicked()));

    /*Admi*/
    m_pSralNumBtn = new PushButton();
    m_pSralNumEdt = new LineEdit();
    m_pSralNumBtn->setText("Serial Number");
    m_pSralNumEdt->setText("");
    m_pSralNumBtn->move(20,250);
    m_pSralNumEdt->move(150,250);
    m_pSralNumBtn->setParent(this);
    m_pSralNumEdt->setParent(this);
    connect(m_pSralNumBtn,SIGNAL(clicked()),this,SLOT(on_SrlNmbr_Btn_clicked()));


    m_pDataBtn = new PushButton();
    m_pDataEdt = new LineEdit();
    m_pDataBtn->setText("DATA");
    m_pDataEdt->setText("");
    m_pDataBtn->move(320,250);
    m_pDataEdt->move(450,250);
    m_pDataBtn->setParent(this);
    m_pDataEdt->setParent(this);
    connect(m_pDataBtn,SIGNAL(clicked()),this,SLOT(on_Data_Btn_clicked()));

    /*Operation*/
    m_pOpnRderBtn = new PushButton();
    m_pCloRderBtn = new PushButton();
    m_pOpnRderBtn->setText("Open Reader");
    m_pCloRderBtn->setText("Close Reader");
    m_pOpnRderBtn->move(320,20);
    m_pCloRderBtn->move(450,20);
    m_pOpnRderBtn->setParent(this);
    m_pCloRderBtn->setParent(this);
    connect(m_pOpnRderBtn,SIGNAL(clicked()),this,SLOT(on_OpnRdr_Btn_clicked()));
    connect(m_pCloRderBtn,SIGNAL(clicked()),this,SLOT(on_ClsRdr_Btn_clicked()));

    m_pInitBtn = new PushButton();
    m_pInitBtn->setText("Initialize");
    m_pInitBtn->move(320,70);
    m_pInitBtn->setParent(this);
    connect(m_pInitBtn,SIGNAL(clicked()),this,SLOT(on_Intliz_Btn_clicked()));

    m_pRechargeBtn = new PushButton();
    m_pRechargeEdt = new LineEdit();
    m_pRechargeBtn->setText("Recharge");
    m_pRechargeEdt->setText("0");
    m_pRechargeBtn->move(320,120);
    m_pRechargeEdt->move(450,120);
    m_pRechargeBtn->setParent(this);
    m_pRechargeEdt->setParent(this);
    connect(m_pRechargeBtn,SIGNAL(clicked()),this,SLOT(on_Recharge_Btn_clicked()));


    m_pChargeBtn = new PushButton();
    m_pChargeEdt = new LineEdit();
    m_pChargeBtn->setText("Charge");
    m_pChargeEdt->setText("0");
    m_pChargeBtn->move(320,170);
    m_pChargeEdt->move(450,170);
    m_pChargeBtn->setParent(this);
    m_pChargeEdt->setParent(this);
    connect(m_pChargeBtn,SIGNAL(clicked()),this,SLOT(on_Charge_Btn_clicked()));

}

Widget::~Widget()
{

    if(m_pLabelDevStaMark)
    {
        m_pLabelDevStaMark->deleteLater();
        m_pLabelDevStaMark   = NULL;
    }
    if(m_pLabelDevSta)
    {
        m_pLabelDevSta->deleteLater();
        m_pLabelDevSta   = NULL;
    }


}

static int count = 0;
void Widget::slot_check_Card()
{
    qDebug() << "check now :" << count++;
    bool bCheckCard = CheckCard();
    qDebug() << "bCheckCard:" << bCheckCard ;
    if(!bCheckCard)
    {
        qDebug() << "check: not found!";
    }
    update();
}

void Widget::on_ShwName_Btn_clicked()
{
    qDebug() << "ShwName";

    qDebug() << "ShwName:1";
    int ReadID, rt, len;
    QString name;
    unsigned char  SerialNo[4],  Data[16];
    unsigned char Password[6]={0,0x5A,0xFF,0xA5,0xBC,0xA1};
    int PassMode;
    unsigned short CardType;
    unsigned char CardMem;
    int CardNoLen;
    ReadID=0;
    rt = 1;
    if(rt>=0)
    {
        qDebug() << "ShwName:2";
        rt = YW_RequestCard(ReadID,REQUESTMODE_ALL,&CardType);
        if(rt>=0)
        {
            rt = YW_AntiCollideAndSelect(ReadID,1, &CardMem,&CardNoLen, &SerialNo[0]);
            if(rt>=0)
            {
                PassMode =PASSWORD_A;

                rt = YW_KeyAuthorization(ReadID, PassMode,4, &Password[0]);
                if(rt>=0)
                {
                    qDebug() << "ShwName:3";
                    rt = YW_ReadaBlock(ReadID ,6, 16, &Data[0]);
                    len=Data[15];
                    char buff[15] = {0};
                    if(rt>=0)
                    {
                        qDebug() << "ShwName:4";
                        //memset(buff,0,15);
                        qDebug() << "ShwName:5";
                        memcpy(buff,Data,len);
                        qDebug() << "ShwName:6";
                        name = QString(buff);
                        qDebug() << "ShwName:7";
                        qDebug() << "name: " << name;
                        //ui->ShowName_label->setText("name");
                        //update();
                        qDebug() << "ShwName:8";
                    }
                }
                else
                    QMessageBox::warning(NULL, "Failed", "Card Not Recognized", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            }

        }
        else
            QMessageBox::warning(NULL, "Failed", "Card Not Recognized", QMessageBox::Yes, QMessageBox::Yes);
    }
    qDebug() << "ShwName:9";

    qDebug() << "ShwName:10";

}

void Widget::on_ChngName_Btn_clicked()
{
    qDebug() << "ChngNameBtn";

    // TODO: Add your control notification handler code here
    int ReadID, rt,len;
    QString IDText;
    unsigned char  SerialNo[4],  name[16];
    unsigned char Password[6]={0,0x5A,0xFF,0xA5,0xBC,0xA1};
    int PassMode;
    unsigned short CardType;
    unsigned char CardMem;
    int CardNoLen;
    ReadID=0;
    rt = 1;
    if(rt>=0)
    {
        rt = YW_RequestCard(ReadID,REQUESTMODE_ALL,&CardType);
        if(rt>=0)
        {
            rt = YW_AntiCollideAndSelect(ReadID,1, &CardMem,&CardNoLen, &SerialNo[0]);
            if(rt>=0)
            {
                PassMode =PASSWORD_A;

                rt = YW_KeyAuthorization(ReadID, PassMode,4, &Password[0]);
                if(rt>=0)
                {
                    // ui->label_5->setText(IDText);
                    len=IDText.size();
                    if(len>15)
                        QMessageBox::critical(NULL, "Error", "No More Than 15 Letters!", QMessageBox::Yes , QMessageBox::Yes);
                    else
                    {
                        memcpy(name,IDText.begin(),len);
                        name[15]=len;
                        rt=YW_WriteaBlock(ReadID,6,16,name);
                        if(rt>=0)
                        {
                            QMessageBox::warning(NULL, "Success", "Change name success", QMessageBox::Yes, QMessageBox::Yes);
                        }
                        else
                            QMessageBox::warning(NULL, "Failed", "Change name failed", QMessageBox::Yes, QMessageBox::Yes);

                    }
                }
                else
                    QMessageBox::warning(NULL, "Failed", "Card Not Recognized", QMessageBox::Yes, QMessageBox::Yes);

            }

        }
        else
            QMessageBox::warning(NULL, "Failed", "NO Card Found!", QMessageBox::Yes, QMessageBox::Yes);
    }
    update();

}

void Widget::on_Blnc_Btn_clicked()
{
    qDebug() << "BalnBtn";

    // TODO: Add your control notification handler code here
    int ReadID, rt,temp;
    float Money;
    ReadID = 0;
    unsigned char  SerialNo[4];
    unsigned char Password[6]={0,0x5A,0xFF,0xA5,0xBC,0xA1};
    int PassMode;
    unsigned short CardType;
    unsigned char CardMem;
    int CardNoLen;
    ReadID=0;
    rt = 1;
    if(rt>=0)
    {
        rt = YW_RequestCard(ReadID,REQUESTMODE_ALL,&CardType);
        if(rt>=0)
        {
            rt = YW_AntiCollideAndSelect(ReadID,1, &CardMem,&CardNoLen, &SerialNo[0]);
            if(rt>=0)
            {
                PassMode =PASSWORD_A;

                rt = YW_KeyAuthorization(ReadID, PassMode,4, &Password[0]);
                if(rt>=0)
                {
                    rt=YW_Purse_Read(ReadID,4,&temp);
                    if(temp<=0)
                        Money=0;
                    Money=temp/100.00;
                    if(rt>=0)
                    {
                        QString str = QString("%.2f").arg(Money);
                        qDebug() << "QString str = QString().arg(Money):" << str;

                        //ui->lineEdit_2->setText(str);
                    }
                }
                else
                    QMessageBox::warning(NULL, "Failed", "Card Not Recognized!", QMessageBox::Yes, QMessageBox::Yes);
            }

        }
        else
            QMessageBox::warning(NULL, "Failed", "NO Card Found!", QMessageBox::Yes, QMessageBox::Yes);
    }
    update();

}

void Widget::on_SrlNmbr_Btn_clicked()
{
    qDebug() << "SralNumBtn";

    int ReadID, rt, i;
    QString IDText, sSerial;
    char Serial[8], tmp[4];
    //IDText = ui->lineEdit_5->text();
    ReadID = atoi(IDText.toStdString().c_str());
    rt = YW_GetReaderSerial(ReadID, Serial);
    if(rt>=0)
    {
        sSerial="";
        for(i=0;i<8;i++)
        {
            itoa(Serial[i],tmp,16);
            sSerial=sSerial+QString(tmp);
        }
        // ui->lineEdit_3->setText(sSerial);
    }

}

void Widget::on_Data_Btn_clicked()
{
    qDebug() << "DataBtn";

    int ReadID, rt;
    unsigned char  SerialNo[4];
    unsigned char Data[16];
    unsigned char Password[6]={0,0x5A,0xFF,0xA5,0xBC,0xA1};
    int PassMode;
    unsigned short CardType;
    unsigned char CardMem;
    int CardNoLen;

    ReadID=0;
    //ui->lineEdit_4->setText("");
    rt = 1;
    if(rt>=0)
    {
        rt = YW_RequestCard(ReadID,REQUESTMODE_ALL,&CardType);
        if(rt>=0)
        {
            rt = YW_AntiCollideAndSelect(ReadID,1,&CardMem, &CardNoLen,&SerialNo[0]);
            if(rt>=0)
            {

                PassMode =PASSWORD_A;
                rt = YW_KeyAuthorization(ReadID, PassMode,4, &Password[0]);
                if(rt>=0)
                {
                    rt = YW_ReadaBlock(ReadID ,4, 16, &Data[0]);
                    if(rt>=0)
                    {
                        char buf[26];
                        sprintf(buf,"%f",Data);
                        QString str = QString(buf);
                        // ui->lineEdit_5->setText(str);
                    }
                }
            }
        }
    }
    update();

}

void Widget::on_OpnRdr_Btn_clicked()
{
    qDebug() << "OpnRderBtn";
    int rt=0;
    rt = YW_USBHIDInitial();
    if(rt>0)
    {
        m_pLabelDevSta->setText("Device On");
        m_pCheckCardTimer->start(TIME_OUT_TO_CHRCK_CARD);
    }
    else
    {
        m_pLabelDevSta->setText("Device Off");
    }
}

void Widget::on_ClsRdr_Btn_clicked()
{
    qDebug() << "CloRderBtn";
    if(m_pCheckCardTimer->isActive())
    {
        m_pCheckCardTimer->stop();
    }
    YW_USBHIDFree();
    m_pLabelDevSta->setText("Device Off");
}

void Widget::on_Intliz_Btn_clicked()
{
    qDebug() << "InitBtn";
    int ReadID, rt;
    unsigned char  SerialNo[4];
    unsigned char Password[6]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    unsigned char User[16]={0x01,0x01,0x02,0x03,0x05,0x08,0xFF,0x07,0x80,0x69,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    unsigned char key[16]={0,0x5A,0xFF,0xA5,0xBC,0xA1,0xFF,0x07,0x80,0x69,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    int PassMode;
    unsigned short CardType;
    unsigned char CardMem;
    int CardNoLen;
    ReadID=0;
    rt = 1;
    if(rt>=0)
    {
        rt = YW_RequestCard(ReadID,REQUESTMODE_ALL,&CardType);
        if(rt>=0)
        {
            rt = YW_AntiCollideAndSelect(ReadID,1, &CardMem,&CardNoLen, &SerialNo[0]);
            if(rt>=0)
            {
                PassMode =PASSWORD_B;
                rt = YW_KeyAuthorization(ReadID, PassMode,4, &Password[0]);
                if(rt>=0)
                {
                    rt=YW_WriteaBlock(ReadID,5,16,User);
                    if(rt>=0)
                    {
                        rt=YW_WriteaBlock(ReadID,7,16,key);
                        if(rt>=0)
                        {
                            rt=YW_Purse_Initial(ReadID,4,0);
                            unsigned char name[16]={0};
                            int rt1=YW_WriteaBlock(ReadID,6,16,name);
                            if(rt>=0)
                            {
                                QMessageBox::warning(NULL, "warning", "Initialize Success", QMessageBox::Yes, QMessageBox::Yes);
                            }
                            else
                                QMessageBox::warning(NULL, "warning", "Initialize Failed", QMessageBox::Yes, QMessageBox::Yes);
                            if(rt1>=0)
                            {
                                //m_pLabelShwNme->setText("None");
                                qDebug() << "11111111111111";
                            }
                        }

                    }


                }
                else
                    QMessageBox::warning(NULL, "warning", "Card Not Recognized", QMessageBox::Yes, QMessageBox::Yes);
            }

        }
        else
            QMessageBox::warning(NULL, "warning", "NO Card Found!", QMessageBox::Yes, QMessageBox::Yes);

    }

}

void Widget::on_Recharge_Btn_clicked()
{
    qDebug() << "RechargeBtn";
    int ReadID, rt;
    float value;
    QString IDText;
    unsigned char  SerialNo[4];
    unsigned char Password[6]={0,0x5A,0xFF,0xA5,0xBC,0xA1};
    int PassMode;
    unsigned short CardType;
    unsigned char CardMem;
    int CardNoLen;

    ReadID=0;
    IDText = m_pRechargeEdt->text();
    value=atof(IDText.toStdString().c_str())*100;

    if(value<=0)
    {
        QMessageBox::warning(NULL, "Failed", "Invalid Vlue!", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    rt = 1;
    if(rt>=0)
    {
        rt = YW_RequestCard(ReadID,REQUESTMODE_ALL,&CardType);
        if(rt>=0)
        {
            rt = YW_AntiCollideAndSelect(ReadID,1, &CardMem,&CardNoLen, &SerialNo[0]);
            if(rt>=0)
            {
                PassMode =PASSWORD_A;

                rt = YW_KeyAuthorization(ReadID, PassMode,4, &Password[0]);
                if(rt>=0)
                {
                    qDebug() << "RechargeBtn 1";
                    rt=YW_Purse_Charge(ReadID,4,value);
                    if(rt>=0)
                    {
                        qDebug() << "RechargeBtn 2";
                        YW_Led(ReadID,02,2,2,1,00);
                        qDebug() << "RechargeBtn 3";
                        YW_Buzzer(ReadID,1,1,2);
                        qDebug() << "RechargeBtn 4";
                        QMessageBox::warning(NULL, "Success", "Recharge Success!", QMessageBox::Yes, QMessageBox::Yes);
                        qDebug() << "RechargeBtn 5";
                    }
                    else
                    {
                        qDebug() << "RechargeBtn 6";
                        YW_Buzzer(ReadID,3,1,1);
                        qDebug() << "RechargeBtn 7";
                        QMessageBox::warning(NULL, "Failed", "Recharge Failed!", QMessageBox::Yes, QMessageBox::Yes);
                        qDebug() << "RechargeBtn 8";
                    }
                }
                else
                {
                    qDebug() << "RechargeBtn 9";
                    QMessageBox::warning(NULL, "Failed", "Card Not Recognized!", QMessageBox::Yes, QMessageBox::Yes);
                }
            }
            else
            {
                qDebug() << "RechargeBtn 10";
                QMessageBox::warning(NULL, "Failed", "NO Card Found!", QMessageBox::Yes, QMessageBox::Yes);
            }
        }
    }
}

bool Widget::CheckCard() // open之后实时检测
{
    int ReadID, rt;
    unsigned char  SerialNo[4];
    unsigned short CardType;
    unsigned char CardMem;
    int CardNoLen;
    ReadID=0;

    rt = 1;
    if(rt>=0)
    {
        rt = YW_RequestCard(ReadID,REQUESTMODE_ALL,&CardType);
        if(rt>=0)
        {
            rt = YW_AntiCollideAndSelect(ReadID,1,&CardMem, &CardNoLen,&SerialNo[0]);
            if(rt>=0)
            {
                YW_Led(ReadID,02,1,0,0,02);
                return true;
            }
        }
    }

    m_pLabelCardSta->setText("No Card Found");
    m_pLabelShwNme->setText("None");
    YW_Led(ReadID,01,1,0,0,01);
    return false;
}


void Widget::on_Charge_Btn_clicked()
{
    qDebug() << "ChargeBtn";
    int ReadID, rt,Money,temp;
    double value;
    QString IDText;
    unsigned char  SerialNo[4];
    unsigned char Password[6]={0,0x5A,0xFF,0xA5,0xBC,0xA1};
    int PassMode;
    unsigned short CardType;
    unsigned char CardMem;
    int CardNoLen;

    ReadID=0;
    // IDText = ui->lineEdit_6->text();
    value=atof(IDText.toStdString().c_str());
    temp=value*100;
    if(value<=0)
    {
        QMessageBox::warning(NULL, "Failed", "Invalid Vlue!", QMessageBox::Yes, QMessageBox::Yes);
        return;
    }
    rt = 1;
    if(rt>=0)
    {
        rt = YW_RequestCard(ReadID,REQUESTMODE_ALL,&CardType);
        if(rt>=0)
        {
            rt = YW_AntiCollideAndSelect(ReadID,1, &CardMem,&CardNoLen, &SerialNo[0]);
            if(rt>=0)
            {
                PassMode =PASSWORD_A;

                rt = YW_KeyAuthorization(ReadID, PassMode,4, &Password[0]);
                if(rt>=0)
                {
                    rt=YW_Purse_Read(ReadID,4,&Money);
                    if(rt>=0)
                    {
                        if(Money<temp)
                            QMessageBox::warning(NULL, "Failed", "No enogh money to charge!", QMessageBox::Yes, QMessageBox::Yes);
                        else
                        {
                            rt=YW_Purse_Decrease(ReadID,4,temp);
                            QMessageBox::warning(NULL, "Success", "Charge Success!", QMessageBox::Yes, QMessageBox::Yes);
                        }

                    }
                }
                else
                    QMessageBox::warning(NULL, "Failed", "Card Not Recognized!", QMessageBox::Yes, QMessageBox::Yes);

            }

        }
        else
            QMessageBox::warning(NULL, "Failed", "NO Card Found!", QMessageBox::Yes, QMessageBox::Yes);

    }
    update();
}


