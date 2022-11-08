#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QSortFilterProxyModel;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

private:
    QSortFilterProxyModel *filterModel;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
