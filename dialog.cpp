#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <mainwindow.h>
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->lineEdit_pwd->setEchoMode(QLineEdit::Password);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_login_clicked()
{
    if(ui->lineEdit_pwd->text()=="1")
    {
      accept();

    }
    else
    {
    QMessageBox::warning(this,"warning","用户名或密码错误!",QMessageBox::Yes);
    ui->lineEdit_usr->clear();
    ui->lineEdit_pwd->clear();
    ui->lineEdit_usr->setFocus();
    }
}

void Dialog::on_pushButton_quit_clicked()
{
   close();
}
