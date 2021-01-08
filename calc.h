#ifndef CALC_H
#define CALC_H

#include <QObject>
#include <mainwindow.h>
class Ccalc : public QObject
{
    Q_OBJECT
public:
    explicit Ccalc(QObject *parent = nullptr);


///////////片区表/////////////////////////////
//片区人员总数
int getSum();
//片区投运总工时
//片区剩余工时
//片区借用工时
//

//////////////////////////合同表//////////////////////
//计算工时：工时=金额*类型系数*片区系数
//统计合同号ID支取次数
//统计合同号ID支取数量
//统计合同号ID剩余数量
/////////////////////员工表///////////////////////
//计算单个员工ID投运工时
//单个员工I统计剩余工时
//单个员工I统计借用工时
//////////绩效表//////////////
//计算绩效
signals:

public slots:
};

#endif // CALC_H
