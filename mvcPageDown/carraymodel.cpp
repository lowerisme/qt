#include "carraymodel.h"

CArrayModel::CArrayModel(QObject *parent)
    : QAbstractTableModel(parent)
{
}

//设置Model数据
void CArrayModel::SetArrayData(const std::map<int, QString> &map)
{
    m_mpData = map;
}

//获得总数据
std::map<int, QString> CArrayModel::GetArrayData()
{
    return m_mpData;
}

//总行数
int CArrayModel::RowCount() const
{
    return m_mpData.size();
}

//设置页数据
void CArrayModel::SetCurPage(int iPage)
{
    //当前页必须小于总页数
    if (iPage < GetPageCount())
    {
        m_iCurPage = iPage;

        //查询起始索引
        int iStart = m_iPageSize * m_iCurPage;
        //查询结束索引
        int iend = 0;
        //如果本页可以填满
        if (iStart + m_iPageSize < RowCount())
        {
            iend = iStart + m_iPageSize;
        }
        //如果本页不可以填满
        else
        {
            iend = RowCount() - 1;
        }

        //填充当前页数据
        m_mpPageData.clear();
        for (int i = iStart; i <= iend; ++i)
        {
            auto it = m_mpData.find(i);
            if (it == m_mpData.end())
            {
                return;
            }

            m_mpPageData.insert(std::pair<int, QString>(i, it->second));
        }
    }

    return;
}

//获得当前页
int CArrayModel::GetCurPage()
{
    return m_iCurPage;
}

//获得总页数
int CArrayModel::GetPageCount()
{
    return (RowCount() % m_iPageSize == 0)
        ? (RowCount() / m_iPageSize)
        : (RowCount() / m_iPageSize + 1);
}

//设置每页数据条数
void CArrayModel::SetPageSize(int iPageSize)
{
    if (iPageSize <= 0)
    {
        return;
    }

    m_iPageSize = iPageSize;
    SetCurPage(0);

    //刷新Model，否则TableView不会刷新显示
    refrushModel();
}


//获得每页数据条数
int CArrayModel::GetPageSize()
{
    return m_iPageSize;
}

//行数
int CArrayModel::rowCount(const QModelIndex & parent) const
{
    return m_iPageSize;
}

//列数
int CArrayModel::columnCount(const QModelIndex & parent) const
{
    //仅仅有两列数据
    return 2;
}


void CArrayModel::refrushModel()
{
    beginResetModel();
    endResetModel();
}

QVariant CArrayModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role == Qt::TextAlignmentRole)
    {
        return int(Qt::AlignCenter | Qt::AlignVCenter);
    }
    else if (role == Qt::DisplayRole)
    {
        if ( 0 == index.column())
        {
            //如果处于最后一页，索引没必要全部列出，只列出范围内的
            if (index.row() + m_iCurPage * m_iPageSize > this->RowCount())
            {
                return QVariant();
            }

            return index.row() + m_iCurPage * m_iPageSize;
        }
        else if (1 == index.column())
        {
            auto it = m_mpPageData.find(index.row() + m_iCurPage * m_iPageSize);
            if (it != m_mpPageData.end())
            {
                return it->second;
            }
        }
    }

    return QVariant();
}

Qt::ItemFlags CArrayModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

bool CArrayModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole)
    {
        QVariant oldData = data(index, Qt::EditRole);
        QString strold = oldData.toString();
        QString strnew = value.toString();
        //相同则不编辑
        if (strnew.compare(strold) == 0)
        {
            return true;
        }

        //计算实际数据的下标
        int dataindex = index.row() + m_iCurPage * m_iPageSize;

        //改变总数据集
        auto it  = m_mpData.find(dataindex);
        if (it != m_mpData.end())
        {
            it->second = strnew;
        }

        //改变当页数据集
        auto itcur = m_mpPageData.find(dataindex);
        if (itcur != m_mpPageData.end())
        {
            itcur->second = strnew;
        }

        return true;
    }
    return false;
}

QVariant CArrayModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
    {
        return QVariant();
    }

    if (0 == section)
    {
        return QStringLiteral("索引");
    }
    else if (1 == section)
    {
        return QStringLiteral("值");
    }

    return QVariant();
}


QString CArrayModel::currencyAt(int offset) const
{
    auto it = m_mpData.find(offset);
    if (it != m_mpData.end())
    {
        return it->second;
    }

    return QString();
}
