/*************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved。
* 文件名称:  FaBaseTime.cpp
* 描述:      日期时间相关的基类
* @author:   王成龙 <fatedier@gmail.com>
*
*************************************************************************/

#include "FaBaseTime.h"

int FaBaseTime::m_nMonthDayC[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int FaBaseTime::m_nMonthDayS[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

/**构造及析构函数**/
//构造初始字符串
FaBaseTime::FaBaseTime()
{
    m_strDateTime = "";
}

//根据字符串构造时间对象
FaBaseTime::FaBaseTime(const char* sDateTime)
{
    m_strDateTime = sDateTime;
}

//根据字符串构造时间对象
FaBaseTime::FaBaseTime(const string& strDateTime)
{
    m_strDateTime = strDateTime;
}

FaBaseTime::~FaBaseTime()
{
}



/**常用函数**/
//判断是否是闰年
bool FaBaseTime::isLeapYear(int year) const
{
    if (year%100 == 0)
    {
        return (year%400 == 0);
    }
    else
    {
        return (year%4 == 0);
    }
}

//获取指定年月的最后一天
int FaBaseTime::getLastDayOfMonth(int year, int month) const
{
    //闰年
    if (this->isLeapYear(year))
    {
        return m_nMonthDayS[month-1];
    }
    //非闰年
    else
    {
        return m_nMonthDayC[month-1];
    }
}

//返回日期时间字符串
string FaBaseTime::toString() const
{
    return m_strDateTime;
}


/**内部调用函数**/
//检查8位字符的日期格式是否正确
void FaBaseTime::verifyDate(const string& strDate)
{
    int year = atoi(strDate.substr(0, 4).c_str());
    int month = atoi(strDate.substr(4, 2).c_str());
    int day = atoi(strDate.substr(6, 2).c_str());

    if (year <= 0 || year > 9999)
    {
        throw FaException(ERROR_TIME, "年份错误！");
    }
    if (month <= 0 || month > 12)
    {
        throw FaException(ERROR_TIME, "月份错误！");
    }
    if (day <= 0 || day > this->getLastDayOfMonth(year, month))
    {
        throw FaException(ERROR_TIME, "日(day)错误！");
    }
}

//检查6位字符的时间格式是否正确
void FaBaseTime::verifyTime(const string& strTime)
{
    int hour = atoi(strTime.substr(0, 2).c_str());
    int minute = atoi(strTime.substr(2, 2).c_str());
    int second = atoi(strTime.substr(4, 2).c_str());

    if (hour < 0 || hour > 23)
    {
        throw FaException(ERROR_TIME, "小时错误！");
    }
    if (minute < 0 || minute > 59)
    {
        throw FaException(ERROR_TIME, "分钟错误！");
    }
    if (second < 0 || second > 59)
    {
        throw FaException(ERROR_TIME, "秒错误！");
    }
}