#ifndef NETWORKIMP_H
#define NETWORKIMP_H

#include <QObject>
#include <QtNetwork>
#include <QTimer>
#include <boost/noncopyable.hpp>
#include <singleton.h>
#include <string>
#include <vector>
using namespace std;

#define WAIT_FOR_CONNECT_TIME 2000
#define NO_MESSAGE_TIME       2*60*1000
#define MESSAGE_HEARD_LENGTH 12
enum e_networkerror
{
    no_error      = 0 ,
    no_machinenum = 1 ,
    no_serverip_port,
    reconnect10count,
    hardware_error,
    msg_error,
};

enum e_networkstatus
{
    UNCONNECT = 0,
    CONNECTED = 1,
    LOGIN,
};


class networkImp : public QObject , boost::noncopyable
{
    Q_OBJECT
    friend class singleton<networkImp>;
public:
    static networkImp& getInstance();
    string serverIP; //current ip
private:
    networkImp();
    ~networkImp();



private:
    int    serverPort;
    int    machinenum;
    QTcpSocket * m_client;
    vector<string> serverIPs;
    e_networkerror error_code;
    e_networkstatus net_status;
    int    currentIP;
    QTimer* msgTimer;

    bool isRevMsg;
    bool enableNetwork;
public:
//init
    void setDisableNetwork();
    bool init(string ip , int port , int num);
    void addIPs(string ip);
    void changeIP();
    string getCurrenIP();

    void setServerLogin();
//connect
    bool connectToServer();
//status
    e_networkerror getNetworkCode();
    e_networkstatus getNetworkStatus();

    void sendMsgToServer(string msg , bool isLoginMsg = false);
public slots:
    void slot_readServer();


    //void slot_error( QAbstractSocket::SocketError);
    void slot_checkMsg();

signals:

    void sig_error_parameter();
    //void sig_error_environment();

    void sig_disconnect();
    void sig_connected();

    void sig_revMsg(QString);
    void sig_msg_error(QString);
};

#endif // NETWORKIMP_H
