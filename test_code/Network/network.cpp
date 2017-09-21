#include "network.h"

networkWidget::networkWidget(QObject *parent)
    : QObject(parent)
{
    m_str = "";
    m_manager = new QNetworkAccessManager(this);//新建QNetworkAccessManager对象
    connect(m_manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_replayFinished(QNetworkReply*))); //关联信号和槽
    m_manager->get(QNetworkRequest(QUrl("http://mkcaffee.chinaeast.cloudapp.chinacloudapi.cn/api/coffees/getQRContent?vmc=33333")));
}

networkWidget::~networkWidget()
{

}

void networkWidget::slot_replayFinished(QNetworkReply *reply)
{
    QTextCodec *codec = QTextCodec::codecForName("utf8");
    //使用utf8编码, 这样可以显示中文
    QString str = codec->toUnicode(reply->readAll());
    qDebug() << "QString str:" << str;
    m_str = str;
    reply->deleteLater();//最后要释放replay对象
}

/*
void networkWidget::readJson()
{
    QString simpjson_str = m_str;

//简单的QT解析JSON
    QJsonParseError simp_json_error;
    QString name, myAccount;
    QString result,data;
    int age;
    //QTJSON所有的元素
    QJsonDocument simp_parse_doucment = QJsonDocument::fromJson(simpjson_str.toUtf8(), &simp_json_error);
    //检查json是否有错误
    if (simp_json_error.error == QJsonParseError::NoError)
    {
        if (simp_parse_doucment.isObject())
        {
            //开始解析json对象
            QJsonObject obj = simp_parse_doucment.object();
            //如果包含name
            if (obj.contains("result"))
            {
                //得到name
                QJsonValue name_value = obj.take("result");
                if (name_value.isString())
                {
                    //转换name
                    result = name_value.toVariant().toString();
                }
            }
            if (obj.contains("data"))
            {
                QJsonValue myAccount_value = obj.take("data");
                if (myAccount_value.isDouble())
                {
                    data = myAccount_value.toVariant().toString();
                }
            }
            if (obj.contains("age"))
            {
                QJsonValue age_value = obj.take("age");
                if (age_value.isDouble())
                {
                    age = age_value.toVariant().toInt();
                }
            }
        }
    }
    qDebug() << QString::fromLocal8Bit("简单的QT解析出来的数据：") << result << "," << data;

}

// {"result":true,"data":"http://mkcaffee.chinaeast.cloudapp.chinacloudapi.cn/app/coffees/index.html#/myCoffees/33333"}

/*
test.json
{
   "appDesc": {
      "description": "SomeDescription",
      "message": "SomeMessage"
   },

   "appName": {
      "description": "Home",
      "message": "Welcome",
      "imp":["awesome","best","good"]
   }
}

void networkWidget::readJson()
{
//    QString val;
//    QFile file;
//    file.setFileName("test.json");
//    file.open(QIODevice::ReadOnly | QIODevice::Text);
//    val = file.readAll();
//    file.close();
//    qWarning() << val;

    QString val = m_str;
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject sett2 = d.object();
   QJsonValue value = sett2.value(QString("appName"));
    qWarning() << value;
    QJsonObject item = value.toObject();
    qWarning() << tr("QJsonObject of description: ") << item;

     incase of string value get value and convert into string
    qWarning() << tr("QJsonObject[appName] of description: ") << item["description"];
    QJsonValue subobj = item["description"];
    qWarning() << subobj.toString();

     incase of array get array and convert into string
    qWarning() << tr("QJsonObject[appName] of value: ") << item["imp"];
    QJsonArray test = item["imp"].toArray();
    qWarning() << test[1].toString();
}
*/
