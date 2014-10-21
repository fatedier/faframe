/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved。
* 文件名称:  FaTime.h
* 描述:      时间类
* @author:   王成龙
* 注意：     1970年之前的时间处理可能会有异常
* 修改记录：
*
***************************************************************************************/

#ifndef FAFRAME_PUBLIC_FATIME_H_
#define FAFRAME_PUBLIC_FATIME_H_

#include "FaBaseTime.h"

class FaTime:public FaBaseTime
{
/**构造及析构函数**/
public:
    FaTime();                           //构造空字符串
    FaTime(const char* sTime);          //根据字符串构造时间对象
    FaTime(const string& strTime);      //根据字符串构造时间对象
    virtual ~FaTime();

/**常用函数**/
    virtual time_t mkTime() const;      //获取从1970年开始到指定日期的秒数
    virtual string getSysTime();        //获取系统时间
    int getHour() const;                //获取小时
    int getMinute() const;              //获取分钟
    int getSecond() const;              //获取秒
    void addDay(int nDay);              //增加天数
    void addHour(int nHour);            //增加小时
    void addMinute(int nMinute);        //增加分钟
    void addSecond(int nSecond);        //增加秒
    //基类函数
    //bool isLeapYear(int year) const;                  //判断是否是闰年
    //int getLastDayOfMonth(int year, int month) const; //获取指定年月的最后一天
    //string toString() const;                          //返回日期时间字符串

/**运算符重载**/
    FaTime& operator =(const char* sTime);
    FaTime& operator =(const string& strTime);
    FaTime& operator =(const FaTime& faTime);
    friend bool operator >(const FaTime& left, const FaTime& right);
    friend bool operator >=(const FaTime& left, const FaTime& right);
    friend bool operator <(const FaTime& left, const FaTime& right);
    friend bool operator <=(const FaTime& left, const FaTime& right);
    friend bool operator ==(const FaTime& left, const FaTime& right);
    friend bool operator !=(const FaTime& left, const FaTime& right);
    friend int  operator -(const FaTime& left, const FaTime& right);    //返回值为两者间隔的秒数

/**内部调用函数**/
protected:
    virtual bool verifyFormat();        //检查时间格式和字符串是否符合要求
};

#endif //FAFRAME_PUBLIC_FATIME_H_