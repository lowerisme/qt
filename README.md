# qt-c
一起学习学习c++叭

2.代理学习感想：

1》重写编辑器函数：构造一个控件，记得retun
QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const;


2》给编辑器设置数据：根据各个控件的特性，灵活应用
void setEditorData(QWidget *editor, const QModelIndex &index) const;


3》把数据写到模型当中：就是拿到空中所填充的数据然后set到model中即可。
void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const;

