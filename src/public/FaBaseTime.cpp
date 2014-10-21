/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved��
* �ļ�����:  FaBaseTime.cpp
* ����:      ����ʱ����صĻ���
* @author:   ������
* �޸ļ�¼��
*
***************************************************************************************/

#include "FaBaseTime.h"

int FaBaseTime::m_nMonthDayC[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
int FaBaseTime::m_nMonthDayS[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	
/**���켰��������**/
//�����ʼ�ַ���
FaBaseTime::FaBaseTime()
{
	m_strDateTime = "";
}

//�����ַ�������ʱ�����
FaBaseTime::FaBaseTime(const char* sDateTime)
{
	m_strDateTime = sDateTime;
}

//�����ַ�������ʱ�����
FaBaseTime::FaBaseTime(const string& strDateTime)
{
	m_strDateTime = strDateTime;
}

FaBaseTime::~FaBaseTime()
{
}



/**���ú���**/
//�ж��Ƿ�������
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

//��ȡָ�����µ����һ��
int FaBaseTime::getLastDayOfMonth(int year, int month) const
{
	//����
	if (this->isLeapYear(year))
	{
		return m_nMonthDayS[month-1];
	}
	//������
	else
	{
		return m_nMonthDayC[month-1];
	}
}

//��������ʱ���ַ���
string FaBaseTime::toString() const
{
	return m_strDateTime;
}


/**�ڲ����ú���**/
//���8λ�ַ������ڸ�ʽ�Ƿ���ȷ
void FaBaseTime::verifyDate(const string& strDate)
{
	int year = atoi(strDate.substr(0, 4).c_str());
	int month = atoi(strDate.substr(4, 2).c_str());
	int day = atoi(strDate.substr(6, 2).c_str());
	
	if (year <= 0 || year > 9999)
	{
		throw FaException(ERROR_TIME, "��ݴ���");
	}
	if (month <= 0 || month > 12)
	{
		throw FaException(ERROR_TIME, "�·ݴ���");
	}
	if (day <= 0 || day > this->getLastDayOfMonth(year, month))
	{
		throw FaException(ERROR_TIME, "��(day)����");
	}
}

//���6λ�ַ���ʱ���ʽ�Ƿ���ȷ
void FaBaseTime::verifyTime(const string& strTime)
{
	int hour = atoi(strTime.substr(0, 2).c_str());
	int minute = atoi(strTime.substr(2, 2).c_str());
	int second = atoi(strTime.substr(4, 2).c_str());
	
	if (hour < 0 || hour > 23)
	{
		throw FaException(ERROR_TIME, "Сʱ����");
	}
	if (minute < 0 || minute > 59)
	{
		throw FaException(ERROR_TIME, "���Ӵ���");
	}
	if (second < 0 || second > 59)
	{
		throw FaException(ERROR_TIME, "�����");
	}
}