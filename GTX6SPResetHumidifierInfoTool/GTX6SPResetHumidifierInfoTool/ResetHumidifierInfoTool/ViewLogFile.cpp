// ViewLogFile.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "bgjservtool.h"
#include "ViewLogFile.h"
#include "EEPDispSel.h"
#include "LogView.h"
#include "LogFileInfo.h"
#include "LogAnal.h"
#include "StatDlg.h"
#include "HeadHistory.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CViewLogFile �v���p�e�B �y�[�W

IMPLEMENT_DYNCREATE(CViewLogFile, CPropertyPage)

CViewLogFile::CViewLogFile() : CPropertyPage(CViewLogFile::IDD)
{
	//{{AFX_DATA_INIT(CViewLogFile)
	m_csLogFile = _T("");
	//}}AFX_DATA_INIT
}

CViewLogFile::~CViewLogFile()
{
}

void CViewLogFile::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewLogFile)
	DDX_Text(pDX, IDC_LOG_FILE, m_csLogFile);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewLogFile, CPropertyPage)
	//{{AFX_MSG_MAP(CViewLogFile)
	ON_BN_CLICKED(IDC_BTN_SETTINGS, OnBtnSettings)
	ON_BN_CLICKED(IDC_BTN_LOG, OnBtnLog)
	ON_BN_CLICKED(IDC_BTN_INFO, OnBtnInfo)
	ON_BN_CLICKED(IDC_BTN_LOG_ANAL, OnBtnLogAnal)
	ON_BN_CLICKED(IDC_BTN_STAT, OnBtnStat)
	ON_BN_CLICKED(IDC_BTN_HEAD, OnBtnHead)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewLogFile ���b�Z�[�W �n���h��

BOOL CViewLogFile::OnSetActive() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_FINISH );
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

	LangSetWndTxt( GetDlgItem( IDC_VIEW_LOG1_1 )  , IDS_VIEW_LOG1_1	 );
	LangSetWndTxt( GetDlgItem( IDC_BTN_INFO )	  , IDS_BTN_INFO	 );
	LangSetWndTxt( GetDlgItem( IDC_BTN_LOG )	  , IDS_BTN_LOG		 );
	LangSetWndTxt( GetDlgItem( IDC_BTN_SETTINGS ) , IDS_BTN_SETTINGS );
	LangSetWndTxt( GetDlgItem( IDC_BTN_LOG_ANAL ) , IDS_BTN_LOG_ANAL );
	LangSetWndTxt( GetDlgItem( IDC_BTN_STAT )	  , IDS_BTN_STAT	 );
	LangSetWndTxt( GetDlgItem( IDC_BTN_HEAD )	  , IDS_BTN_HEAD	 );
	LangSetWndTxt( GetDlgItem( IDC_LOGFILE )	  , IDS_LOGFILE1	 );

	m_csLogFile = pApp->m_csLogFileName;
	CheckLogFile();
	UpdateData( FALSE );
	return CPropertyPage::OnSetActive();
}

LRESULT CViewLogFile::OnWizardBack() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

BOOL CViewLogFile::OnWizardFinish() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	
	return CPropertyPage::OnWizardFinish();
}

void CViewLogFile::OnBtnSettings() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	CEEPDispSel dlg;
	dlg.m_csLogFile = pApp->m_csLogFileName;
	dlg.DoModal();
}

void CViewLogFile::OnBtnLog() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	CLogView dlg;
	dlg.m_csLogFile = pApp->m_csLogFileName;
	dlg.DoModal();
}

bool CViewLogFile::CheckLogFile()
{
	bool bRet = true;
	CGTLogFile cfLog;
	CString csDate;
	int iRet = cfLog.Open( m_csLogFile, csDate );
	if( iRet == 1 )
	{
		GetDlgItem( IDC_BTN_SETTINGS )->ShowWindow( SW_SHOW );
		GetDlgItem( IDC_BTN_INFO )->ShowWindow( SW_SHOW );
		
	}else if( iRet == 0 )
	{
		GetDlgItem( IDC_BTN_SETTINGS )->ShowWindow( SW_HIDE );
		GetDlgItem( IDC_BTN_INFO )->ShowWindow( SW_HIDE );
	}
	cfLog.Close();
	return bRet;
}

void CViewLogFile::OnBtnInfo() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	CLogFileInfo dlg;
	dlg.m_csFileName = pApp->m_csLogFileName;
	dlg.DoModal();
	 
}

void CViewLogFile::OnBtnLogAnal() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	CLogAnal dlg;
	dlg.m_csLogFile = pApp->m_csLogFileName;
	dlg.DoModal();
}

void CViewLogFile::OnBtnStat() 
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	CStatDlg dlg;
	dlg.m_csLogFile = pApp->m_csLogFileName;
	CWaitCursor w;
	dlg.DoModal();
}

void CViewLogFile::OnBtnHead()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	CHeadHistory dlg;
	dlg.m_csLogFile = pApp->m_csLogFileName;
	dlg.DoModal();
}
