/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved。
* 文件名称:  FaProperties.h
* 描述:      配置文件相关
* @author:   王成龙
* @注意：    根据键查找值如果没有默认值时需要捕获异常
* 修改记录：
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

/*--常用函数--*/
    //加载配置文件，错误则抛出异常
    void open(const char* sFileName);
    //清空map中的内容
    void close();
    //根据键获取字符串，若不存在，抛出异常
    string getString(const string& strKey);
    //根据键获取字符串，含默认值
    string getString(const string& strKey, const string& strDefaultValue);
    //根据键获取数，若不存在，抛出异常
    int getInt(const string& strKey);
    //根据键获取数，含默认值
    int getInt(const string& strKey, int nDefaultValue);

/*--内部函数--*/
private:
    void parseLineToMap(char* sLineStr);    //将一行的内容解析为Key-Value格式插入map中
    void trim(char* str);                   //去除掉首尾的空格和Tab

private:
    string m_strFileName;               //文件名
    map<string, string> mapLinevalue;   //每一行的键值对，中间用"="号分隔
};

#endif //FAFRAME_PUBLIC_FAPROPERTIES_H_