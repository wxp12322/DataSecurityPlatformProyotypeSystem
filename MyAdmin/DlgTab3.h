#pragma once


// CDlgTab3 �Ի���

class CDlgTab3 : public CDialog
{
	DECLARE_DYNAMIC(CDlgTab3)

public:
	CDlgTab3(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTab3();

// �Ի�������
	enum { IDD = IDD_DIALOG_TAB3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
