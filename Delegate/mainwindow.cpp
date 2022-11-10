#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStandardItemModel * model = new QStandardItemModel(ui->tableView);
    model->setItem(0, 0, new QStandardItem("11"));
    model->setItem(0, 1, new QStandardItem("11"));
    model->setItem(0, 2, new QStandardItem("11"));
    model->setItem(0, 3, new QStandardItem("11"));
    model->setItem(0, 4, new QStandardItem("1"));
    model->setItem(0, 5, new QStandardItem("111"));
    model->setItem(0, 6, new QStandardItem("11"));
    model->setItem(0, 7, new QStandardItem("222"));
    model->setItem(0, 8, new QStandardItem("222"));
    model->setItem(1, 7, new QStandardItem("333"));
    model->setItem(1, 8, new QStandardItem("3333"));


    ui->tableView->setModel(model);
    //de = new delegate(this);
    SexDelegate* m = new SexDelegate(this);

    ui->tableView->setItemDelegateForColumn(2,m);
    Checkbox * s = new Checkbox(this);
    ui->tableView->setItemDelegateForColumn(3, s);
}

MainWindow::~MainWindow()
{
    // 验证一下是否在model把数据更新了
    QString str = ui->tableView->model()->index(0, 2).data().toString();
    qDebug()<<"~~~~~~~"<<str;
    delete ui;
}

