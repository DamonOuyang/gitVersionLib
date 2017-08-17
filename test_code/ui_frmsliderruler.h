/********************************************************************************
** Form generated from reading UI file 'frmsliderruler.ui'
**
** Created by: Qt User Interface Compiler version 5.6.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRMSLIDERRULER_H
#define UI_FRMSLIDERRULER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <sliderruler.h>

QT_BEGIN_NAMESPACE

class Ui_frmSliderRuler
{
public:
    QVBoxLayout *verticalLayout;
    SliderRuler *widget1;

    void setupUi(QWidget *frmSliderRuler)
    {
        if (frmSliderRuler->objectName().isEmpty())
            frmSliderRuler->setObjectName(QStringLiteral("frmSliderRuler"));
        frmSliderRuler->resize(754, 98);
        verticalLayout = new QVBoxLayout(frmSliderRuler);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        widget1 = new SliderRuler(frmSliderRuler);
        widget1->setObjectName(QStringLiteral("widget1"));

        verticalLayout->addWidget(widget1);


        retranslateUi(frmSliderRuler);

        QMetaObject::connectSlotsByName(frmSliderRuler);
    } // setupUi

    void retranslateUi(QWidget *frmSliderRuler)
    {
        frmSliderRuler->setWindowTitle(QApplication::translate("frmSliderRuler", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class frmSliderRuler: public Ui_frmSliderRuler {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRMSLIDERRULER_H
