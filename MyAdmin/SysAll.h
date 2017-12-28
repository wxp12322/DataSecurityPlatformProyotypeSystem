#pragma once
#include "afxcmn.h"
#include "TabSheet.h"

#include "DlgTab1.h"
#include "DlgTab2.h"
#include "DlgTab3.h"



// CSysAll ������ͼ

class CSysAll : public CFormView
{
	DECLARE_DYNCREATE(CSysAll)

protected:
	CSysAll();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CSysAll();

public:
	enum { IDD = IDD_DIALOG_SYSALL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	//CTabCtrl myTab;  //vc�� ֻ�� �ṩĬ�ϵ���
	CTabSheet myTab;  //�ֹ��޸ĳ� �û��Զ�����
	CDlgTab1		m_dlgTab1;
	CDlgTab2		m_dlgTab2;
	CDlgTab3		m_dlgTab3;

	virtual void OnInitialUpdate();
	afx_msg void OnPaint();
};


