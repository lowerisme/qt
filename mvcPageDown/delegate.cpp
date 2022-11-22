#include "delegate.h"

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


//样式定制
void ValueDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const
{
    if (!index.isValid())
    {
        // 如果当前项具有焦点，它就绘制一个焦点矩形(不重要)
        drawFocus(painter, option, option.rect);
    }
    else
    {
        QItemDelegate::paint(painter, option, index);
    }
}

QWidget *ValueDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,  const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    return editor;
}

void ValueDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString text = index.model()->data(index, Qt::EditRole).toString();
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    lineEdit->setText(text);
}

void ValueDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,  const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    QString text = lineEdit->text();
    model->setData(index, text, Qt::EditRole);
}

void ValueDelegate::updateEditorGeometry(QWidget *editor,  const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
