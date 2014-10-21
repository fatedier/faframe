/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved。
* 文件名称:  FaFramebase.cpp
* 描述:      进程框架基类
* @author:   王成龙
* 修改记录：
*
***************************************************************************************/

#include "FaFrameBase.h"

FaLogger g_Logger;  //全局日志对象，通过配置文件初始化，打印日志时需要指定为该对象

FaFrameBase::FaFrameBase()
{
}

FaFrameBase::~FaFrameBase()
{
}

//进程初始化
int FaFrameBase::initialize(int argc,char* argv[])
{
}

//启动进程前的准备工作
void FaFrameBase::prepare()
{
}

//业务处理函数
void FaFrameBase::handle()
{
}

//进程退出
void FaFrameBase::finish()
{
}