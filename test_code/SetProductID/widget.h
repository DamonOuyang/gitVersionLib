#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

#include <QObject>
#include <QtNetwork>
#include <QDebug>
#include <QTcpSocket>
#include <string>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    void newTcpConnect();

private slots:
    void on_ConfirmButton_clicked();
    void on_CancelButton_clicked();

    void sendMessage(); //发送消息
    void receiveMessage(); //接收消息

private:

     QTcpSocket * m_tcpSocket;

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
