/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved。
* 文件名称:  FaFunc.cpp
* 描述:      常用函数接口
* @author:   王成龙
* 修改记录：
*
***************************************************************************************/

#include "FaFunc.h"

char* fa_ltoa(long number, char* str, int nBufferLen)
{
    snprintf(str, nBufferLen, "%ld", number);
    return str;
}

string fa_ltostr(long number)
{
    char str[33] = {0};
    snprintf(str, sizeof(str), "%ld", number);
    string strTemp = str;
    return strTemp;
}

int fa_getWeekDay(int year, int month, int day)
{
	if (month == 1 || month == 2)
	{
		year -= 1;
		month += 12;
	}
	return (day + 1 + 2*month + 3*(month+1)/5 + year + (year)/4 - year/100 + year/400)%7;
}

string fa_getSysTime()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	struct tm* pTime;
	pTime = localtime(&tv.tv_sec);
	
	char sTemp[30] = {0};
	snprintf(sTemp, sizeof(sTemp), "%04d%02d%02d%02d%02d%02d%03d%03d", pTime->tm_year+1900, \
			 pTime->tm_mon+1, pTime->tm_mday, pTime->tm_hour, pTime->tm_min, pTime->tm_sec, \
			 tv.tv_usec/1000, tv.tv_usec%1000);
	return (string)sTemp;
}