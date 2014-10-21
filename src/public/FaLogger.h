/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved��
* �ļ�����:  FaLogger.h
* ����:      ��־��
* @author:   ������
* �޸ļ�¼��
*
***************************************************************************************/

#ifndef FAFRAME_PUBLIC_FALOGGER_H_
#define FAFRAME_PUBLIC_FALOGGER_H_

#include "FaProperties.h"
#include "FaFunc.h"
using namespace std;

//��־�ȼ�����
enum FaLogLevel
{
	FAFATAL,	//0
	FAERROR,	//1
	FAWARN,		//2
	FAINFO,		//3
	FADEBUG		//4
};

//��־�ȼ���Ӧ���ַ���
const char sLogLevelName[][10] = 
{
	"FATAL",
	"ERROR",
	"WARN ",
	"INFO ",
	"DEBUG"
};

//��ǰ����
class FaLogger;

//��־�����궨��
#define LOG_FATAL(logger, strMsg)\
{\
	if(true == (logger)->isEnableFor(FAFATAL))\
	{\
		(logger)->log(FAFATAL, strMsg, __FILE__, __LINE__);\
	}\
}\

#define LOG_ERROR(logger, strMsg)\
{\
	if(true == (logger)->isEnableFor(FAERROR))\
	{\
		(logger)->log(FAERROR, strMsg, __FILE__, __LINE__);\
	}\
}\

#define LOG_WARN(logger, strMsg)\
{\
	if(true == (logger)->isEnableFor(FAWARN))\
	{\
		(logger)->log(FAWARN, strMsg, __FILE__, __LINE__);\
	}\
}\

#define LOG_INFO(logger, strMsg)\
{\
	if(true == (logger)->isEnableFor(FAINFO))\
	{\
		(logger)->log(FAINFO, strMsg, __FILE__, __LINE__);\
	}\
}\

#define LOG_DEBUG(logger, strMsg)\
{\
	if(true == (logger)->isEnableFor(FADEBUG))\
	{\
		(logger)->log(FADEBUG, strMsg, __FILE__, __LINE__);\
	}\
}\

class FaLogger
{
public:
	FaLogger();
	//���캯������Ҫ�����ļ��������õ�ǰ׺������ test.log.level��test����ǰ׺����
	FaLogger(FaProperties& cfgFile, const char* preName);
	virtual ~FaLogger();

	//��ʼ��
	void init(FaProperties& cfgFile, const char* preName);
	//�ر��ļ��������
	void close();
	//���ָ����־�����Ƿ��ܹ����
	bool isEnableFor(FaLogLevel logLevel);
	
	/*
	* ��¼һ����־
	* @param logLevel:  ��־����
	* @param msg: 	    ��־����
	* @param file: 		���������ļ���
	* @param line:		������������
	*/
	void log(FaLogLevel logLevel, const string& msg, const char* file, int line);

private:
	int m_nLogLevel;		//��־����
	string m_strLogFile;	//��־�ļ�
	FILE* m_fileOut;		//�ļ��������
};

#endif //FAFRAME_PUBLIC_FALOGGER_H_