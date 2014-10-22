/*************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved。
* 文件名称:  FaFrameDefine.h
* 描述:      宏定义及全局变量定义
* @author:   王成龙 <fatedier@gmail.com>
*
*************************************************************************/

#ifndef FAFRAME_FRAME_FAFRAMEDEFINE_H_
#define FAFRAME_FRAME_FAFRAMEDEFINE_H_

//STL头文件定义
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <deque>
#include <queue>
#include <map>
#include <limits>
#include<sys/file.h> 
using namespace std;

//框架头文件
#include "FaLogger.h"
#include "FaProperties.h"

//全局变量定义
class FaFrameBase;
extern FaFrameBase *const theApp;   //进程对象指针，指向业务相关的派生类进程

extern FaLogger *g_Logger;          //全局日志对象指针，需要根据配置文件进行初始化

#endif //FAFRAME_FRAME_FAFRAMEDEFINE_H_