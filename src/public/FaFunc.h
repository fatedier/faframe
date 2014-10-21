/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved��
* �ļ�����:  FaFunc.h
* ����:      ���ú����ӿ�
* @author:   ������
* �޸ļ�¼��
*
***************************************************************************************/

#ifndef FAFRAME_PUBLIC_FAFUNC_H_
#define FAFRAME_PUBLIC_FAFUNC_H_

#include <iostream>
#include <string>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>
using namespace std;

/*
* longת��Ϊchar*
* @param number:     Ҫת����long������
* @param str: 	     Ԥ�ȷ���ÿռ��char���飬���� > 10
* @param nBufferLen: str����ռ�Ĵ�С��������sizeof��ȡ
* @return        ָ��str��ָ�룬����ת����ɵ��ַ���
*/
char* fa_ltoa(long number, char* str, int nBufferLen);

/*
* longת��Ϊstring
* @param number: Ҫת����long������
* @return        ת����ɺ��string�����ַ���
*/
string fa_ltostr(long number);

/*
* ����ָ�����ڷ��������ڼ�
* @param year:  ��
* @param month: ��
* @param day:   ��
* @return       ����һ�������ն�Ӧ int��(1 ���� 7)
*/
int fa_getWeekDay(int year, int month, int day);

/*
* ���ص�ǰϵͳʱ�䣬��ȷ��΢�
* @return		string�����ַ�������ʽΪ������ʱ�������΢����� "20140930102408001002"
*/
string fa_getSysTime();

#endif //FAFRAME_PUBLIC_FAFUNC_H_