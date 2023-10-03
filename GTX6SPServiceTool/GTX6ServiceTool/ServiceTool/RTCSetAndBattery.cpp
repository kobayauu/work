// RTCSetAndBattery.cpp : 実装ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "RTCSetAndBattery.h"
#include "Language.h"

// CRTCSetAndBattery ダイアログ

IMPLEMENT_DYNAMIC(CRTCSetAndBattery, CPropertyPage)

CRTCSetAndBattery::CRTCSetAndBattery()
	: CPropertyPage(CRTCSetAndBattery::IDD)
	, m_Month(0)
	, m_Day(0)
	, m_Year(0)
	, m_Hour(0)
	, m_Minute(0)
	, m_Second(0)
{

}

CRTCSetAndBattery::~CRTCSetAndBattery()
{
}

void CRTCSetAndBattery::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_USE_PC, m_chkUsePC);
	DDX_Text(pDX, IDC_MONTH, m_Month);
	DDX_Text(pDX, IDC_DAY, m_Day);
	DDX_Text(pDX, IDC_YEAR, m_Year);
	DDX_Text(pDX, IDC_HOUR, m_Hour);
	DDX_Text(pDX, IDC_MINUTE, m_Minute);
	DDX_Text(pDX, IDC_SECOND, m_Second);
}


BEGIN_MESSAGE_MAP(CRTCSetAndBattery, CPropertyPage)
	ON_BN_CLICKED(IDC_USE_PC, &CRTCSetAndBattery::OnBnClickedUsePc)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CRTCSetAndBattery メッセージ ハンドラ

BOOL CRTCSetAndBattery::OnSetActive()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	pApp->SetPrevIDD( IDD_RTC_SET_AND_RESET_EEPROM );

	LangSetWndTxt( GetDlgItem( IDC_RTC_AND_RESET_BATTERY1 ) , IDS_RTC_AND_BATTERY1 );
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

LRESULT CRTCSetAndBattery::OnWizardBack()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CRTCSetAndBattery::OnWizardNext()
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
		nNextID = IDD_SERV_SEL_OPE;
	}


	return pApp->IDDPush( nNextID );
}

void CRTCSetAndBattery::OnBnClickedUsePc()
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
void CRTCSetAndBattery::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	if( nIDEvent == 1 ){
		UpdateTimeDisp();
	}
	CPropertyPage::OnTimer(nIDEvent);
}

BOOL CRTCSetAndBattery::WriteDateToPrinter()
{
	bool bRet = false;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	CTime ct( m_Year, m_Month, m_Day, m_Hour, m_Minute, m_Second );
	DWORD dwInternal = (DWORD)pApp->GetCurrentGMTSecond( ct.GetTime() );
	if( pApp->SetRTCAndBattery( dwInternal ) == 0)
	{
		bRet = true;
	}
	else
	{
		LangAfxMsgBox( IDS_EER_COMMUNICATION , -191 );
	}

	return bRet;
}


void CRTCSetAndBattery::UpdateTimeDisp()
{
	if( m_chkUsePC.GetCheck() == 1 ){
		CTime ct = CTime::GetCurrentTime();
		m_Year = ct.GetYear();
		m_Month = ct.GetMonth();
		m_Day = ct.GetDay();
		m_Hour = ct.GetHour();
		m_Minute = ct.GetMinute();
		m_Second = ct.GetSecond();
		UpdateData( FALSE );
	}
}

void CRTCSetAndBattery::ViewDateType()
{
	TIME_ZONE_INFORMATION tzinfo;
	DWORD tzstate = ::GetTimeZoneInformation(&tzinfo);
	if(TIME_ZONE_ID_DAYLIGHT == tzstate){
		m_csDateType = (LPCWSTR)tzinfo.DaylightName;
	}else{
		m_csDateType = (LPCWSTR)tzinfo.StandardName;
	}
}