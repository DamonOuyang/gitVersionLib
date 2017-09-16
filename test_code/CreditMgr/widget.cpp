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

enum {TIME_OUT_TO_CHRCK_CARD = 100};

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
    if(m_pCheckCardTimer->isActive())
    {
        m_pCheckCardTimer->stop();
    }
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
        ui->label_5->setText("label_5 can setText");
        m_pCheckCardTimer->start(TIME_OUT_TO_CHRCK_CARD);
    }
    else
    {
        ui->DeviceStatue_label_2->setText("Device Off");
    }
    update();
}

static int count = 0;
void Widget::slot_check_Card()
{
    qDebug() << "check now :" << count++;
    if(!CheckCard())
    {
         qDebug() << "check: not found!";
    }


    update();
}

void Widget::on_ShwName_Btn_clicked()
{
    int ReadID, rt,len;
        QString IDText, sData,name;
        unsigned char  SerialNo[4],  Data[16];
        unsigned char Password[6]={0,0x5A,0xFF,0xA5,0xBC,0xA1};
        int PassMode, BlockID;
        unsigned short CardType;
        unsigned char CardMem;
        int CardNoLen;
        QString strKey;
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
                        rt = YW_ReadaBlock(ReadID ,6, 16, &Data[0]);
                        len=Data[15];
                        char buff[15];
                        if(rt>=0)
                        {
                            memset(buff,0,15);
                            memcpy(buff,Data,len);
                            name = QString(buff);
                            //name.Format("%s",buff);
                            //((CStatic *)GetDlgItem(IDC_STATIC9))->SetWindowText(name);
                            ui->ShowName_label->setText(name);
                        }
                   }
                  else
                     QMessageBox::warning(NULL, "Failed", "Card Not Recognized", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
               }

          }
          else
            QMessageBox::warning(NULL, "Failed", "Card Not Recognized", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
        }
        update();
}

void Widget::on_ClsRdr_Btn_clicked()
{
    if(m_pCheckCardTimer->isActive())
    {
        m_pCheckCardTimer->stop();
    }
    YW_USBHIDFree();
    ui->DeviceStatue_label_2->setText("Device Off");
    update();
}

void Widget::on_Intliz_Btn_clicked()
{
    int ReadID, rt;
    QString IDText, sData, sBlockID;
    unsigned char  SerialNo[4],Data[16];
    unsigned char Password[6]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    unsigned char User[16]={0x01,0x01,0x02,0x03,0x05,0x08,0xFF,0x07,0x80,0x69,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    unsigned char key[16]={0,0x5A,0xFF,0xA5,0xBC,0xA1,0xFF,0x07,0x80,0x69,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
    int PassMode, BlockID;
    unsigned short CardType;
    unsigned char CardMem;
    int CardNoLen;
    QString strKey;
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
             /*  if(m_Pass==1)
                   PassMode =PASSWORD_B;
               else*/
                   PassMode =PASSWORD_B;

               /*((CEdit *)GetDlgItem(IDC_BLOCKID))->GetWindowText(sBlockID);
               BlockID = atoi(sBlockID);

                m_Key.GetWindowTextEx(strKey);
                memcpy(Password,strKey.GetBuffer(6),6);*/

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
                             QString namenull="";
                            int rt1=YW_WriteaBlock(ReadID,6,16,name);
                              if(rt>=0)
                            {
                                  QMessageBox::warning(NULL, "warning", "Initialize Success", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
                             }
                              else
                                  QMessageBox::warning(NULL, "warning", "Initialize Failed", QMessageBox::Yes/* | QMessageBox::No*/, QMessageBox::Yes);
                              if(rt1>=0)
                              {
//                                  ((CStatic *)GetDlgItem(IDC_STATIC9))->SetWindowText(namenull);
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
    update();
}

void Widget::on_ChngName_Btn_clicked()
{

    // TODO: Add your control notification handler code here
/*	int ReadID, rt;
    CString IDText;

    ((CEdit *)GetDlgItem(IDC_edtNewID))->GetWindowText(IDText);
    ReadID = atoi(IDText);
    rt = YW_AntennaStatus(ReadID, true);*/
    int ReadID, rt,value,Money,len;
    QString IDText, sData;
    unsigned char  SerialNo[4],  name[16];
    unsigned char Password[6]={0,0x5A,0xFF,0xA5,0xBC,0xA1};
    int PassMode, BlockID;
    unsigned short CardType;
    unsigned char CardMem;
    int CardNoLen;
    QString strKey;
    ReadID=0;
    /*((CEdit *)GetDlgItem(IDC_EDIT1))->GetWindowText(IDText);
    value=atoi(IDText);
    if(value<=0)
    {
        MessageBox(_T("Invalid Vlue"),_T("Failed"), MB_OK);
        return;
    }*/
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
//                 ((CEdit *)GetDlgItem(IDC_EDIT1 ))->GetWindowText(IDText);
                 ui->label_5->setText(IDText);
//                 len=IDText.GetLength();
                 len=IDText.size();
                 if(len>15)
                 QMessageBox::critical(NULL, "Error", "No More Than 15 Letters!", QMessageBox::Yes /*| QMessageBox::No*/, QMessageBox::Yes);
                 else
                 {
//                     memcpy(name , IDText.GetBuffer(len),len);
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
//    ((CEdit *)GetDlgItem(IDC_edtNewID))->GetWindowText(IDText);
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
//      ((CEdit *)GetDlgItem(IDC_EDIT4))->SetWindowText(sSerial);
      ui->lineEdit_3->setText(sSerial);
    }
}

void Widget::on_Charge_Btn_clicked()
{
    int ReadID, rt,Money,temp;
    double value;
    QString IDText, sData;
    unsigned char  SerialNo[4],  Data[16];
    unsigned char Password[6]={0,0x5A,0xFF,0xA5,0xBC,0xA1};
    int PassMode, BlockID;
    unsigned short CardType;
    unsigned char CardMem;
    int CardNoLen;
    QString strKey;
    ReadID=0;
//    ((CEdit *)GetDlgItem(IDC_EDIT3))->GetWindowText(IDText);
    IDText = ui->lineEdit_6->text();
    value=atof(IDText.toStdString().c_str());
    temp=value*100;
    if(value<=0)
    {
//        MessageBox(_T("Invalid Vlue"),_T("Failed"), MB_OK);
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
    // TODO: Add your control notification handler code here
    //int ReadID;
    //CString IDText;
    //((CEdit *)GetDlgItem(IDC_edtNewID))->GetWindowText(IDText);
    //ReadID = atoi(IDText);
    //YW_SetReaderID(0, ReadID);
    int ReadID, rt,Money;
    float value;
    QString IDText, sData;
    unsigned char  SerialNo[4],  Data[16];
    unsigned char Password[6]={0,0x5A,0xFF,0xA5,0xBC,0xA1};
    int PassMode, BlockID;
    unsigned short CardType;
    unsigned char CardMem;
    int CardNoLen;
    QString strKey;
    ReadID=0;
//    ((CEdit *)GetDlgItem(IDC_edtNewID))->GetWindowText(IDText);
    IDText = ui->lineEdit_5->text();
    value=atof(IDText.toStdString().c_str())*100;

    if(value<=0)
    {
//        MessageBox(_T("Invalid Vlue"),_T("Failed"), MB_OK);
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

    QString sData;
    unsigned char  SerialNo[4],  Data[16];
    unsigned char Password[6]={0,0x5A,0xFF,0xA5,0xBC,0xA1};
    int PassMode, BlockID;
    unsigned short CardType;
    unsigned char CardMem;
    int CardNoLen;
    QString strKey;
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

             /*m_Key.GetWindowTextEx(strKey);
             memcpy(Password,strKey.GetBuffer(6),6);*/

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
//                     str.Format("%.2f" , Money);

//                    ((CEdit *)GetDlgItem(IDC_EDIT2))->SetWindowText(str);
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
    /*itoa(ReadID, IDText, 10);
    ((CEdit *)GetDlgItem(IDC_edtNewID))->SetWindowText(IDText);
    ((CEdit *)GetDlgItem(IDC_EDIT2))->SetWindowText(IDText);*/
    update();
}

void Widget::on_Data_Btn_clicked()
{
    int ReadID, rt;
    QString IDText, sData, sBlockID;
    unsigned char  SerialNo[4];
    unsigned char Data[16];
    unsigned char Password[6]={0,0x5A,0xFF,0xA5,0xBC,0xA1};
    int PassMode, BlockID;
    unsigned short CardType;
    unsigned char CardMem;
     int CardNoLen;
    QString strKey;


    /*((CEdit *)GetDlgItem(IDC_edtNewID))->GetWindowText(IDText);
    ReadID = atoi(IDText);*/
    ReadID=0;
//    ((CEdit *)GetDlgItem(IDC_DATA))->SetWindowText("");
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
              /* if(m_Pass==1)
                   PassMode =PASSWORD_B;
               else*/
                   PassMode =PASSWORD_A;
/*
               ((CEdit *)GetDlgItem(IDC_BLOCKID))->GetWindowText(sBlockID);
               BlockID = atoi(sBlockID);*/

                /*m_Key.GetWindowTextEx(strKey);
                memcpy(Password,strKey.GetBuffer(6),6);*/

               rt = YW_KeyAuthorization(ReadID, PassMode,4, &Password[0]);
               if(rt>=0)
               {
                 rt = YW_ReadaBlock(ReadID ,4, 16, &Data[0]);
                 if(rt>=0)
                 {
                     char buf[26];
                     sprintf(buf,"%f",Data);
//                     m_BlockRead.SetWindowTextEx(Data, 16);
                     QString str = QString(buf);
                     ui->lineEdit_5->setText(str);
                 }
               }
           }
        }
    }
    update();
}

bool Widget::CheckCard()// open之后实时检测
{
    qDebug()<<"1";
    int ReadID, rt;
    QString IDText, sData, sBlockID;
    unsigned char  SerialNo[4], Password[6], Data[16];
    int PassMode, BlockID;
    unsigned short CardType;
    unsigned char CardMem;
    int CardNoLen;
    QString strKey;
    QString cardno;
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
              ui->label_5->setText("cardno");
              YW_Led(ReadID,02,1,0,0,02);
              ui->label_5->setText("cardno2");

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
