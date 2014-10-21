/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved。
* 文件名称:  FaLogger.cpp
* 描述:      日志类
* @author:   王成龙
* 修改记录：
*
***************************************************************************************/

#include "FaLogger.h"

FaLogger::FaLogger()
{
	m_nLogLevel = FADEBUG;
}

//构造函数：需要配置文件对象、配置的前缀名（如 test.log.level，test就是前缀名）
FaLogger::FaLogger(FaProperties& cfgFile, const char* preName)
{
	this->init(cfgFile, preName);
}

FaLogger::~FaLogger()
{
	
}


//初始化
void FaLogger::init(FaProperties& cfgFile, const char* preName)
{
	string strPreName = preName;
	if (strPreName != "")
	{
		strPreName += ".";
	}
	//取日志级别
	m_nLogLevel = cfgFile.getInt(strPreName + "log.level", FADEBUG);
	//取日志文件名
	m_strLogFile = cfgFile.getString(strPreName + "log.filename", "./logs/default.log");
	
	//初始化日志文件对象
	m_fileOut = fopen(m_strLogFile.c_str(), "a+");
}

//关闭文件输出对象
void FaLogger::close()
{
	fclose(m_fileOut);
	m_fileOut = NULL;
}

//检测指定日志级别是否能够输出
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

//记录一条日志
void FaLogger::log(FaLogLevel logLevel, const string& msg, const char* file, int line)
{
	if (false == this->isEnableFor(logLevel))
	{
		return;
	}
	
	string strNow = fa_getSysTime();
	stringstream os;
	os << "[";
	os << strNow.substr(0, 4) << "-" << strNow.substr(4, 2) << "-" << strNow.substr(6, 2) << " "; 	//年月日
	os << strNow.substr(8, 2) << ":" << strNow.substr(10, 2) << ":" << strNow.substr(12, 2) << ".";	//时分秒
	os << strNow.substr(14, 3);				//毫秒
	os << "] ";
	os << sLogLevelName[logLevel] << " - ";	//日志等级
	os << msg << " ";						//日志内容
	os << "[" << file << ":";				//代码所在文件名
	os << line << "]\n";					//代码所在行
	
	fprintf(m_fileOut, "%s", os.str().c_str());
}