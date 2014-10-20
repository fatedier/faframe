/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved。
* 文件名称:  FaDateTime.h
* 描述:      日期时间类
* @author:   王成龙
* @date:     2014-09-30
* 注意：	 1970年之前的时间处理可能会有异常
* 修改记录：
*
***************************************************************************************/

#ifndef _FADATETIME_H_
#define _FADATETIME_H_

#include "FaBaseTime.h"
#include "FaDate.h"
#include "FaTime.h"

class FaDateTime:public FaBaseTime
{
/**构造及析构函数**/
public:
	FaDateTime();							//构造空字符串
	FaDateTime(const char* sDateTime);		//根据字符串构造时间对象
	FaDateTime(const string& strDateTime);	//根据字符串构造时间对象
	virtual ~FaDateTime();

/**常用函数**/
public:
	virtual time_t mkTime() const;		//获取从1970年开始到指定日期的秒数
	virtual string getSysTime();		//获取系统时间
	int getYear() const;				//获取年份
	int getMonth() const;				//获取月份
	int getDay() const;					//获取所属月份的第几天
	int getHour() const;				//获取小时
	int getMinute() const;				//获取分钟
	int getSecond() const;				//获取秒
	void addDay(int nDay);				//增加天数
	void addHour(int nHour);			//增加小时
	void addMinute(int nMinute);		//增加分钟
	void addSecond(int nSecond);		//增加秒
	//基类函数
	//bool isLeapYear(int year) const;					//判断是否是闰年
	//int getLastDayOfMonth(int year, int month) const;	//获取指定年月的最后一天
	//string toString() const;							//返回日期时间字符串

/**运算符重载**/
public:
	FaDateTime& operator =(const char* sDateTime);
	FaDateTime& operator =(const string& strDateTime);
	FaDateTime& operator =(const FaDateTime& faDateTime);
	friend bool operator >(const FaDateTime& left, const FaDateTime& right);
	friend bool operator >=(const FaDateTime& left, const FaDateTime& right);
	friend bool operator <(const FaDateTime& left, const FaDateTime& right);
	friend bool operator <=(const FaDateTime& left, const FaDateTime& right);
	friend bool operator ==(const FaDateTime& left, const FaDateTime& right);
	friend bool operator !=(const FaDateTime& left, const FaDateTime& right);
	//返回值为两者间隔的秒数（只能用于计算1970年之后的时间）
	friend int  operator -(const FaDateTime& left, const FaDateTime& right);
	
/**内部调用函数**/
protected:
	virtual bool verifyFormat();		//检查时间格式和字符串是否符合要求
};

#endif