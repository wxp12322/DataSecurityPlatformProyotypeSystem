#pragma once



// CCfgView ������ͼ

class CCfgView : public CFormView
{
	DECLARE_DYNCREATE(CCfgView)

protected:
	CCfgView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CCfgView();

public:
	enum { IDD = IDD_DIALOG_CFG };
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
	CString m_strsrvip;
	CString m_strsrvnodenum;
	CString m_strsrvport;
	virtual void OnInitialUpdate();
	void  CCfgView::OnInitialUpdate2();
	afx_msg void OnBnClickedButtonSaveserver();
};


