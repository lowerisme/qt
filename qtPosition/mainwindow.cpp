#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->installEventFilter(this);
    ui->pushButton->installEventFilter(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"点击坐标  :"<<event->pos();
    qDebug()<<"相对于屏幕的坐标  :"<<ui->pushButton->mapToGlobal(event->pos());

    qDebug()<<"相对坐标  :"<<ui->pushButton->mapFromGlobal(ui->pushButton->mapToGlobal(event->pos()));
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->lineEdit)
    {

        if(event->type() == QEvent::FocusOut)
        {
            qDebug()<<"lineedit 焦点出去了";
        }
    }
    if(obj == ui->pushButton)
    {

        if(event->type() == QEvent::MouseButtonPress)
        {
            qDebug()<<"pushButton 被点击了";
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

