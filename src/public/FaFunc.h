/*************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved。
* 文件名称:  FaFunc.h
* 描述:      常用函数接口
* @author:   王成龙 <fatedier@gmail.com>
*
*************************************************************************/

#ifndef FAFRAME_PUBLIC_FAFUNC_H_
#define FAFRAME_PUBLIC_FAFUNC_H_

#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
#include <sys/stat.h>
using namespace std;

/*
 * long转换为char*
 * @param number:     要转换的long型数字
 * @param str:        预先分配好空间的char数组，容量 > 10
 * @param nBufferLen: str分配空间的大小，建议用sizeof获取
 *
 * @return        指向str的指针，保存转换完成的字符串
 */
char* fa_ltoa(long number, char* str, int nBufferLen);

/*
 * long转换为string
 * @param number: 要转换的long型数字
 *
 * @return        转换完成后的string类型字符串
 */
string fa_ltostr(long number);

/*
 * 根据指定日期返回是星期几
 * @param year:  年
 * @param month: 月
 * @param day:   日
 *
 * @return       星期一至星期日对应 int型(1 —— 7)
 */
int fa_getWeekDay(int year, int month, int day);

/*
 * 返回当前系统时间，精确到微秒级
 *
 * @return       string类型字符串，格式为年月日时分秒毫秒微妙，类似 "20140930102408001002"
 */
string fa_getSysTime();

/*
 * 根据文件路径获取实际的文件名
 * @param strFilePath:  文件路径名
 *
 * @return  实际的文件名
 */
string fa_getRealFileName(const string& strFilePath);

/*
 * 根据文件路径字符串获取文件所在目录
 * @param strFilePath:  文件路径名
 *
 * @return  文件所在目录的字符串
 */
string fa_getDirOfFile(const string& strFilePath);

/*
 * 根据文件路径获取文件大小
 * @param strFilePath:  文件路径名
 *
 * @return   文件的大小，如果文件不存在返回-1
 */
int fa_getFileSize(const string& strFilePath);

/*
 * 检查文件是否存在
 * @param strFilePath:  文件路径名
 *
 * @return  文件是否存在
 */
bool fa_fileExists(const string& strFilePath);
#endif //FAFRAME_PUBLIC_FAFUNC_H_
