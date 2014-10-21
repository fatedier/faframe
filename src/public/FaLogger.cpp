/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved��
* �ļ�����:  FaLogger.cpp
* ����:      ��־��
* @author:   ������
* �޸ļ�¼��
*
***************************************************************************************/

#include "FaLogger.h"

FaLogger::FaLogger()
{
	m_nLogLevel = FADEBUG;
}

//���캯������Ҫ�����ļ��������õ�ǰ׺������ test.log.level��test����ǰ׺����
FaLogger::FaLogger(FaProperties& cfgFile, const char* preName)
{
	this->init(cfgFile, preName);
}

FaLogger::~FaLogger()
{
	
}


//��ʼ��
void FaLogger::init(FaProperties& cfgFile, const char* preName)
{
	string strPreName = preName;
	if (strPreName != "")
	{
		strPreName += ".";
	}
	//ȡ��־����
	m_nLogLevel = cfgFile.getInt(strPreName + "log.level", FADEBUG);
	//ȡ��־�ļ���
	m_strLogFile = cfgFile.getString(strPreName + "log.filename", "./logs/default.log");
	
	//��ʼ����־�ļ�����
	m_fileOut = fopen(m_strLogFile.c_str(), "a+");
}

//�ر��ļ��������
void FaLogger::close()
{
	fclose(m_fileOut);
	m_fileOut = NULL;
}

//���ָ����־�����Ƿ��ܹ����
bool FaLogger::isEnableFor(FaLogLevel logLevel)
{
	if (logLevel >= m_nLogLevel)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//��¼һ����־
void FaLogger::log(FaLogLevel logLevel, const string& msg, const char* file, int line)
{
	if (false == this->isEnableFor(logLevel))
	{
		return;
	}
	
	string strNow = fa_getSysTime();
	stringstream os;
	os << "[";
	os << strNow.substr(0, 4) << "-" << strNow.substr(4, 2) << "-" << strNow.substr(6, 2) << " "; 	//������
	os << strNow.substr(8, 2) << ":" << strNow.substr(10, 2) << ":" << strNow.substr(12, 2) << ".";	//ʱ����
	os << strNow.substr(14, 3);				//����
	os << "] ";
	os << sLogLevelName[logLevel] << " - ";	//��־�ȼ�
	os << msg << " ";						//��־����
	os << "[" << file << ":";				//���������ļ���
	os << line << "]\n";					//����������
	
	fprintf(m_fileOut, "%s", os.str().c_str());
}