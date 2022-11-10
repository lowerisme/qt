#include "delegate.h"
#include <QPen>
#include <QPainter>
#include <QApplication>
#include <QCheckBox>

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

Checkbox::Checkbox(QObject *parent):QItemDelegate(parent)
{

}

QWidget *Checkbox::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QCheckBox* checkBox = new QCheckBox(parent);
    checkBox->setText("是男生吗？");
    return checkBox;
}

void Checkbox::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    bool text = index.model()->data(index, Qt::EditRole).toBool();
    QCheckBox *CheckBox = static_cast<QCheckBox*>(editor);
    CheckBox->setChecked(text);
}

void Checkbox::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QCheckBox *CheckBox = static_cast<QCheckBox*>(editor);
    bool text = CheckBox->isChecked();
    model->setData(index, text?QString("是"):QString("否"), Qt::EditRole);
}
