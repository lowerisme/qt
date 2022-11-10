#ifndef DELEGATE_H
#define DELEGATE_H

#include <QStyledItemDelegate>>
#include <QItemDelegate>
#include <QModelIndex>
#include <QComboBox>

class delegate : public QStyledItemDelegate
{
public:
    delegate(QObject* parent = nullptr);
    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;

};


class SexDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    SexDelegate(QObject *parent = 0): QItemDelegate(parent) { }
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
        const QModelIndex &index) const
    {
        QComboBox *editor = new QComboBox(parent);
        editor->addItem("Female");
        editor->addItem("Male");
        return editor;
    }
    void setEditorData(QWidget *editor, const QModelIndex &index) const
    {
        QString text = index.model()->data(index, Qt::EditRole).toString();
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        int tindex = comboBox->findText(text);
        comboBox->setCurrentIndex(tindex);
    }
    void setModelData(QWidget *editor, QAbstractItemModel *model,
        const QModelIndex &index) const
    {
        QComboBox *comboBox = static_cast<QComboBox*>(editor);
        QString text = comboBox->currentText();
        model->setData(index, text, Qt::EditRole);
    }
    void updateEditorGeometry(QWidget *editor,
        const QStyleOptionViewItem &option, const QModelIndex &index) const
    {
        editor->setGeometry(option.rect);
    }
};



#endif // DELEGATE_H
