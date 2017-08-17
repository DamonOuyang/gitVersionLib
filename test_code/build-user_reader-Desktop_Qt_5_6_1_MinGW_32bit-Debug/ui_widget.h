/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *OK_Button;
    QPushButton *can_pushButton;
    QLabel *cnet_status_label;
    QLabel *card_label;
    QLabel *card_ser_label;
    QLineEdit *con_lineEdit;
    QLineEdit *card_lineEdit;
    QLineEdit *nuber_lineEdit;
    QPushButton *pushButton;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(664, 398);
        OK_Button = new QPushButton(Widget);
        OK_Button->setObjectName(QStringLiteral("OK_Button"));
        OK_Button->setGeometry(QRect(170, 320, 75, 23));
        can_pushButton = new QPushButton(Widget);
        can_pushButton->setObjectName(QStringLiteral("can_pushButton"));
        can_pushButton->setGeometry(QRect(400, 320, 75, 23));
        cnet_status_label = new QLabel(Widget);
        cnet_status_label->setObjectName(QStringLiteral("cnet_status_label"));
        cnet_status_label->setGeometry(QRect(60, 70, 121, 41));
        card_label = new QLabel(Widget);
        card_label->setObjectName(QStringLiteral("card_label"));
        card_label->setGeometry(QRect(60, 140, 101, 31));
        card_ser_label = new QLabel(Widget);
        card_ser_label->setObjectName(QStringLiteral("card_ser_label"));
        card_ser_label->setGeometry(QRect(60, 210, 141, 41));
        con_lineEdit = new QLineEdit(Widget);
        con_lineEdit->setObjectName(QStringLiteral("con_lineEdit"));
        con_lineEdit->setGeometry(QRect(200, 80, 113, 20));
        card_lineEdit = new QLineEdit(Widget);
        card_lineEdit->setObjectName(QStringLiteral("card_lineEdit"));
        card_lineEdit->setGeometry(QRect(180, 150, 113, 20));
        nuber_lineEdit = new QLineEdit(Widget);
        nuber_lineEdit->setObjectName(QStringLiteral("nuber_lineEdit"));
        nuber_lineEdit->setGeometry(QRect(200, 220, 113, 20));
        pushButton = new QPushButton(Widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(420, 200, 111, 31));

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", 0));
        OK_Button->setText(QApplication::translate("Widget", "OK", 0));
        can_pushButton->setText(QApplication::translate("Widget", "Cancel", 0));
        cnet_status_label->setText(QApplication::translate("Widget", "connection status:", 0));
        card_label->setText(QApplication::translate("Widget", "card status:", 0));
        card_ser_label->setText(QApplication::translate("Widget", "Card searial number:", 0));
        pushButton->setText(QApplication::translate("Widget", "change passward", 0));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
