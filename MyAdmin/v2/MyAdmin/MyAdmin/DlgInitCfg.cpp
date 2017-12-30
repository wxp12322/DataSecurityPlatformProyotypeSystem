// DlgInitCfg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyAdmin.h"
#include "DlgInitCfg.h"
#include "afxdialogex.h"
#include "cfg_op.h"


// CDlgInitCfg �Ի���

IMPLEMENT_DYNAMIC(CDlgInitCfg, CDialog)

CDlgInitCfg::CDlgInitCfg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgInitCfg::IDD, pParent)
	, m_dbdsn(_T(""))
	, m_dbpw(_T(""))
	, m_dbuid(_T(""))
{

}

CDlgInitCfg::~CDlgInitCfg()
{
}

void CDlgInitCfg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DBDSN, m_dbdsn);
	DDX_Text(pDX, IDC_EDIT_DBPW, m_dbpw);
	DDX_Text(pDX, IDC_EDIT_DBUID, m_dbuid);
}


BEGIN_MESSAGE_MAP(CDlgInitCfg, CDialog)
	ON_BN_CLICKED(IDOK, &CDlgInitCfg::OnBnClickedOk)
	ON_BN_CLICKED(IDOK_TEST, &CDlgInitCfg::OnBnClickedTest)
	ON_BN_CLICKED(IDCANCEL, &CDlgInitCfg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CDlgInitCfg ��Ϣ�������
extern CString g_SecMngIniName;
extern CString	g_dbSource, g_dbUse, g_dbpw;
//�������ļ� 
void CDlgInitCfg::OnBnClickedOk()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);


	m_dbdsn.TrimRight(); m_dbdsn.TrimLeft();
	m_dbpw.TrimRight(); m_dbpw.TrimLeft();
	m_dbuid.TrimRight(); m_dbuid.TrimLeft();

	if (m_dbdsn.IsEmpty() || m_dbpw.IsEmpty() || m_dbuid.IsEmpty())
	{
		AfxMessageBox("�û������ ��������");
	}

	//�������ļ�
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


	//д������ DSN
	ret = WriteCfgItem((LPTSTR)(LPCTSTR)g_strINIPath, "DSN" /*in*/, (LPTSTR)(LPCTSTR)m_dbdsn/*in*/, m_dbdsn.GetLength());
	if (ret != 0)
	{
		AfxMessageBox("д������ DSN ʧ��");
		return;
	}
	g_dbSource = m_dbdsn;

	//д������ UID
	ret = WriteCfgItem((LPTSTR)(LPCTSTR)g_strINIPath, "UID" /*in*/, (LPTSTR)(LPCTSTR)m_dbuid/*in*/, m_dbuid.GetLength());
	if (ret != 0)
	{
		AfxMessageBox("д������ UID ʧ��");
		return;
	}
	g_dbUse = m_dbuid;

	//д������ PWD
	ret = WriteCfgItem((LPTSTR)(LPCTSTR)g_strINIPath, "PWD" /*in*/, (LPTSTR)(LPCTSTR)m_dbpw/*in*/, m_dbpw.GetLength());
	if (ret != 0)
	{
		AfxMessageBox("д������ PWD ʧ��");
		return;
	}
	g_dbpw = m_dbpw;
	CDialog::OnOK();
}


void CDlgInitCfg::OnBnClickedTest()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDatabase db;

	UpdateData(TRUE);
	m_dbdsn.TrimLeft(); m_dbdsn.TrimRight();
	m_dbuid.TrimLeft(); m_dbuid.TrimRight();
	m_dbpw.TrimLeft(); m_dbpw.TrimRight();

	CString		strCon;
	strCon.Format("DSN=%s;UID=%s;PWD=%s", m_dbdsn, m_dbuid, m_dbpw);

	TRY 
	{
		if (!db.OpenEx(strCon, CDatabase::noOdbcDialog))
		{
			AfxMessageBox("���� �������ݿ�������Ϣʧ�� ");
			return;

		}
	}
	CATCH_ALL (e)
	{
		e->ReportError();
	}
	END_CATCH_ALL

	AfxMessageBox("���� �������ݿ�������Ϣ ok");
}


void CDlgInitCfg::OnBnClickedCancel()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialog::OnCancel();
}
