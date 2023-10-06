// RTCSetAndResetEEPROM.cpp : 実装ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "RTCSetAndResetEEPROM.h"
#include "Language.h"

// CRTCSetAndResetEEPROM ダイアログ

IMPLEMENT_DYNAMIC(CRTCSetAndResetEEPROM, CPropertyPage)

CRTCSetAndResetEEPROM::CRTCSetAndResetEEPROM()
	: CPropertyPage(CRTCSetAndResetEEPROM::IDD)
	, m_txtRTCSetAndResetEEPROMMsg1(_T(""))
	, m_nMonth(0)
	, m_nDay(0)
	, m_nYear(0)
	, m_nHour(0)
	, m_nMinute(0)
	, m_nSecond(0)
{

}

CRTCSetAndResetEEPROM::~CRTCSetAndResetEEPROM()
{
}

void CRTCSetAndResetEEPROM::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
//	DDX_Text(pDX, IDC_RTC_SET_AND_RESET_MSG1, m_txtRTCSetAndResetEEPROMMsg1);
	DDX_Control(pDX, IDC_USE_PC, m_chkUsePC);
	DDX_Text(pDX, IDC_MONTH, m_nMonth);
	DDX_Text(pDX, IDC_DAY, m_nDay);
	DDX_Text(pDX, IDC_YEAR, m_nYear);
	DDX_Text(pDX, IDC_HOUR, m_nHour);
	DDX_Text(pDX, IDC_MINUTE, m_nMinute);
	DDX_Text(pDX, IDC_SECOND, m_nSecond);
}


BEGIN_MESSAGE_MAP(CRTCSetAndResetEEPROM, CPropertyPage)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_USE_PC, &CRTCSetAndResetEEPROM::OnBnClickedUsePc)
END_MESSAGE_MAP()


// CRTCSetAndResetEEPROM メッセージ ハンドラ

BOOL CRTCSetAndResetEEPROM::OnSetActive()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	pApp->SetPrevIDD( IDD_RTC_SET_AND_RESET_EEPROM );

	LangSetWndTxt( GetDlgItem( IDC_RTC_AND_RESET1 ) , IDS_RTC_AND_RESET1 );
	LangSetWndTxt( GetDlgItem( IDC_USE_PC	   ) , IDS_USE_PC	   );
	LangSetWndTxt( GetDlgItem( IDC_MONTH1	   ) , IDS_MONTH	   );
	LangSetWndTxt( GetDlgItem( IDC_DAY1		   ) , IDS_DAY		   );
	LangSetWndTxt( GetDlgItem( IDC_YEAR1	   ) , IDS_YEAR		   );
	LangSetWndTxt( GetDlgItem( IDC_HOUR1	   ) , IDS_HOUR		   );
	LangSetWndTxt( GetDlgItem( IDC_MINUTE1	   ) , IDS_MINUTE	   );
	LangSetWndTxt( GetDlgItem( IDC_SECOND1	   ) , IDS_SECOND	   );

	m_chkUsePC.SetCheck( 1 );
	OnBnClickedUsePc();
	UpdateTimeDisp();
	SetTimer( 1, 1000, NULL );
	ViewDateType();

	UpdateData(FALSE);

	return CPropertyPage::OnSetActive();
}

LRESULT CRTCSetAndResetEEPROM::OnWizardBack()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CRTCSetAndResetEEPROM::OnWizardNext()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	BOOL bRet = TRUE;
	int nNextID = -1;
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
//		nNextID = IDD_IP_CLEAR;
		nNextID = IDD_INIT_INK_STATE;
	}


	return pApp->IDDPush( nNextID );
}

void CRTCSetAndResetEEPROM::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	if( nIDEvent == 1 ){
		UpdateTimeDisp();
	}
	CPropertyPage::OnTimer(nIDEvent);

}

void CRTCSetAndResetEEPROM::OnBnClickedUsePc()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
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

BOOL CRTCSetAndResetEEPROM::WriteDateToPrinter()
{
	bool bRet = false;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	CTime ct( m_nYear, m_nMonth, m_nDay, m_nHour, m_nMinute, m_nSecond );
	DWORD dwInternal = (DWORD)pApp->GetCurrentGMTSecond( ct.GetTime() );
	if( pApp->SetRTCAndResetEEPROM8014( dwInternal ) == 0 )
	{
		bRet = true;
	}
	else
	{
		LangAfxMsgBox( IDS_EER_COMMUNICATION , -191 );
	}

	return bRet;
}


void CRTCSetAndResetEEPROM::UpdateTimeDisp()
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

void CRTCSetAndResetEEPROM::ViewDateType()
{
	TIME_ZONE_INFORMATION tzinfo;
	DWORD tzstate = ::GetTimeZoneInformation(&tzinfo);
	if(TIME_ZONE_ID_DAYLIGHT == tzstate){
		m_csDateType = (LPCWSTR)tzinfo.DaylightName;
	}else{
		m_csDateType = (LPCWSTR)tzinfo.StandardName;
	}
}


