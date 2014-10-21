/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved��
* �ļ�����:  FaDate.h
* ����:      ������
* @author:   ������
* @date:     2014-09-30
* ע�⣺	 1970��֮ǰ��ʱ�䴦����ܻ����쳣
* �޸ļ�¼��
*
***************************************************************************************/

#ifndef _FADATE_H_
#define _FADATE_H_

#include "FaBaseTime.h"

class FaDate:public FaBaseTime
{
/**���켰��������**/
public:
	FaDate();							//������ַ���
	FaDate(const char* sDate);			//�����ַ�������ʱ�����
	FaDate(const string& strDate);		//�����ַ�������ʱ�����
	virtual ~FaDate();

/**���ú���**/
public:
	virtual time_t mkTime() const;		//��ȡ��1970�꿪ʼ��ָ�����ڵ�����
	virtual string getSysTime();		//��ȡϵͳʱ��
	int getYear() const;				//��ȡ���
	int getMonth() const;				//��ȡ�·�
	int getDay() const;					//��ȡ�����·ݵĵڼ���
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
	FaDate& operator =(const char* sDate);
	FaDate& operator =(const string& strDate);
	FaDate& operator =(const FaDate& faDate);
	friend bool operator >(const FaDate& left, const FaDate& right);
	friend bool operator >=(const FaDate& left, const FaDate& right);
	friend bool operator <(const FaDate& left, const FaDate& right);
	friend bool operator <=(const FaDate& left, const FaDate& right);
	friend bool operator ==(const FaDate& left, const FaDate& right);
	friend bool operator !=(const FaDate& left, const FaDate& right);
	//����ֵΪ���߼����������ֻ�����ڼ���1970��֮���ʱ�䣩
	friend int  operator -(const FaDate& left, const FaDate& right);
	
/**�ڲ����ú���**/
protected:
	virtual bool verifyFormat();		//���ʱ���ʽ���ַ����Ƿ����Ҫ��
};

#endif