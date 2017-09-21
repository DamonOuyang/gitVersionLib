#include "widget.h"
#include "ui_widget.h"
#include <QDebug>
#include <QString>
#include <QMessageBox>
#include <QTimer>
#include <QThread>

extern "C" {
#include "SDT_VC.h"
}

enum {TIME_OUT_TO_CHRCK_CARD = 1000};

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(800,600);
    m_pCheckCardTimer = new QTimer(this);
    connect(m_pCheckCardTimer,SIGNAL(timeout()),this,SLOT(slot_check_Card()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_OpnRdr_Btn_clicked()
{
    // TODO: Add your control notification handler code here
    int rt;
    rt = YW_USBHIDInitial();
    if(rt>0)
    {
        ui->DeviceStatue_label_2->setText("Device On");
        m_pCheckCardTimer->start(TIME_OUT_TO_CHRCK_CARD);
    }
    else
    {
        ui->DeviceStatue_label_2->setText(" ");
    }
    update();
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

bool Widget::CheckCard()// open之后实时检测
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
                //              ui->label_5->setText("cardno");
                YW_Led(ReadID,02,1,0,0,02);
                //              ui->label_5->setText("cardno2");
                //              qDebug()<<"ReadID:"<<ReadID;

                qDebug()<<"2";
                //char buf[1024]={0};
                qDebug()<<"2.1";
                //sprintf(buf,"%x",SerialNo);
                //memcpy(buf,SerialNo,4);
                qDebug()<<"2.2";
                //                     m_BlockRead.SetWindowTextEx(Data, 16);
                //cardno = QString(buf);
                qDebug()<<"2.3";

                //cardno.Format("%X%X%X%X" , SerialNo[0] , SerialNo[1] , SerialNo[2] , SerialNo[3]);
                //((CEdit *)GetDlgItem(IDC_STATIC8))->SetWindowText(cardno);


                //ui->label_5->setText("cardno");

                qDebug()<<"3";
                return true;
            }
        }
    }

    ui->label_5->setText("No Card Found");
    ui->ShowName_label->setText("None");
    qDebug()<<"4";
    YW_Led(ReadID,01,1,0,0,01);
    return false;
}


void Widget::on_ShwName_Btn_clicked()
{
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
                        update();
                        qDebug() << "ShwName:8";
                    }
                }
                else
                    QMessageBox::warning(NULL, "Failed", "Card Not Recognized", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
            }

        }
        else
            QMessageBox::warning(NULL, "Failed", "Card Not Recognized", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
    }
    qDebug() << "ShwName:9";

    qDebug() << "ShwName:10";
}

void Widget::on_ClsRdr_Btn_clicked()
{
    if(m_pCheckCardTimer->isActive())
    {
        m_pCheckCardTimer->stop();
    }
    YW_USBHIDFree();
    ui->DeviceStatue_label_2->setText("Device Off");
    //update();
}

void Widget::on_Intliz_Btn_clicked()
{
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
                                QMessageBox::warning(NULL, "warning", "Initialize Success", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
                            }
                            else
                                QMessageBox::warning(NULL, "warning", "Initialize Failed", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
                            if(rt1>=0)
                            {
                                ui->ShowName_label->setText("None");
                            }
                        }

                    }


                }
                else
                    QMessageBox::warning(NULL, "warning", "Card Not Recognized", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
            }

        }
        else
            QMessageBox::warning(NULL, "warning", "NO Card Found!", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);

    }
    //update();
}

void Widget::on_ChngName_Btn_clicked()
{

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
                    ui->label_5->setText(IDText);
                    len=IDText.size();
                    if(len>15)
                        QMessageBox::critical(NULL, "Error", "No More Than 15 Letters!", QMessageBox::Yes /*| QMessageBox::No*/, QMessageBox::Yes);
                    else
                    {
                        memcpy(name,IDText.begin(),len);
                        name[15]=len;
                        rt=YW_WriteaBlock(ReadID,6,16,name);
                        if(rt>=0)
                        {
                            QMessageBox::warning(NULL, "Success", "Change name success", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
                        }
                        else
                            QMessageBox::warning(NULL, "Failed", "Change name failed", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);

                    }
                }
                else
                    QMessageBox::warning(NULL, "Failed", "Card Not Recognized", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);

            }

        }
        else
            QMessageBox::warning(NULL, "Failed", "NO Card Found!", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
    }
    update();
}

void Widget::on_SrlNmbr_Btn_clicked()
{
    int ReadID, rt, i;
    QString IDText, sSerial;
    char Serial[8], tmp[4];
    IDText = ui->lineEdit_5->text();
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
        ui->lineEdit_3->setText(sSerial);
    }
}

void Widget::on_Charge_Btn_clicked()
{
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
    IDText = ui->lineEdit_6->text();
    value=atof(IDText.toStdString().c_str());
    temp=value*100;
    if(value<=0)
    {
        QMessageBox::warning(NULL, "Failed", "Invalid Vlue!", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
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
                            QMessageBox::warning(NULL, "Failed", "No enogh money to charge!", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
                        else
                        {
                            rt=YW_Purse_Decrease(ReadID,4,temp);
                            QMessageBox::warning(NULL, "Success", "Charge Success!", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
                        }

                    }
                }
                else
                    QMessageBox::warning(NULL, "Failed", "Card Not Recognized!", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);

            }

        }
        else
            QMessageBox::warning(NULL, "Failed", "NO Card Found!", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);

    }
    update();
}

void Widget::on_Recharge_Btn_clicked()
{
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
    IDText = ui->lineEdit_5->text();
    value=atof(IDText.toStdString().c_str())*100;

    if(value<=0)
    {
        QMessageBox::warning(NULL, "Failed", "Invalid Vlue!", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
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
                    rt=YW_Purse_Charge(ReadID,4,value);
                    if(rt>=0)
                    {
                        YW_Led(ReadID,02,2,2,1,00);
                        YW_Buzzer(ReadID,1,1,2);
                        QMessageBox::warning(NULL, "Success", "Recharge Success!", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);

                    }
                    else
                    {
                        YW_Buzzer(ReadID,3,1,1);
                        QMessageBox::warning(NULL, "Failed", "Recharge Failed!", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
                    }
                }
                else
                    QMessageBox::warning(NULL, "Failed", "Card Not Recognized!", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
            }

        }
        else
            QMessageBox::warning(NULL, "Failed", "NO Card Found!", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);

    }
    update();
}

void Widget::on_Blnc_Btn_clicked()
{
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

                        ui->lineEdit_2->setText(str);
                    }
                }
                else
                    QMessageBox::warning(NULL, "Failed", "Card Not Recognized!", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
            }

        }
        else
            QMessageBox::warning(NULL, "Failed", "NO Card Found!", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
    }
    update();
}

void Widget::on_Data_Btn_clicked()
{
    int ReadID, rt;
    unsigned char  SerialNo[4];
    unsigned char Data[16];
    unsigned char Password[6]={0,0x5A,0xFF,0xA5,0xBC,0xA1};
    int PassMode;
    unsigned short CardType;
    unsigned char CardMem;
    int CardNoLen;

    ReadID=0;
    ui->lineEdit_4->setText("");
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
                        ui->lineEdit_5->setText(str);
                    }
                }
            }
        }
    }
    update();
}

