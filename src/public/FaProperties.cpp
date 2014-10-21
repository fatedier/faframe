/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved。
* 文件名称:  FaProperties.cpp
* 描述:      配置文件相关
* @author:   王成龙
* 修改记录：
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

/*--常用函数--*/
//加载配置文件，错误则抛出异常
void FaProperties::open(const char* sFileName)
{
    m_strFileName = sFileName;

    //以只读方式打开指定文件
    fstream file(m_strFileName.c_str(), ios::in);

    char sLineStr[MAX_LINE_LENGTH] = {0};
    if (file.is_open())
    {
        while (file.getline(sLineStr, MAX_LINE_LENGTH))
        {
            this->parseLineToMap(sLineStr);
        }
        file.close();
    }
    else
    {
        //打开文件失败
        throw FaException(ERROR_PROPERTIES, "读取文件失败！");
    }
}

//清空map中的内容
void FaProperties::close()
{
    mapLinevalue.clear();
}

//根据键获取字符串，若不存在，抛出异常
string FaProperties::getString(const string& strKey)
{
    map<string, string>::iterator iter;
    iter = mapLinevalue.find(strKey);
    if (iter != mapLinevalue.end())
    {
        return iter->second;
    }
    else
    {
        string strErrorMsg = "未找到 [" + strKey + "] 对应的值！";
        throw FaException(ERROR_PROPERTIES, strErrorMsg);
    }
}

//根据键获取字符串，含默认值
string FaProperties::getString(const string& strKey, const string& strDefaultValue)
{
    map<string, string>::iterator iter;
    iter = mapLinevalue.find(strKey);
    if (iter != mapLinevalue.end())
    {
        return iter->second;
    }
    else
    {
        string strReturn = strDefaultValue;
        return strReturn;
    }
}

//根据键获取数，若不存在，抛出异常
int FaProperties::getInt(const string& strKey)
{
    //查找字符串，未找到会抛出异常
    string strValue = this->getString(strKey);
    //将查到的值转换为int型返回
    return atoi(strValue.c_str());
}

//根据键获取数，含默认值
int FaProperties::getInt(const string& strKey, int nDefaultValue)
{
    stringstream os;
    os << nDefaultValue;
    string strValue = this->getString(strKey, os.str());
    return atoi(strValue.c_str());
}



/*--内部函数--*/
//将一行的内容解析为Key-Value格式插入map中
void FaProperties::parseLineToMap(char* sLineStr)
{
    string strKey;
    string strValue;

    this->trim(sLineStr);
    char* p = strchr(sLineStr, '#');    //去除掉注释部分
    if (NULL != p)
    {
        *p = '\0';
    }
    //如果只有注释部分，直接返回
    if ('\0' == *sLineStr)
    {
        return;
    }
    //查找分隔符"="
    p = strchr(sLineStr, '=');
    //如果不存在，则为无效的配置
    if (NULL == p)
    {
        return;
    }
    //解析为Key-Value格式，保存在map中
    *p = '\0';
    p++;
    this->trim(sLineStr);
    this->trim(p);
    strKey = sLineStr;
    strValue = p;
    mapLinevalue[strKey] = strValue;
}

//去除掉首尾的空格和Tab
void FaProperties::trim(char* str)
{
    char* head = str;
    char* tail = str + strlen(str);
    //跳过前面的空格和Tab
    while (*head == ' ' || *head == '\t')
    {
        head++;
    }
    //跳过后面的空格和Tab
    if (head != tail)
    {
        tail--;
        while (*tail == ' ' || *tail == '\t' || *tail == '\0')
        {
            tail--;
        }
        *(++tail) = '\0';
    }
    //将非空的字符串移到前面
    while (head != tail)
    {
        *str = *head;
        str++;
        head++;
    }
    *str = '\0';
}