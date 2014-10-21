/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved��
* �ļ�����:  FaBaseTime.h
* ����:      ����ʱ����صĻ���
* @author:   ������
* @date:     2014-09-30
* �޸ļ�¼��
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
/**���켰��������**/
public:
	FaBaseTime();							//������ַ���
	FaBaseTime(const char* sDateTime);		//�����ַ�������ʱ�����
	FaBaseTime(const string& strDateTime);	//�����ַ�������ʱ�����
	virtual ~FaBaseTime();

/**���ú���**/
public:
	bool isLeapYear(int year) const;					//�ж��Ƿ�������
	int getLastDayOfMonth(int year, int month) const;	//��ȡָ�����µ����һ��
	string toString() const;							//��������ʱ���ַ���
	virtual time_t mkTime() const = 0;					//��ȡ��1970�꿪ʼ��ָ�����ڵ�����
	virtual string getSysTime() = 0;					//��ȡϵͳʱ��
	
/**�ڲ����ú���**/
protected:
	void verifyDate(const string& strDate);		//���8λ�ַ������ڸ�ʽ�Ƿ���ȷ
	void verifyTime(const string& strTime);		//���6λ�ַ���ʱ���ʽ�Ƿ���ȷ
	virtual bool verifyFormat() = 0;			//���ʱ���ʽ���ַ����Ƿ����Ҫ��
	
protected:
	static int m_nMonthDayC[];	//��ͨ��ݵ��·ݶ�Ӧ������
	static int m_nMonthDayS[];	//������·ݶ�Ӧ������
	
	string m_strDateTime;		//ʱ���Ӧ�ַ���
};

#endif