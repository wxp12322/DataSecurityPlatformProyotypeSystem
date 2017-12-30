// CfgView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyAdmin.h"
#include "CfgView.h"
#include "SECMNGSRVCFG.h"


// CCfgView

IMPLEMENT_DYNCREATE(CCfgView, CFormView)

CCfgView::CCfgView()
	: CFormView(CCfgView::IDD)
	, m_strsrvip(_T(""))
	, m_strsrvnodenum(_T(""))
	, m_strsrvport(_T(""))
{

}

CCfgView::~CCfgView()
{
}

void CCfgView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SRVIP, m_strsrvip);
	DDX_Text(pDX, IDC_EDIT_SRVNODENUM, m_strsrvnodenum);
	DDX_Text(pDX, IDC_EDIT_SRVPORT, m_strsrvport);
}

BEGIN_MESSAGE_MAP(CCfgView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON_SAVESERVER, &CCfgView::OnBnClickedButtonSaveserver)
END_MESSAGE_MAP()


// CCfgView ���

#ifdef _DEBUG
void CCfgView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CCfgView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCfgView ��Ϣ�������

extern CDatabase	*g_pDB;

//��ѯһ��
void CCfgView::OnInitialUpdate2()
{
	CFormView::OnInitialUpdate();
	// 
	//������һ����¼��� ����
	CSECMNGSRVCFG	srvCfgRecordSet(g_pDB);
	TRY 
	{
		srvCfgRecordSet.m_strFilter.Format("key='%s'", "secmng_server_ip");

		//�൱�� �������������һ��sql��� ���ҽ���Ѿ�����
		if (!srvCfgRecordSet.Open(CRecordset::snapshot, NULL, CRecordset::none))
		{
			AfxMessageBox("�򿪱�SECMNG.SRVCFG��ʧ��");
			return;
		}

		if (!srvCfgRecordSet.IsEOF())
		{
			srvCfgRecordSet.m_KEY.TrimLeft(); srvCfgRecordSet.m_KEY.TrimRight();
			srvCfgRecordSet.m_VALUDE.TrimLeft(); srvCfgRecordSet.m_VALUDE.TrimRight();
			m_strsrvip = srvCfgRecordSet.m_VALUDE;
		}
		else
		{
			m_strsrvip = srvCfgRecordSet.m_VALUDE;
		}
	}
	CATCH_ALL (e)
	{
		e->ReportError();
		if (srvCfgRecordSet.IsOpen())
		{
			srvCfgRecordSet.Close();
		}
	}
	END_CATCH_ALL

	UpdateData(FALSE); //��C++�ı������ݸ�����

}


//������ѯ  
void CCfgView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// 
	//������һ����¼��� ����
	CSECMNGSRVCFG	srvCfgRecordSet(g_pDB);
	TRY
	{
		srvCfgRecordSet.m_strFilter.Format("key='%s'", "secmng_server_ip");

		//�൱�� �������������һ��sql��� ���ҽ���Ѿ�����
		if (!srvCfgRecordSet.Open(CRecordset::snapshot, NULL, CRecordset::none))
		{
			AfxMessageBox("�򿪱�SECMNG.SRVCFG��ʧ��");
			return;
		}

		if (!srvCfgRecordSet.IsEOF())
		{
			srvCfgRecordSet.m_KEY.TrimLeft(); srvCfgRecordSet.m_KEY.TrimRight();
			srvCfgRecordSet.m_VALUDE.TrimLeft(); srvCfgRecordSet.m_VALUDE.TrimRight();
			m_strsrvip = srvCfgRecordSet.m_VALUDE;
		}
		else
		{
			m_strsrvip = "";
		}


		//������ѯ
		srvCfgRecordSet.m_strFilter.Format("key='%s'", "secmng_server_port");
		srvCfgRecordSet.Requery();
		if (!srvCfgRecordSet.IsEOF())
		{
			srvCfgRecordSet.m_KEY.TrimLeft(); srvCfgRecordSet.m_KEY.TrimRight();
			srvCfgRecordSet.m_VALUDE.TrimLeft(); srvCfgRecordSet.m_VALUDE.TrimRight();
			m_strsrvport = srvCfgRecordSet.m_VALUDE;
		}
		else
		{
			m_strsrvport = "";
		}

		//������ѯ ��ѯ secmng_server_maxnetnum
		srvCfgRecordSet.m_strFilter.Format("key='%s'", "secmng_server_maxnetnum");
		srvCfgRecordSet.Requery();
		if (!srvCfgRecordSet.IsEOF())
		{
			srvCfgRecordSet.m_KEY.TrimLeft(); srvCfgRecordSet.m_KEY.TrimRight();
			srvCfgRecordSet.m_VALUDE.TrimLeft(); srvCfgRecordSet.m_VALUDE.TrimRight();
			m_strsrvnodenum = srvCfgRecordSet.m_VALUDE;
		}
		else
		{
			m_strsrvnodenum = "";
		}


	}
	CATCH_ALL(e)
	{
		e->ReportError();
		if (srvCfgRecordSet.IsOpen())
		{
			srvCfgRecordSet.Close();
		}
	}
	END_CATCH_ALL

	UpdateData(FALSE); //��C++�ı������ݸ�����

}


// ��ѯ��û������
//1 ��û�м�¼	������¼
//2 ���м�¼ʱ	 �޸ļ�¼
void CCfgView::OnBnClickedButtonSaveserver()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	int			idbTag = 0; //�ɹ�
	//�ѽ������� ���� �� C++������
	UpdateData(TRUE);
	m_strsrvip.TrimLeft(); m_strsrvip.TrimRight();
	m_strsrvport.TrimLeft(); m_strsrvport.TrimRight();
	m_strsrvnodenum.TrimLeft(); m_strsrvnodenum.TrimRight();

	if (m_strsrvip.IsEmpty() || m_strsrvport.IsEmpty() || m_strsrvnodenum.IsEmpty())
	{
		AfxMessageBox("�û�����Ϊ��");
	}

	g_pDB->BeginTrans();
	CSECMNGSRVCFG	srvCfgRecordSet(g_pDB);
	TRY
	{
		srvCfgRecordSet.m_strFilter.Format("key='%s'", "secmng_server_ip");

		//�൱�� �������������һ��sql��� ���ҽ���Ѿ�����
		if (!srvCfgRecordSet.Open(CRecordset::snapshot, NULL, CRecordset::none))
		{
			idbTag = 1;
			g_pDB->Rollback();
			AfxMessageBox("�򿪱�SECMNG.SRVCFG��ʧ��");
			return;
		}

		if (!srvCfgRecordSet.IsEOF()) //�м�¼ ���޸�
		{
			srvCfgRecordSet.Edit();
			srvCfgRecordSet.m_VALUDE = m_strsrvip;
			srvCfgRecordSet.m_KEY.Format("%s", "secmng_server_ip");
			srvCfgRecordSet.Update();	
		}
		else
		{
			srvCfgRecordSet.AddNew();
			srvCfgRecordSet.m_VALUDE = m_strsrvip;
			srvCfgRecordSet.m_KEY.Format("%s", "secmng_server_ip");
			srvCfgRecordSet.Update();
		}

		//����port
		srvCfgRecordSet.m_strFilter.Format("key='%s'", "secmng_server_port");
		srvCfgRecordSet.Requery();
		if (!srvCfgRecordSet.IsEOF()) //�м�¼ ���޸�
		{
			srvCfgRecordSet.Edit();
			srvCfgRecordSet.m_VALUDE = m_strsrvport;
			srvCfgRecordSet.m_KEY.Format("%s", "secmng_server_port");
			srvCfgRecordSet.Update();
		}
		else
		{
			srvCfgRecordSet.AddNew();
			srvCfgRecordSet.m_VALUDE = m_strsrvport;
			srvCfgRecordSet.m_KEY.Format("%s", "secmng_server_port");
			srvCfgRecordSet.Update();
		}

		//�������� secmng_server_maxnetnum
		srvCfgRecordSet.m_strFilter.Format("key='%s'", "secmng_server_maxnetnum");
		srvCfgRecordSet.Requery();
		if (!srvCfgRecordSet.IsEOF()) //�м�¼ ���޸�
		{
			srvCfgRecordSet.Edit();
			srvCfgRecordSet.m_VALUDE = m_strsrvnodenum;
			srvCfgRecordSet.m_KEY.Format("%s", "secmng_server_maxnetnum");
			srvCfgRecordSet.Update();
		}
		else
		{
			srvCfgRecordSet.AddNew();
			srvCfgRecordSet.m_VALUDE = m_strsrvnodenum;
			srvCfgRecordSet.m_KEY.Format("%s", "secmng_server_maxnetnum");
			srvCfgRecordSet.Update();
		}
	}
	CATCH_ALL(e)
	{
		idbTag = 1;
		e->ReportError();
	}
	END_CATCH_ALL

	if (idbTag == 0)
	{
		g_pDB->CommitTrans();
	}
	else
	{
		g_pDB->Rollback();
	}
	if (srvCfgRecordSet.IsOpen())
	{
		srvCfgRecordSet.Close();
	}

}