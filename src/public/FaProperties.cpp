/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved��
* �ļ�����:  FaProperties.cpp
* ����:      �����ļ����
* @author:   ������
* @date:     2014-10-10
* �޸ļ�¼��
*
***************************************************************************************/

#include "FaProperties.h"

#define MAX_LINE_LENGTH 2048

FaProperties::FaProperties()
{
}

FaProperties::~FaProperties()
{
}

/*--���ú���--*/
//���������ļ����������׳��쳣
void FaProperties::open(const char* sFileName)
{
	m_strFileName = sFileName;
	
	//��ֻ����ʽ��ָ���ļ�
	fstream file(m_strFileName.c_str(), ios::in);
	
	char sLineStr[MAX_LINE_LENGTH] = {0};
	if(file.is_open())
	{
		while(file.getline(sLineStr, MAX_LINE_LENGTH))
		{
			this->parseLineToMap(sLineStr);
		}
		file.close();
	}
	else
	{
		//���ļ�ʧ��
		throw FaException(ERROR_PROPERTIES, "��ȡ�ļ�ʧ�ܣ�");
	}
}

//���map�е�����
void FaProperties::close()
{
	mapLinevalue.clear();
}
	
//���ݼ���ȡ�ַ������������ڣ��׳��쳣
string FaProperties::getString(const string& strKey)
{
	map<string, string>::iterator iter;
	iter = mapLinevalue.find(strKey);
	if(iter != mapLinevalue.end())
	{
		return iter->second;
	}
	else
	{
		string strErrorMsg = "δ�ҵ� [" + strKey + "] ��Ӧ��ֵ��";
		throw FaException(ERROR_PROPERTIES, strErrorMsg);
	}
}

//���ݼ���ȡ�ַ�������Ĭ��ֵ
string FaProperties::getString(const string& strKey, const string& strDefaultValue)
{
	map<string, string>::iterator iter;
	iter = mapLinevalue.find(strKey);
	if(iter != mapLinevalue.end())
	{
		return iter->second;
	}
	else
	{
		string strReturn = strDefaultValue;
		return strReturn;
	}
}

//���ݼ���ȡ�����������ڣ��׳��쳣
int FaProperties::getInt(const string& strKey)
{
	//�����ַ�����δ�ҵ����׳��쳣
	string strValue = this->getString(strKey);
	//���鵽��ֵת��Ϊint�ͷ���
	return atoi(strValue.c_str());
}

//���ݼ���ȡ������Ĭ��ֵ
int FaProperties::getInt(const string& strKey, int nDefaultValue)
{
	stringstream os;
	os << nDefaultValue;
	string strValue = this->getString(strKey, os.str());
	return atoi(strValue.c_str());
}
	


/*--�ڲ�����--*/
//��һ�е����ݽ���ΪKey-Value��ʽ����map��
void FaProperties::parseLineToMap(char* sLineStr)
{
	string strKey;
	string strValue;
	
	this->trim(sLineStr);
	char* p = strchr(sLineStr, '#');	//ȥ����ע�Ͳ���
	if(NULL != p)
	{
		*p = '\0';
	}
	//���ֻ��ע�Ͳ��֣�ֱ�ӷ���
	if('\0' == *sLineStr)
	{
		return;
	}
	//���ҷָ���"="
	p = strchr(sLineStr, '=');
	//��������ڣ���Ϊ��Ч������
	if(NULL == p)
	{
		return;
	}
	//����ΪKey-Value��ʽ��������map��
	*p = '\0';
	p++;
	this->trim(sLineStr);
	this->trim(p);
	strKey = sLineStr;
	strValue = p;
	mapLinevalue[strKey] = strValue;
}

//ȥ������β�Ŀո��Tab
void FaProperties::trim(char* str)
{
	char* head = str;
	char* tail = str + strlen(str);
	//����ǰ��Ŀո��Tab
	while(*head == ' ' || *head == '\t')
	{
		head++;
	}
	//��������Ŀո��Tab
	if(head != tail)
	{
		tail--;
		while(*tail == ' ' || *tail == '\t' || *tail == '\0')
		{
			tail--;
		}
		*(++tail) = '\0';
	}
	//���ǿյ��ַ����Ƶ�ǰ��
	while(head != tail)
	{
		*str = *head;
		str++;
		head++;
	}
	*str = '\0';
}