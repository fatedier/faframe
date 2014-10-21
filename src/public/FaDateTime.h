/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved��
* �ļ�����:  FaDateTime.h
* ����:      ����ʱ����
* @author:   ������
* @date:     2014-09-30
* ע�⣺	 1970��֮ǰ��ʱ�䴦����ܻ����쳣
* �޸ļ�¼��
*
***************************************************************************************/

#ifndef _FADATETIME_H_
#define _FADATETIME_H_

#include "FaBaseTime.h"
#include "FaDate.h"
#include "FaTime.h"

class FaDateTime:public FaBaseTime
{
/**���켰��������**/
public:
	FaDateTime();							//������ַ���
	FaDateTime(const char* sDateTime);		//�����ַ�������ʱ�����
	FaDateTime(const string& strDateTime);	//�����ַ�������ʱ�����
	virtual ~FaDateTime();

/**���ú���**/
public:
	virtual time_t mkTime() const;		//��ȡ��1970�꿪ʼ��ָ�����ڵ�����
	virtual string getSysTime();		//��ȡϵͳʱ��
	int getYear() const;				//��ȡ���
	int getMonth() const;				//��ȡ�·�
	int getDay() const;					//��ȡ�����·ݵĵڼ���
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
	FaDateTime& operator =(const char* sDateTime);
	FaDateTime& operator =(const string& strDateTime);
	FaDateTime& operator =(const FaDateTime& faDateTime);
	friend bool operator >(const FaDateTime& left, const FaDateTime& right);
	friend bool operator >=(const FaDateTime& left, const FaDateTime& right);
	friend bool operator <(const FaDateTime& left, const FaDateTime& right);
	friend bool operator <=(const FaDateTime& left, const FaDateTime& right);
	friend bool operator ==(const FaDateTime& left, const FaDateTime& right);
	friend bool operator !=(const FaDateTime& left, const FaDateTime& right);
	//����ֵΪ���߼����������ֻ�����ڼ���1970��֮���ʱ�䣩
	friend int  operator -(const FaDateTime& left, const FaDateTime& right);
	
/**�ڲ����ú���**/
protected:
	virtual bool verifyFormat();		//���ʱ���ʽ���ַ����Ƿ����Ҫ��
};

#endif