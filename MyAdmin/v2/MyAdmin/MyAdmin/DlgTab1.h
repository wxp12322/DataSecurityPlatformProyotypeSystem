#pragma once


// CDlgTab1 �Ի���

class CDlgTab1 : public CDialog
{
	DECLARE_DYNAMIC(CDlgTab1)

public:
	CDlgTab1(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgTab1();

// �Ի�������
	enum { IDD = IDD_DIALOG_TAB1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
