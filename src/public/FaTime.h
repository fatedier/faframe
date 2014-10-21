/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved��
* �ļ�����:  FaTime.h
* ����:      ʱ����
* @author:   ������
* @date:     2014-09-30
* ע�⣺	 1970��֮ǰ��ʱ�䴦����ܻ����쳣
* �޸ļ�¼��
*
***************************************************************************************/

#ifndef _FATIME_H_
#define _FATIME_H_

#include "FaBaseTime.h"

class FaTime:public FaBaseTime
{
/**���켰��������**/
public:
	FaTime();							//������ַ���
	FaTime(const char* sTime);			//�����ַ�������ʱ�����
	FaTime(const string& strTime);		//�����ַ�������ʱ�����
	virtual ~FaTime();

/**���ú���**/
public:
	virtual time_t mkTime() const;		//��ȡ��1970�꿪ʼ��ָ�����ڵ�����
	virtual string getSysTime();		//��ȡϵͳʱ��
	int getHour() const;				//��ȡСʱ
	int getMinute() const;				//��ȡ����
	int getSecond() const;				//��ȡ��
	void addDay(int nDay);				//��������
	void addHour(int nHour);			//����Сʱ
	void addMinute(int nMinute);		//���ӷ���
	void addSecond(int nSecond);		//������
	//���ຯ��
	//bool isLeapYear(int year) const;					//�ж��Ƿ�������
	//int getLastDayOfMonth(int year, int month) const;	//��ȡָ�����µ����һ��
	//string toString() const;							//��������ʱ���ַ���

/**���������**/
public:
	FaTime& operator =(const char* sTime);
	FaTime& operator =(const string& strTime);
	FaTime& operator =(const FaTime& faTime);
	friend bool operator >(const FaTime& left, const FaTime& right);
	friend bool operator >=(const FaTime& left, const FaTime& right);
	friend bool operator <(const FaTime& left, const FaTime& right);
	friend bool operator <=(const FaTime& left, const FaTime& right);
	friend bool operator ==(const FaTime& left, const FaTime& right);
	friend bool operator !=(const FaTime& left, const FaTime& right);
	friend int  operator -(const FaTime& left, const FaTime& right);	//����ֵΪ���߼��������
	
/**�ڲ����ú���**/
protected:
	virtual bool verifyFormat();		//���ʱ���ʽ���ַ����Ƿ����Ҫ��
};

#endif