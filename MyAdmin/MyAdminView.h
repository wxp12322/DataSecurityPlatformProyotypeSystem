
// MyAdminView.h : CMyAdminView ��Ľӿ�
//

#pragma once


class CMyAdminView : public CView
{
protected: // �������л�����
	CMyAdminView();
	DECLARE_DYNCREATE(CMyAdminView)

// ����
public:
	CMyAdminDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// ʵ��
public:
	virtual ~CMyAdminView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MyAdminView.cpp �еĵ��԰汾
inline CMyAdminDoc* CMyAdminView::GetDocument() const
   { return reinterpret_cast<CMyAdminDoc*>(m_pDocument); }
#endif

