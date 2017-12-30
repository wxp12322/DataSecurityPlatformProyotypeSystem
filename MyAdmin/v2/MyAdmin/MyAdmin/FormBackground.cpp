// FormBackground.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyAdmin.h"
#include "FormBackground.h"


// CFormBackground

IMPLEMENT_DYNCREATE(CFormBackground, CFormView)

CFormBackground::CFormBackground()
	: CFormView(CFormBackground::IDD)
{

}

CFormBackground::~CFormBackground()
{
}

void CFormBackground::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFormBackground, CFormView)
END_MESSAGE_MAP()


// CFormBackground ���

#ifdef _DEBUG
void CFormBackground::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CFormBackground::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CFormBackground ��Ϣ�������

void CFormBackground::OnDraw(CDC* pDC)
{
	// TODO:  �ڴ����ר�ô����/����û���

	// TODO: �ڴ����ר�ô����/����û���
	CRect clientRect;
	GetClientRect(&clientRect);

	for (int k = 13; k < 18; k++) //��ͼʾ������ʾλͼ
	{
		CBrush* pTempBrush = NULL;
		CBrush OrigBrush;
		OrigBrush.FromHandle((HBRUSH)pTempBrush);

		CRect rc;
		GetClientRect(&rc);
		//ScreenToClient(&rc);
		try
		{
			CBitmap bmp;
			bmp.LoadBitmap(IDB_BITMAP_BACK);
			CBrush brush(&bmp);

			pTempBrush = (CBrush*)pDC->SelectObject(brush);

			pDC->Rectangle(rc.left, rc.top, rc.Width(), rc.Height());
			pDC->SelectObject(&OrigBrush);
			break;
		}
		catch (CResourceException* e)
		{
			e->ReportError();
			e->Delete();
		}
	}

	CRect rect;
	GetClientRect(&rect);
	CRect rect2;
	GetClientRect(&rect2);

	CFont font;
	font.CreatePointFont(340, _T("Arial"));
	CString string = "��ӭʹ��KeyMngServer�����ն�";

	pDC->SelectObject(&font);
	pDC->SetBkMode(TRANSPARENT);
	rect.OffsetRect(6, -90); //��Ӱ
	pDC->SetTextColor(RGB(192, 192, 192));
	pDC->DrawText(string, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

	rect2.OffsetRect(0, -100);
	pDC->SetTextColor(RGB(0, 0, 0));
	pDC->DrawText(string, &rect2, DT_SINGLELINE | DT_CENTER | DT_VCENTER);

}
