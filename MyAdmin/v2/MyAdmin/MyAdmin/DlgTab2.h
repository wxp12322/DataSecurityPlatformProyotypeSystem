#pragma once


// CDlgTab2 �Ի���

class CDlgTab2 : public CDialog
{
	DECLARE_DYNAMIC(CDlgTab2)

public:
	CDlgTab2(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTab2();

// �Ի�������
	enum { IDD = IDD_DIALOG_TAB2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
