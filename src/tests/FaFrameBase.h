/*************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved。
* 文件名称:  FaFramebase.h
* 描述:      进程框架基类
* @author:   王成龙 <fatedier@gmail.com>
*
*************************************************************************/

#ifndef FAFRAME_FRAME_FAFRAMEBASE_H
#define FAFRAME_FRAME_FAFRAMEBASE_H

#include <stdio.h>
#include "FaFrameDefine.h"
using namespace std;

class FaFrameBase
{
/*--构造及析构函数--*/
public:
    FaFrameBase();
    virtual ~FaFrameBase();

/*--常用函数--*/
    //进程初始化
    virtual int  initialize(int argc, char* argv[]);
    //启动进程前的准备工作
    virtual void prepare();
    //业务处理函数
    virtual void handle();
    //进程退出
    virtual void finish();
    
    //进程运行，执行顺序prepare -> 循环执行handle -> finish
    void run();
};

#endif //FAFRAME_FRAME_FAFRAMEBASE_H