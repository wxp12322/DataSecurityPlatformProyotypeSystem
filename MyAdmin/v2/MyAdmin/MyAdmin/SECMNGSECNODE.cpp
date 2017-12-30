// SECMNGSECNODE.h : CSECMNGSECNODE ���ʵ��



// CSECMNGSECNODE ʵ��

// ���������� 2015��12��23��, 16:04

#include "stdafx.h"
#include "SECMNGSECNODE.h"
#include "SECMNGSECNODE.h"

IMPLEMENT_DYNAMIC(CSECMNGSECNODE, CRecordset)

CSECMNGSECNODE::CSECMNGSECNODE(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ID = "";
	m_NAME = "";
	m_NODEDESC = "";
	m_CREATETIME;
	m_AUTHCODE = 0;
	m_STATE = 0;
	m_nFields = 6;
	m_nDefaultType = dynaset;
}
//#error ��ȫ���⣺�����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CSECMNGSECNODE::GetDefaultConnect()
{
	return _T("DSN=SECMNGADMIN;UID=SECMNGADMIN;PWD=123456;DBQ=SECMNGADMIN;DBA=W;APA=T;EXC=F;FEN=T;QTO=T;FRC=10;FDL=10;LOB=T;RST=T;GDE=F;FRL=F;BAM=IfAllSuccessful;NUM=NLS;DPM=F;MTS=T;MDI=F;CSR=F;FWC=F;FBS=64000;TLO=0;");
}

CString CSECMNGSECNODE::GetDefaultSQL()
{
	return _T("[SECMNG].[SECNODE]");
}

void CSECMNGSECNODE::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[NAME]"), m_NAME);
	RFX_Text(pFX, _T("[NODEDESC]"), m_NODEDESC);
	RFX_Date(pFX, _T("[CREATETIME]"), m_CREATETIME);
	RFX_Int(pFX, _T("[AUTHCODE]"), m_AUTHCODE);
	RFX_Int(pFX, _T("[STATE]"), m_STATE);

}
/////////////////////////////////////////////////////////////////////////////
// CSECMNGSECNODE ���

#ifdef _DEBUG
void CSECMNGSECNODE::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSECMNGSECNODE::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


