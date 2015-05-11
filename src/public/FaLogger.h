/*************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved。
* 文件名称:  FaLogger.h
* 描述:      日志类
* @author:   王成龙 <fatedier@gmail.com>
*
*************************************************************************/

#ifndef FAFRAME_PUBLIC_FALOGGER_H_
#define FAFRAME_PUBLIC_FALOGGER_H_

#include <pthread.h>
#include <sstream>
#include <limits>
#include "FaProperties.h"
#include "FaFunc.h"

// 日志等级定义
enum FaLogLevel
{
    FAFATAL,    // 0
    FAERROR,    // 1
    FAWARN,     // 2
    FAINFO,     // 3
    FADEBUG     // 4
};

// 日志切分方式定义
enum FaLogRotateWay
{
    FANONE,     // 0
    FASIZE,     // 1
    FADAY       // 2
};

// 日志等级对应的字符串
const char sLogLevelName[][10] =
{
    "FATAL",
    "ERROR",
    "WARN ",
    "INFO ",
    "DEBUG"
};

// 提前声明
class FaLogger;

// 日志函数宏定义
#define LOG_FATAL(logger, strMsg)\
{\
    if (true == (logger)->isEnableFor(FAFATAL))\
    {\
        ostringstream os;\
        os.precision(numeric_limits<double>::digits10 + 1);\
        os << strMsg;\
        (logger)->log(FAFATAL, os.str(), __FILE__, __LINE__);\
    }\
}\

#define LOG_ERROR(logger, strMsg)\
{\
    if (true == (logger)->isEnableFor(FAERROR))\
    {\
        ostringstream os;\
        os.precision(numeric_limits<double>::digits10 + 1);\
        os << strMsg;\
        (logger)->log(FAERROR, os.str(), __FILE__, __LINE__);\
    }\
}\

#define LOG_WARN(logger, strMsg)\
{\
    if (true == (logger)->isEnableFor(FAWARN))\
    {\
        ostringstream os;\
        os.precision(numeric_limits<double>::digits10 + 1);\
        os << strMsg;\
        (logger)->log(FAWARN, os.str(), __FILE__, __LINE__);\
    }\
}\

#define LOG_INFO(logger, strMsg)\
{\
    if (true == (logger)->isEnableFor(FAINFO))\
    {\
        ostringstream os;\
        os.precision(numeric_limits<double>::digits10 + 1);\
        os << strMsg;\
        (logger)->log(FAINFO, os.str(), __FILE__, __LINE__);\
    }\
}\

#define LOG_DEBUG(logger, strMsg)\
{\
    if (true == (logger)->isEnableFor(FADEBUG))\
    {\
        ostringstream os;\
        os.precision(numeric_limits<double>::digits10 + 1);\
        os << strMsg;\
        (logger)->log(FADEBUG, os.str(), __FILE__, __LINE__);\
    }\
}\


/*
* 先调用 init 函数从配置文件初始化日志对象
* 在需要打印日志的代码中使用 LOG_XXXX(logger, strMsg)，logger为已经初始化的日志对象
* 结束时调用 close函数
*
* 需要从配置文件读取日志配置信息，xxx为前缀名，这样可以在同一个进程中配置多个日志对象
* xxx.log.level: 日志级别
* xxx.log.filename: 日志文件名
* xxx.log.rotateway: 日志切分方式 size(按文件大小) day(按天)
* xxx.log.max_backup_index: 最多保留的日志个数
* xxx.log.max_file_size: 如果选择按size切分，需要设置日志文件大小，单位MB
*/
class FaLogger
{
public:
    FaLogger();
    // 构造函数：需要配置文件对象、配置的前缀名（如 test.log.level，test就是前缀名）
    FaLogger(FaProperties& cfgFile, const string& strPreName);
    // 构造函数：需要配置文件路径、配置的前缀名
    FaLogger(const string& cfgFilePath, const string& strPreName);
    virtual ~FaLogger();

    // 通过FaProperties对象初始化
    void init(FaProperties& cfgFile, const string& strPreName);
    // 通过配置文件路径进行初始化
    void init(const string& cfgFilePath, const string& strPreName);
    // 关闭文件输出对象
    void close();
    // 检测指定日志级别是否能够输出
    bool isEnableFor(FaLogLevel logLevel);

    /*
    * 记录一条日志
    * @param logLevel:  日志级别
    * @param msg:       日志内容
    * @param file:      代码所在文件名
    * @param line:      代码所在行数
    */
    void log(FaLogLevel logLevel, const string& msg, const char* file, int line);

private:
    pthread_mutex_t m_lock; // 互斥锁

    int m_nLogLevel;        // 日志级别
    string m_strLogFile;    // 日志文件
    int m_nRotateWay;       // 日志切分方式
    int m_nMaxBackupIndex;  // 最多保留的日志个数
    int m_nMaxFileSize;     // 如果按文件大小切分，切分文件的阀值，单位为Byte
    FILE* m_fileOut;        // 文件输出对象

    int m_nNowBackupNum;    // 当前存在的日志个数
};

#endif //FAFRAME_PUBLIC_FALOGGER_H_
