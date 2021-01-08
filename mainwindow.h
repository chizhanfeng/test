#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include    <QtSql>
#include <QMainWindow>
#include <data.h>
#include <calc.h>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QSqlDatabase  DB;//数据库连接
    QSqlRelationalTableModel  *tabModel;  //数据模型
    QSqlQueryModel queryModel;
    int CurTableID;//跟踪当前表
    QItemSelectionModel *theSelection; //选择模型
    QString CurUser;//跟踪当前登录用户
    bool bLogin=false;
    //Ccalc calc;
//    QDataWidgetMapper   *dataMapper; //数据映射
//    QWComboBoxDelegate   delegateSex; //自定义数据代理，性别
//    QWComboBoxDelegate   delegateDepart; //自定义数据代理，部门
    void    init();//初始化数据库
    void    openTable();//打开数据表
    void    getFieldNames();//获取字段名称,填充“排序字段”的comboBox
    void    importExcelToDatabase();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void on_actionOpenDB_triggered();

    void on_listWidget_clicked(const QModelIndex &index);

    void on_actionRecAppend_triggered();

    void on_actionSubmit_triggered();

    void on_actionRevert_triggered();
    void on_currentChanged(QModelIndex,QModelIndex);
    void on_actionCalworkingHours_triggered();

    void on_actionInput_triggered();

    void on_actionRecDelete_triggered();

    void on_actionRecInsert_triggered();

    void on_actionHoursquery_triggered();


private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
