#include "test.h"

Test app;
FaFrameBase *const theApp = &app;

Test::Test()
{
}

Test::~Test()
{
}

//启动进程前的准备工作
void Test::prepare()
{
    cout << "prepare" << endl;
}

//业务处理函数
void Test::handle()
{
    cout << "handle" << endl;
}

//进程退出
void Test::finish()
{
    cout << "finish" << endl;
}