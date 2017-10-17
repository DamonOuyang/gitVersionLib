#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent)
    ,ui(new Ui::Widget)
    ,m_tcpSocket(NULL)
{
    ui->setupUi(this);
    ui->label->show();

    if(NULL == m_tcpSocket)
    {
        m_tcpSocket = new QTcpSocket;
        newTcpConnect();
        //This signal is emitted once every time new data is available for reading from the device.
        connect(m_tcpSocket,SIGNAL(readyRead()),SLOT(receiveMessage()));
    }

}

void Widget::newTcpConnect()
{
    //Aborts the current connection and resets the socket.
    //Unlike disconnectFromHost(), this function immediately closes the socket, discarding any pending data in the write buffer.
    m_tcpSocket->abort();
    //Attempts to make a connection to hostName on the given port.
    m_tcpSocket->connectToHost("192.168.10.59",4567);

}

void Widget::sendMessage()
{
   QString str = ui->lineEdit->text();
   ui->lineEdit->clear();
   QByteArray data = str.toUtf8();
   m_tcpSocket->write(data);
}

void Widget::receiveMessage()
{
    //Reads all remaining data from the device, and returns it as a byte array.
    QByteArray data = m_tcpSocket->readAll();
    QString str(data);
    ui->lineEdit->setText(str);
}

Widget::~Widget()
{
    delete ui;

    if(NULL != m_tcpSocket)
    {
        m_tcpSocket->deleteLater();
        m_tcpSocket = NULL;
    }
}

void Widget::on_ConfirmButton_clicked()
{
    sendMessage();
}

void Widget::on_CancelButton_clicked()
{

    this->close();
}
