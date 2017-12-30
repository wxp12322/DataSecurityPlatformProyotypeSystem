// SysAll.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyAdmin.h"
#include "SysAll.h"


// CSysAll

IMPLEMENT_DYNCREATE(CSysAll, CFormView)

CSysAll::CSysAll()
	: CFormView(CSysAll::IDD)
{

}

CSysAll::~CSysAll()
{
}

void CSysAll::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MYTAB, myTab);
}

BEGIN_MESSAGE_MAP(CSysAll, CFormView)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CSysAll ���

#ifdef _DEBUG
void CSysAll::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CSysAll::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSysAll ��Ϣ�������

// �����OnInitialUpdate ʲôʱ��MFC��ܵ�����?
void CSysAll::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	myTab.AddPage(_T("���������ڴ�"), &m_dlgTab1, IDD_DIALOG_TAB1);
	myTab.AddPage(_T("���������ڴ�"), &m_dlgTab2, IDD_DIALOG_TAB2);
	myTab.AddPage(_T("���������ڴ�"), &m_dlgTab3, IDD_DIALOG_TAB3);
	myTab.Show();


	// TODO:  �ڴ����ר�ô����/����û���
}

class MyBase
{
public:
	virtual int myPrintf()
	{
		printf("���ǵ�\n");
		return 0;

	}
};


class MyChild : public MyBase
{
public:
	virtual int myPrintf()
	{
		printf("���Ƕ���\n");
		return 0;
	}
};

void howToPrint(MyBase *base)
{
	base->myPrintf();
}


void myMain()
{
	MyChild c1;
	howToPrint(&c1);

	MyBase  b1;
	howToPrint(&b1);
}


void CSysAll::OnPaint()
{
	

	CPaintDC dc(this); // device context for painting

	CRect rect, rect1;
	this->GetClientRect(&rect);
	myTab.GetClientRect(&rect1);

	if ((rect1.Width() < rect.Width()))
		myTab.MoveWindow(rect, FALSE);

	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CFormView::OnPaint()


}
