// SetDate.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "SetDate.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSetDate プロパティ ページ

IMPLEMENT_DYNCREATE(CSetDate, CPropertyPage)

CSetDate::CSetDate() : CPropertyPage(CSetDate::IDD)
{
	//{{AFX_DATA_INIT(CSetDate)
	m_nDay = 1;
	m_nHour = 0;
	m_nMinute = 0;
	m_nMonth = 1;
	m_nSecond = 0;
	m_nYear = 2000;
	m_csDateType = _T("");
	//}}AFX_DATA_INIT
}

CSetDate::~CSetDate()
{
}

void CSetDate::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetDate)
	DDX_Control(pDX, IDC_USE_PC, m_chkUsePC);
	DDX_Text(pDX, IDC_DAY, m_nDay);
	DDV_MinMaxUInt(pDX, m_nDay, 1, 31);
	DDX_Text(pDX, IDC_HOUR, m_nHour);
	DDV_MinMaxUInt(pDX, m_nHour, 0, 23);
	DDX_Text(pDX, IDC_MINUTE, m_nMinute);
	DDV_MinMaxUInt(pDX, m_nMinute, 0, 59);
	DDX_Text(pDX, IDC_MONTH, m_nMonth);
	DDV_MinMaxUInt(pDX, m_nMonth, 1, 12);
	DDX_Text(pDX, IDC_SECOND, m_nSecond);
	DDV_MinMaxUInt(pDX, m_nSecond, 0, 59);
	DDX_Text(pDX, IDC_YEAR, m_nYear);
	DDV_MinMaxUInt(pDX, m_nYear, 2000, 2100);
	DDX_Text(pDX, IDC_DATE_TYPE, m_csDateType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetDate, CPropertyPage)
	//{{AFX_MSG_MAP(CSetDate)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_USE_PC, OnUsePc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetDate メッセージ ハンドラ

BOOL CSetDate::OnSetActive() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	//pApp->Log( _T("Set Date and Time Step 1 Page") );
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

	LangSetWndTxt( GetDlgItem( IDC_SET_DATE1_1 ) , IDS_SET_DATE1_1 );
	LangSetWndTxt( GetDlgItem( IDC_SET_DATE1_2 ) , IDS_SET_DATE1_2 );
	LangSetWndTxt( GetDlgItem( IDC_MONTH1	   ) , IDS_MONTH	   );
	LangSetWndTxt( GetDlgItem( IDC_DAY1		   ) , IDS_DAY		   );
	LangSetWndTxt( GetDlgItem( IDC_YEAR1	   ) , IDS_YEAR		   );
	LangSetWndTxt( GetDlgItem( IDC_HOUR1	   ) , IDS_HOUR		   );
	LangSetWndTxt( GetDlgItem( IDC_MINUTE1	   ) , IDS_MINUTE	   );
	LangSetWndTxt( GetDlgItem( IDC_SECOND1	   ) , IDS_SECOND	   );
	LangSetWndTxt( GetDlgItem( IDC_USE_PC	   ) , IDS_USE_PC	   );

	m_chkUsePC.SetCheck( 1 );
	OnUsePc();
	UpdateTimeDisp();
	SetTimer( 1, 1000, NULL );
	ViewDateType();
	UpdateData( FALSE );
	return CPropertyPage::OnSetActive();
}

LRESULT CSetDate::OnWizardBack() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	KillTimer( 1 );
	return pApp->IDDPop();
	//return CPropertyPage::OnWizardBack();
}

LRESULT CSetDate::OnWizardNext() 
{
	BOOL bRet = TRUE;
	
	LRESULT nNextID = -1;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	UpdateData( TRUE );
	KillTimer( 1 );

	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	CWaitCursor wc;
		
	if( pApp->IsOnline() )
	{
		if( bRet )
		{
			bRet = WriteDateToPrinter();
		}
	}
		
	if( !bRet )
	{
		SetTimer( 1, 1000, NULL );
	}else
	{
		nNextID = IDD_SERV_SET_DATE2;
	}

	return pApp->IDDPush( nNextID );
}

BOOL CSetDate::OnQueryCancel() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	BOOL bRet = FALSE;
	if( LangCancelYesNoMsgBox() == IDYES )
	{
		bRet = TRUE;
		KillTimer( 1 );
	}
	return bRet;
}

void CSetDate::OnTimer(UINT_PTR nIDEvent) 
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	if( nIDEvent == 1 ){
		UpdateTimeDisp();
	}
	CPropertyPage::OnTimer(nIDEvent);
}

void CSetDate::UpdateTimeDisp()
{
	if( m_chkUsePC.GetCheck() == 1 ){
		CTime ct = CTime::GetCurrentTime();
		m_nYear = ct.GetYear();
		m_nMonth = ct.GetMonth();
		m_nDay = ct.GetDay();
		m_nHour = ct.GetHour();
		m_nMinute = ct.GetMinute();
		m_nSecond = ct.GetSecond();
		UpdateData( FALSE );
	}
}


//左右に送る
BOOL CSetDate::WriteDateToPrinter()
{
	bool bRet = false;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	CTime ct( m_nYear, m_nMonth, m_nDay, m_nHour, m_nMinute, m_nSecond );
	DWORD dwInternal = (DWORD)pApp->GetCurrentGMTSecond( ct.GetTime() );
	if( pApp->SetRTC( dwInternal ) == 0)
	{
		bRet = true;
	}
	else
	{
		LangAfxMsgBox( IDS_EER_COMMUNICATION , -191 );
	}
	return bRet;
}


void CSetDate::OnUsePc() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	BOOL bEnable = FALSE;
	if( m_chkUsePC.GetCheck() == 0 ){
		bEnable = TRUE;
	}
	GetDlgItem( IDC_YEAR )->EnableWindow( bEnable );
	GetDlgItem( IDC_MONTH )->EnableWindow( bEnable );
	GetDlgItem( IDC_DAY )->EnableWindow( bEnable );
	GetDlgItem( IDC_HOUR )->EnableWindow( bEnable );
	GetDlgItem( IDC_MINUTE )->EnableWindow( bEnable );
	GetDlgItem( IDC_SECOND )->EnableWindow( bEnable );
}

void CSetDate::ViewDateType()
{
	TIME_ZONE_INFORMATION tzinfo;
	DWORD tzstate = ::GetTimeZoneInformation(&tzinfo);
	if(TIME_ZONE_ID_DAYLIGHT == tzstate){
		m_csDateType = (LPCWSTR)tzinfo.DaylightName;
	}else{
		m_csDateType = (LPCWSTR)tzinfo.StandardName;
	}
}
