/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved��
* �ļ�����:  FaProperties.h
* ����:      �����ļ����
* @author:   ������
* @ע�⣺	 ���ݼ�����ֵ���û��Ĭ��ֵʱ��Ҫ�����쳣
* �޸ļ�¼��
*
***************************************************************************************/

#ifndef FAFRAME_PUBLIC_FAPROPERTIES_H_
#define FAFRAME_PUBLIC_FAPROPERTIES_H_

#include <string>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <map>
#include <stdio.h>
#include "FaException.h"
using namespace std;

class FaProperties
{
public:
	FaProperties();
	virtual ~FaProperties();

/*--���ú���--*/
	//���������ļ����������׳��쳣
	void open(const char* sFileName);
	//���map�е�����
	void close();
	//���ݼ���ȡ�ַ������������ڣ��׳��쳣
	string getString(const string& strKey);
	//���ݼ���ȡ�ַ�������Ĭ��ֵ
	string getString(const string& strKey, const string& strDefaultValue);
	//���ݼ���ȡ�����������ڣ��׳��쳣
	int getInt(const string& strKey);
	//���ݼ���ȡ������Ĭ��ֵ
	int getInt(const string& strKey, int nDefaultValue);
	
/*--�ڲ�����--*/
private:
	void parseLineToMap(char* sLineStr);	//��һ�е����ݽ���ΪKey-Value��ʽ����map��
	void trim(char* str);					//ȥ������β�Ŀո��Tab
	
private:
	string m_strFileName;				//�ļ���
	map<string, string> mapLinevalue;	//ÿһ�еļ�ֵ�ԣ��м���"="�ŷָ�
};

#endif //FAFRAME_PUBLIC_FAPROPERTIES_H_