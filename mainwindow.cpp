#include "mainwindow.h"
#include "ui_mainwindow.h"
#include    <QFileDialog>
#include    <QMessageBox>
#include    "QStatusBar"
#include    "QLabel"
#include <QAxObject>
#include <QAxWidget>
#include <qaxselect.h>
#include <QDebug.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->splitter);
    QLabel *statusBarLabel=new QLabel();
    statusBarLabel->setText("当前登录：管理员");
    ui->statusBar->addWidget(statusBarLabel);
QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF8"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{    if(DB.isOpen()) return;
    //打开数据表
    QString aFile=QFileDialog::getOpenFileName(this,"选择数据库文件","",
                             "SQL Lite数据库(*.db *.db3)");
    if (aFile.isEmpty())  //选择SQL Lite数据库文件
       return;

//打开数据库
    DB=QSqlDatabase::addDatabase("QSQLITE"); //添加 SQL LITE数据库驱动
    DB.setDatabaseName(aFile); //设置数据库名称
//    DB.setHostName();
//    DB.setUserName();
//    DB.setPassword();
    if (!DB.open())   //打开数据库
    {
        QMessageBox::warning(this, "错误", "打开数据库失败",
                                 QMessageBox::Ok,QMessageBox::NoButton);
        return;
    }

//打开数据表
    openTable();
}
///////////////////////////////////
///  openTable
///数据库初始化
void MainWindow::openTable()
{//打开数据表
    tabModel=new QSqlRelationalTableModel(this,DB);//数据表
    CurTableID=ID_Contract_Data;
    tabModel->setTable(DEF_Table[CurTableID].m_sName); //设置数据表
    tabModel->setRelation(tabModel->fieldIndex("RegionID"),QSqlRelation("Region","ID","Name"));
    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//数据保存方式，OnManualSubmit , OnRowChange
    tabModel->setSort(tabModel->fieldIndex("ID"),Qt::AscendingOrder); //排序

    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView)); //为关系型字段设置缺省代理组件
    if (!(tabModel->select()))//查询数据
    {
       QMessageBox::critical(this, "错误信息",
              "打开数据表错误,错误信息\n"+tabModel->lastError().text(),
                 QMessageBox::Ok,QMessageBox::NoButton);
       return;
    }

//字段显示名
    tabModel->setHeaderData(tabModel->fieldIndex("ID"),Qt::Horizontal,"索引");
    tabModel->setHeaderData(tabModel->fieldIndex("ContractNumber"),Qt::Horizontal,"合同号");
    tabModel->setHeaderData(tabModel->fieldIndex("Name"),Qt::Horizontal,"工程名");
    tabModel->setHeaderData(tabModel->fieldIndex("AmountOnContract"),Qt::Horizontal,"金额");
    tabModel->setHeaderData(tabModel->fieldIndex("AmountPurchased"),Qt::Horizontal,"外购金额");
    tabModel->setHeaderData(tabModel->fieldIndex("Classification"),Qt::Horizontal,"合同分类");
    tabModel->setHeaderData(tabModel->fieldIndex("FinishDate"),Qt::Horizontal,"投运日期");
    tabModel->setHeaderData(tabModel->fieldIndex("GetWorkingHours"),Qt::Horizontal,"领取工时");
    tabModel->setHeaderData(tabModel->fieldIndex("Times"),Qt::Horizontal,"领取次数");
    tabModel->setHeaderData(tabModel->fieldIndex("RemainWorkingHours"),Qt::Horizontal,"剩余工时");
    tabModel->setHeaderData(tabModel->fieldIndex("TotalWorkingHours"),Qt::Horizontal,"工资");
    tabModel->setHeaderData(tabModel->fieldIndex("RegionID"),Qt::Horizontal,"区域");

    theSelection=new QItemSelectionModel(tabModel);//关联选择模型
//theSelection当前项变化时触发currentChanged信号
    connect(theSelection,SIGNAL(currentChanged(QModelIndex,QModelIndex)),
            this,SLOT(on_currentChanged(QModelIndex,QModelIndex)));
//选择行变化时
    connect(theSelection,SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            this,SLOT(on_currentRowChanged(QModelIndex,QModelIndex)));

    ui->tableView->setModel(tabModel);//设置数据模型
    ui->tableView->setSelectionModel(theSelection); //设置选择模型
   // ui->tableView->setModel(tabModel);//设置数据模型
    //    ui->tableView->setColumnHidden(tabModel->fieldIndex("ID"),true);//隐藏列
}

void MainWindow::on_actionOpenDB_triggered()
{
    init();
}

void MainWindow::on_listWidget_clicked(const QModelIndex &index)
{
    if(!bLogin)return;
    if(!DB.isOpen()) return;

    if(tabModel->isDirty())
    {
        QMessageBox::critical(this, "错误信息",
                                   "数据未保存请检查",
                                      QMessageBox::Ok,QMessageBox::NoButton);
    return;
    }
 switch(index.row())
        {
    case 0:
            CurTableID=ID_Contract_Data;
            tabModel->setTable(DEF_Table[CurTableID].m_sName); //设置数据表"Contract"
            for(int i=0;i<DEF_Contract_Def_Sum;i++)
            {
                tabModel->setHeaderData(tabModel->fieldIndex(DEF_Contract_Def[i].m_sName),Qt::Horizontal,DEF_Contract_Def[i].m_sDesc);
            };
            tabModel->setRelation(tabModel->fieldIndex("RegionID"),QSqlRelation("Region","ID","Name"));

            break;
    case 1:
            CurTableID=ID_WorkingHours_Data;
            tabModel->setTable(DEF_Table[CurTableID].m_sName); //设置数据表WorkingHours
            for(int i=0;i<DEF_WorkingHours_Def_Sum;i++)
            {
                tabModel->setHeaderData(tabModel->fieldIndex(DEF_WorkingHours_Def[i].m_sName),Qt::Horizontal,DEF_WorkingHours_Def[i].m_sDesc);
            };
            tabModel->setRelation(tabModel->fieldIndex("EmployeeID"),QSqlRelation("User","ID","Name"));
            tabModel->setRelation(tabModel->fieldIndex("RegionUserID"),QSqlRelation("User","ID","RegionID"));
            tabModel->setRelation(tabModel->fieldIndex("RegionContractID"),QSqlRelation("Contract","ID","RegionID"));
             break;
    case 2:
            CurTableID=ID_User_Data;
            tabModel->setTable(DEF_Table[CurTableID].m_sName); //设置数据表"User"
            for(int i=0;i<DEF_User_Def_Sum;i++)
            {
                tabModel->setHeaderData(tabModel->fieldIndex(DEF_User_Def[i].m_sName),Qt::Horizontal,DEF_User_Def[i].m_sDesc);
            };
            tabModel->setRelation(tabModel->fieldIndex("RegionID"),QSqlRelation("Region","ID","Name"));
            break;
     case 3:
            CurTableID=ID_Region_Data;
            tabModel->setTable(DEF_Table[CurTableID].m_sName); //设置数据表"Region"
            for(int i=0;i<DEF_Region_Def_Sum;i++)
            {
                tabModel->setHeaderData(tabModel->fieldIndex(DEF_Region_Def[i].m_sName),Qt::Horizontal,DEF_Region_Def[i].m_sDesc);
            };
            break;
     case 4:
             CurTableID=ID_Skill_Data;
            tabModel->setTable(DEF_Table[CurTableID].m_sName); //设置数据表"Skill"
            for(int i=0;i<DEF_Skill_Def_Sum;i++)
            {
                tabModel->setHeaderData(tabModel->fieldIndex(DEF_Skill_Def[i].m_sName),Qt::Horizontal,DEF_Skill_Def[i].m_sDesc);
            };
        break;
    case 5:
         CurTableID=ID_Performance_Data;
        tabModel->setTable(DEF_Table[CurTableID].m_sName); //设置数据表"Performance"
        for(int i=0;i<DEF_Performance_Def_Sum;i++)
        {
            tabModel->setHeaderData(tabModel->fieldIndex(DEF_Performance_Def[i].m_sName),Qt::Horizontal,DEF_Performance_Def[i].m_sDesc);
        };
        tabModel->setRelation(tabModel->fieldIndex("UserID"),QSqlRelation("User","ID","Name"));
        break;
     default:return;
         };

    tabModel->setEditStrategy(QSqlTableModel::OnManualSubmit);//数据保存方式，OnManualSubmit , OnRowChange
    tabModel->setSort(tabModel->fieldIndex("ID"),Qt::AscendingOrder); //排序

   if (!(tabModel->select()))//查询数据
    {
       QMessageBox::critical(this, "错误信息",
              "打开数据表错误,错误信息\n"+tabModel->lastError().text(),
                 QMessageBox::Ok,QMessageBox::NoButton);
       return;
    }
    theSelection->clearCurrentIndex();
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(ui->tableView)); //为关系型字段设置缺省代理组件
    ui->tableView->setModel(tabModel);
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->show();
}

void MainWindow::on_actionRecAppend_triggered()
{
    if(!bLogin)return;
    if(!DB.isOpen()) return;
    tabModel->insertRow(tabModel->rowCount(),QModelIndex());
  QModelIndex curIndex=tabModel->index(tabModel->rowCount()-1,1);
  int currow= curIndex.row();
  tabModel->setData(tabModel->index(currow,0),tabModel->rowCount()+1);
  if(tabModel->isDirty())
      {
          ui->actionSubmit->setEnabled(true);
          ui->actionRevert->setEnabled(true);
      }

}

void MainWindow::on_actionSubmit_triggered()
{
    if(!bLogin)return;
    if(!DB.isOpen()) return;
  bool res=tabModel->submitAll();
  if(!res)
  {
      QMessageBox::information(this,"消息","数据保存错误\n"+tabModel->lastError().text(),QMessageBox::Ok);

  }
  else {
      ui->actionSubmit->setEnabled(false);
      ui->actionRevert->setEnabled(false);
  }
}

void MainWindow::on_actionRevert_triggered()
{     if(!bLogin)return;
    if(!DB.isOpen()) return;
        tabModel->revertAll();
        ui->actionSubmit->setEnabled(false);
        ui->actionRevert->setEnabled(false);
}
void MainWindow::on_currentChanged(QModelIndex,QModelIndex)
{
if(tabModel->isDirty())
    {
        ui->actionSubmit->setEnabled(true);
        ui->actionRevert->setEnabled(true);
    }

}
//////////////////
/// \brief MainWindow::on_actionCalworkingHours_triggered
///完成工时计算问题
/// 公式：工时=金额*片区系数*类型系数；
void MainWindow::on_actionCalworkingHours_triggered()
{
    if(!bLogin)return;
    if(CurTableID!=ID_Contract_Data)return;
    if(!DB.isOpen()) return;
    int wk; QSqlRecord Rec;
   for(int i=0; i<tabModel->rowCount();i++)
   {
       Rec=tabModel->record(i);
       wk=Rec.value("AmountOnContract").toInt();
        Rec.setValue("TotalWorkingHours",wk);
        tabModel->setRecord(i,Rec);
   }

   if(tabModel->isDirty())
       {
           ui->actionSubmit->setEnabled(true);
           ui->actionRevert->setEnabled(true);
       }
}

void MainWindow::on_actionInput_triggered()
{
    if(!bLogin)return;
    importExcelToDatabase();
}

void MainWindow::on_actionRecDelete_triggered()
{
    if(!bLogin)return;
    QModelIndex curIndex=theSelection->currentIndex();
    qDebug()<<curIndex.row();
    tabModel->removeRow(curIndex.row());
    theSelection->clearSelection();
    if(tabModel->isDirty())
        {
            ui->actionSubmit->setEnabled(true);
            ui->actionRevert->setEnabled(true);
        }
}
void MainWindow::importExcelToDatabase()
{
    QString strFilePathName = QFileDialog::getOpenFileName(this,QStringLiteral("选择Excel文件"),"",tr("Exel file(*.xls *.xlsx)"));
    if(strFilePathName.isNull())
    {
        return ;
    }
    QAxObject *excel = new QAxObject(this);	//连接Excel控件
    if (excel->setControl("Excel.Application"))
    {

    }
    else
    {
        excel->setControl("ket.Application");  //连接Excel控件
    }
    excel->setProperty("Visible", true);  //不显示窗体

    QAxObject* workbooks = excel->querySubObject("WorkBooks");  //获取工作簿集合，从控件获取工作簿集合
    workbooks->dynamicCall("Open(const QString&)", strFilePathName); //打开已存在的工作簿

    QAxObject* workbook = excel->querySubObject("ActiveWorkBook"); //获取当前工作簿
    //QAxObject* sheets = workbook->querySubObject("Sheets");  //获取工作表集合，Sheets也可换用WorkSheets
    QAxObject* sheet = workbook->querySubObject("WorkSheets(int)", 1);//获取工作表集合的工作表1，即sheet1
    QAxObject* range = sheet->querySubObject("UsedRange"); //获取该sheet的使用范围对象
    QVariant var = range->dynamicCall("Value");
    delete range;
    QVariantList varRows = var.toList();  //得到表格中的所有数据
    if(varRows.isEmpty())
    {
        return;
    }
    const int rowCount1 = varRows.size();//得到行数。
   // QString m_userid;
    CurTableID=ID_Contract_Data;
    tabModel->setTable(DEF_Table[CurTableID].m_sName); //设置数据表"Contract"
    for(int i=0;i<DEF_Contract_Def_Sum;i++)
    {
        tabModel->setHeaderData(tabModel->fieldIndex(DEF_Contract_Def[i].m_sName),Qt::Horizontal,DEF_Contract_Def[i].m_sDesc);
    };
    tabModel->setRelation(tabModel->fieldIndex("RegionID"),QSqlRelation("Region","ID","Name"));
    QSqlRecord Rec=tabModel->record();
    for(int i=1;i<rowCount1;i++)
    {
        QVariantList rowData = varRows[i].toList();//i行数据
        Rec.setValue("ID",tabModel->rowCount());qDebug()<<"rowCount插入前:"<<tabModel->rowCount();
        Rec.setValue("ContractNumber",rowData[1].toString());
        Rec.setValue("Name",rowData[2].toString());
        Rec.setValue("AmountOnContract",rowData[3].toString());
        Rec.setValue("AmountPurchased","0");
        Rec.setValue("Classification",rowData[6].toString());
        Rec.setValue("RegionID","1");
        tabModel->insertRecord(-1,Rec);
        qDebug()<<"rowCount:"<<tabModel->rowCount();
        tabModel->submitAll();
    }
}
void MainWindow::on_actionRecInsert_triggered()
{
    if(tabModel->isDirty())
        {
            ui->actionSubmit->setEnabled(true);
            ui->actionRevert->setEnabled(true);
        }
}

void MainWindow::on_actionHoursquery_triggered()
{
    // queryModel =new  QSqlQueryModel(this);
     QSqlQueryModel *queryModel = new QSqlQueryModel;
     queryModel->setQuery("SELECT "
                          "Contract.ContractNumber, "
                          "Contract.Name, "
                          "Contract.RegionID, "
                          "Contract.AmountOnContract "
                          "FROM "
                          "Contract "
                          "WHERE "
                          "Contract.RegionID = 1");
     qDebug()<<queryModel->lastError();
     ui->tableView->setModel(queryModel);
     if(tabModel->isDirty())
         {
             ui->actionSubmit->setEnabled(true);
             ui->actionRevert->setEnabled(true);
         }
}
