#include <iostream>
#include "FaFrameBase.h"
using namespace std;

class Test:public FaFrameBase
{
public:
    Test();
    virtual ~Test();
    
    //启动进程前的准备工作
    virtual void prepare();
    //业务处理函数
    virtual void handle();
    //进程退出
    virtual void finish();
};