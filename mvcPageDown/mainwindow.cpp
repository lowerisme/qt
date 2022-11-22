#include "mainwindow.h"


#include <QtGui>
#include <QRegExp>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include <QSplitter>
#include <QTableView>
#include <QHeaderView>
#include <QMessageBox>
#include <Qstring>
#include <QScrollBar>



MyMainWindow::MyMainWindow(QWidget *parent, Qt::WindowFlags flags) : QWidget(parent, flags)
{
    //创建窗口
    MyCreateWindow();
    //设置表格
    SetTableView();

    //翻页按钮
    connect((const QObject *)m_pFirstPageBtn, SIGNAL(clicked()),this, SLOT(OnFirstButtonClick()));
    connect((const QObject *)m_pLastPageBtn, SIGNAL(clicked()),this, SLOT(OnLastButtonClick()));
    connect((const QObject *)prevButton, SIGNAL(clicked()),this, SLOT(OnPrevButtonClick()));
    connect((const QObject *)nextButton, SIGNAL(clicked()),this, SLOT(OnNextButtonClick()));
    connect((const QObject *)m_pGoIndexBtn, SIGNAL(clicked()),this, SLOT(OnIndexButtonClick()));
    connect(m_pIndexEdit, SIGNAL(returnPressed()), this, SLOT(OnIndexButtonClick()));
    //跳转按钮和跳转到页回车相应
    connect((const QObject *)switchPageButton,SIGNAL(clicked()), this, SLOT(OnSwitchPageButtonClick()));
    connect(switchPageLineEdit, SIGNAL(returnPressed()), this, SLOT(OnSwitchPageButtonClick()));
    //设置每页显示行数按钮
    connect(m_pPerPageCountEdit, SIGNAL(returnPressed()), this, SLOT(OnSetPageSizeButtonClick()));
    connect((const QObject *)m_pSetPerPageCountBtn, SIGNAL(clicked()), this, SLOT(OnSetPageSizeButtonClick()));
}

MyMainWindow::~MyMainWindow()
{
}

//对键盘事件处理
void MyMainWindow::keyPressEvent(QKeyEvent *event)
{
    switch(event->key())
    {
        //进行界面退出，重写Esc键，否则重写reject()方法
    case Qt::Key_Escape:
        this->close();
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}

//创建窗口
void MyMainWindow::MyCreateWindow()
{
    //设置窗口属性
    setMinimumSize(600,400);
    setWindowTitle(QStringLiteral("查看数组"));
    m_pFirstPageBtn = new QPushButton(QStringLiteral("首页"));
    prevButton = new QPushButton(QStringLiteral("上一页"));
    nextButton = new QPushButton(QStringLiteral("下一页"));
    m_pLastPageBtn = new QPushButton(QStringLiteral("末页"));
    //一直按下持续执行功能打开，提升浏览体验
    prevButton->setAutoRepeat(true);
    nextButton->setAutoRepeat(true);

    QLabel *switchPage = new QLabel(QStringLiteral("    第"));
    switchPageLineEdit = new QLineEdit;
    switchPageLineEdit->setFixedWidth(40);
    QLabel *page = new QLabel(QStringLiteral("页"));
    switchPageButton = new QPushButton(QStringLiteral("转到"));
    switchPageButton->setFixedWidth(40);

    QLabel *pIndexLabel = new QLabel(QStringLiteral("    索引"));
    m_pIndexEdit = new QLineEdit;
    m_pIndexEdit->setFixedWidth(40);
    m_pGoIndexBtn = new QPushButton(QStringLiteral("转到"));
    m_pGoIndexBtn->setFixedWidth(40);

    //操作布局
    QHBoxLayout *operatorLayout = new QHBoxLayout;
    operatorLayout->addWidget(m_pFirstPageBtn);
    operatorLayout->addWidget(prevButton);
    operatorLayout->addWidget(nextButton);
    operatorLayout->addWidget(m_pLastPageBtn);
    operatorLayout->addWidget(switchPage);
    operatorLayout->addWidget(switchPageLineEdit);
    operatorLayout->addWidget(page);
    operatorLayout->addWidget(switchPageButton);
    operatorLayout->addWidget(pIndexLabel);
    operatorLayout->addWidget(m_pIndexEdit);
    operatorLayout->addWidget(m_pGoIndexBtn);
    operatorLayout->addWidget(new QSplitter());

    //状态
    totalPageLabel = new QLabel;
    totalPageLabel->setFixedWidth(90);
    currentPageLabel = new QLabel;
    currentPageLabel->setFixedWidth(90);
    QLabel *pPerPageCountDisLabel = new QLabel(QStringLiteral("每页显示"));
    m_pPerPageCountEdit = new QLineEdit;
    m_pPerPageCountEdit->setFixedWidth(40);
    QLabel *pPerPageCountLineLabel = new QLabel(QStringLiteral("行"));
    m_pSetPerPageCountBtn = new QPushButton(QStringLiteral("设置"));
    m_pSetPerPageCountBtn->setFixedWidth(40);

    //状态布局
    QHBoxLayout *statusLayout = new QHBoxLayout;
    statusLayout->addWidget(totalPageLabel);
    statusLayout->addWidget(currentPageLabel);
    statusLayout->addWidget(pPerPageCountDisLabel);
    statusLayout->addWidget(m_pPerPageCountEdit);
    statusLayout->addWidget(pPerPageCountLineLabel);
    statusLayout->addWidget(m_pSetPerPageCountBtn);
    statusLayout->addWidget(new QSplitter());

    //设置表格属性
    tableView = new QTableView;
    tableView->verticalHeader()->hide();//隐藏垂直索引
    tableView->setEditTriggers( QAbstractItemView::AllEditTriggers);
    tableView->horizontalHeader()->setStretchLastSection(true); //设置充满表宽度
    //tableView->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选中的方式
    tableView->setAlternatingRowColors(true);
    tableView->setStyleSheet("QTableView{background-color: rgb(186, 202, 224);"
        "alternate-background-color: rgb(212, 212, 212);}");

    tableView->horizontalHeader()->resizeSection(0,70); //设置表头第一列的宽度为150
    tableView->horizontalHeader()->setFixedHeight(25); //设置表头的高度
    tableView->setStyleSheet("selection-background-color:skyblue;"); //设置选中背景色
    tableView->horizontalHeader()->setStyleSheet("QHeaderView::section{background:skyblue;}"); //设置表头背景色

    //窗口布局
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(operatorLayout);
    mainLayout->addWidget(tableView);
    mainLayout->addLayout(statusLayout);
}

// 设置表格
void MyMainWindow::SetTableView()
{
    //声明查询模型
    m_pDataModel = new CArrayModel;

    std::map<int, QString> map;

    for (int i = 0; i < 100; ++i)
    {
        QString str = QString("%1").arg(QString::number(i));
        map.insert(std::pair<int, QString>(i, str));
    }

    m_pDataModel->SetArrayData(map);

    //设置每页数据条数
    m_pDataModel->SetPageSize(PageRecordCount);

    //设置模型
    tableView->setModel(m_pDataModel);

    //设置委托
    tableView->setItemDelegateForColumn(0, new ReadOnlyDelegate(this));
    tableView->setItemDelegateForColumn(1, new ValueDelegate(this));

    //刷新状态
    UpdateStatus();

    return;
}

//刷新界面状态
void MyMainWindow::UpdateStatus()
{
    //刷新表格
    tableView->reset();

    //总页数
    QString szPageCountText = QString(QStringLiteral("总共%1页")).arg(QString::number(m_pDataModel->GetPageCount()));
    totalPageLabel->setText(szPageCountText);

    //设置当前页文本
    int iCurPage = m_pDataModel->GetCurPage() + 1;
    QString szCurrentText = QString(QStringLiteral("当前第%1页")).arg(QString::number(iCurPage));
    currentPageLabel->setText(szCurrentText);

    //每页显示行数
    QString strPerPageCount = QString(QStringLiteral("%1")).arg(QString::number(m_pDataModel->GetPageSize()));
    m_pPerPageCountEdit->setText(strPerPageCount);

    //当前第一页，且总共只有一页
    if (1 == iCurPage && 1 == m_pDataModel->GetPageCount())
    {
        m_pFirstPageBtn->setEnabled(false);
        m_pLastPageBtn->setEnabled(false);
        prevButton->setEnabled(false);
        nextButton->setEnabled(false);

    }
    //当前第一页，且总页数大于1页
    else if(1 == iCurPage && m_pDataModel->GetPageCount() > 1)
    {
        m_pFirstPageBtn->setEnabled(false);
        m_pLastPageBtn->setEnabled(true);
        prevButton->setEnabled(false);
        nextButton->setEnabled(true);
    }
    //当前是最后一页
    else if(iCurPage == m_pDataModel->GetPageCount())
    {
        m_pFirstPageBtn->setEnabled(true);
        m_pLastPageBtn->setEnabled(false);
        prevButton->setEnabled(true);
        nextButton->setEnabled(false);
    }
    //中间页
    else
    {
        m_pFirstPageBtn->setEnabled(true);
        m_pLastPageBtn->setEnabled(true);
        prevButton->setEnabled(true);
        nextButton->setEnabled(true);
    }

    return;
}

//首页按钮按下
void MyMainWindow::OnFirstButtonClick()
{
    m_pDataModel->SetCurPage(0);
    UpdateStatus();
}

//末页按钮按下
void MyMainWindow::OnLastButtonClick()
{
    m_pDataModel->SetCurPage(m_pDataModel->GetPageCount() - 1);
    UpdateStatus();
}

//前一页按钮按下
void MyMainWindow::OnPrevButtonClick()
{
    m_pDataModel->SetCurPage(m_pDataModel->GetCurPage() - 1);
    UpdateStatus();
}

//后一页按钮按下
void MyMainWindow::OnNextButtonClick()
{
    m_pDataModel->SetCurPage(m_pDataModel->GetCurPage() + 1);
    UpdateStatus();
}

//转到索引按钮按下
void MyMainWindow::OnIndexButtonClick()
{
    //得到输入字符串
    QString szText = m_pIndexEdit->text();
    //数字正则表达式
    QRegExp regExp("-?[0-9]*");
    //判断是否为数字
    if(!regExp.exactMatch(szText))
    {
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请输入数字"));

        return;
    }
    //是否为空
    if(szText.isEmpty())
    {
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请输入跳转索引"));

        return;
    }
    //得到页数
    int Index = szText.toInt();
    //判断是否有指定页
    if(Index >= m_pDataModel->RowCount() || Index < 0)
    {
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("索引超出范围，请重新输入"));

        return;
    }
    //记录查询
    m_pDataModel->SetCurPage(Index / m_pDataModel->GetPageSize());

    //刷新状态
    UpdateStatus();

    return;
}

//转到页按钮按下
void MyMainWindow::OnSwitchPageButtonClick()
{
    //得到输入字符串
    QString szText = switchPageLineEdit->text();
    //数字正则表达式
    QRegExp regExp("-?[0-9]*");
    //判断是否为数字
    if(!regExp.exactMatch(szText))
    {
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请输入数字"));

        return;
    }
    //是否为空
    if(szText.isEmpty())
    {
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请输入跳转页面"));

        return;
    }
    //得到页数
    int pageIndex = szText.toInt();
    //判断是否有指定页
    if(pageIndex > m_pDataModel->GetPageCount() || pageIndex < 1)
    {
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("页面超出范围，请重新输入"));

        return;
    }
    //记录查询
    m_pDataModel->SetCurPage(pageIndex - 1);
    //刷新状态
    UpdateStatus();

    return;
}

//设置每页显示行数
void MyMainWindow::OnSetPageSizeButtonClick()
{
    //得到输入字符串
    QString szText = m_pPerPageCountEdit->text();
    //数字正则表达式
    QRegExp regExp("-?[0-9]*");
    //判断是否为数字
    if(!regExp.exactMatch(szText))
    {
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请输入数字"));

        return;
    }
    //是否为空
    if(szText.isEmpty())
    {
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("请输入设置的行数"));

        return;
    }
    //得到行数
    int Index = szText.toInt();
    //判断范围是否合理
    if(Index > m_pDataModel->RowCount() || Index <= 0)
    {
        QMessageBox::information(this, QStringLiteral("提示"), QStringLiteral("设置值超出范围，请重新输入"));

        return;
    }

    //设置每页容量
    m_pDataModel->SetPageSize(Index);

    //刷新状态
    UpdateStatus();

    return;
}
