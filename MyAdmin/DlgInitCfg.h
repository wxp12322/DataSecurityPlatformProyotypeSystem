#pragma once


// CDlgInitCfg �Ի���

class CDlgInitCfg : public CDialog
{
	DECLARE_DYNAMIC(CDlgInitCfg)

public:
	CDlgInitCfg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgInitCfg();

// �Ի�������
	enum { IDD = IDD_DIALOG_INITDB };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedTest();
	afx_msg void OnBnClickedCancel();
	CString m_dbdsn;
	CString m_dbpw;
	CString m_dbuid;
};
