#include "networkmgr.h"
#include "networkimp.h"

networkMgr::networkMgr(QObject *parent) : QObject(parent)
  , reconnectTime(5000)
  , reconnectTimer(NULL)
  , reloginTimer(NULL)
  , reSendErrorTimer(NULL)
  , m_machinenum(0)
  , m_scene(NULL)
  , hbTimer(NULL)
  , startProductDoneTimer(NULL)
  , m_lastOrder_no("")
  , isUseProductsMake(false)
  , isHasInit(false)
  , isMachineStatueNormal(true)
  , m_lastProductDoneMsg("")
{
    networkImp& net_imp = networkImp::getInstance();

    connect(&net_imp , SIGNAL(sig_disconnect()) , this , SLOT(ondisConnected()));
    connect(&net_imp , SIGNAL(sig_connected()) , this , SLOT(onConnected()));
    connect(&net_imp , SIGNAL(sig_revMsg(QString)) , this , SLOT(onrecvMsg(QString)));
    connect(&net_imp , SIGNAL(sig_error_parameter()) , this , SLOT(parameter_error()));

    if(reconnectTimer == NULL)
    {
        reconnectTimer = new QTimer(this);
        connect(reconnectTimer , SIGNAL(timeout()) , this , SLOT(startNetwork()));
    }

    if(reloginTimer == NULL)
    {
        reloginTimer = new QTimer(this);
        connect(reloginTimer , SIGNAL(timeout()) , this , SLOT(sendLogin()));
    }

    if(hbTimer == NULL)
    {
        hbTimer = new QTimer(this);
        connect(hbTimer , SIGNAL(timeout()) , this , SLOT(sendHB()));
    }

    if(reSendErrorTimer == NULL)
    {
        reSendErrorTimer = new QTimer(this);
        connect(reSendErrorTimer , SIGNAL(timeout()) , this , SLOT(resendError()));
    }

    if(startProductDoneTimer == NULL)
    {
        startProductDoneTimer = new QTimer(this);
        connect(startProductDoneTimer , SIGNAL(timeout()) , this , SLOT(resendProductDone()));
    }
}

networkMgr::~networkMgr()
{

}

networkMgr& networkMgr::getInstance()
{
    return singleton<networkMgr>::instance();
}

void networkMgr::resendError()
{
    emit sig_need_resend_errorinfo();
}

bool networkMgr::initNetwordEnvironment()
{
    networkImp& net_imp = networkImp::getInstance();
    //get ip port ips machinenum

    bool isSuccess = false;
    m_machinenum = IMachineNumConfig::getInstance().getVmcNO();
    if(net_imp.init(IVersionConfig::getInstance().getServerIP() ,
                  IVersionConfig::getInstance().getServerPort(),
                  m_machinenum))
    {
        QString ipString = QString::fromStdString(IVersionConfig::getInstance().getServerIPS());
        if(ipString != "")
        {
            QStringList  ips= ipString.split(",");
            if(0 !=ips.size())
            {
                for(int i = 0 ; i<ips.size() ;++i)
                    net_imp.addIPs(ips.at(i).toStdString());
            }
        }
        isSuccess = true;
    }
    if(isSuccess)
    {
        QTime t;
        t= QTime::currentTime();
        qsrand(t.msec()+t.second()*1000);
        if(5000 == reconnectTime)
            reconnectTime += 1000 * (qrand()%10);

        m_signStr    = QString::fromStdString(IVersionConfig::getInstance().getVerificationCode());
        m_signStr+= QString::number(IMachineNumConfig::getInstance().getVmcNO());
        MD5 md5(m_signStr.toStdString());
        m_signStr = QString::fromStdString(md5.md5());
    }
    isHasInit = isSuccess;
    return isSuccess;
}

void networkMgr::startNetwork()
{
    networkImp& net_imp = networkImp::getInstance();
    if(!isHasInit)
        initNetwordEnvironment();

    if(net_imp.connectToServer())
    {
        reconnectTimer->stop();
    }
    else
    {
        IErrorMgr::getInstance().addSysError(eNoInternet);
        reconnectTimer->stop();
        reconnectTimer->start(reconnectTime);
    }
}

void networkMgr::onConnected()
{
    sendLogin();
}
void networkMgr::ondisConnected()
{
    IErrorMgr::getInstance().addSysError(eNoInternet);
    reconnectTimer->stop();
    reloginTimer->stop();
    hbTimer->stop();
    startNetwork();
}

void networkMgr::parameter_error()
{
    IErrorMgr::getInstance().addSysError(eNoInternet2);
    reconnectTimer->stop();
    reloginTimer->stop();
    hbTimer->stop();
}

void networkMgr::splistMsg(QString msg , QStringList& strlist)
{
    QString tmpMsg = msg;
    while(1)
    {
        if(tmpMsg == "")
            break;
        else if(tmpMsg.size() < 12)
            break;
        else
        {
            MessageBase msg_base;
            bool b = msg_base.parseMessage(tmpMsg.toStdString());
            if(!b)
                return;

            if(msg_base.getLength() ==  tmpMsg.length())
            {
                strlist.append(tmpMsg);
                return;
            }
            else if(msg_base.getLength() > tmpMsg.length())
            {
                return;
            }
            else
            {
                strlist.append(tmpMsg.left(msg_base.getLength()));
                tmpMsg = tmpMsg.right(tmpMsg.size() - msg_base.getLength());
            }
        }
    }
}

void networkMgr::onrecvMsg(QString msg)
{
    MessageBase msg_base;
    bool b = msg_base.parseMessage(msg.toStdString());
    if(!b)
        return;

    if(msg.length() < 12 && msg.length() > 1024)
        return;


    if(msg_base.getLength() < msg.length())
    {

        QStringList strList ;
        splistMsg(msg , strList);
        for(int i = 0 ; i<strList.size() ; ++i)
        {
            if(strList.at(i).size()>12 && strList.at(i).size() < 1024)
                handleMsg(strList.at(i));
            else
                return;
        }
    }
    else if(msg_base.getLength() == msg.length())
    {

        handleMsg(msg);
    }
    else
    {

        return;
    }
}

void networkMgr::handleMsg(QString msg)
{
    MessageBase msg_base;
    msg_base.parseMessage(msg.toStdString());
    string cmd = msg_base.getCmd();
    if (cmd == "")
    {
        return;
    }
    else
    {
        hbTimer->stop();

        try
        {
            if(IVersionConfig::getInstance().isyoubao())
                hbTimer->start(10000);
            else
                hbTimer->start(HB_TIME);

            if (cmd == "login_r")
            {
                onRecvLoginMsg(msg);
            }
            if(cmd =="priceset")
            {
                onRecvPriceSet(msg);
            }
            if (cmd == "qrcode_r")
            {
                onRecvQrcode(msg);
            }
            if(cmd == "url_r")
            {
                onRecvQrcode(msg);
            }
            if(cmd == "pay_done")
            {
                onRecvPayDone(msg);
            }
            if (cmd == "products") // for test
            {
                onRecvProducts(msg);
            }
            if(cmd == "reboot")
            {
                IErrorMgr::getInstance().clearAllError();
                IErrorMgr::getInstance().clearAllWarning();

                BoardMachine* bMachine = MachineHelper::getBoardMachine();
                if (NULL != bMachine)
                {
                    bMachine->resetSlaves();
                }
                ::rebootStum();
            }
            if(cmd == "opendoor")
            {
                lockDoor(false , 255);
            }
            if(cmd == "openminidoor")
            {
                onRecvMiniDoorOpen();
            }
            if(cmd == "statusquery")
            {
                onRecvMachineStatus();
            }
            if(cmd == "discount")
            {
                onRecvQrDiscount(msg);
            }
            if(cmd == "rinsing")
            {
                emit sig_start_rinsing();
            }
            if(cmd == "upgrade")
            {
                onRecvUpgradMsg(msg);
            }
            if(cmd == "error_r")
            {
                if(reSendErrorTimer)
                {
                    reSendErrorTimer->stop();
                }
            }
            if(cmd == "productdone_r")
            {
                stopResendProductDone();
            }
            if(cmd == "bottommenu")
            {
                onRecvBottommenu(msg);
            }
            if(cmd == "screensaver")
            {
                onRecvShowScreensaver(msg);
            }
            if(cmd == "clearscreensaver")
            {
                onRecvClearScreensaver();
            }
            if(cmd == "querysupplies")
            {
                sendIngredits();
            }
        }
        catch(...)
        {
            return;
        }

    }
}

void networkMgr::onRecvClearScreensaver()
{
    ::myRemoveDir("./screensaver");

    ::rebootStum();
}

void networkMgr::onRecvBottommenu(QString msg)
{
    Message_function fun;
    fun.parseMessage(msg.toStdString());
    fun.parse_bottommenu();
    if(fun.m_recv_vmcno != m_machinenum)
        return;

    IVersionConfig::getInstance().setUseOtherButtons(fun.isShowBottomMenu);
    ::rebootStum();
}

void networkMgr::onRecvShowScreensaver(QString msg)
{

}

void networkMgr::onRecvUpgradMsg(QString msg)
{
    UpdateView * view = new UpdateView();
       view->init(false);
       if(m_scene)
       {
           view->setPos(0, 0);
           view->resize(1920,1080);
           m_scene->addItem(view);

       }

       Message_login upgradeMsg;
       upgradeMsg.parseMessage(msg.toStdString());
       string urlPath = upgradeMsg.getUpgradeXMLPath();
       QStringList arguments;
       arguments << "-qws";
       arguments << urlPath.c_str();

       QProcess * process = new QProcess(this);
       process->start("./upgrade" ,  arguments);
}

void networkMgr::resendProductDone()
{
    if(""!= m_lastProductDoneMsg)
    {
        networkImp& net_imp = networkImp::getInstance();
        string msg = m_lastProductDoneMsg;
        net_imp.sendMsgToServer(msg);
    }
}

void networkMgr::stopResendProductDone()
{
    if(""!= m_lastProductDoneMsg)
    {
       m_lastProductDoneMsg = "";
       startProductDoneTimer->stop();
    }
}
void networkMgr::onRecvMachineStatus()
{
    Message_send_emptyError status;
    string  msg = status.packageMachineStatus(isMachineStatueNormal , m_machinenum);
    networkImp& net_imp = networkImp::getInstance();
    net_imp.sendMsgToServer(msg);
}

void networkMgr::onrecvErrorMsg(QString)
{
    return;
}

QString networkMgr::getHostMacAddress()
{
    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();
    int nCnt = nets.count();
    QString strMacAddr = "";

    QString macAddress = "";
    for(int i = 0; i < nCnt; i ++)
    {
        if(nets[i].flags().testFlag(QNetworkInterface::IsUp) &&
                //nets[i].flags().testFlag(QNetworkInterface::IsRunning) &&
                !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            if(macAddress != "")
                macAddress+= ",";

            strMacAddr = nets[i].hardwareAddress();
            macAddress+= strMacAddr;
        }
    }
    return strMacAddr;
}

void networkMgr::sendLogin()
{
    //QString mac = getHostMacAddress();
    int comp_id = IMachineNumConfig::getInstance().getCompanyid();
    networkImp& net_imp = networkImp::getInstance();
    Message_send_login slogin;
    string loginMsg = slogin.packageLogin(m_machinenum ,comp_id, m_signStr.toStdString());
    net_imp.sendMsgToServer(loginMsg , true);

    reloginTimer->stop();
    reloginTimer->start(LOGIN_TIME);
}

void networkMgr::sendQrCodeInfo(ProductId proID , long sPriceString , Qr_Type type , bool need_orderno)
{/*
    if(isUseProductsMake)
        return;

    networkImp& net_imp = networkImp::getInstance();

    if(need_orderno)
    {
        QString tmp = QDateTime::currentDateTime().toString();
        QTime t;
        t= QTime::currentTime();
        qsrand(t.msec()+t.second()*1000);
        int n = qrand()%999;
        tmp+= QString::number(m_machinenum);
        tmp+= QString::number(n);
        MD5 md5(tmp.toStdString());
        string result = md5.md5();
        m_lastOrder_no = result;
    }


    int disc = IVersionConfig::getInstance().getDiscount();
    sPriceString = sPriceString * disc / 100;
    Message_send_qr sqr;
    string qrString = sqr.packageQr(m_machinenum , proID , sPriceString , m_lastOrder_no , type);
    net_imp.sendMsgToServer(qrString);*/

    stopResendProductDone();
    if(isUseProductsMake)
        return;

    networkImp& net_imp_tmp = networkImp::getInstance();

    if(need_orderno)
    {
        QDateTime time = QDateTime::currentDateTime(); // 订单号随机数增加???位数
        QString tmp = time.toString("yyyyMMddhhmmss"); // 不采用MD5加密方式

        QTime t;
        t= QTime::currentTime();
        qsrand(t.msec()+t.second()*1000);
        int n = qrand()%100000;
        tmp+= QString::number(m_machinenum);
        QString str;
        str.sprintf("%05d",n);
        tmp+= str;
        //MD5 md5(tmp.toStdString());
        //string result = md5.md5();

        m_lastOrder_no = tmp.toStdString();
    }


    int disc = IVersionConfig::getInstance().getDiscount();
    sPriceString = sPriceString * disc / 100;
    Message_send_qr sqr;
    string qrString = sqr.packageQr(m_machinenum , proID , sPriceString , m_lastOrder_no , type);
    net_imp_tmp.sendMsgToServer(qrString);
}

void networkMgr::sendMakeProduce(bool isOK , ProductId id)
{
    networkImp& net_imp = networkImp::getInstance();
    string name = "";
    MDFMachine *mdfMachine=MachineHelper::getMDFMachine();
    if (mdfMachine)
    {
        MDFReader *mdfReader=mdfMachine->getMDFReader();
        assert(mdfReader!=NULL);
        vector<PRODUCT_DESCRIPTION> products;
        mdfReader->getAllProduct(products);
        vector<PRODUCT_DESCRIPTION>::iterator it = products.begin();
        for( ; it != products.end(); ++it)
        {
            if (it->Id == id)
            {
                name = it->name;
                break;
            }
        }
    }

    //all products
    CreditConfig_t config=ICreditConfig::getInstance().getCreditConfig();
    bool isFree = config.isFreeMode;

    int payMount = 0;
    string payType = "free";
    if(!isFree)
    {
        switch(m_payType)
        {
        case QR_PAY:
            payMount = m_cashMount;
            payType  = "qr_pay";
            break;
        case CASH_PAY:
            payMount = m_cashMount;
            payType  = "cash";
            break;
        case QUICKPASS_PAY:
            payMount = m_cashMount;
            payType  = "quickpass";
            break;
        case CODE_PAY:
            payMount = m_cashMount;
            payType  = "cardcode";
            break;
        case FASTCODE_PAY:
            payMount = m_cashMount;
            payType  = "fastcode";
            break;
        case USER_QR_PAY:
            payMount = m_cashMount;
            payType = "url";
            break;
        case WEI_PAY:
            payMount = m_cashMount;
            payType  = "wx_pub";
            break;

        case ALI_PAY:
            payMount = m_cashMount;
            payType  = "alipay";
            break;

        case DOG_Pay:
            payMount = m_cashMount;
            payType  = "jdpay";
            break;

        case ZT_WEI_PAY:
            payMount = m_cashMount;
            payType  = "wxPubQR";
            break;
        case ZT_BAO_PAY:
            payMount = m_cashMount;
            payType  = "alipayQR";
            break;
        case TEST:
            payMount = m_cashMount;
            payType  = "test";
            break;
        case ABC_PAY:
            payMount = m_cashMount;
            payType  = "abcpay";
            break;
        case DRAGON_PAY:
            payMount = m_cashMount;
            payType  = "dragonpay";
            break;
        case XINGYE_WEI_PAY:
            payMount = m_cashMount;
            payType  = "swf_wx";
            break;
        case XINGYE_ALI_PAY:
            payMount = m_cashMount;
            payType  = "swf_ali";
            break;
        }
    }

    string order = createNewOrdernum();
    if(payType == "cash")
        m_lastOrder_no = order;
    else if(payType == "free")
        m_lastOrder_no = order;
    else if(payType == "quickpass")
        m_lastOrder_no = order;
    else if(payType == "test")
        m_lastOrder_no = order;

    MessageMakeProduct mp;
    string msg = mp.packageMakeProductInfo(isOK , id ,name , m_machinenum ,payType , payMount , m_lastOrder_no);
    m_lastProductDoneMsg = msg;
    startProductDoneTimer->start(3000);
    net_imp.sendMsgToServer(msg);
/*
    if(isOK == true)
    {
        singleton<ingConfig>::instance().load();
        if(singleton<ingConfig>::instance().isActive())
        {
            int count = singleton<ingConfig>::instance().reduceCount();
            if(count <= 0)
            {
                singleton<ingConfig>::instance().resetCount();
                sendIngredits();
            }
        }
    }*/
    m_payType = FREE_PAY;
    m_cashMount = 0;
    m_lastOrder_no = "";
}
string networkMgr::createNewOrdernum()
{
    QDateTime time = QDateTime::currentDateTime(); // 订单号随机数增加???位数
    QString tmp = time.toString("yyyyMMddhhmmss"); // 不采用MD5加密方式

    QTime t;
    t= QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);
    int n = qrand()%100000;
    tmp+= QString::number(m_machinenum);
    QString str;
    str.sprintf("%05d",n);
    tmp+= str;
    //MD5 md5(tmp.toStdString());
    //string result = md5.md5();

    return tmp.toStdString();
    //m_lastOrder_no = tmp.toStdString();
}

void networkMgr::sendErrorInfo(ErrorPair_t error, bool isSet)
{
    networkImp& net_imp = networkImp::getInstance();
    ErrorKey_t key = error.first;
    ErrorInfo_t info = error.second;
    ErrorDBInfo_t errorInfo = info.dbInfo;

    string error_code = key.id;
    bool is_fatal_error = errorInfo.isFatal;
    bool is_pessistance_error = info.isPersistent;
    QString q_error_info = Langhelper::getLangTypeText(LangMgr::e_english , error_code.c_str());
    string error_description = q_error_info.toStdString();
    string datetime = errorInfo.dateTime;
    MessageErrorInfo ei;
    string msg = ei.packageErrorInfo(m_machinenum , isSet ,  error_code ,  is_fatal_error ,  is_pessistance_error ,  error_description , datetime);

    net_imp.sendMsgToServer(msg);
}


void networkMgr::startErrorTimer()
{
    if(reSendErrorTimer)
    {
        if(!reSendErrorTimer->isActive())
        {
            reSendErrorTimer->start(ERROR_TIME);
        }
    }
}
void networkMgr::stopErrorTimer()
{
    if(reSendErrorTimer)
    {
        if(reSendErrorTimer->isActive())
        {
            reSendErrorTimer->stop();
        }
    }
}
void networkMgr::sendSpecialError(bool isSet , string error_code , bool is_fatal_error , bool is_pessistance_error , string error_description)
{
    networkImp& net_imp = networkImp::getInstance();
    MessageErrorInfo ei;
    string msg = ei.packageErrorInfo(m_machinenum , isSet ,  error_code ,  is_fatal_error ,  is_pessistance_error ,  error_description , "");
    net_imp.sendMsgToServer(msg);

}

void networkMgr::sendErrorEmpty()
{
    networkImp& net_imp = networkImp::getInstance();
    Message_send_emptyError clearError;
    string msg = clearError.packageErrorEmpty(m_machinenum);
    net_imp.sendMsgToServer(msg);
}

void networkMgr::sendDoorClose()
{
    networkImp& net_imp = networkImp::getInstance();
    Message_send_emptyError doorClose;
    string msg = doorClose.packageDoorClose(m_machinenum);
    net_imp.sendMsgToServer(msg);
}

void networkMgr::sendDoorOpen()
{
    networkImp& net_imp = networkImp::getInstance();
    Message_send_emptyError doorOpen;
    string msg = doorOpen.packageDoorOpen(m_machinenum);
    net_imp.sendMsgToServer(msg);
}

void networkMgr::sendMiniDoorOpen()
{
    networkImp& net_imp = networkImp::getInstance();
    Message_send_emptyError miniDoorOpen;
    string msg = miniDoorOpen.packageMiniDoorOpen(m_machinenum);
    net_imp.sendMsgToServer(msg);
}

void networkMgr::sendCupBlock()
{
    networkImp& net_imp = networkImp::getInstance();
    Message_send_emptyError cupBlock;
    string msg = cupBlock.packageCupBlock(m_machinenum);
    net_imp.sendMsgToServer(msg);
}

void networkMgr::sendHB()
{
    networkImp& net_imp = networkImp::getInstance();
    Message_send_hb shb;
    net_imp.sendMsgToServer(shb.packageHB(m_machinenum , isMachineStatueNormal));
}
void networkMgr::resetServerTime(string dateTime)
{
    if(dateTime != "")
    {//YYYY-MM-DD HH:MM:SS
        QString dt = QString::fromStdString(dateTime);
        QStringList dtlist  = dt.split(" ");

        QStringList datelist = dtlist.at(0).split("-");
        QStringList timeList = dtlist.at(1).split(":");


        int year = datelist.at(0).toInt();
        int month = datelist.at(1).toInt();
        int day = datelist.at(2).toInt();
        int hour = timeList.at(0).toInt();
        int minute = timeList.at(1).toInt();
        int second = timeList.at(2).toInt();
        SystemTime t1(year,month,day,hour,minute,second);
        EvaDDCMPAdaptor::setDateTime(t1);
    }
}

void networkMgr::onRecvLoginMsg(QString msg)
{
    Message_login msgLogin;
    msgLogin.parseMessage(msg.toStdString());

    int res = msgLogin.getLoginSuccess();
    if (0 == res) //success
    {
        networkImp& net_imp = networkImp::getInstance();
        net_imp.setServerLogin();
        singleton<ErrorMgr>::instance().removeStatWarning("machine" ,eInternetConnectError);
        singleton<ErrorMgr>::instance().removeStatWarning("machine" ,eInternetConnectError2);
        IErrorMgr::getInstance().removeSysError(eNoInternet);
        IErrorMgr::getInstance().removeSysError(eNoInternet2);
        IErrorMgr::getInstance().removeSysError(eNoInternet3);
        //hb
        reloginTimer->stop();

        if(IVersionConfig::getInstance().isyoubao())
            hbTimer->start(10000);
        else
            hbTimer->start(HB_TIME);

        string dateTime = msgLogin.getDateTime();
        resetServerTime(dateTime);


        QTimer::singleShot(1*10*1000, this, SLOT(sendIngredits()));

        QTimer::singleShot(1*15*1000, this, SLOT(firstSendDoorStatus()));

        if(reSendErrorTimer)
        {
            reSendErrorTimer->start(ERROR_TIME);
        }

    }
    else
    {
        singleton<ErrorMgr>::instance().addStatWarning("machine" ,eInternetConnectError2,false);//server error

        if(reconnectTimer)
            reconnectTimer->stop();

        if(reloginTimer)
            reloginTimer->stop();

        if(hbTimer)
            hbTimer->stop();

        if(reSendErrorTimer)
            reSendErrorTimer->stop();

        networkImp& net_imp = networkImp::getInstance();
        net_imp.setDisableNetwork();
    }
}

void networkMgr::onRecvQrcode(QString msg)
{

    MessageQrinfo info;
    info.parseMessage(msg.toStdString());
    info.parseQrInfoMsg();
    // need credit code
    if(info.m_order_no != m_lastOrder_no)
    {
        return;
    }
    //printf("aaa\n");
    //printf(msg.toStdString().c_str());
    //printf("\n");

    Qr_Type type;
    if(info.m_qrType == "wx_pub")
        type = WEI;
    else if(info.m_qrType == "alipay")
        type = BAO;
    else if(info.m_qrType == "dragonpay")
        type = DRAGON;
    else if(info.m_qrType == "user")
        type = USER;
    else if(info.m_qrType == "url")
        type = USER;
    else if(info.m_qrType == "jdpay")
        type = DOG;
    else if(info.m_qrType == "wxPubQR")
        type = WEI;
    else if(info.m_qrType == "alipayQR")
        type = BAO;
    else if(info.m_qrType == "abcpay")
        type = S_ABC;
    else
        return;
    if("" == info.m_qrCode)
        return;

    emit sig_qr_info(info.m_qrCode , type);
}

void networkMgr::onRecvPriceSet(QString msg)
{
    Message_set_price setprice;
    setprice.parseMessage(msg.toStdString());
    setprice.parseSetPrice();

    if(setprice.m_recv_vmcno != m_machinenum)
        return;

    if(!setprice.price_nodes.empty())
    {
        for(int i = 0 ; i< setprice.price_nodes.size() ; ++i)
        {
            price_node node = setprice.price_nodes.at(i);
            if(node.price >= 0 && node.productid >= 100 & node.type>= 0 && node.type <  4)
            {

                MDFMachine* machine = MachineHelper::getMDFMachine();
                if(machine)
                {

                    EVAAdm & adm = singleton<EVAAdm>::instance();
                    adm.setItemPrice(MDFUID(machine, node.productid).getItemCode(), (EPriceList)node.type, node.price);
                }
            }
        }
        ::rebootStum();
    }
}

void networkMgr::sendPayDone_r()
{
    Message_send_qr paydone_r;
    string tmp = paydone_r.packagePaydone_r(m_machinenum , m_lastOrder_no);
    networkImp& net_imp = networkImp::getInstance();
    net_imp.sendMsgToServer(tmp);
}

void networkMgr::onRecvPayDone(QString msg)
{
    Message_paydone paydone;
    paydone.parseMessage(msg.toStdString());
    paydone.parsePaydone();
    if (m_machinenum != paydone.m_recv_vmcno)
    {
        return;
    }
    if (m_lastOrder_no != paydone.m_recv_orderno)
    {
        return;
    }
    if(paydone.m_isPaydone == false)
    {
        if(paydone.m_payType == "cardcode")
            emit sig_cardcode_false();

        return;
    }
    TCREDIT credit=paydone.m_amount;

    if (paydone.m_payType == "qr_pay")
    {
        setCashMount(credit);
        setPayType(QR_PAY);
    }
    else if(paydone.m_payType == "alipay")
    {
        setCashMount(credit);
        setPayType(ALI_PAY);
    }
    else if(paydone.m_payType == "wx_pub")
    {
        setCashMount(credit);
        setPayType(WEI_PAY);
    }
    else if(paydone.m_payType == "jdpay")
    {
        setCashMount(credit);
        setPayType(DOG_Pay);
    }
    else if(paydone.m_payType == "cardcode")
    {
        setCashMount(credit);
        setPayType(CODE_PAY);
    }
    else if(paydone.m_payType == "fastcode")
    {
        setCashMount(credit);
        setPayType(FASTCODE_PAY);
    }
    else if(paydone.m_payType == "url")
    {
        setCashMount(credit);
        setPayType(USER_QR_PAY);
    }
    else if(paydone.m_payType == "wxPubQR")
    {
        setCashMount(credit);
        setPayType(ZT_WEI_PAY);
    }
    else if(paydone.m_payType == "alipayQR")
    {
        setCashMount(credit);
        setPayType(ZT_BAO_PAY);
    }
    else if(paydone.m_payType == "abcpay")
    {
        setCashMount(credit);
        setPayType(ABC_PAY);
    }
    else if(paydone.m_payType == "dragonpay")
    {
        setCashMount(credit);
        setPayType(DRAGON_PAY);
    }
    else if(paydone.m_payType == "swf_wx")
    {
        setCashMount(credit);
        setPayType(XINGYE_WEI_PAY);
    }
    else if(paydone.m_payType == "swf_ali")
    {
        setCashMount(credit);
        setPayType(XINGYE_ALI_PAY);
    }

    sendPayDone_r();

    if(IVersionConfig::getInstance().isyoubao())
    {
        SlVenduiHelper helper;
        helper.onStart();
    }
    emit sig_exit_player();
    ISupervisorStateMgr::getInstance().postEvent(EvEnough());
}


void networkMgr::onRecvMiniDoorOpen()
{

}

void networkMgr::onRecvQrDiscount(QString msg)
{
    MessageQrDiscount qrDiscount;
    qrDiscount.parseMessage(msg.toStdString());
    qrDiscount.parseQrDiscount();

    if (m_machinenum != qrDiscount.m_vmcno)
    {
        return;
    }
    if(qrDiscount.m_discount >100 || qrDiscount.m_discount <= 0)
    {
        return;
    }

    IVersionConfig::getInstance().setDiscount(qrDiscount.m_discount);
    ::rebootStum();
}

void networkMgr::onRecvProducts(QString msg)
{
    Message_paydone paydone;
    paydone.parseMessage(msg.toStdString());
    paydone.parseProductsMsg();
    m_lastOrder_no = paydone.m_recv_orderno;
    if (m_machinenum != paydone.m_recv_vmcno)
    {
        return;
    }

    if(paydone.m_isPaydone == false)
    {
        printf("emit sig_cardcode_false()\n");
        emit sig_cardcode_false();
        return;
    }

    isUseProductsMake = true;
    TCREDIT credit= 0;//???
    setCashMount(credit);
    setPayType(FASTCODE_PAY);
    MDFMachine* machine = MachineHelper::getMDFMachine();

    string name = "";
    if(machine)
    {
        SlVenduiHelper helper;
        helper.onCancel();
        MDFReader *mdfReader=machine->getMDFReader();
        assert(machine!=NULL);
        vector<PRODUCT_DESCRIPTION> products;
        mdfReader->getAllProduct(products);
        vector<PRODUCT_DESCRIPTION>::iterator it = products.begin();
        for( ; it != products.end(); ++it)
        {
            if (it->Id == paydone.m_proid)
            {
                name = it->name;
                break;
            }
        }
        if(name == "")
        {

            isUseProductsMake = false;
            networkImp& net_imp = networkImp::getInstance();
            MessageMakeProduct mp;
            string msg = mp.packageMakeProductInfo(false ,
                                                   paydone.m_proid ,
                                                   name ,
                                                   m_machinenum ,
                                                   "fastcode" , 0 , m_lastOrder_no,
                                                   "can not find this product.");

            net_imp.sendMsgToServer(msg);
            return;
        }


        VendMenu_t menu = helper.getVendMenu();
        vector<VendMenuItem>::iterator itmenu = menu.menuItems.begin();
        int selectID = 0;
        for( ; itmenu != menu.menuItems.end(); ++itmenu, ++selectID)
        {
            if(itmenu->productId == paydone.m_proid)
            {
                //selectID = it->menuItemId;
                break;
            }
        }
        if(selectID >= menu.menuItems.size())
        {
            isUseProductsMake = false;
            networkImp& net_imp = networkImp::getInstance();
            MessageMakeProduct mp;
            string msg = mp.packageMakeProductInfo(false ,
                                                   paydone.m_proid ,
                                                   name ,
                                                   m_machinenum ,
                                                   "fastcode" , 0 , m_lastOrder_no,
                                                   "the product is not in productmenu.");

            net_imp.sendMsgToServer(msg);
            return;
        }

        if(menu.menuItems[selectID].isEnable)
        {

            helper.selectMenuItem(menu.menuItems[selectID]);
            VendDosages_t doses = helper.getDosage();
            //fastcode 0-5  5555
            VendDosages_t::iterator it = doses.begin();
            //printf("paydone.m_fastcode : %d\n" , paydone.m_fastcode);
            for( ; it != doses.end(); ++it)
            {

                VendDosage_t& tmp = *it;

                if(tmp.nameTextId == "TEXT_STRENGTH")
                {

                    int strengthCode = paydone.m_fastcode / 100;
                    if(strengthCode >= tmp.minLevel && strengthCode <= tmp.maxLevel)
                        tmp.activeLevel = strengthCode;
                }
                if(tmp.nameTextId == "TEXT_WHITENESS")
                {

                    int whitenessCode = paydone.m_fastcode / 10;
                    whitenessCode = whitenessCode % 10;
                    if(whitenessCode >= tmp.minLevel && whitenessCode <= tmp.maxLevel)
                        tmp.activeLevel = whitenessCode;
                }
                if(tmp.nameTextId == "TEXT_SWEETNESS")
                {

                    int sweetnessCode = paydone.m_fastcode % 10;
                    //printf("sweetnessCode : %d" , sweetnessCode);
                    if(sweetnessCode >= tmp.minLevel && sweetnessCode <= tmp.maxLevel)
                        tmp.activeLevel = sweetnessCode;
                }

            }
            helper.setDosage(doses);

            helper.onStart();

            ISupervisorStateMgr::getInstance().postEvent(EvEnough());
            isUseProductsMake = false;
        }
        else
        {
            isUseProductsMake = false;
            networkImp& net_imp = networkImp::getInstance();
            MessageMakeProduct mp;
            string msg = mp.packageMakeProductInfo(false ,
                                                   paydone.m_proid ,
                                                   name ,
                                                   m_machinenum ,
                                                   "fastcode" , 0 , m_lastOrder_no,
                                                   "the product is not available");

            net_imp.sendMsgToServer(msg);
            return;
        }
    }
}

void networkMgr::addScene(QGraphicsScene* scene)
{
    m_scene = scene;
}

void networkMgr::setCashMount(int mount)
{
    m_cashMount= mount;
}

void networkMgr::setPayType(payType type) //free qr_pay cash quickpass fastcode
{
    m_payType = type;
}

void networkMgr::sendBillOfLadingInfo(ProductId proID , long sPriceString ,string cardcode)
{
    networkImp& net_imp = networkImp::getInstance();
    m_cashMount = -1;
    QString tmp = QDateTime::currentDateTime().toString();
    QTime t;
    t= QTime::currentTime();
    qsrand(t.msec()+t.second()*1000);
    int n = qrand()%999;
    tmp+= QString::number(n);
    MD5 md5(tmp.toStdString());
    string result = md5.md5();
    m_lastOrder_no = result;

    string goodCode = cardcode;
    Message_send_qr sqr;
    string msg = sqr.packageGoodCode(m_machinenum , proID , sPriceString , result , goodCode);

    net_imp.sendMsgToServer(msg);
}


void networkMgr::firstSendDoorStatus()
{
    SlVenduiHelper helper;
    if(helper.IsDoorOpen())
    {

        sendDoorOpen();
    }
    else
    {

        sendDoorClose();
    }
}

void networkMgr::setMachineStaus(bool b)
{
    isMachineStatueNormal = b;
}


void networkMgr::sendIngredits()
{
    singleton<ingConfig>::instance().load();
    if(singleton<ingConfig>::instance().isActive())
    {
        vector<ings_group> group = singleton<ingConfig>::instance().getIngs();
        vector<ings_group>::iterator it = group.begin();
        vector<mount_info> infos;
        for( ; it != group.end(); ++it)
        {
            ings_group gr = *it;
            mount_info info;
            info.ing_id = QString::number(gr.ingID).toStdString();
            info.ing_mount = QString::number(gr.ingRemain).toStdString();
            info.ing_name = gr.ingName;
            infos.push_back(info);
        }

        if(!infos.empty())
        {

            Message_send_emptyError ing_remain;
            networkImp& net_imp = networkImp::getInstance();
            QString datetime = "";
            datetime = QDateTime::currentDateTime().toString("yyyyMMddhhmmss");
            string msg = ing_remain.packageMountInfo(m_machinenum,datetime.toStdString() , infos);
            net_imp.sendMsgToServer(msg);
        }
    }
}



