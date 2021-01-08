#include "mainwindow.h"
#include <QApplication>
#include "dialog.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog logindlg;
//     bLogin=false;
//     CurUser=ui->lineEdit_usr;
    if(logindlg.exec()==QDialog::Accepted)
    {
        MainWindow w;
        w.show();
        return a.exec();
    }
    else  return 0;
}
