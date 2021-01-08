#ifndef DATA_H
#define DATA_H
#include <QString>

//通用结构定义
struct RecordWithName
{
    int m_nId;			//编号int类型，也可以是enum类型。
    QString m_sName;		//标识
    QString m_sDesc;	//描述
};
//表定义
enum DEF_Table_ID
{
    ID_Table_Invalid = -1, //无效表标识

    ID_Contract_Data = 0,	//合同表信息
    ID_WorkingHours_Data,	//工时表信息
    ID_User_Data,		//用户信息
    ID_Region_Data,	//片区信息
    ID_Skill_Data,		//技能信息
    ID_Performance_Data,//绩效表信息
};

#define DEF_Table_Sum 6
static RecordWithName DEF_Table[DEF_Table_Sum]//静态全局变量，
= {
    ID_Contract_Data, "Contract", QString::fromLocal8Bit("合同表"),//ID_Contract_Data是枚举值=0；
    ID_WorkingHours_Data, "WorkingHours", QString::fromLocal8Bit("工时记录表"),
    ID_User_Data, "User", QString::fromLocal8Bit("用户信息"),
    ID_Region_Data, "Region", QString::fromLocal8Bit("片区表"),
    ID_Skill_Data, "Skill", QString::fromLocal8Bit("技能表"),
    ID_Performance_Data, "Performance", QString::fromLocal8Bit("绩效表"),
};

//表定义
enum DEF_FieldItem_Type
{
    FieldItem_PRIMARY,	//序号
    FieldItem_INT,		//整形
    FieldItem_ENUM,		//整形
    FieldItem_FLOAT,
    FieldItem_VCHAR,	//字符串
    FieldItem_VCHARL,	//长字符串
    FieldItem_Month,	//整形
    FieldItem_DATETIME,	//整形
};

//字段结构定义
struct FieldItem
{
    QString m_sName;		//字段名称
    QString m_sDesc;		//字段描述
    int m_nType;		//字段定义
    int m_nEditAuthority;			//编辑权限
    int m_nViewAuthority;			//查看权限
    bool m_bEditable;		//字段是否可编辑
    bool m_bVisible;			//字段是否可显示
    bool m_bSelectable;			//字段是否可选择
};
#define DEF_Contract_Def_Sum 13
static FieldItem DEF_Contract_Def[DEF_Contract_Def_Sum]//静态全局变量，
= {
    "ID", "序号", FieldItem_PRIMARY, 0x7fffffff, 0x7fffffff, 0, 1, 0,
    "ContractNumber", "合同号", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "Name", "工程名", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "AmountOnContract", "金额", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "AmountPurchased", "外购金额", FieldItem_ENUM, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "Classification", "合同分类", FieldItem_DATETIME, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "FinishDate", "投运日期", FieldItem_DATETIME, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "GetWorkingHours", "领取工时", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 0, 1, 0,
    "Times", "领取次数", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 0, 1, 0,
    "RemainWorkingHours", "剩余工时", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 0, 1, 0,
    "TotalWorkingHours", "总工时", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "Province", "省份", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "RegionID", "区域", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
};

#define DEF_WorkingHours_Def_Sum 13
static FieldItem DEF_WorkingHours_Def[DEF_WorkingHours_Def_Sum]//静态全局变量，
= {
    "ID", "序号", FieldItem_PRIMARY, 0x7fffffff, 0x7fffffff, 0, 1, 0,
    "ContractID", "合同号索引", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "ContractNumber", "合同号", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "ContractName", "工程名称", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "GetDate", "领取日期", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "Amount", "领取数量", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "EmployeeID", "领取人员索引", FieldItem_ENUM, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "Type", "领取类型", FieldItem_DATETIME, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "Cause", "领取原因", FieldItem_DATETIME, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "RegionUserID", "人员区域", FieldItem_DATETIME, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "RegionContractID", "合同区域", FieldItem_DATETIME, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "GetDateYear", "领取年度", FieldItem_DATETIME, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "GetDateMonth", "领取月份", FieldItem_DATETIME, 0x7fffffff, 0x7fffffff, 1, 1, 1,
};

#define DEF_User_Def_Sum 14
static FieldItem DEF_User_Def[DEF_User_Def_Sum]//静态全局变量，
= {
    "ID", "序号", FieldItem_PRIMARY, 0x7fffffff, 0x7fffffff, 0, 1, 0,
    "User", "用户名", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "Name", "姓名", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "RegionID", "片区", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "OutsourceType", "外包类型", FieldItem_ENUM, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "EntryTime", "入职年份", FieldItem_DATETIME, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "LevelOfSkill", "技能等级", FieldItem_DATETIME, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "Position", "职位", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 0, 1, 0,
    "WorkingHours", "投运工时", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 0, 1, 0,
    "RemainWorkingHours", "剩余工时", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 0, 1, 0,
    "BorrowWorkingHours", "借用工时", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "SkillList", "技能列表", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "BasicWage", "基础工资", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "Password", "密码", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
};

#define DEF_Region_Def_Sum 8
static FieldItem DEF_Region_Def[DEF_Region_Def_Sum]//静态全局变量，
= {
    "ID", "序号", FieldItem_PRIMARY, 0x7fffffff, 0x7fffffff, 0, 1, 0,
    "Name", "片区名称", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "WorkingHours", "投运总工时", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "RemainWorkingHours", "剩余工时", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "BorrowWorkingHours", "借用工时", FieldItem_ENUM, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "TotalEmployee", "人员总数", FieldItem_DATETIME, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "RegionCoefficient", "地区系数", FieldItem_DATETIME, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "RegionMaster", "主管", FieldItem_DATETIME, 0x7fffffff, 0x7fffffff, 1, 1, 1,
};

#define DEF_Skill_Def_Sum 3
static FieldItem DEF_Skill_Def[DEF_Skill_Def_Sum]//静态全局变量，
= {
    "ID", "序号", FieldItem_PRIMARY, 0x7fffffff, 0x7fffffff, 0, 1, 0,
    "Name", "技能名称", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "SkillPoints", "技能积分", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
};
#define DEF_Performance_Def_Sum 8
static FieldItem DEF_Performance_Def[DEF_Performance_Def_Sum]//静态全局变量，
= {
    "ID", "序号", FieldItem_PRIMARY, 0x7fffffff, 0x7fffffff, 0, 1, 0,
    "Month", "月份", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "UserID", "人员", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "TravelDays", "出差天数", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "Estimate", "主管评价", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "PerformanceRelatedWages", "绩效工资", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "WageIncentive", "奖励工资", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
    "TotalWages", "总工资", FieldItem_VCHAR, 0x7fffffff, 0x7fffffff, 1, 1, 1,
};
#endif // DATA_H
