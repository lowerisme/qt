#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QWidget>
#include <QAbstractItemModel>
#include <QStyledItemDelegate>
#include <QItemDelegate>
#include <vector>
#include "carraymodel.h"
#include "delegate.h"


class QTableView;
class QSqlQueryModel;
class QLabel;
class QLineEdit;
class QPushButton;



//自定义窗口类
class MyMainWindow : public QWidget
{
    Q_OBJECT

public:
    MyMainWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);
    ~MyMainWindow();

    void keyPressEvent(QKeyEvent *event);

    //槽函数
    private slots:
        void OnFirstButtonClick();           //首页按钮按下
        void OnLastButtonClick();           //末页按钮按下
        void OnPrevButtonClick();            //前一页按钮按下
        void OnNextButtonClick();            //后一页按钮按下
        void OnSwitchPageButtonClick();      //转到页按钮按下
        void OnIndexButtonClick();           //转到索引按钮按下
        void OnSetPageSizeButtonClick();     //设置每页显示行数按钮按下

private :
    void MyCreateWindow();                   //创建窗口
    void SetTableView();                     //设置表格
    void UpdateStatus();                     //刷新状态

private:
    CArrayModel       *m_pDataModel;        //数据模型
    QTableView        *tableView;           //数据表
    QLineEdit         *switchPageLineEdit;  //转到页输入框
    QPushButton       *m_pFirstPageBtn;     //首页按钮
    QPushButton       *m_pLastPageBtn;      //末页按钮
    QPushButton       *prevButton;          //前一页按钮
    QPushButton       *nextButton;          //下一页按钮
    QPushButton       *switchPageButton;    //转到页按钮
    QLineEdit         *m_pIndexEdit;        //索引输入框
    QPushButton       *m_pGoIndexBtn;       //按索引跳转按钮
    QLabel            *totalPageLabel;      //总数页文本
    QLabel            *currentPageLabel;    //当前页文本
    QLineEdit         *m_pPerPageCountEdit; //每页显示行数
    QPushButton       *m_pSetPerPageCountBtn;//设置每页显示行数按钮
    enum      {PageRecordCount = 10};       //默认每页显示记录数
};
#endif // MAINWINDOW_H
