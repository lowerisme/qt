#ifndef DELEGATE_H
#define DELEGATE_H

#include <QtWidgets/QWidget>
#include <QAbstractItemModel>
#include <QStyledItemDelegate>
#include <QItemDelegate>
#include <vector>

//只读委托(给索引列使用)
class ReadOnlyDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ReadOnlyDelegate(QObject *parent = 0): QItemDelegate(parent) { }
    QWidget *createEditor(QWidget*parent, const QStyleOptionViewItem &option,
        const QModelIndex &index) const
    {
        return NULL;
    }
};

//值列
class ValueDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ValueDelegate(QObject *parent = 0): QItemDelegate(parent) { }
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,  const QModelIndex &index) const;
    void paint(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,  const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,  const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // DELEGATE_H
