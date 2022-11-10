#include "delegate.h"
#include <QPen>
#include <QPainter>
#include <QApplication>

delegate::delegate(QObject* parent): QStyledItemDelegate(parent)
{

}

void delegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //获取值
    const QString strValue = index.model()->data(index,Qt::DisplayRole).toString();

    //设置字体样式和颜色
    QPen pen(Qt::red);
    painter->setPen(pen);
    painter->setFont( QFont("Times",10,QFont::Bold));

    //绘制背景样式
    QStyleOptionViewItem myOption = option;
    myOption.text = "";
    QStyle *pStyle = myOption.widget ? myOption.widget->style() : QApplication::style();
    pStyle->drawControl(QStyle::CE_ItemViewItem,&myOption,painter,option.widget);

    //绘制文本
    pStyle->drawItemText(painter,option.rect,Qt::AlignCenter,QApplication::palette(),true,strValue);

}
