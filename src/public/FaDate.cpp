/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved。
* 文件名称:  FaDate.cpp
* 描述:      日期类
* @author:   王成龙
* 修改记录：
*
***************************************************************************************/

#include "FaDate.h"

//构造空字符串
FaDate::FaDate()
	:FaBaseTime()
{
	m_strDateTime = "19000101";
}

//根据字符串构造时间对象
FaDate::FaDate(const char* sDate)
	:FaBaseTime(sDate)
{
	this->verifyFormat();
}

//根据字符串构造时间对象
FaDate::FaDate(const string& strDate)
	:FaBaseTime(strDate)
{
	this->verifyFormat();
}

FaDate::~FaDate()
{
}


/**常用函数**/
//获取从1970年开始到指定日期的秒数
time_t FaDate::mkTime() const
{
	struct tm tmTime;

    memset(&tmTime, 0, sizeof(tmTime));
    tmTime.tm_year = this->getYear() - 1900;
    tmTime.tm_mon = this->getMonth() - 1;
    tmTime.tm_mday = this->getDay();
    tmTime.tm_hour = 0;
    tmTime.tm_min = 0;
    tmTime.tm_sec = 0;

    return mktime(&tmTime);
}

//获取系统时间
string FaDate::getSysTime()
{
	string strSysTime = fa_getSysTime();
	m_strDateTime = strSysTime.substr(0, 8);
	return m_strDateTime;
}

//获取年份
int FaDate::getYear() const
{
	return atoi(m_strDateTime.substr(0, 4).c_str());
}

//获取月份
int FaDate::getMonth() const
{
	return atoi(m_strDateTime.substr(4, 2).c_str());
}

//获取所属月份的第几天
int FaDate::getDay() const
{
	return atoi(m_strDateTime.substr(6, 2).c_str());
}

//增加天数
void FaDate::addDay(int nDay)
{
	this->addSecond(nDay*24*60*60);
}

//增加小时
void FaDate::addHour(int nHour)
{
	this->addSecond(nHour*60*60);
}

//增加分钟
void FaDate::addMinute(int nMinute)
{
	this->addSecond(nMinute*60);
}

//增加秒
void FaDate::addSecond(int nSecond)
{
	time_t timer = this->mkTime() + nSecond;
	
	struct tm *tmNew;
	tmNew = localtime(&timer);
	
	char sFormat[15] = {0};
	snprintf(sFormat, sizeof(sFormat), "%04d%02d%02d", tmNew->tm_year+1900, \
			tmNew->tm_mon+1, tmNew->tm_mday);
	
	m_strDateTime = sFormat;
}




/**运算符重载**/
FaDate& FaDate::operator =(const char* sDate)
{
	m_strDateTime = sDate;
	this->verifyFormat();
	return *this;
}

FaDate& FaDate::operator =(const string& strDate)
{
	m_strDateTime = strDate;
	this->verifyFormat();
	return *this;
}

FaDate& FaDate::operator =(const FaDate& faDate)
{
	this->m_strDateTime = faDate.m_strDateTime;
	return *this;
}

bool operator >(const FaDate& left, const FaDate& right)
{
	if (strcmp(left.m_strDateTime.c_str(), right.m_strDateTime.c_str()) > 0)
	{
		return true;
	}
	return false;
}

bool operator >=(const FaDate& left, const FaDate& right)
{
	if (strcmp(left.m_strDateTime.c_str(), right.m_strDateTime.c_str()) >= 0)
	{
		return true;
	}
	return false;
}

bool operator <(const FaDate& left, const FaDate& right)
{
	if (strcmp(left.m_strDateTime.c_str(), right.m_strDateTime.c_str()) < 0)
	{
		return true;
	}
	return false;
}

bool operator <=(const FaDate& left, const FaDate& right)
{
	if (strcmp(left.m_strDateTime.c_str(), right.m_strDateTime.c_str()) <= 0)
	{
		return true;
	}
	return false;
}

bool operator ==(const FaDate& left, const FaDate& right)
{
	if (strcmp(left.m_strDateTime.c_str(), right.m_strDateTime.c_str()) == 0)
	{
		return true;
	}
	return false;
}

bool operator !=(const FaDate& left, const FaDate& right)
{
	if (strcmp(left.m_strDateTime.c_str(), right.m_strDateTime.c_str()) != 0)
	{
		return true;
	}
	return false;
}

//返回值为两者间隔的秒数（只能用于计算1970年之后的时间）
int operator -(const FaDate& left, const FaDate& right)
{
	struct tm tmLeft,tmRight;
	memset(&tmLeft, 0, sizeof(tmLeft));
	memset(&tmLeft, 0, sizeof(tmRight));

	tmLeft.tm_year = left.getYear() - 1900;
	tmLeft.tm_mon = left.getMonth() - 1;
	tmLeft.tm_mday = left.getDay();
    tmLeft.tm_hour = 0;
    tmLeft.tm_min = 0;
    tmLeft.tm_sec = 0;
    
    tmRight.tm_year = right.getYear() - 1900;
	tmRight.tm_mon = right.getMonth() - 1;
	tmRight.tm_mday = right.getDay();
    tmRight.tm_hour = 0;
    tmRight.tm_min = 0;
    tmRight.tm_sec = 0;
    
    return (int)(mktime(&tmLeft) - mktime(&tmRight));
}


/**内部调用函数**/
//检查时间格式和字符串是否符合要求
bool FaDate::verifyFormat()
{
	//检查时间字符串是否全都是数字
	for (int i=0; i<m_strDateTime.size(); i++)
	{
		if (!isdigit(m_strDateTime[i]))
		{
			throw FaException(ERROR_TIME, "时间字符串含有非数字字符！");
		}
	}
	
	if (m_strDateTime.size() != 8)
	{
		throw FaException(ERROR_TIME, "日期格式长度错误！");
	}
	this->verifyDate(m_strDateTime);
	
	return true;
}