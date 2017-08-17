#ifndef KEYWIDGET_H
#define KEYWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QAction>
#include <QApplication>
#include <QMainWindow>


class SoftKeyLineEdit;
class KeyWidget : public QWidget
{
    Q_OBJECT

public:
    KeyWidget(QWidget *parent = 0);
    ~KeyWidget();

    KeyWidget       *centralWidget;
    QPushButton     *pushButton;
    SoftKeyLineEdit *lineEdit;
};

#endif // KEYWIDGET_H
