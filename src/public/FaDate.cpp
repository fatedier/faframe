/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved��
* �ļ�����:  FaDate.cpp
* ����:      ������
* @author:   ������
* �޸ļ�¼��
*
***************************************************************************************/

#include "FaDate.h"

//������ַ���
FaDate::FaDate()
	:FaBaseTime()
{
	m_strDateTime = "19000101";
}

//�����ַ�������ʱ�����
FaDate::FaDate(const char* sDate)
	:FaBaseTime(sDate)
{
	this->verifyFormat();
}

//�����ַ�������ʱ�����
FaDate::FaDate(const string& strDate)
	:FaBaseTime(strDate)
{
	this->verifyFormat();
}

FaDate::~FaDate()
{
}


/**���ú���**/
//��ȡ��1970�꿪ʼ��ָ�����ڵ�����
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

//��ȡϵͳʱ��
string FaDate::getSysTime()
{
	string strSysTime = fa_getSysTime();
	m_strDateTime = strSysTime.substr(0, 8);
	return m_strDateTime;
}

//��ȡ���
int FaDate::getYear() const
{
	return atoi(m_strDateTime.substr(0, 4).c_str());
}

//��ȡ�·�
int FaDate::getMonth() const
{
	return atoi(m_strDateTime.substr(4, 2).c_str());
}

//��ȡ�����·ݵĵڼ���
int FaDate::getDay() const
{
	return atoi(m_strDateTime.substr(6, 2).c_str());
}

//��������
void FaDate::addDay(int nDay)
{
	this->addSecond(nDay*24*60*60);
}

//����Сʱ
void FaDate::addHour(int nHour)
{
	this->addSecond(nHour*60*60);
}

//���ӷ���
void FaDate::addMinute(int nMinute)
{
	this->addSecond(nMinute*60);
}

//������
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




/**���������**/
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

//����ֵΪ���߼����������ֻ�����ڼ���1970��֮���ʱ�䣩
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


/**�ڲ����ú���**/
//���ʱ���ʽ���ַ����Ƿ����Ҫ��
bool FaDate::verifyFormat()
{
	//���ʱ���ַ����Ƿ�ȫ��������
	for (int i=0; i<m_strDateTime.size(); i++)
	{
		if (!isdigit(m_strDateTime[i]))
		{
			throw FaException(ERROR_TIME, "ʱ���ַ������з������ַ���");
		}
	}
	
	if (m_strDateTime.size() != 8)
	{
		throw FaException(ERROR_TIME, "���ڸ�ʽ���ȴ���");
	}
	this->verifyDate(m_strDateTime);
	
	return true;
}