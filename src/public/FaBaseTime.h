/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved。
* 文件名称:  FaBaseTime.h
* 描述:      日期时间相关的基类
* @author:   王成龙
* @date:     2014-09-30
* 修改记录：
*
***************************************************************************************/

#ifndef _FABASETIME_H_
#define _FABASETIME_H_

#include <string>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "FaException.h"
#include "FaFunc.h"
using namespace std;

class FaBaseTime
{
/**构造及析构函数**/
public:
	FaBaseTime();							//构造空字符串
	FaBaseTime(const char* sDateTime);		//根据字符串构造时间对象
	FaBaseTime(const string& strDateTime);	//根据字符串构造时间对象
	virtual ~FaBaseTime();

/**常用函数**/
public:
	bool isLeapYear(int year) const;					//判断是否是闰年
	int getLastDayOfMonth(int year, int month) const;	//获取指定年月的最后一天
	string toString() const;							//返回日期时间字符串
	virtual time_t mkTime() const = 0;					//获取从1970年开始到指定日期的秒数
	virtual string getSysTime() = 0;					//获取系统时间
	
/**内部调用函数**/
protected:
	void verifyDate(const string& strDate);		//检查8位字符的日期格式是否正确
	void verifyTime(const string& strTime);		//检查6位字符的时间格式是否正确
	virtual bool verifyFormat() = 0;			//检查时间格式和字符串是否符合要求
	
protected:
	static int m_nMonthDayC[];	//普通年份的月份对应的天数
	static int m_nMonthDayS[];	//闰年的月份对应的天数
	
	string m_strDateTime;		//时间对应字符串
};

#endif