#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStringListModel>
#include <QSortFilterProxyModel>
#include <QLineEdit>
#include <QDebug>>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList list2;
    list2<<"hefei"<<"hefeilinux"<<"Qt"<<"Qt Creator";
    QStringListModel *listModel2=new QStringListModel(list2,this);

    //添加右键菜单
    ui->listView->setContextMenuPolicy(Qt::ContextMenuPolicy::CustomContextMenu);

    filterModel=new QSortFilterProxyModel(this);
    //为代理模型添加源模型
    filterModel->setSourceModel(listModel2);
    //在视图中使用代理模型
    ui->listView->setModel(filterModel);

    filterModel->sort(0);
    connect(ui->lineEdit, &QLineEdit::textEdited, this, [&]{ filterModel->setFilterRegExp(ui->lineEdit->text());});
    connect(ui->listView, &QAbstractItemView::customContextMenuRequested, this, [&](const QPoint pos)
    {
        QModelIndex idx = ui->listView->indexAt(pos);
        if(!idx.isValid()) return;

        //拿到选中行的数据
        QMap<int, QVariant> m = filterModel->itemData(idx);
        auto str  = m.first().toString();

        QMenu popmenu(ui->listView);
        QAction* ac= new QAction(this);

        ac->setText("123");
        popmenu.addAction(ac);
        QAction* ac1= new QAction(this);
        ac->setText("1111");
        ;
        popmenu.addAction(ac1);
        popmenu.exec(QCursor::pos());
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{

    QRegExp rx(ui->lineEdit->text());
    filterModel->setFilterRegExp(rx);

}

