
// MyAdmin.h : MyAdmin Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMyAdminApp:
// �йش����ʵ�֣������ MyAdmin.cpp
//

class CMyAdminApp : public CWinApp
{
public:
	CMyAdminApp();

public:
	int CMyAdminApp::ReadSecMngCfg();
	int CMyAdminApp::OdbcConnect();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMyAdminApp theApp;
