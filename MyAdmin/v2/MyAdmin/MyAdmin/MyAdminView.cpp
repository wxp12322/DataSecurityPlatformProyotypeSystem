
// MyAdminView.cpp : CMyAdminView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MyAdmin.h"
#endif

#include "MyAdminDoc.h"
#include "MyAdminView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyAdminView

IMPLEMENT_DYNCREATE(CMyAdminView, CView)

BEGIN_MESSAGE_MAP(CMyAdminView, CView)
END_MESSAGE_MAP()

// CMyAdminView ����/����

CMyAdminView::CMyAdminView()
{
	// TODO:  �ڴ˴���ӹ������

}

CMyAdminView::~CMyAdminView()
{
}

BOOL CMyAdminView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMyAdminView ����

void CMyAdminView::OnDraw(CDC* /*pDC*/)
{
	CMyAdminDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CMyAdminView ���

#ifdef _DEBUG
void CMyAdminView::AssertValid() const
{
	CView::AssertValid();
}

void CMyAdminView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMyAdminDoc* CMyAdminView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMyAdminDoc)));
	return (CMyAdminDoc*)m_pDocument;
}
#endif //_DEBUG


// CMyAdminView ��Ϣ�������
