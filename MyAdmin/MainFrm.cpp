
// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "MyAdmin.h"

#include "MainFrm.h"
#include "FormBackground.h"
#include "CfgView.h"
#include "DlgNetInfo.h"
#include "SysAll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_MESSAGE(WM_OUTBAR_NOTIFY, OnOutbarNotify)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO:  �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO:  �������Ҫ��ͣ������������ɾ��������
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return TRUE;
}

// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame ��Ϣ�������

static UINT nImages[] =
{
	IDI_ICON_SET,
	IDI_ICON_USER,
	IDI_ICON_OP_LOG,
	IDI_ICON_LOG,
	IDI_ICON_REQ,
	IDI_ICON_RE,
	IDI_ICON_REPORT,
};

BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO:  �ڴ����ר�ô����/����û���
	//AfxMessageBox("���Ǻ�����,��д�Ĵ���");
	//return CFrameWnd::OnCreateClient(lpcs, pContext);

	// TODO: �ڴ����ר�ô����/����û���
	if (!wndSplitter.CreateStatic(this, 1, 2)) return false;

	if (!wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CFormBackground), CSize(0, 0), pContext))
		return false;

	//pContext->m_pNewViewClass RUNTIME_CLASS(CFormUserManager) CFormUserManager
	DWORD dwf = CGfxOutBarCtrl::fDragItems |
		CGfxOutBarCtrl::fEditGroups |
		CGfxOutBarCtrl::fEditItems |
		CGfxOutBarCtrl::fRemoveGroups |
		CGfxOutBarCtrl::fRemoveItems |
		CGfxOutBarCtrl::fAddGroups |
		CGfxOutBarCtrl::fAnimation;

	wndBar.Create(WS_CHILD | WS_VISIBLE, CRect(0, 0, 0, 0), &wndSplitter,
		wndSplitter.IdFromRowCol(0, 0), dwf);
	wndBar.SetOwner(this);

	imaLarge.Create(32, 32, true, 2, 1);
	HICON hIcon;

	for (int i = 0; i < 7; ++i)
	{
		hIcon = AfxGetApp()->LoadIcon(nImages[i]);
		imaLarge.Add(hIcon);
	}

	wndBar.SetImageList(&imaLarge, CGfxOutBarCtrl::fLargeIcon);
	wndBar.SetImageList(&imaSmall, CGfxOutBarCtrl::fSmallIcon);

	wndTree.Create(WS_CHILD | TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS,
		CRect(0, 0, 0, 0), &wndBar, 1010);
	wndTree.SetImageList(&imaSmall, TVSIL_NORMAL);
	wndBar.SetAnimationTickCount(20);
	wndBar.SetAnimSelHighlight(200);

	wndBar.AddFolder("SecMngServer���ù���", 0);
	wndBar.AddFolder("SecMngAdmin�������", 1);
	wndBar.AddFolder("��Ա����", 2);
	wndBar.AddFolder("�豸����", 3);
	//wndBar.AddFolder("CA��Ա������ѯ", 4);	

	wndBar.InsertItem(0, 0, "SecMngServer����", 0, 0);
	wndBar.InsertItem(0, 1, "������Ϣ����", 1, 0);
	wndBar.InsertItem(0, 2, "��̨ҵ�����", 4, 0); //
	wndBar.InsertItem(0, 3, "��̨���ײ�ѯ", 5, 0); //

	wndBar.InsertItem(1, 0, "ǰ̨��ϵ����", 6, 0);
	wndBar.InsertItem(1, 1, "ǰ̨ҵ�����", 4, 0);
	wndBar.InsertItem(1, 2, "ǰ̨���ײ�ѯ", 3, 0);

	wndBar.InsertItem(2, 0, "������Ա", 3, 0);
	wndBar.InsertItem(2, 1, "������Ա", 4, 0);
	wndBar.InsertItem(2, 2, "�ⶳ", 2, 0);
	wndBar.InsertItem(2, 3, "ע����Ա", 1, 0);

	wndBar.InsertItem(3, 0, "�����豸", 5, 0);
	wndBar.InsertItem(3, 1, "ע������", 4, 0);

	wndBar.SetSelFolder(0);

	CRect r;
	GetClientRect(&r);
	int w1 = r.Width() / 5;
	int w2 = r.Width() / 4;

	wndSplitter.SetColumnInfo(0, w1, 0);
	wndSplitter.SetColumnInfo(1, w2, 0);
	wndSplitter.RecalcLayout();
	return true;
}

long CMainFrame::OnOutbarNotify(WPARAM wParam, LPARAM lParam)
{
	switch (wParam)
	{
		case NM_OB_ITEMCLICK:
			// cast the lParam to an integer to get the clicked item
		{
			int index = (int)lParam;
			CString cText, cs1;
			cText = wndBar.GetItemText(index);
			CCreateContext   Context;
			//AfxMessageBox(cText);

			if (cText == _T("SecMngServer����"))
			{
				//AfxMessageBox(cText);

				Context.m_pNewViewClass = RUNTIME_CLASS(CCfgView);
				Context.m_pCurrentFrame = this;
				Context.m_pLastView = (CView *)wndSplitter.GetPane(0, 1);
				wndSplitter.DeleteView(0, 1);
				wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CCfgView), CSize(500, 0), &Context);
				CCfgView *pNewView = (CCfgView *)wndSplitter.GetPane(0, 1);
				wndSplitter.RecalcLayout();
				pNewView->OnInitialUpdate();
				wndSplitter.SetActivePane(0, 1);
				//IsHisKeyRecovry=0;		   
			}

			else if (cText == _T("������Ϣ����"))
			{
				Context.m_pNewViewClass = RUNTIME_CLASS(CDlgNetInfo);
				Context.m_pCurrentFrame = this;
				Context.m_pLastView = (CView *)wndSplitter.GetPane(0, 1);
				wndSplitter.DeleteView(0, 1);
				wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CDlgNetInfo), CSize(500, 0), &Context);
				CDlgNetInfo *pNewView = (CDlgNetInfo *)wndSplitter.GetPane(0, 1);
				wndSplitter.RecalcLayout();
				pNewView->OnInitialUpdate();
				wndSplitter.SetActivePane(0, 1);
			}

			else if (cText == _T("��̨ҵ�����"))
			{
			Context.m_pNewViewClass = RUNTIME_CLASS(CSysAll);
			Context.m_pCurrentFrame = this;
			Context.m_pLastView = (CView *)wndSplitter.GetPane(0, 1);
			wndSplitter.DeleteView(0, 1);
			wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CSysAll), CSize(500, 0), &Context);
			CSysAll *pNewView = (CSysAll *)wndSplitter.GetPane(0, 1);
			wndSplitter.RecalcLayout();
			pNewView->OnInitialUpdate();
			wndSplitter.SetActivePane(0, 1);
			}
			

		}

			return 0;

		case NM_OB_ONLABELENDEDIT:
			// cast the lParam to an OUTBAR_INFO * struct; it will contain info about the edited item
			// return 1 to do the change and 0 to cancel it
		{
			/*
			if(IsLoginOutFlag == 1)
			{
			AfxMessageBox("��Ա�ѵǳ��������µ�¼CA��Ա�Խ�����Ӧ������");
			return 1;
			}
			*/

			OUTBAR_INFO * pOI = (OUTBAR_INFO *)lParam;
			TRACE2("Editing item %d, new text:%s\n", pOI->index, pOI->cText);
		}
			return 1;

		case NM_OB_ONGROUPENDEDIT:
			// cast the lParam to an OUTBAR_INFO * struct; it will contain info about the edited folder
			// return 1 to do the change and 0 to cancel it
		{
			/*
			if(IsLoginOutFlag == 1)
			{
			AfxMessageBox("��Ա�ѵǳ��������µ�¼��Ա�Խ�����Ӧ������");
			return 1;
			}
			*/

			OUTBAR_INFO * pOI = (OUTBAR_INFO *)lParam;
			TRACE2("Editing folder %d, new text:%s\n", pOI->index, pOI->cText);
		}
			return 1;

		case NM_OB_DRAGITEM:
			// cast the lParam to an OUTBAR_INFO * struct; it will contain info about the dragged items
			// return 1 to do the change and 0 to cancel it
		{
			/*
			if(IsLoginOutFlag == 1)
			{
			AfxMessageBox("��Ա�ѵǳ��������µ�¼��Ա�Խ�����Ӧ������");
			return 1;
			}*/

			OUTBAR_INFO * pOI = (OUTBAR_INFO *)lParam;
			TRACE2("Drag item %d at position %d\n", pOI->iDragFrom, pOI->iDragTo);
		}
		return 1;
	}
	return 0;
}
