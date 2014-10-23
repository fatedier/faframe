/*************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved。
* 文件名称:  FaFramebase.cpp
* 描述:      进程框架基类
* @author:   王成龙 <fatedier@gmail.com>
*
*************************************************************************/

#include "FaFrameBase.h"

FaFrameBase::FaFrameBase()
{
}

FaFrameBase::~FaFrameBase()
{
}

//进程初始化
int FaFrameBase::initialize(int argc, char* argv[])
{
    map<string, string> map_parameter;
    for (int i = 1; i < argc; i++)
    {
        string strKey = argv[i];
    }
    //TODO:将类似"-F test.cfg"这样的参数作为键值对放入map中，之后按需要取
    return 0;
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

//进程运行，执行顺序prepare -> 循环执行handle -> finish
void FaFrameBase::run()
{
    this->prepare();
    this->handle();
    this->finish();
}


//进程入口处
int main(int argc, char* argv[])
{
    theApp->initialize(argc, argv);
    theApp->run();
    return 0;
}