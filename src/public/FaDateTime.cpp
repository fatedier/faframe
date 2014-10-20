/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved。
* 文件名称:  FaDateTime.h
* 描述:      日期时间类
* @author:   王成龙
* @date:     2014-09-30
* 修改记录：
*
***************************************************************************************/

#include "FaDateTime.h"

//构造初始字符串
FaDateTime::FaDateTime()
	:FaBaseTime()
{
	m_strDateTime = "19000101000000";
}

//根据字符串构造时间对象
FaDateTime::FaDateTime(const char* sDateTime)
	:FaBaseTime(sDateTime)
{
	this->verifyFormat();
}

//根据字符串构造时间对象
FaDateTime::FaDateTime(const string& strDateTime)
	:FaBaseTime(strDateTime)
{
	this->verifyFormat();
}

FaDateTime::~FaDateTime()
{
}


/**常用函数**/
//获取从1970年开始到指定日期的秒数
time_t FaDateTime::mkTime() const
{
	struct tm tmTime;

    memset(&tmTime, 0, sizeof(tmTime));
    tmTime.tm_year = this->getYear() - 1900;
    tmTime.tm_mon = this->getMonth() - 1;
    tmTime.tm_mday = this->getDay();
    tmTime.tm_hour = this->getHour();
    tmTime.tm_min = this->getMinute();
    tmTime.tm_sec = this->getSecond();

    return mktime(&tmTime);
}

//获取系统时间
string FaDateTime::getSysTime()
{
	string strSysTime = fa_getSysTime();
	m_strDateTime = strSysTime.substr(0, 14);
	return m_strDateTime;
}

//获取年份
int FaDateTime::getYear() const
{
	return atoi(m_strDateTime.substr(0, 4).c_str());
}

//获取月份
int FaDateTime::getMonth() const
{
	return atoi(m_strDateTime.substr(4, 2).c_str());
}

//获取所属月份的第几天
int FaDateTime::getDay() const
{
	return atoi(m_strDateTime.substr(6, 2).c_str());
}

//获取小时
int FaDateTime::getHour() const
{
	return atoi(m_strDateTime.substr(8, 2).c_str());
}

//获取分钟
int FaDateTime::getMinute() const
{
	return atoi(m_strDateTime.substr(10, 2).c_str());
}

//获取秒
int FaDateTime::getSecond() const
{
	return atoi(m_strDateTime.substr(12, 2).c_str());
}

//增加天数
void FaDateTime::addDay(int nDay)
{
	this->addSecond(nDay*24*60*60);
}

//增加小时
void FaDateTime::addHour(int nHour)
{
	this->addSecond(nHour*60*60);
}

//增加分钟
void FaDateTime::addMinute(int nMinute)
{
	this->addSecond(nMinute*60);
}

//增加秒
void FaDateTime::addSecond(int nSecond)
{
	time_t timer = this->mkTime() + nSecond;
	
	struct tm *tmNew;
	tmNew = localtime(&timer);
	
	char sFormat[15] = {0};
	snprintf(sFormat, sizeof(sFormat), "%04d%02d%02d%02d%02d%02d", tmNew->tm_year+1900, tmNew->tm_mon+1, \
			tmNew->tm_mday, tmNew->tm_hour, tmNew->tm_min, tmNew->tm_sec);
	
	m_strDateTime = sFormat;
}


/**运算符重载**/
FaDateTime& FaDateTime::operator =(const char* sDateTime)
{
	m_strDateTime = sDateTime;
	this->verifyFormat();
	return *this;
}

FaDateTime& FaDateTime::operator =(const string& strDateTime)
{
	m_strDateTime = strDateTime;
	this->verifyFormat();
	return *this;
}

FaDateTime& FaDateTime::operator =(const FaDateTime& faDateTime)
{
	this->m_strDateTime = faDateTime.m_strDateTime;
	return *this;
}

bool operator >(const FaDateTime& left, const FaDateTime& right)
{
	if(strcmp(left.m_strDateTime.c_str(), right.m_strDateTime.c_str()) > 0)
	{
		return true;
	}
	return false;
}

bool operator >=(const FaDateTime& left, const FaDateTime& right)
{
	if(strcmp(left.m_strDateTime.c_str(), right.m_strDateTime.c_str()) >= 0)
	{
		return true;
	}
	return false;
}

bool operator <(const FaDateTime& left, const FaDateTime& right)
{
	if(strcmp(left.m_strDateTime.c_str(), right.m_strDateTime.c_str()) < 0)
	{
		return true;
	}
	return false;
}

bool operator <=(const FaDateTime& left, const FaDateTime& right)
{
	if(strcmp(left.m_strDateTime.c_str(), right.m_strDateTime.c_str()) <= 0)
	{
		return true;
	}
	return false;
}

bool operator ==(const FaDateTime& left, const FaDateTime& right)
{
	if(strcmp(left.m_strDateTime.c_str(), right.m_strDateTime.c_str()) == 0)
	{
		return true;
	}
	return false;
}

bool operator !=(const FaDateTime& left, const FaDateTime& right)
{
	if(strcmp(left.m_strDateTime.c_str(), right.m_strDateTime.c_str()) != 0)
	{
		return true;
	}
	return false;
}

//返回值为两者间隔的秒数（只能用于计算1970年之后的时间）
int operator -(const FaDateTime& left, const FaDateTime& right)
{
	struct tm tmLeft,tmRight;
	memset(&tmLeft, 0, sizeof(tmLeft));
	memset(&tmLeft, 0, sizeof(tmRight));

	tmLeft.tm_year = left.getYear() - 1900;
	tmLeft.tm_mon = left.getMonth() - 1;
	tmLeft.tm_mday = left.getDay();
    tmLeft.tm_hour = left.getHour();
    tmLeft.tm_min = left.getMinute();
    tmLeft.tm_sec = left.getSecond();
    
    tmRight.tm_year = right.getYear() - 1900;
	tmRight.tm_mon = right.getMonth() - 1;
	tmRight.tm_mday = right.getDay();
    tmRight.tm_hour = right.getHour();
    tmRight.tm_min = right.getMinute();
    tmRight.tm_sec = right.getSecond();
    
    return (int)(mktime(&tmLeft) - mktime(&tmRight));
}



/**内部调用函数**/
//检查时间格式和字符串是否符合要求
bool FaDateTime::verifyFormat()
{
	//检查时间字符串是否全都是数字
	for(int i=0; i<m_strDateTime.size(); i++)
	{
		if(!isdigit(m_strDateTime[i]))
		{
			throw FaException(ERROR_TIME, "时间字符串含有非数字字符！");
		}
	}
	
	if(m_strDateTime.size() != 14)
	{
		throw FaException(ERROR_TIME, "完整时间格式长度错误！");
	}
	string strTemp = m_strDateTime.substr(0, 8);
	this->verifyDate(strTemp);
	strTemp = m_strDateTime.substr(8, 6);
	this->verifyTime(strTemp);
	
	return true;
}