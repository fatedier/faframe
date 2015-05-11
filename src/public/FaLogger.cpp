/*************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved。
* 文件名称:  FaLogger.cpp
* 描述:      日志类
* @author:   王成龙 <fatedier@gmail.com>
*
*************************************************************************/

#include "FaLogger.h"

FaLogger::FaLogger()
{
    m_nLogLevel = FADEBUG;
    m_nMaxBackupIndex = 1;
    m_nMaxFileSize = 1;
    m_nNowBackupNum = 0;
    m_nRotateWay = FANONE;
}

// 构造函数：需要配置文件对象、配置的前缀名（如 test.log.level，test就是前缀名）
FaLogger::FaLogger(FaProperties& cfgFile, const string& strPreName)
{
    this->init(cfgFile, strPreName);
}

// 构造函数：需要配置文件路径、配置的前缀名
FaLogger::FaLogger(const string& cfgFilePath, const string& strPreName)
{
    this->init(cfgFilePath, strPreName);
}

FaLogger::~FaLogger()
{
}


// 通过FaProperties对象初始化
void FaLogger::init(FaProperties& cfgFile, const string& strPreName)
{
    string strPreNameFull = strPreName;
    if (strPreNameFull != "")
    {
        strPreNameFull += ".";
    }
    // 取日志级别
    m_nLogLevel = cfgFile.getInt(strPreNameFull + "log.level", FADEBUG);
    // 取日志文件名
    m_strLogFile = cfgFile.getString(strPreNameFull + "log.filename", "./logs/default.log");
    // 取日志切分方式
    string strRotateWay = cfgFile.getString(strPreNameFull + "log.rotateway", "size");
    if (strRotateWay == "size")
    {
        m_nRotateWay = FASIZE;
        m_nMaxFileSize = cfgFile.getInt(strPreNameFull + "log.max_file_size", 1) * 1024 * 1024;
    }
    else if (strRotateWay == "day")
    {
        m_nRotateWay = FADAY;
    }
    // 取最多保留的日志个数
    m_nMaxBackupIndex = cfgFile.getInt(strPreNameFull + "log.max_backup_index", 1);

    string dirName = fa_getDirOfFile(m_strLogFile);
    if (dirName != "")
    {
        if (!fa_fileExists(dirName))
        {
            if (mkdir(dirName.c_str(), 0755) != 0)
            {
                string e = "创建目录 [" + dirName + "] 失败！";
                throw FaException(ERROR_FILE, e);
            }
        }
    }
    // 初始化日志文件对象
    m_fileOut = fopen(m_strLogFile.c_str(), "a+");
    if (m_fileOut == NULL)
    {
        string e = "创建日志文件 [" + m_strLogFile + "] 失败！";
        throw FaException(ERROR_FILE, e);
    }

    m_nNowBackupNum = 0;
}

// 通过配置文件路径进行初始化
void FaLogger::init(const string& cfgFilePath, const string& strPreName)
{
    FaProperties cfgFile;
    cfgFile.open(cfgFilePath.c_str());
    this->init(cfgFile, strPreName);
    cfgFile.close();
}

// 关闭文件输出对象
void FaLogger::close()
{
    fclose(m_fileOut);
    m_fileOut = NULL;
}

// 检测指定日志级别是否能够输出
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

// 记录一条日志
void FaLogger::log(FaLogLevel logLevel, const string& msg, const char* file, int line)
{
    if (false == this->isEnableFor(logLevel))
    {
        return;
    }

    // 拼接日志
    string strNow = fa_getSysTime();
    stringstream os;
    os << "[";
    os << strNow.substr(0, 4) << "-" << strNow.substr(4, 2) << "-" << strNow.substr(6, 2) << " ";   //年月日
    os << strNow.substr(8, 2) << ":" << strNow.substr(10, 2) << ":" << strNow.substr(12, 2) << "."; //时分秒
    os << strNow.substr(14, 3);             //毫秒
    os << "] ";
    os << sLogLevelName[logLevel] << " - "; //日志等级
    os << msg << " ";                       //日志内容
    os << "[" << file << ":";               //代码所在文件名
    os << line << "]\n";                    //代码所在行

    pthread_mutex_lock(&m_lock);

    // 检查日志文件大小是否需要切分
    if (m_nRotateWay == FASIZE)
    {
        int nFileSize = ftell(m_fileOut);
        // 当前文件大小已经超出设置值，进行文件切分
        if (nFileSize >= m_nMaxFileSize)
        {
            if (m_nNowBackupNum >= m_nMaxBackupIndex)
            {
                unlink((m_strLogFile + "." + fa_ltostr(m_nNowBackupNum)).c_str());
                m_nNowBackupNum--;
            }
            for (int i=m_nNowBackupNum; i>0; i--)
            {
                string strOldFile = m_strLogFile + "." + fa_ltostr(i);
                string strNewFile = m_strLogFile + "." + fa_ltostr(i + 1);
                rename(strOldFile.c_str(), strNewFile.c_str());
            }
            this->close();
            rename(m_strLogFile.c_str(), (m_strLogFile + ".1").c_str());

            string dirName = fa_getDirOfFile(m_strLogFile);
            if (dirName != "")
            {
                if (!fa_fileExists(dirName))
                {
                    if (mkdir(dirName.c_str(), 0755) != 0)
                    {
                        string e = "创建目录 [" + dirName + "] 失败！";
                        throw FaException(ERROR_FILE, e);
                    }
                }
            }
            
            // 重新生成一个日志文件
            m_fileOut = fopen(m_strLogFile.c_str(), "a+");
            if (m_fileOut == NULL)
            {
                string e = "创建日志文件 [" + m_strLogFile + "] 失败！";
                throw FaException(ERROR_FILE, e);
            }
            m_nNowBackupNum++;
            pthread_mutex_unlock(&m_lock);
        }
    }

    fprintf(m_fileOut, "%s", os.str().c_str());
    pthread_mutex_unlock(&m_lock);
}
