#ifndef NETWORKMGR_H
#define NETWORKMGR_H

#include <QObject>
#include <boost/noncopyable.hpp>
#include <singleton.h>
#include <string.h>
//#include "error_mgr_def.h"
//#include "Message_send_qr.h"
#include <QGraphicsScene>
//#include "product_def.h"
#define LOGIN_TIME 10000
#define HB_TIME    30000
#define ERROR_TIME 3*1000*60

enum payType
{
  NO_PAY   =0,
  FREE_PAY = 1,
  QR_PAY,
  CASH_PAY,
  QUICKPASS_PAY,
  CODE_PAY,
  FASTCODE_PAY,
  USER_QR_PAY,
  WEI_PAY,
  ALI_PAY,
  DOG_Pay,

  ZT_WEI_PAY,
  ZT_BAO_PAY,
  TEST,
  ABC_PAY,
 DRAGON_PAY,
    XINGYE_WEI_PAY,
    XINGYE_ALI_PAY,

};
class networkMgr : public QObject , boost::noncopyable
{
    Q_OBJECT
    friend class singleton<networkMgr>;
public:
    static networkMgr& getInstance();

    bool initNetwordEnvironment();
    void addScene(QGraphicsScene* scene);

    void setCashMount(int mount);
    void setPayType(payType type);
private:
    explicit networkMgr(QObject *parent = 0);
    ~networkMgr();

    QString m_signStr;
    int reconnectTime;
    QTimer* reconnectTimer;
    QTimer* reloginTimer;
    QTimer* hbTimer;
    QTimer* reSendErrorTimer;
    QTimer* startProductDoneTimer;

    int m_machinenum;
    string m_lastOrder_no;
    string m_lastProductDoneMsg;
    int m_cashMount;
    payType m_payType;
    QGraphicsScene* m_scene;

    bool isUseProductsMake;
    bool isHasInit;
    bool isMachineStatueNormal;
signals:
    void sig_qr_info(string , Qr_Type);
    void sig_need_resend_errorinfo();
    void sig_start_rinsing();
    void sig_paydonefalse();
    void sig_cardcode_false();

    void sig_exit_player();
public slots:

    void firstSendDoorStatus();
    void startNetwork();

    void onConnected();
    void ondisConnected();
    void onrecvMsg(QString);
    void onrecvErrorMsg(QString);


    void sendLogin();
    void sendQrCodeInfo(ProductId proID , long sPriceString , Qr_Type type , bool need_orderno = true);
    void sendMakeProduce(bool isOK , ProductId id);
    void sendErrorInfo(ErrorPair_t error, bool isSet);
    void sendSpecialError(bool isSet , string error_code , bool is_fatal_error , bool is_pessistance_error , string error_description );
    void sendErrorEmpty();
    void sendCupBlock();
    void sendDoorOpen();
    void sendMiniDoorOpen();
    void sendDoorClose();
    void sendPayDone_r();
    void sendHB();
    void sendBillOfLadingInfo(ProductId proID , long sPriceString ,string cardcode);

    void sendIngredits();

    void parameter_error();

    void resendError();
    void setMachineStaus(bool b);

    void startErrorTimer();
    void stopErrorTimer();

    void resendProductDone();
    void stopResendProductDone();
private:
    void onRecvLoginMsg(QString msg);
    void onRecvQrcode(QString msg);
    void onRecvPayDone(QString msg);
    void onRecvProducts(QString msg);
    void onRecvMachineStatus();
    void onRecvPriceSet(QString msg);
    void onRecvQrDiscount(QString msg);
    void resetServerTime(string dateTime);
    void onRecvUpgradMsg(QString msg);
    void onRecvBottommenu(QString msg);
    void onRecvMiniDoorOpen();

    void onRecvShowScreensaver(QString msg);
    void onRecvClearScreensaver();
    QString getHostMacAddress();

    void splistMsg(QString msg , QStringList& strlist);
    void handleMsg(QString msg);

    string createNewOrdernum();
};

#endif // NETWORKMGR_H
