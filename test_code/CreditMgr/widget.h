#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}
class QTimer;
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    bool CheckCard();

private slots:
    void on_OpnRdr_Btn_clicked();

    void on_ShwName_Btn_clicked();

    void on_ClsRdr_Btn_clicked();

    void on_Intliz_Btn_clicked();

    void on_ChngName_Btn_clicked();

    void on_SrlNmbr_Btn_clicked();

    void on_Charge_Btn_clicked();

    void on_Recharge_Btn_clicked();

    void on_Blnc_Btn_clicked();

    void on_Data_Btn_clicked();

    void slot_check_Card();

private:
    Ui::Widget *ui;
    QTimer * m_pCheckCardTimer;

};

#endif // WIDGET_H
