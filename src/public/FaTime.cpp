/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved。
* 文件名称:  FaTime.cpp
* 描述:      时间类
* @author:   王成龙
* @date:     2014-09-30
* 修改记录：
*
***************************************************************************************/

#include "FaTime.h"

//构造空字符串
FaTime::FaTime()
	:FaBaseTime()
{
	m_strDateTime = "000000";
}

//根据字符串构造时间对象
FaTime::FaTime(const char* sTime)
	:FaBaseTime(sTime)
{
	this->verifyFormat();
}

//根据字符串构造时间对象
FaTime::FaTime(const string& strTime)
	:FaBaseTime(strTime)
{
	this->verifyFormat();
}

FaTime::~FaTime()
{
}


/**常用函数**/
//获取从1970年开始到指定日期的秒数
time_t FaTime::mkTime() const
{
	struct tm tmTime;
    memset(&tmTime, 0, sizeof(tmTime));
    
    tmTime.tm_year = 70;
    tmTime.tm_mon = 0;
    tmTime.tm_mday = 1;
    tmTime.tm_hour = this->getHour();
    tmTime.tm_min = this->getMinute();
    tmTime.tm_sec = this->getSecond();

    return mktime(&tmTime);
}

//获取系统时间
string FaTime::getSysTime()
{
	string strSysTime = fa_getSysTime();
	m_strDateTime = strSysTime.substr(8, 6);
	return m_strDateTime;
}

//获取小时
int FaTime::getHour() const
{
	return atoi(m_strDateTime.substr(0, 2).c_str());
}

//获取分钟
int FaTime::getMinute() const
{
	return atoi(m_strDateTime.substr(2, 2).c_str());
}

//获取秒
int FaTime::getSecond() const
{
	return atoi(m_strDateTime.substr(4, 2).c_str());
}

//增加天数
void FaTime::addDay(int nDay)
{
	this->addSecond(nDay*24*60*60);
}

//增加小时
void FaTime::addHour(int nHour)
{
	this->addSecond(nHour*60*60);
}

//增加分钟
void FaTime::addMinute(int nMinute)
{
	this->addSecond(nMinute*60);
}

//增加秒
void FaTime::addSecond(int nSecond)
{
	time_t timer = this->mkTime() + nSecond;
	
	struct tm *tmNew;
	tmNew = localtime(&timer);
	
	char sFormat[15] = {0};
	snprintf(sFormat, sizeof(sFormat), "%02d%02d%02d", tmNew->tm_hour, \
			tmNew->tm_min, tmNew->tm_sec);
	
	m_strDateTime = sFormat;
}




/**运算符重载**/
FaTime& FaTime::operator =(const char* sTime)
{
	m_strDateTime = sTime;
	this->verifyFormat();
	return *this;
}

FaTime& FaTime::operator =(const string& strTime)
{
	m_strDateTime = strTime;
	this->verifyFormat();
	return *this;
}

FaTime& FaTime::operator =(const FaTime& faTime)
{
	this->m_strDateTime = faTime.m_strDateTime;
	return *this;
}

bool operator >(const FaTime& left, const FaTime& right)
{
	if(strcmp(left.m_strDateTime.c_str(), right.m_strDateTime.c_str()) > 0)
	{
		return true;
	}
	return false;
}

bool operator >=(const FaTime& left, const FaTime& right)
{
	if(strcmp(left.m_strDateTime.c_str(), right.m_strDateTime.c_str()) >= 0)
	{
		return true;
	}
	return false;
}

bool operator <(const FaTime& left, const FaTime& right)
{
	if(strcmp(left.m_strDateTime.c_str(), right.m_strDateTime.c_str()) < 0)
	{
		return true;
	}
	return false;
}

bool operator <=(const FaTime& left, const FaTime& right)
{
	if(strcmp(left.m_strDateTime.c_str(), right.m_strDateTime.c_str()) <= 0)
	{
		return true;
	}
	return false;
}

bool operator ==(const FaTime& left, const FaTime& right)
{
	if(strcmp(left.m_strDateTime.c_str(), right.m_strDateTime.c_str()) == 0)
	{
		return true;
	}
	return false;
}

bool operator !=(const FaTime& left, const FaTime& right)
{
	if(strcmp(left.m_strDateTime.c_str(), right.m_strDateTime.c_str()) != 0)
	{
		return true;
	}
	return false;
}

//返回值为两者间隔的秒数
int operator -(const FaTime& left, const FaTime& right)
{
	struct tm tmLeft,tmRight;
	memset(&tmLeft, 0, sizeof(tmLeft));
	memset(&tmLeft, 0, sizeof(tmRight));

	tmLeft.tm_year = 70;
	tmLeft.tm_mon = 0;
	tmLeft.tm_mday = 1;
    tmLeft.tm_hour = left.getHour();
    tmLeft.tm_min = left.getMinute();
    tmLeft.tm_sec = left.getSecond();
    
    tmRight.tm_year = 70;
	tmRight.tm_mon = 0;
	tmRight.tm_mday = 1;
    tmRight.tm_hour = right.getHour();
    tmRight.tm_min = right.getMinute();
    tmRight.tm_sec = right.getSecond();
    
    return (int)(mktime(&tmLeft) - mktime(&tmRight));
}



/**内部调用函数**/
//检查时间格式和字符串是否符合要求
bool FaTime::verifyFormat()
{
	//检查时间字符串是否全都是数字
	for(int i=0; i<m_strDateTime.size(); i++)
	{
		if(!isdigit(m_strDateTime[i]))
		{
			throw FaException(ERROR_TIME, "时间字符串含有非数字字符！");
		}
	}
	
	if(m_strDateTime.size() != 6)
	{
		throw FaException(ERROR_TIME, "时间格式长度错误！");
	}
	this->verifyTime(m_strDateTime);
	
	return true;
}