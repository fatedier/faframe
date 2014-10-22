/*************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved。
* 文件名称:  FaException.h
* 描述:      异常处理类
* @author:   王成龙 <fatedier@gmail.com>
*
*************************************************************************/

#ifndef FAFRAME_PUBLIC_FAEXCEPTION_H_
#define FAFRAME_PUBLIC_FAEXCEPTION_H_

#include <string>
#include <exception>
#include "DefineErrors.h"
using namespace std;

class FaException:public exception
{
public:
    FaException(int nErrorCode, const char* pErrorMsg) throw();
    FaException(int nErrorCode, string strErrorMsg) throw();
    virtual ~FaException() throw();

    virtual const char* what() const throw();   //标准库异常基类的方法
    int getCode() throw();                      //获取异常编码
    const char* getMsg() const throw();         //获取异常信息

private:
    int m_nErrorCode;           //异常编码
    string m_strErrorMsg;       //异常信息
};

#endif //FAFRAME_PUBLIC_FAEXCEPTION_H_