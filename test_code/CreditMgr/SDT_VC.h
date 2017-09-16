/*
 *****************************************************************************
 * Copyright @ 2011 by YOWO RFID                                             *
 * All rights are reserved.                                                  *
 *                                                                           *
 * YW SDT RFID Reader   Include File                                         *
 * C++                                                                     *
 * SDT.h                                                                 *
 * file vesion: 1.2                                                          *
 * web: http://www.youwokeji.com.cn                                          *
 * tel: 010-59395668                                                         *
 *****************************************************************************
*/


#define REQUESTMODE_ALL                         0x52
#define REQUESTMODE_ACTIVE                      0x26

#define SAM_BOUND_9600 			        0
#define SAM_BOUND_38400 		        1

#define PASSWORD_A                              0x60
#define PASSWORD_B                              0x61

#define  ENCRYPT                                00
#define  DECRYPT                                01


#define RFIDFUNCTION int


//*******************************************DLL��غ��� ************************/


/*    ������ YW_GetDLLVersion
 *    ���ƣ� ���ص�ǰDLL�İ汾
 *    ��������
 *  ����ֵ���汾��
*/ 
RFIDFUNCTION  YW_GetDLLVersion(void);


/*    ������ DES
 *    ���ƣ� DES�ӽ��ܺ���
 *    ������cModel�� ���ܻ��߽��� �� 0���ܣ�1���ܣ���Ӧ����ENCRYPT =0��DECRYPT = 1
              pkey���ӽ�����Կָ�룬8���ֽ�
            inData��Ҫ�ӽ��ܵ�����ָ�룬8���ֽ�
            OutData: �����ӽ��ܺ������ָ�룬8���ֽ�
 *  ����ֵ��������
*/ 
RFIDFUNCTION  DES(unsigned char cModel, unsigned char *pkey, unsigned char *in, unsigned char *out);


/*    ������ DES3
 *    ���ƣ� 3DES�ӽ��ܺ���
 *    ������cModel�� ���ܻ��߽��� �� 0���ܣ�1���ܣ���Ӧ����ENCRYPT =0��DECRYPT = 1
              pkey���ӽ�����Կָ�룬16���ֽ�
            inData��Ҫ�ӽ��ܵ�����ָ�룬8���ֽ�
            OutData: �����ӽ��ܺ������ָ�룬8���ֽ�
 *  ����ֵ��������
*/ 
RFIDFUNCTION  DES3(unsigned char cModel, unsigned char *pKey, unsigned char *pInData, unsigned char *pOutData);

/*    ������ DES3_CBC
 *    ���ƣ� ��������3DES�ӽ��ܺ���
 *    ������cModel�� ���ܻ��߽��� �� 0���ܣ�1���ܣ���Ӧ����ENCRYPT =0��DECRYPT = 1
             pkey���ӽ�����Կָ�룬8���ֽ�
             inData��Ҫ�ӽ��ܵ�����ָ�룬8���ֽ�
             OutData: �����ӽ��ܺ������ָ�룬8���ֽ�
             pIV:    ����ָ�룬8���ֽ�

 *  ����ֵ��������
*/ 
RFIDFUNCTION  DES3_CBC(unsigned char cModel,  unsigned char *pKey,unsigned char *pInData, unsigned char *pOutData, unsigned char *pIV);


//*******************************************��д����غ��� ************************/


/*    ������ YW_USBHIDInitial
 *    ���ƣ� ����USB�˿ڳ�ʼ��
 *    ������ ��
 *  ����ֵ��>0Ϊ�ɹ� ������ʧ��
*/ 
RFIDFUNCTION YW_USBHIDInitial(void);

/*    ������ YW_USBHIDInitial
 *    ���ƣ� ����USB�˿��ͷ�
 *    ������ ��
 *  ����ֵ��>0Ϊ�ɹ�������ʧ��
*/ 
RFIDFUNCTION YW_USBHIDFree(void);


/*    ������ YW_SetReaderID
 *    ���ƣ� ���ö�д��ID
 *    ������ OldID����д���ϵ�ID
             NewID����д���µ�ID
 *  ����ֵ��>0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_SetReaderID(int OldID, int NewID);


/*    ������ YW_GetReaderID
 *    ���ƣ� ��ȡ��д��ID
 *    ������ ReaderID����д��ID�ţ�0Ϊ�㲥��ַ
 *  ����ֵ��>=0Ϊ�ɹ�������Ϊ��д��ID ������ʧ��
*/
RFIDFUNCTION YW_GetReaderID(int ReaderID);

/*    ������ YW_GetReaderVersion
 *    ���ƣ� ��ȡ��д���İ汾
 *    ������ ReaderID����д��ID�ţ�0Ϊ�㲥��ַ
 *  ����ֵ��>=0Ϊ�ɹ�������Ϊ��д���汾 ������ʧ��
*/
RFIDFUNCTION YW_GetReaderVersion(int ReaderID);

/*    ������ YW_GetReaderSerial
 *    ���ƣ� ��ȡ��д�������к�
 *    ������     ReaderID����д��ID�ţ�0Ϊ�㲥��ַ
             ReaderSerial�����Ϊ��д�������кţ�8���ֽ�
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_GetReaderSerial(int ReaderID, char *ReaderSerial);


/*    ������ YW_GetReaderNo
 *    ���ƣ� ��ȡ��д�����ͺ�
 *    ������ ReaderID����д��ID�ţ�0Ϊ�㲥��ַ
              ReadeNo�����Ϊ��д�����ͺţ�8���ֽ�
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_GetReaderNo(int ReaderID, char *ReadeNo);



/*    ������ YW_Buzzer
 *    ���ƣ� ��������������
 *    ������ ReaderID����д��ID�ţ�0Ϊ�㲥��ַ
              Time_ON����������ʱ�䣬��λ0.1s
             Time_OFF������������ʱ�䣬��λ0.1s
                Cycle��  ������ѭ������
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_Buzzer(int ReaderID,int Time_ON, int Time_OFF, int Cycle);   //5



/*    ������ YW_Led
 *    ���ƣ� LED�Ʋ�������
 *    ������ ReaderID����д��ID�ţ�0Ϊ�㲥��ַ
             LEDIndex��ѡ��Ҫ������LED��
              Time_ON�� ������ʱ�䣬��λ0.1s
             Time_OFF���Ʋ���ʱ�䣬��λ0.1s
                Cycle��   ѭ������
             LedIndexOn�����Ҫ���ĵ�
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_Led(int ReaderID,int LEDIndex, int Time_ON, int Time_OFF, int Cycle, int LedIndexOn);    //6



/*    ������ YW_AntennaStatus
 *    ���ƣ� �������ߣ������п�����֮ǰ���뿪������
 *    ������  ReaderID����д��ID�ţ�0Ϊ�㲥��ַ
               Status: trueΪ�������ߣ� falseΪ�ر�����
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_AntennaStatus(int ReaderID,bool Status);



//*******************************************ISO14443A��Ƭ�������� ************************/



/*    ������ YW_RequestCard
 *    ���ƣ� Ѱ��TypeA��
 *    ������  ReaderID����д��ID�ţ�0Ϊ�㲥��ַ
           RequestMode: Ѱ��ģʽ
                        ���п�  ���� REQUESTMODE_ALL=$52;
                        ����Ŀ� ���� REQUESTMODE_ACTIVE=$26;
           CardType�����������
                      0x4400 -> Ultralight/UltraLight C /MifarePlus(7Byte UID)
                      0x4200 -> MifarePlus(7Byte UID)
                      0x0400 ->Mifare Mini/Mifare 1K (S50) /MifarePlus(4Byte UID)
                      0x0200->Mifare_4K(S70)/ MifarePlus(4Byte UID)
                      0x4403 ->Mifare_DESFire
                      0x0800 ->Mifare_Pro
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_RequestCard(int ReaderID,unsigned char RequestMode, unsigned short *CardType);


/*    ������ YW_AntiCollide
 *    ���ƣ� �ó�ͻ����
 *    ������  ReaderID����д��ID�ţ�0Ϊ�㲥��ַ
           LenSNO:   ������ŵĳ���
              SNO��  �������
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_AntiCollide(int ReaderID,unsigned char *LenSNO, unsigned char *SNO);



/*    ������ YW_CardSelect
 *    ���ƣ� ѡ��
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ
                LenSNO:   Ҫѡ�񿨿��ŵĳ���
                   SNO��  Ҫѡ�񿨿���
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_CardSelect(int ReaderID,char LenSNO, unsigned char *SNO);


/*    ������ YW_KeyAuthorization
 *    ���ƣ� M1����Ȩ
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ
                KeyMode:  ��Կѡ��Key A����Key B
                           ����  PASSWORD_A           =    $60;
                           ����  PASSWORD_B           =    $61;
              BlockAddr��  Ҫ��Ȩ�Ŀ�
                   Key��  ��Կ�ֽ�ָ�룬6�ֽ�
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_KeyAuthorization(int ReaderID,int KeyMode, int BlockAddr, unsigned char *Key);


/*    ������ YW_ReadaBlock
 *    ���ƣ� ��ȡM1��һ����
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ
             BlockAddr:   Ҫ��ȡ�Ŀ��
              LenData��  Ҫ��ȡ���ֽ��������Ϊ16
                 Data��  ����ָ��
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_ReadaBlock(int ReaderID,int BlockAddr, int LenData, unsigned char *pData);


/*    ������ YW_WriteaBlock
 *    ���ƣ� д��M1��һ����
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ
             BlockAddr:   Ҫд��Ŀ��
              LenData��  Ҫ��ȡ���ֽ���������Ϊ16
                 Data��  ����ָ��
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_WriteaBlock(int ReaderID,int BlockAddr, int LenData, unsigned char *pData);


/*    ������ YW_Purse_Initial
 *    ���ƣ� M1����ĳһ���ʼ��Ǯ��
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ
             BlockAddr:   Ҫ��ʼ��Ǯ���Ŀ��
              IniValue��  Ǯ����ʼ��ֵ
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_Purse_Initial(int ReaderID,int BlockAddr, int IniMoney);


/*    ������ YW_Purse_Read
 *    ���ƣ� ��ȡM1��ĳ�����Ǯ��ֵ
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ
             BlockAddr:   Ҫ��ʼ��Ǯ���Ŀ��
                Value��  Ǯ���ĵ�ǰֵ
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_Purse_Read(int ReaderID,int BlockAddr, int *Money);  //16


/*    ������ YW_Purse_Decrease
 *    ���ƣ� ��Ǯ�����м�ֵ����
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ
             BlockAddr:   Ҫ��ʼ��Ǯ���Ŀ��
             Decrement��  Ҫ��ȥ��ֵ
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION  YW_Purse_Decrease(int ReaderID,int BlockAddr, int Decrement);  //17


/*    ������ YW_Purse_Decrease
 *    ���ƣ� ��Ǯ�����м�ֵ����
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ
             BlockAddr:   Ҫ��ʼ��Ǯ���Ŀ��
             Charge��    Ҫ���ӵ�ֵ
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_Purse_Charge(int ReaderID,int BlockAddr, int Charge);  //18


/*    ������ YW_Purse_Decrease
 *    ���ƣ� ��Ǯ������Restor����
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ
             BlockAddr:   Ǯ���Ŀ��
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_Restore(int ReaderID,int BlockAddr);


/*    ������ YW_Purse_Decrease
 *    ���ƣ� ��Ǯ������Transfer����
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ
             BlockAddr:   Ǯ���Ŀ��
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_Transfer(int ReaderID,int BlockAddr);



/*    ������ YW_CardHalt
 *    ���ƣ� ��M1������Halt����
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_CardHalt(int ReaderID);


/*    ������ YW_AntiCollide_Level
 *    ���ƣ� ��M1������n������ײ
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ
              Leveln��n������ײ����1��3
              LenSNO�����ŵĳ���
                SNO������ָ��
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_AntiCollide_Level(int ReaderID,int Leveln,char *LenSNO, unsigned char *SNO);



/*    ������ YW_SelectCard_Level
 *    ���ƣ� ��M1������n��ѡ��
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ
              Leveln��n������ײ����1��3
                 SAK�����SAK
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_SelectCard_Level(int ReaderID,int Leveln,unsigned char *SAK);


/*    ������ YW_AntiCollideAndSelect
 *    ���ƣ� ��M1�����з���ײ��ѡ��
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ

         MultiCardMode���Զ��ſ��Ĵ���ʽ
                         00  ���ض࿨����
                         01  ����һ�ſ�Ƭ
               CardMem�����ؿ����ڴ����
                SNOLen: ������ŵĳ���
                   SNO���������к�        
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_AntiCollideAndSelect(int ReaderID, unsigned char MultiCardMode, unsigned char *CardMem, int *SNLen, unsigned char *SN);


/*    ������ YW_RequestAntiandSelect
 *    ���ƣ� ��M1��Ѱ��������ײ��ѡ��
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ
           RequestMode��Ѱ��ģʽ
                        ���п�  ���� REQUESTMODE_ALL=$52;
                        ����Ŀ� ���� REQUESTMODE_ACTIVE=$26;
         MultiCardMode���Զ��ſ��Ĵ���ʽ
                         00  ���ض࿨����
                         01  ����һ�ſ�Ƭ
                 ATQA �� ATQA
                  SAK ��SAK
                SNOLen: ������ŵĳ���
                   SNO���������к�        
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_RequestAntiandSelect(int ReaderID,int SearchMode,int MultiCardMode,unsigned short *ATQA,unsigned char *SAK,unsigned char *LenSNO,unsigned char *SNO);


/*    ������ YW_WriteM1MultiBlock
 *    ���ƣ� ��M1��д���
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ
              StartBlock����ʼ���
              BlockNums�� Ҫд�ÿ�����
                LenData�� Ҫд�����ݳ��ȣ�16�ı���
                 pData��  Ҫд������
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_WriteM1MultiBlock(int ReaderID, int StartBlock, int BlockNums, int LenData, char *pData);


/*    ������ YW_ReadM1MultiBlock
 *    ���ƣ� ��M1����ȡ���
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ
              StartBlock����ʼ���
              BlockNums�� Ҫ��ȡ�Ŀ�����
                LenData�� ���ض�ȡ�����ݳ���
                 pData��  ���ص�����
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_ReadM1MultiBlock(int ReaderID, int StartBlock, int BlockNums, int *LenData, char *pData);


//*******************************************UltraLight��Ƭ�������� ************************/


/*    ������ YW_UltraLightRead
 *    ���ƣ� Ultra Light ����ȡ��
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ
              BlockID �� ��ȡ�Ŀ��
                 pData��  ���ص�����
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_UltraLightRead(int ReaderID, int BlockID, unsigned char *pData);


/*    ������ YW_UltraLightWrite
 *    ���ƣ� Ultra Light ��д��
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ
              BlockID �� Ҫд�Ŀ��
                 pData��  д�������
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_UltraLightWrite(int ReaderID, int BlockID, unsigned char *pData);


//*******************************************Type A CPU ��Ƭ�������� ************************/


/*    ������ YW_TypeA_Reset
 *    ���ƣ� Type A CPU����λ
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ
           RequestMode��Ѱ��ģʽ
                        ���п�  ���� REQUESTMODE_ALL=$52;
                        ����Ŀ� ���� REQUESTMODE_ACTIVE=$26;
         MultiCardMode���Զ��ſ��Ĵ���ʽ
                         00  ���ض࿨����
                         01  ����һ�ſ�Ƭ
                 rtLen: ��λ�������ݵĳ���        
                 pData�� ��λ���ص�����
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_TypeA_Reset(int ReaderID, unsigned char Mode, unsigned char MultiMode, int *rtLen, unsigned char *pData);


/*    ������ YW_TypeA_COS
 *    ���ƣ� Type A CPU��ִ��COS����
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ
                LenCOS��  COS����ĳ���
               Com_COS��  COS����
                 rtLen:   ִ��COS�󷵻ص����ݳ���
                 pData��  ִ��COS�󷵻ص�����
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION  YW_TypeA_COS(int ReaderID, int LenCOS, unsigned char *Com_COS, int *rtLen, unsigned char *pData);


/*    ������ YW_SAM_ResetBaud
 *    ���ƣ� SAM����λ����������
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ
             SAMIndex:   SAM�����
             BoundIndex:   ���������
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_SAM_ResetBaud(int ReaderID,int SAMIndex, int BaudIndex);


/*    ������ YW_SAM_Reset
 *    ���ƣ� SAM����λ
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ
              SAMIndex:   SAM�����
               DataLen:   ���ظ�λ���ݵĳ���
                 pData:   ��λ����
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_SAM_Reset(int ReaderID,int SAMIndex, int *rtLen, unsigned char *pData);

/*    ������ YW_SAM_Reset
 *    ���ƣ� SAM����λ
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ
              SAMIndex:   SAM�����
                LenCOS:   COS�����
               Com_COS:   COS��������
               DataLen:   ���ظ�λ���ݵĳ���
                 pData:   ��λ����
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_SAM_COS(int ReaderID,int SAMIndex, int LenCOS, unsigned char *Com_COS, int *rtLen, unsigned char *pData);


/*    ������ YW_SAM_PPSBaud
 *    ���ƣ� SAM��PPS����������
 *    ������  ReaderID��  ��д��ID�ţ�0Ϊ�㲥��ַ
              SAMIndex:   SAM�����
             BoundIndex:   ���������
 *  ����ֵ��>=0Ϊ�ɹ�������ʧ��
*/
RFIDFUNCTION YW_SAM_PPSBaud(int ReaderID,int SAMIndex, int BaudIndex);


