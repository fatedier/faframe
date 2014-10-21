/**************************************************************************************
*
* Copyright  (c) 2014, FateDier All rights reserved��
* �ļ�����:  FaException.h
* ����:      �쳣������
* @author:   ������
* @date:     2014-09-30
* �޸ļ�¼��
*
***************************************************************************************/

#ifndef _FAEXCEPTION_H_
#define _FAEXCEPTION_H_

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
	
	virtual const char* what() const throw();	//��׼���쳣����ķ���
	int getCode() throw();						//��ȡ�쳣����
	const char* getMsg() const throw();			//��ȡ�쳣��Ϣ
	
private:
	int m_nErrorCode;			//�쳣����
	string m_strErrorMsg;		//�쳣��Ϣ
};

#endif