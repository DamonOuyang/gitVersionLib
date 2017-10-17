#include "networkimp.h"
//#include "IVersionConfig.h"

networkImp::networkImp()
    : serverIP("")
    , serverPort(0)
    , error_code(no_error)
    , machinenum(0)
    , m_client(NULL)
    , currentIP(1)
    , net_status(UNCONNECT)
    , msgTimer(NULL)
    , isRevMsg(false)
    , enableNetwork(true)
{
    if(NULL == msgTimer)
    {
        msgTimer = new QTimer(this);
        connect(msgTimer , SIGNAL(timeout()) , this , SLOT(slot_checkMsg()));
    }
}

networkImp::~networkImp()
{

}
networkImp& networkImp::getInstance()
{
    return singleton<networkImp>::instance();
}

bool networkImp::init(string ip , int port , int num)
{
    if(ip == "" || port == 0)
    {
        emit sig_error_parameter();
        error_code = no_serverip_port;
        return false;
    }
    else
    {
        if(port <=0 || port >65535)
        {
            emit sig_error_parameter();
            error_code = no_serverip_port;
            return false;
        }
        QString checkIP = QString::fromStdString(ip);
        QStringList spiteIp = checkIP.split(".");
        if(spiteIp.size() != 4)
        {
            emit sig_error_parameter();
            error_code = no_serverip_port;
            return false;
        }
    }

    if(num <= 0)
    {
        emit sig_error_parameter();
        error_code = no_machinenum;
        return false;
    }

    machinenum = num;
    serverIP = ip;
    serverPort = port;
    return true;
}
void networkImp::addIPs(string ip)
{
    serverIPs.push_back(ip);
    return;
}
bool networkImp::connectToServer()
{
    if(!enableNetwork)
        return false;

    if(NULL != m_client)
    {
        m_client->close();
        if(NULL != m_client)
        {
            delete m_client;
            m_client = NULL;
        }
    }

    if (NULL  == m_client)
    {
        m_client = new QTcpSocket(this);
        connect(m_client, SIGNAL(readyRead()), this, SLOT(slot_readServer()));
    }
    m_client->connectToHost(QHostAddress(QString::fromStdString(serverIP)), serverPort);
    if (m_client->waitForConnected(WAIT_FOR_CONNECT_TIME))
    {
        net_status = CONNECTED;
        error_code = no_error;

//        if(IVersionConfig::getInstance().isyoubao())
//            msgTimer->start(30000);
//        else
            msgTimer->start(NO_MESSAGE_TIME); //start check timer

        emit sig_connected();
        return true;
    }
    else
    {
       changeIP();
       net_status = UNCONNECT;
       return false;//emit sig_disconnect();
    }
    return false;
}

e_networkerror networkImp::getNetworkCode()
{
    return error_code;
}

void networkImp::changeIP()
{
    if(serverIPs.empty())
        return;

    int count = serverIPs.size();
    currentIP++;
    if(currentIP >= count)
        currentIP = 0;

    serverIP = serverIPs[currentIP];
}

void networkImp::sendMsgToServer(string msg , bool isLoginMsg)
{
    if (NULL == m_client || msg == "")
    {
        return;
    }

    if(net_status == LOGIN || isLoginMsg)
    {
        printf(msg.c_str());
        printf("\n");
        m_client->write(msg.c_str());
        m_client->flush();
    }
}

e_networkstatus networkImp::getNetworkStatus()
{
    return net_status;
}

void networkImp::slot_checkMsg()
{
    if(isRevMsg)
    {
        isRevMsg = false;
        if(net_status == UNCONNECT)
            net_status = CONNECTED;
        else
            net_status = LOGIN;
    }
    else
    {
        net_status = UNCONNECT;
        msgTimer->stop(); //stop check timer
        emit sig_disconnect();
    }
}

void networkImp::slot_readServer()
{
    isRevMsg = true;
    if(NULL == m_client)
        return;

    QString  recvMsg = m_client->readAll();

    printf(recvMsg.toStdString().c_str());
    printf("\n");

    if(recvMsg == "" || recvMsg.length() <=MESSAGE_HEARD_LENGTH)
    {
        error_code = msg_error;
        emit sig_msg_error(recvMsg);
    }
    else
    {
        if(recvMsg.length() <= 12)
            return;
        if(recvMsg.at(12) != '{')
            return;

        emit sig_revMsg(recvMsg);
    }
}

string networkImp::getCurrenIP()
{
    return serverIP;
}

void networkImp::setDisableNetwork()
{
    enableNetwork = false;
    if(NULL != m_client)
    {
        m_client->close();
        m_client->deleteLater();
        m_client = NULL;
    }
    if(NULL != msgTimer)
    {
        msgTimer->stop();
    }
}

void networkImp::setServerLogin()
{
    net_status = LOGIN;
}
