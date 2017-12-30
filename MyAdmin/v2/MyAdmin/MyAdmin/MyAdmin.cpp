
// MyAdmin.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "MyAdmin.h"
#include "MainFrm.h"

#include "MyAdminDoc.h"
#include "MyAdminView.h"
#include "cfg_op.h"
#include "secmng_globvar.h"
#include "DlgInitCfg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyAdminApp

BEGIN_MESSAGE_MAP(CMyAdminApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CMyAdminApp::OnAppAbout)
	// �����ļ��ı�׼�ĵ�����
	ON_COMMAND(ID_FILE_NEW, &CWinApp::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, &CWinApp::OnFileOpen)
END_MESSAGE_MAP()


// CMyAdminApp ����

CMyAdminApp::CMyAdminApp()
{

	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	// ���Ӧ�ó��������ù�����������ʱ֧��(/clr)�����ģ���: 
	//     1) �����д˸������ã�������������������֧�ֲ�������������
	//     2) ��������Ŀ�У������밴������˳���� System.Windows.Forms ������á�
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	// TODO:  ������Ӧ�ó��� ID �ַ����滻ΪΨһ�� ID �ַ�����������ַ�����ʽ
	//Ϊ CompanyName.ProductName.SubProduct.VersionInformation
	SetAppID(_T("MyAdmin.AppID.NoVersion"));

	// TODO:  �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}

// Ψһ��һ�� CMyAdminApp ����

CMyAdminApp theApp;


//CString g_SecMngIniName = "secmngadmin.ini";

//��Ҫ��̬�Ļ�ȡ�������ڵ�·�� 
int CMyAdminApp::ReadSecMngCfg()
{
	int				ret = 0;
		 
	char strFileName[2048] = { 0 };
	CString  g_strINIPath = "";

	GetModuleFileName(AfxGetInstanceHandle(), strFileName, sizeof(strFileName)); ////������г�������
	//AfxMessageBox(strFileName);
	//��ȡ��������Ŀ¼����������ļ�·��
	g_strINIPath.Format("%s", strFileName);
	int i = g_strINIPath.ReverseFind('\\');
	g_strINIPath = g_strINIPath.Left(i);
	g_strINIPath = g_strINIPath + "\\" + g_SecMngIniName;


	//��ȡ������
	char	tmpBuf[1024] = { 0 };
	int		tmpBufLen = 0;
	//���ļ� ������ DSN 
	
	ret = GetCfgItem((LPTSTR)(LPCTSTR)g_strINIPath /*in*/, "DSN"/*in*/, tmpBuf, &tmpBufLen);
	if (ret != 0)
	{
		AfxMessageBox("������ DSN ʧ��");
		return ret;
	}
	g_dbSource = tmpBuf;
	

	//���ļ� ������ UID 
	memset(tmpBuf, 0, sizeof(tmpBuf));
	ret = GetCfgItem((LPTSTR)(LPCTSTR)g_strINIPath /*in*/, "UID"/*in*/, tmpBuf, &tmpBufLen);
	if (ret != 0)
	{
		AfxMessageBox("������ UID ʧ��");
		return ret;
	}
	g_dbUse = tmpBuf;
	
	//���ļ� ������ PWD 
	memset(tmpBuf, 0, sizeof(tmpBuf));
	ret = GetCfgItem((LPTSTR)(LPCTSTR)g_strINIPath /*in*/, "PWD"/*in*/, tmpBuf, &tmpBufLen);
	if (ret != 0)
	{
		AfxMessageBox("������ PWD ʧ��");
		return ret;
	}
	g_dbpw = tmpBuf;

	return 0;
}
// CMyAdminApp ��ʼ��

int CMyAdminApp::OdbcConnect()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	CString		strCon;
	strCon.Format("DSN=%s;UID=%s;PWD=%s", g_dbSource, g_dbUse, g_dbpw);

	TRY
	{
		if (!myDB.OpenEx(strCon, CDatabase::noOdbcDialog))
		{
			AfxMessageBox("���� �������ݿ�������Ϣʧ�� ");
			return -1;
		}
	}
	CATCH_ALL(e)
	{
		e->ReportError();
	}
	END_CATCH_ALL

	g_pDB = &myDB;
	//AfxMessageBox("���� �������ݿ�������Ϣ ok");
	return 0;
}


BOOL CMyAdminApp::InitInstance()
{
	//AfxMessageBox("");
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()��  ���򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();
	EnableTaskbarInteraction(FALSE);
	
	int				ret = 0;
	//��Ϣϵͳ�ĳ�ʼ��
	ret = ReadSecMngCfg();
	if (ret != 0)
	{
		CDlgInitCfg   dlgInitCfg;

		if (dlgInitCfg.DoModal() == IDCANCEL)
		{
			return FALSE;
		}
		else
		{
			//g_dbSource = dlgInitCfg.m_dbsource; //��ȫ�ֱ�����ֵ
			//g_dbpw = dlgInitCfg.m_dbpw;
			//g_dbUse = dlgInitCfg.m_dbuser;
		}
	}

	//�����ݿ⽨��һ������
	ret = CMyAdminApp::OdbcConnect();
	if (ret != 0)
	{
		AfxMessageBox("�����ݿ⽨��һ������ ʧ��");
		return FALSE;
	}

	// ʹ�� RichEdit �ؼ���Ҫ  AfxInitRichEdit2()	
	// AfxInitRichEdit2();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO:  Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	LoadStdProfileSettings(4);  // ���ر�׼ INI �ļ�ѡ��(���� MRU)


	// ע��Ӧ�ó�����ĵ�ģ�塣  �ĵ�ģ��
	// �������ĵ�����ܴ��ں���ͼ֮�������
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CMyAdminDoc),
		RUNTIME_CLASS(CMainFrame),       // �� SDI ��ܴ���
		RUNTIME_CLASS(CMyAdminView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);


	// ������׼ shell ���DDE�����ļ�������������
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);



	// ��������������ָ�������  ���
	// �� /RegServer��/Register��/Unregserver �� /Unregister ����Ӧ�ó����򷵻� FALSE��
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// Ψһ��һ�������ѳ�ʼ���������ʾ����������и���
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();
	return TRUE;
}

// CMyAdminApp ��Ϣ�������


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

// �������жԻ����Ӧ�ó�������
void CMyAdminApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

// CMyAdminApp ��Ϣ�������



