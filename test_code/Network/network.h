#ifndef NETWORKWIDGET_H
#define NETWORKWIDGET_H

#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QtWidgets/QWidget>
#include <QTextCodec>
#include <QString>
#include <QUrl>

class networkWidget : public QObject
{
    Q_OBJECT

public:
    networkWidget(QObject *parent = 0);
    ~networkWidget();

private Q_SLOTS:
    void slot_replayFinished(QNetworkReply *reply);

private:

    QNetworkAccessManager *m_manager;
    QString                m_str;
    //QNetworkReply *m_replay;
};

#endif // NETWORKWIDGET_H
