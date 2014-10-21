/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved��
* �ļ�����:  FaException.cpp
* ����:      �쳣������
* @author:   ������
* @date:     2014-09-30
* �޸ļ�¼��
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

//��׼���쳣����ķ���
const char* FaException::what() const throw()
{
	return m_strErrorMsg.c_str();
}

//��ȡ�쳣����
int FaException::getCode() throw()
{
	return m_nErrorCode;
}

//��ȡ�쳣��Ϣ
const char* FaException::getMsg() const throw()
{
	return m_strErrorMsg.c_str();
}