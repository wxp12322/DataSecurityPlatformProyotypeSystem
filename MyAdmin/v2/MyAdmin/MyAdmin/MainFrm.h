
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

#include "GfxSplitterWnd.h"
#include "GfxOutBarCtrl.h"


class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
	afx_msg long OnOutbarNotify(WPARAM wParam, LPARAM lParam);

public:
	CGfxSplitterWnd		wndSplitter;
	CGfxOutBarCtrl		wndBar;
	CImageList			imaLarge, imaSmall;
	CTreeCtrl			wndTree;


	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
};


