#include <iostream>


using namespace std;


// (0x5A)(0x00,0x01)(0x01)(0xA2)(0x00,0x04)(0x02,0x02,0x02,0x02)(0x08)
//    5A    00   01    01    A2    00   04    00   00   00   64   LRC

//char creatLRC(char buff[],int len)
//{
//    char tem=buff[1];
//    for(int i=2;i<len;i++)
//    {
//        cout<< " " << endl;
//        tem ^= buff[i];
//    }
//    return tem;
//}
void display(unsigned char buff[],int dataLen)
{
    for(int i=0;i<dataLen;i++)
    {

        printf("0x%x ",buff[i]);
    }
}


static unsigned short framId = 0;
//void vmc_sendCmd(char cmd,char data[],char dataLen)
//{
//    char buff[20] = {0};
//    buff[0] = 0x5A;
//    buff[1] = framId>>8;
//    buff[2] = framId&0xff;
//    buff[3] = 0x01;
//    buff[4] = cmd;
//    buff[5] = dataLen>>8;
//    buff[6] = dataLen&0xff;
//    for (int i=0;i<dataLen;i++)
//    {
//        buff[7+i] = data[i];
//    }
//    buff[7+dataLen]=creatLRC(buff,7+dataLen-1);

//    display(buff,7+dataLen);
//}

void int216Code(int price , unsigned char* code , int len)
{
    memcpy(code , &price , len);
}

unsigned char creatLRC_ZKTeco(unsigned char buff[],int len)
{
    char tem=buff[1];
    for(int i=2;i<len;i++)
    {
        cout<< " " << endl;
        tem ^= buff[i];
    }
    return tem;
}


void cmdCreate_ZKTeco(char cmd,unsigned char data[],char dataLen)
{
    if(dataLen > 13)
        return;

    unsigned char buff[20] = {0};
    buff[0] = 0x5A;
    buff[1] = framId>>8;
    buff[2] = framId&0xff;
    buff[3] = 0x01;
    buff[4] = cmd;
    buff[5] = dataLen>>8;
    buff[6] = dataLen&0xff;
    for (int i=0;i<dataLen;i++)
    {
        buff[7+i] = data[i];
    }
    buff[7+dataLen]=creatLRC_ZKTeco(buff,7+dataLen);

    // send cmd
    //write_uart(buff, 8+dataLen);
    display(buff,8+dataLen);
}

void send_status_ZKTeco(int price)
{
    printf("send_status : %d\n" ,price);

    char cmd = 0xA2;

//    const int dataLen = 4;
//    unsigned char data[dataLen];
//    int216Code(price , data , dataLen);
    const int dataLen = 4;  // 数组和变量十六进制存储刚好相反
    unsigned char data[dataLen];
    price*=100;
    data[0]=price>>24;
    data[1]=price>>16;
    data[2]=price>>8;
    data[3]=price;

    cmdCreate_ZKTeco(cmd,data,dataLen);
}

//void generateAscendRandomNumber()
//{
//    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
//    for(i=0;i<10;i++)
//    {
//        numbersList.append(qrand()%65535);
//    }
//    qSort(numbersList.begin(),numbersList.end());
//    for(i=0;i<10;i++)
//    {
//        qDebug()<<numbersList[i];
//    }
//}


int main(int argc, char *argv[])
{
    char buff[]={0x0,0x0,0x0,0x64};
    send_status_ZKTeco(1);

    return 0;
}













