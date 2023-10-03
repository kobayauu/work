// EEPROMRestore.cpp : 実装ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "EEPROMRestore.h"
#include "Language.h"

// CEEPROMRestore ダイアログ

IMPLEMENT_DYNAMIC(CEEPROMRestore, CPropertyPage)

CEEPROMRestore::CEEPROMRestore()
	: CPropertyPage(CEEPROMRestore::IDD)
	, m_bDone(FALSE)
	, m_nMonth(0)
	, m_nDay(0)
	, m_nYear(0)
	, m_nHour(0)
	, m_nMinute(0)
	, m_nSecond(0)
{

}

CEEPROMRestore::~CEEPROMRestore()
{
}

void CEEPROMRestore::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//	DDX_Check(pDX, IDC_CHECK_RESTORE_EEPROM_COMFIRMATION, m_bDone);
	DDX_Text(pDX, IDC_MONTH, m_nMonth);
	DDX_Text(pDX, IDC_DAY, m_nDay);
	DDX_Text(pDX, IDC_YEAR, m_nYear);
	DDX_Text(pDX, IDC_HOUR, m_nHour);
	DDX_Text(pDX, IDC_MINUTE, m_nMinute);
	DDX_Text(pDX, IDC_SECOND, m_nSecond);
	DDX_Control(pDX, IDC_USE_PC, m_chkUsePC);
}


BEGIN_MESSAGE_MAP(CEEPROMRestore, CPropertyPage)
//	ON_BN_CLICKED(IDC_CHECK_RESTORE_EEPROM_COMFIRMATION, &CEEPROMRestore::OnBnClickedCheckRestoreEepromComfirmation)
ON_BN_CLICKED(IDC_USE_PC, &CEEPROMRestore::OnBnClickedUsePc)
ON_WM_TIMER()
END_MESSAGE_MAP()


// CEEPROMRestore メッセージ ハンドラ

BOOL CEEPROMRestore::OnSetActive()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	m_nPrevIDD = pApp->SetPrevIDD( IDD_EEPROM_RESTORE1 );

	LangSetWndTxt( GetDlgItem( IDC_EEPROM_RESTORE_MSG1	   ) , IDS_EEPROM_RESTORE1_1	   );
	LangSetWndTxt( GetDlgItem( IDC_USE_PC	   ) , IDS_USE_PC	   );

	m_chkUsePC.SetCheck( 1 );
	OnBnClickedUsePc();
	UpdateTimeDisp();
	SetTimer( 1, 1000, NULL );
	ViewDateType();

	m_bDone = FALSE;
	UpdateData( FALSE );

	return CPropertyPage::OnSetActive();
}

LRESULT CEEPROMRestore::OnWizardBack()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CEEPROMRestore::OnWizardNext()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	int nNextID = IDD_BACKUP;
	BOOL bRet = TRUE;
	
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
		nNextID = IDD_BACKUP;
	}


	
	return pApp->IDDPush( nNextID );
}

void CEEPROMRestore::OnBnClickedCheckRestoreEepromComfirmation()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	UpdateData( TRUE );

	CPropertySheet* pSheet = (CPropertySheet*)GetParent();

	if( m_bDone )
	{
		pSheet->SetWizardButtons( PSWIZB_NEXT | PSWIZB_BACK );
	}else
	{
		pSheet->SetWizardButtons( PSWIZB_BACK );
	}
}

void CEEPROMRestore::OnBnClickedUsePc()
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

void CEEPROMRestore::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	if( nIDEvent == 1 ){
		UpdateTimeDisp();
	}
	CPropertyPage::OnTimer(nIDEvent);
}

BOOL CEEPROMRestore::WriteDateToPrinter()
{
	bool bRet = false;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	CTime ct( m_nYear, m_nMonth, m_nDay, m_nHour, m_nMinute, m_nSecond );
	DWORD dwInternal = (DWORD)pApp->GetCurrentGMTSecond( ct.GetTime() );
	if( pApp->RestoreEEPROMAndSetRTCAndBackup( dwInternal ) == 0)
	{
		bRet = true;
	}
	else
	{
		LangAfxMsgBox( IDS_EER_COMMUNICATION , -191 );
	}
	return bRet;
}

void CEEPROMRestore::ViewDateType()
{
	TIME_ZONE_INFORMATION tzinfo;
	DWORD tzstate = ::GetTimeZoneInformation(&tzinfo);
	if(TIME_ZONE_ID_DAYLIGHT == tzstate){
		m_csDateType = (LPCWSTR)tzinfo.DaylightName;
	}else{
		m_csDateType = (LPCWSTR)tzinfo.StandardName;
	}
}

void CEEPROMRestore::UpdateTimeDisp()
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