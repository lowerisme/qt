#ifndef CARRAYMODEL_H
#define CARRAYMODEL_H

#include <QAbstractTableModel>

class CArrayModel : public QAbstractTableModel
{
public:
    CArrayModel(QObject *parent = 0);
    //设置总数据
    void SetArrayData(const std::map<int, QString> &map);

    //获得总数据
    std::map<int, QString> GetArrayData();

    //设置页数据
    void SetCurPage(int iPage);
    //获得当前页
    int GetCurPage();
    //获得总页数
    int GetPageCount();
    //设置每页数据条数
    void SetPageSize(int iPageSize);
    //获得每页数据条数
    int GetPageSize();

    //总行数
    int RowCount() const;
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value,int role = Qt::EditRole);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void refrushModel();
private:
    QString currencyAt(int offset) const;
    std::map<int, QString> m_mpData;    //总数据
    std::map<int, QString> m_mpPageData;//每页数据
    int m_iPageSize;                    //每页数据条数
    int m_iCurPage;                     //当前页
};


#endif // CARRAYMODEL_H
