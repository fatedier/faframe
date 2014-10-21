/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved。
* 文件名称:  FaException.cpp
* 描述:      异常处理类
* @author:   王成龙
* 修改记录：
*
***************************************************************************************/

#include "FaException.h"

FaException::FaException(int nErrorCode, const char* pErrorMsg) throw()
{
    this->m_nErrorCode = nErrorCode;
    this->m_strErrorMsg = pErrorMsg;
}

FaException::FaException(int nErrorCode, string strErrorMsg) throw()
{
    this->m_nErrorCode = nErrorCode;
    this->m_strErrorMsg = strErrorMsg;
}

FaException::~FaException() throw()
{
}

//标准库异常基类的方法
const char* FaException::what() const throw()
{
    return m_strErrorMsg.c_str();
}

//获取异常编码
int FaException::getCode() throw()
{
    return m_nErrorCode;
}

//获取异常信息
const char* FaException::getMsg() const throw()
{
    return m_strErrorMsg.c_str();
}