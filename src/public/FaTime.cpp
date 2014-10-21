/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved��
* �ļ�����:  FaTime.cpp
* ����:      ʱ����
* @author:   ������
* @date:     2014-09-30
* �޸ļ�¼��
*
***************************************************************************************/

#include "FaTime.h"

//������ַ���
FaTime::FaTime()
	:FaBaseTime()
{
	m_strDateTime = "000000";
}

//�����ַ�������ʱ�����
FaTime::FaTime(const char* sTime)
	:FaBaseTime(sTime)
{
	this->verifyFormat();
}

//�����ַ�������ʱ�����
FaTime::FaTime(const string& strTime)
	:FaBaseTime(strTime)
{
	this->verifyFormat();
}

FaTime::~FaTime()
{
}


/**���ú���**/
//��ȡ��1970�꿪ʼ��ָ�����ڵ�����
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

//��ȡϵͳʱ��
string FaTime::getSysTime()
{
	string strSysTime = fa_getSysTime();
	m_strDateTime = strSysTime.substr(8, 6);
	return m_strDateTime;
}

//��ȡСʱ
int FaTime::getHour() const
{
	return atoi(m_strDateTime.substr(0, 2).c_str());
}

//��ȡ����
int FaTime::getMinute() const
{
	return atoi(m_strDateTime.substr(2, 2).c_str());
}

//��ȡ��
int FaTime::getSecond() const
{
	return atoi(m_strDateTime.substr(4, 2).c_str());
}

//��������
void FaTime::addDay(int nDay)
{
	this->addSecond(nDay*24*60*60);
}

//����Сʱ
void FaTime::addHour(int nHour)
{
	this->addSecond(nHour*60*60);
}

//���ӷ���
void FaTime::addMinute(int nMinute)
{
	this->addSecond(nMinute*60);
}

//������
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




/**���������**/
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

//����ֵΪ���߼��������
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



/**�ڲ����ú���**/
//���ʱ���ʽ���ַ����Ƿ����Ҫ��
bool FaTime::verifyFormat()
{
	//���ʱ���ַ����Ƿ�ȫ��������
	for(int i=0; i<m_strDateTime.size(); i++)
	{
		if(!isdigit(m_strDateTime[i]))
		{
			throw FaException(ERROR_TIME, "ʱ���ַ������з������ַ���");
		}
	}
	
	if(m_strDateTime.size() != 6)
	{
		throw FaException(ERROR_TIME, "ʱ���ʽ���ȴ���");
	}
	this->verifyTime(m_strDateTime);
	
	return true;
}