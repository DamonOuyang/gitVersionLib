#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    BsrWidget* bsrWidget = new BsrWidget;

    setCentralWidget(bsrWidget);

}

MainWindow::~MainWindow()
{
    delete ui;
}
