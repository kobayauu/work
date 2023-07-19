// ChkLog1.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "bgjservtool.h"
#include "ChkLog1.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChkLog1 プロパティ ページ

IMPLEMENT_DYNCREATE(CChkLog1, CPropertyPage)

CChkLog1::CChkLog1() : CPropertyPage(CChkLog1::IDD)
{
	//{{AFX_DATA_INIT(CChkLog1)
	m_csLogFileName = _T("");
	//}}AFX_DATA_INIT
	m_bFirst = true;
}

CChkLog1::~CChkLog1()
{
}

void CChkLog1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChkLog1)
	DDX_Text(pDX, IDC_LOGFILE_NAME, m_csLogFileName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CChkLog1, CPropertyPage)
	//{{AFX_MSG_MAP(CChkLog1)
	ON_BN_CLICKED(IDC_BROWSE, OnBrowse)
	ON_WM_DROPFILES()
	ON_WM_ACTIVATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChkLog1 メッセージ ハンドラ

BOOL CChkLog1::OnQueryCancel() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	
	return CPropertyPage::OnQueryCancel();
}

BOOL CChkLog1::OnSetActive() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	DragAcceptFiles( TRUE );
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	//pApp->Log( _T("Check Driver Log Step 1 Page") );
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

	LangSetWndTxt( GetDlgItem( IDC_LOG_CHECK1_1 ) , IDS_LOG_CHECK1_1 );
	LangSetWndTxt( GetDlgItem( IDC_BROWSE )		  , IDS_BROWSE		 );
	LangSetWndTxt( GetDlgItem( IDC_LOGFILE )	  , IDS_LOGFILE		 );

	if( m_bFirst )
	{
		CString cs = pApp->GetDataPath();
		::SetCurrentDirectory( (LPCTSTR)cs );
		m_bFirst = false;
	}
	m_csLogFileName = pApp->m_csLogFileName;
	UpdateData( FALSE );
	return CPropertyPage::OnSetActive();
}

LRESULT CChkLog1::OnWizardBack() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CChkLog1::OnWizardNext() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	LRESULT nNextID = -1;
	UpdateData( TRUE );
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	pApp->BeginWaitCursor();
	pApp->m_csLogFileName = m_csLogFileName;
	if( ! m_csLogFileName.IsEmpty() ){
		CGTLogFile LogF;
		FILE* pf = _tfopen( (LPCTSTR)m_csLogFileName, _T("rb") );
		if( pf ){
			nNextID = IDD_SERV_VIEW_LOG;
			fclose( pf );
		}else
		{
			LangAfxMsgBox( IDS_EER_FILE_OPEN , -10 );
		}
	}else
	{
		LangAfxMsgBox( IDS_ERR_INPUT_FILENAME , -11 );
	}
	pApp->EndWaitCursor();
	return pApp->IDDPush( nNextID );
}

void CChkLog1::OnBrowse() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	TCHAR szInitPath[MAX_PATH+5];
	::GetCurrentDirectory( MAX_PATH, szInitPath );
	CString FilterStr;
	FilterStr = _T("LOG Files (*.log,*.zlg)|*.log;*.zlg|All Files (*.*)|*.*||");

	CFileDialog dlg(  TRUE, _T("log"), m_csLogFileName, OFN_HIDEREADONLY,
		FilterStr, NULL );
	dlg.m_ofn.lpstrInitialDir = pApp->GetExeFolder();
	if( dlg.DoModal() == IDOK ){
		m_csLogFileName = dlg.GetPathName();
		UpdateData( FALSE );
	}
}

void CChkLog1::OnDropFiles(HDROP hDropInfo) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	TCHAR szFile[MAX_PATH];

	int nFiles = ::DragQueryFile( hDropInfo, -1, NULL, 0 );
	if( 1 == nFiles )
	{
		::DragQueryFile( hDropInfo, 0, szFile, sizeof(szFile) );
	
		m_csLogFileName = szFile;
		UpdateData( FALSE );
	}else if( 1 < nFiles )
	{
		LangAfxMsgBox( IDS_ERR_DROP , -12 );
	}	
	CPropertyPage::OnDropFiles(hDropInfo);
}
