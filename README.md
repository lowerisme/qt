# qt-c
一起学习学习c++叭

1.代理学习感想：

1》重写编辑器函数：构造一个控件，记得retun
QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,const QModelIndex &index) const;


2》给编辑器设置数据：根据各个控件的特性，灵活应用
void setEditorData(QWidget *editor, const QModelIndex &index) const;


3》把数据写到模型当中：就是拿到空中所填充的数据然后set到model中即可。
void setModelData(QWidget *editor, QAbstractItemModel *model,const QModelIndex &index) const;

2,QPainter

Qt中有三个坐标系
设备坐标系: 即Device坐标系。也是物理坐标系。即真实的的物理坐标系。
逻辑坐标系: 即用户坐标系。也就是说日常大家使用Qt的时候的坐标系。
窗口坐标系: 这个坐标系是QPainter设置setWindow以后的一个坐标系。

save(): 保存painter之前的绘制特性，直到restore()调用后恢复之前保存的painter 的特性。

setWindow()：
控制变量，其他的代码不变，我们只单独设置setWindow这个代码setWindow的作用，就是在物理坐标系不变的情况下，将逻辑坐标系进行缩放。

//控制绘图区域。30，30 代表为原点（相当于重新指定了原点）。 W，h 和原来的尺寸成反比。比例系数为 setwindow时的		w，h和 窗口 大小的比值。
Painter.setWindow(30,30,250,250);

setViewport()
大家可以理解setViewport的作用就是控制物理坐标系的。

// x, y, 代表平移（相当于坐标系被平移）。 w，h 代表缩放-》成正比（和原来的窗口大小做比较）比例系数为 setViewport时的w，h和 窗口 大小的比值。
    Painter.setViewport(QRect(10,10,1000,1000 ));

*我们的绘图是在逻辑坐标上进行的，通过setWindow决定展示所绘图片的一部分或者全部。通过setViewport决定放在绘图设备的那个区域进行展示。*
https://blog.csdn.net/weixin_39583140/article/details/92798127#comments

如果存在坐标系的偏移可以使用QTransform 来转换坐标点设备转逻辑或者逻辑转设备。
Eg：1.设备转逻辑
   QTransform  trans = this->deviceTransfrom().inverted();
   devicePoint.x = logicPoint.x * trans;
   devicePoint.y = logicPoint.y * trans;
 2.逻辑转设备
    QTransform  trans = this->deviceTransfrom();
   logicPoint.x = devicePoint.x * trans;
   logicPoint.y= devicePoint.y * trans;




