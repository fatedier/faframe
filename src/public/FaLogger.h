/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved。
* 文件名称:  FaLogger.h
* 描述:      日志类
* @author:   王成龙
* 修改记录：
*
***************************************************************************************/

#ifndef FAFRAME_PUBLIC_FALOGGER_H_
#define FAFRAME_PUBLIC_FALOGGER_H_

#include "FaProperties.h"
#include "FaFunc.h"
using namespace std;

//日志等级定义
enum FaLogLevel
{
	FAFATAL,	//0
	FAERROR,	//1
	FAWARN,		//2
	FAINFO,		//3
	FADEBUG		//4
};

//日志等级对应的字符串
const char sLogLevelName[][10] = 
{
	"FATAL",
	"ERROR",
	"WARN ",
	"INFO ",
	"DEBUG"
};

//提前声明
class FaLogger;

//日志函数宏定义
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
	//构造函数：需要配置文件对象、配置的前缀名（如 test.log.level，test就是前缀名）
	FaLogger(FaProperties& cfgFile, const char* preName);
	virtual ~FaLogger();

	//初始化
	void init(FaProperties& cfgFile, const char* preName);
	//关闭文件输出对象
	void close();
	//检测指定日志级别是否能够输出
	bool isEnableFor(FaLogLevel logLevel);
	
	/*
	* 记录一条日志
	* @param logLevel:  日志级别
	* @param msg: 	    日志内容
	* @param file: 		代码所在文件名
	* @param line:		代码所在行数
	*/
	void log(FaLogLevel logLevel, const string& msg, const char* file, int line);

private:
	int m_nLogLevel;		//日志级别
	string m_strLogFile;	//日志文件
	FILE* m_fileOut;		//文件输出对象
};

#endif //FAFRAME_PUBLIC_FALOGGER_H_