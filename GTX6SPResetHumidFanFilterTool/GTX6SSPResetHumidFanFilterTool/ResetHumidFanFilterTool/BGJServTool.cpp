// BGJServTool.cpp : アプリケーション用クラスの定義を行います。
//
#include "stdafx.h"
#include "BGJServTool.h"
#include "ServSheet.h"
#include "Language.h"

#include "gtlib/gtlib.h"
#include "gtlib/gtx.h"
#include "GtBidi/GtBidi.h"
#include "GtBidi/GtBidiPrivate.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CBGJServToolApp

BEGIN_MESSAGE_MAP(CBGJServToolApp, CWinApp)
	//{{AFX_MSG_MAP(CBGJServToolApp)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
//	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBGJServToolApp クラスの構築

CBGJServToolApp::CBGJServToolApp()
{
	m_bServiceTool = true;
}

/////////////////////////////////////////////////////////////////////////////
// 唯一の CBGJServToolApp オブジェクト

CBGJServToolApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CBGJServToolApp クラスの初期化

BOOL CBGJServToolApp::InitInstance()
{
	AfxEnableControlContainer();

	// 標準的な初期化処理
	// もしこれらの機能を使用せず、実行ファイルのサイズを小さくしたけ
	//  れば以下の特定の初期化ルーチンの中から不必要なものを削除して
	//  ください。

#ifdef _AFXDLL
	Enable3dControls();			// 共有 DLL 内で MFC を使う場合はここをコールしてください。
#else
	Enable3dControlsStatic();	// MFC と静的にリンクする場合はここをコールしてください。
#endif
	::_tzset();
	SetRegistryKey( _T("Brother Industries,Ltd.\\GTResetHumidFanFilterTools") );
	//WriteProfileString(_T("Test"), _T("Test"), _T("test"));
//	m_Prn.m_nEmptyReadCount = GetProfileInt( cszServSection, cszEmptyReadCount, 200 );
	long n = GetProfileInt( cszServSection, cszOneReadByte, (512+4) );
//	m_Prn.SetOneReadByteCount( n );
//	m_Prn.m_nReadWaitMillisec = GetProfileInt( cszServSection, cszReadWaitMillisec, 100 );
//	m_Prn.m_nWaitAfterSendMillisec = GetProfileInt( cszServSection, cszWaitAfterSendMillisec, 500 );

	m_bOffTest = false;
	m_bTemplateIsInResource = true;
	m_Course = COURSE_NONE;
	m_Side   = SIDE_NONE;

	TCHAR szFullPath[MAX_PATH];
	HINSTANCE hInst = AfxGetInstanceHandle( );
	GetModuleFileName(hInst, szFullPath, sizeof(szFullPath));
	m_csExePath = szFullPath;
	CString m_csExeBodyName = m_csExePath;
	int iBodyTop = m_csExePath.ReverseFind( _T('\\') );
	if( iBodyTop > 0 ){
		m_csExeBodyName = m_csExePath.Right( m_csExePath.GetLength() - iBodyTop );
	}

	m_csExeBodyName.MakeLower();
	if( m_csExeBodyName.Find( _T("demo") ) >= 0 )
	{
		m_bOffTest = true;
	}

//	m_bOffTest = true;//////////////

	m_lcid = SetLanguage( m_csExeBodyName );

	CString csCmdLine = m_lpCmdLine;
	csCmdLine.MakeLower();
/*	if( csCmdLine.Find( _T("-unit") ) >= 0 ){
		m_Prn.m_bUnitTest = true;
	}	*/

	if( csCmdLine.Find( _T("-demo") ) >= 0 ){
		m_bOffTest = true;
	}

	/* ミューテックスを作成する */
	HANDLE hMutex;
	hMutex = CreateMutex(NULL, TRUE, _T("GTX6SPRESETHUMIDFANFILTERTOOL"));

	if (!hMutex)
		return FALSE;

	/* もしGetLastError()が、ERROR_ALREADY_EXISTSなら、
	*  すでにアプリケーションが起動している */
	if (GetLastError() == ERROR_ALREADY_EXISTS) 
	{
		/* ------------------------------------------
		* 二重起動時の処理が必要なら、ここに記述する
		* (アプリケーションのアクティブ化等)
		* ------------------------------------------ */
		LangAfxMsgBox( IDS_DR );	
		/* アプリケーションの起動中止 */
		return FALSE;
	}

	m_IDDArray.SetSize( 64 );

	m_bServiceTool = true;
	
	SerialAndLotFileName();
	CTime ct = CTime::GetCurrentTime();
	m_csStartDate = ct.Format( _T("%Y%m%d%H%M") );

	int nCaptionID = IDS_SERV_SHEET_CAPTION;
	int nFirstPage = 0;

	if( m_bServiceTool )
	{
		CServSheet dlg( IDS_SERV_SHEET_CAPTION );
		dlg.SetWizardMode();
		m_pMainWnd = &dlg;
		int nResponse = dlg.DoModal();
		if (nResponse == IDOK)
		{
			// TODO: ダイアログが <OK> で消された時のコードを
			//       記述してください。
		}
		else if (nResponse == IDCANCEL)
		{
			// TODO: ダイアログが <ｷｬﾝｾﾙ> で消された時のコードを
			//       記述してください。
		}
	}
	
	// ダイアログが閉じられてからアプリケーションのメッセージ ポンプを開始するよりは、
	// アプリケーションを終了するために FALSE を返してください。
	return FALSE;
}

#define MAINTE_TOOL_PATH "\\Brother\\GTX-6 SP Tools\\GTX6SPMaintenance.exe"

void CBGJServToolApp::RunMaintenanceTool()
{
	CString strMainteToolPath;

	int iRet = GetProgramFilesPath( &strMainteToolPath );

	if( iRet >= 0 )
	{
		strMainteToolPath += MAINTE_TOOL_PATH;

		ShellExecute( NULL, _T("open") ,strMainteToolPath, _T("") ,NULL, SW_HIDE );
	}

}

//\Program Filesのパスの取得 （セオリー通り）
int CBGJServToolApp::GetProgramFilesPath( CString* pstrPath )
{
	int iRet  = -1;
	*pstrPath = "";

	TCHAR szPath[MAX_PATH+1];
    LPITEMIDLIST pidl;

    IMalloc *pMalloc;
    SHGetMalloc( &pMalloc );

#ifndef _WIN64
	int csidl = CSIDL_PROGRAM_FILES;
#else
	int csidl = CSIDL_PROGRAM_FILESX86;
#endif
    if( SUCCEEDED( SHGetSpecialFolderLocation( NULL , csidl , &pidl ) ) )
    { 
        SHGetPathFromIDList(pidl,szPath);   // パスに変換する
        pMalloc->Free(pidl);				// 取得したIDLを解放する
		*pstrPath = szPath;					//
		iRet = 0;							// 成功
    }

    pMalloc->Release();

	return iRet;
}

LCID CBGJServToolApp::GetLCID()
{
	return m_lcid;
}

void CBGJServToolApp::LocalMessageLoopExec()
{
	BOOL bDoingBackgroundProcessing = TRUE;
	while ( bDoingBackgroundProcessing ) 
	{ 
		MSG msg;
		while ( ::PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) ) 
		{ 
			if ( !PumpMessage( ) ) 
			{ 
				bDoingBackgroundProcessing = FALSE; 
				::PostQuitMessage( 0 ); 
				break; 
			} 
		} 
		// let MFC do its idle processing
		LONG lIdle = 0;
		while ( OnIdle(lIdle++ ) )
			;  
		// Perform some background processing here 
		// using another call to OnIdle
		bDoingBackgroundProcessing = FALSE; 
	}
}

LPCTSTR CBGJServToolApp::GetDataPath()
{
	if( m_csDataPath.IsEmpty() ){
		m_csDataPath = m_csExePath;
		int nPos = m_csDataPath.ReverseFind( _T('\\') );
		if( nPos > 0 ){
			int nLen = m_csDataPath.GetLength();
			m_csDataPath.Delete( nPos + 2, nLen - nPos - 1 );
			m_csDataPath += _T("Data\\");
		}else
		{
			LangAfxMsgBox( IDS_ERR_BUG , -270 );
			//"Error: BGJServTool: GetDataPath failed"
		}
	}
	return (LPCTSTR)m_csDataPath;
}

LPCTSTR CBGJServToolApp::GetLogPath()
{
	if( m_csLogPath.IsEmpty() ){
		m_csLogPath = m_csExePath;
		int nPos = m_csLogPath.ReverseFind( _T('\\') );
		if( nPos > 0 ){
			int nLen = m_csLogPath.GetLength();
			m_csLogPath.Delete( nPos + 2, nLen - nPos - 1 );
			m_csLogPath += _T("Log\\");
		}else
		{
			LangAfxMsgBox( IDS_ERR_BUG , -271 );
			//"Error: BGJServTool: GetLogPath failed"
		}
	}
	return (LPCTSTR)m_csLogPath;
}

LPCTSTR CBGJServToolApp::GetTemplatePath()
{
	if( m_csTemplatePath.IsEmpty() ){
		m_csTemplatePath = m_csExePath;
		int nPos = m_csTemplatePath.ReverseFind( _T('\\') );
		if( nPos > 0 ){
			int nLen = m_csTemplatePath.GetLength();
			m_csTemplatePath.Delete( nPos + 2, nLen - nPos - 1);
			m_csTemplatePath += _T("Template\\");
		}else{
			LangAfxMsgBox( IDS_ERR_BUG , -273 );
			//"BGJServTool: GetTemplatePath failed"
		}
	}
	return (LPCTSTR)m_csTemplatePath;
}


bool CBGJServToolApp::CheckFolder(LPCTSTR pszPath)
{
	bool bRet = true;
	DWORD dwRet = ::GetFileAttributes( pszPath );
	if( dwRet == (DWORD)(-1) ){
		if( ::CreateDirectory( pszPath, NULL ) == 0){
//			CQErr::MsgBoxLastError();
			bRet = false;
		}
	}
	return bRet;
}

void CBGJServToolApp::SetPrinterName(LPCTSTR pszPrinterName)
{
	m_csPrinterName = pszPrinterName;
}

LPCTSTR CBGJServToolApp::GetPrinterName()
{
	return (LPCTSTR)m_csPrinterName;
}

bool CBGJServToolApp::IsEng()
{
	return !m_bIsJapanese;
}

int CBGJServToolApp::SetPrevIDD(int nPrevIDD)
{
	int nRet = m_nPrevIDD;
	m_nPrevIDD = nPrevIDD;
	return nRet;
}

int CBGJServToolApp::GetPrevIDD()
{
	return m_nPrevIDD;
}

LPCTSTR CBGJServToolApp::GetToolStartDateStr()
{
	return (LPCTSTR)m_csStartDate;
}

int CBGJServToolApp::IDDPush(int nIDD)
{
	if( nIDD != -1 )
	{
		m_IDDArray.Add( nIDD );
	}
	return nIDD;
}

int CBGJServToolApp::IDDPop()
{
	int nIDD = -1;
	int nSize = m_IDDArray.GetSize();
	if( nSize > 1 ){
		nIDD = m_IDDArray[ nSize - 2 ];
		m_IDDArray.RemoveAt( nSize - 1 );
	}
	return nIDD;
}

int CBGJServToolApp::IDDPeek(){
	int nSize = m_IDDArray.GetSize();
	int nIDD = m_IDDArray[nSize - 2];

	return nIDD;
}

void CBGJServToolApp::IDDClear()
{
	m_IDDArray.RemoveAll();
}

bool CBGJServToolApp::IsOnline()
{
	return !m_bOffTest;
}

COURSE_TYPE CBGJServToolApp::GetCourse()
{
	return m_Course;
}

void CBGJServToolApp::SetCourse( COURSE_TYPE Course)
{
	m_Course = Course;
}

SIDE_TYPE CBGJServToolApp::GetSide()
{
	return m_Side;
}

void CBGJServToolApp::SetSide( SIDE_TYPE Side)
{
	m_Side = Side;
}

bool CBGJServToolApp::SetPrinterDataSavePath(LPCTSTR lpszSavePath)
{
	m_csPrinterDataSavePath = lpszSavePath;
	return true;
}

LPCTSTR CBGJServToolApp::GetPrinterDataSavePath()
{
	if( m_csPrinterDataSavePath.IsEmpty() ){
		m_csPrinterDataSavePath = GetDataPath();
	}
	return (LPCTSTR)m_csPrinterDataSavePath;
}

//2.00 Production
LPCTSTR CBGJServToolApp::GetNewFirmPath()
{
	if( m_csNewFirmPath.IsEmpty() ){
		m_csNewFirmPath = m_csExePath;
		int nPos = m_csNewFirmPath.ReverseFind( _T('\\') );
		if( nPos > 0 ){
			int nLen = m_csNewFirmPath.GetLength();
			m_csNewFirmPath.Delete( nPos + 2, nLen - nPos - 1 );
			m_csNewFirmPath += _T("NewFirm2.00\\");
		}else
		{
			LangAfxMsgBox( IDS_ERR_BUG , -274 );
			//"Error: BGJServTool: GetNewFirmPath failed"
		}
	}
	return (LPCTSTR)m_csNewFirmPath;
}

void CBGJServToolApp::DebugMsg(LPCTSTR pszFmt, ... )
{
	va_list args;
	va_start( args, pszFmt );     /* 可変個の引数の初期化 */
	TCHAR Buff[4096];
	_vstprintf( Buff, pszFmt, args );
	::OutputDebugString( Buff );
	va_end( args );
}

bool CBGJServToolApp::SerialAndLotLoad(int *pPC, int *pSerial, int *pLot)
{
	bool bRet = false;
	FILE* pf;
	pf = _tfopen( (LPCTSTR)m_csSerialAndLot, _T("rt") );
	if( pf != NULL ){
		char Buff[64];
		DWORD dwWork;
		if( fgets( Buff, 64, pf ) ){
			if( CMemEntry::qAtoDWORD( Buff, &dwWork ) ){
				*pSerial = dwWork;
				if( fgets( Buff, 64, pf ) ){
					if( CMemEntry::qAtoDWORD( Buff, &dwWork ) ){
						*pLot = dwWork;
						if( fgets( Buff, 64, pf ) ){
							if( CMemEntry::qAtoDWORD( Buff, &dwWork ) ){
								*pPC = dwWork;
								bRet = true;
							}
						}
					}
				}
			}
		}
		fclose( pf );
	}
	return bRet;
}

bool CBGJServToolApp::SerialAndLotInit(int nPC, int nSerial, int nLot)
{
	bool bRet = false;
	FILE* pf;
	int orgPC, orgSerial, orgLot;
	if( SerialAndLotLoad( &orgPC, &orgSerial, &orgLot ) ){
		if( nPC < 0 )	nPC = orgPC;
		if( nSerial < 0 ) nSerial = orgSerial;
		if( nLot < 0 ) nLot = orgLot;
	}else{
		if( nPC < 0 ) nPC = 0;
		if( nSerial < 0 ) nSerial = 0;
		if( nLot < 0 ) nLot = 0;
	}
	pf = _tfopen( (LPCTSTR)m_csSerialAndLot, _T("wt") );
	if( pf ){
		CString cs;
		cs.Format( _T("%d\n%d\n%d\n"), nSerial, nLot, nPC );
		if( _fputts( (LPCTSTR)cs, pf ) >= 0 ){
			bRet = true;
		}
		fclose( pf );
	}
	return bRet;
}

bool CBGJServToolApp::SerialUpdate()
{
	bool bRet = false;
	FILE* pf;
	int orgPC, orgSerial, orgLot;
	if( SerialAndLotLoad( &orgPC, &orgSerial, &orgLot ) ){
		pf = _tfopen( (LPCTSTR)m_csSerialAndLot, _T("wt") );
		if( pf ){
			orgSerial += 1;
			CString cs;
			cs.Format( _T("%d\n%d\n%d\n"), orgSerial, orgLot, orgPC );
			if(_fputts( (LPCTSTR)cs, pf ) >= 0 ){
				bRet = true;
			}
		}
		fclose( pf );
	}
	return bRet;
}

void CBGJServToolApp::SerialAndLotFileName()//??????????????
{
	m_csSerialAndLot = m_csExePath;
	int nPos = m_csSerialAndLot.ReverseFind( _T('\\') );
	if( nPos > 0 ){
		int nLen = m_csSerialAndLot.GetLength();
		m_csSerialAndLot.Delete( nPos + 2, nLen - nPos - 1 );
		m_csSerialAndLot += _T("SerialAndLot.dat");
	}else
	{
		LangAfxMsgBox( IDS_ERR_BUG , -275 );
		//"Error: BGJServTool: SerialAndLotFileName failed"
	}
}


LPCTSTR CBGJServToolApp::GetExeFolder()
{
	if( m_csExeFolder.IsEmpty() ){
		m_csExeFolder = m_csExePath;
		int nPos = m_csExeFolder.ReverseFind( _T('\\') );
		if( nPos > 0 ){
			int nLen = m_csExeFolder.GetLength();
			m_csExeFolder.Delete( nPos + 2, nLen - nPos - 1 );
		}else
		{
			LangAfxMsgBox( IDS_ERR_BUG , -276 );
			//"Error: BGJServTool: GetExeFolder failed") );
		}
	}
	return (LPCTSTR)m_csExeFolder;
}

long CBGJServToolApp::GetCurrentGMTSecond( time_t dwTime )
{
	long lRet = 0;
	CTime ct;
	if( dwTime == 0 ){
		ct = CTime::GetCurrentTime();
	}else{
		ct = dwTime;
	}
	CTime ctOrg( 2000, 1, 1, 0, 0, 0, -1 );
	CTimeSpan ctSpan = ct - ctOrg;
	lRet = (DWORD)ctSpan.GetTotalSeconds();
	TIME_ZONE_INFORMATION tzinfo;
	DWORD tzstate = ::GetTimeZoneInformation(&tzinfo);
	if(TIME_ZONE_ID_DAYLIGHT == tzstate){
		lRet -= (tzinfo.DaylightBias * 60); // 夏時間を標準時間に戻す  
	}
	tzinfo.DaylightBias=-60;
	lRet += tzinfo.Bias * 60; // GMTへ _timezone=tzinfo.Bias * 60
	if( lRet < 0 ){
		lRet = 0;
	}
	return lRet;
}

int CBGJServToolApp::GetTimeZoneDiff()
{
	return _timezone;
}

bool CBGJServToolApp::GetTimeZoneInfoStr(CString &csZone)
{
	bool bRet = true;
	TIME_ZONE_INFORMATION tzinfo;
	DWORD tzstate = ::GetTimeZoneInformation(&tzinfo);
	csZone = (LPCWSTR)tzinfo.StandardName;
	/******
	if(TIME_ZONE_ID_DAYLIGHT == tzstate){
		csZone = (LPCWSTR)tzinfo.DaylightName;
	}else{
		csZone = (LPCWSTR)tzinfo.StandardName;
	}
	*******/
	return bRet;
}

int CBGJServToolApp::GetGTPrinters( CComboBox* pPrinterComBox )
{
	auto CallBack = [] ( GTX_PRINTER_TYPE type, LPCTSTR szPrinter, void* pUserData ) {
		auto pComboBox = reinterpret_cast<CComboBox*>(pUserData);
		int index = pComboBox->AddString( szPrinter );
		pComboBox->SetItemData( index, (int)type );
		return	TRUE;
	};

	auto pUserData = reinterpret_cast<void*>(pPrinterComBox);
	auto type = (GTX_PRINTER_TYPE)(TYPE_GTX6SP|TYPE_USB|TYPE_LAN);
	return	GTX_EnumPrinter( type, CallBack, pUserData );
}

int CBGJServToolApp::ResetEEPROM8014()
{
	CT2UTF8 name(GetPrinterName());
	gtbidi_error_t err{ GTBIDI_SUCCESS };
	gtbidiprv_printer_t* p = gtbidiprv_open_printer(name, &err);
	if (err.code != GTBIDI_SUCCESS) {
		return err.code;
	}

	gtbidi_history_information_t history = GTBIDI_HISTORY_INFORMATION_EEPROM8014_DATE;
	gtbidiprv_reset_history_information(p, history, &err);
	gtbidiprv_close_printer(p);

	return err.code;
}

int CBGJServToolApp::ResetIpAddress()
{
	CT2UTF8 name(GetPrinterName());
	gtbidi_error_t err{ GTBIDI_SUCCESS };
	gtbidi_printer_t* p = gtbidi_open_printer(name, &err);
	if (err.code != GTBIDI_SUCCESS) {
		return err.code;
	}

	gtbidi_ipv4_address_set_t address{ 0, 0, 0 };
	gtbidi_update_ipv4_address(p, address, &err);
	gtbidi_close_printer(p);

	return err.code;
}

int CBGJServToolApp::ResetMoter()
{
	CT2UTF8 name(GetPrinterName());
	gtbidi_error_t err{ GTBIDI_SUCCESS };
	gtbidiprv_printer_t* p = gtbidiprv_open_printer(name, &err);
	if (err.code != GTBIDI_SUCCESS) {
		return err.code;
	}

	gtbidi_history_information_t history = GTBIDI_HISTORY_INFORMATION_CR_MOTER;
	gtbidiprv_reset_history_information(p, history, &err);
	gtbidiprv_close_printer(p);

	return err.code;
}

int CBGJServToolApp::ResetBattery()
{
	CT2UTF8 name(GetPrinterName());
	gtbidi_error_t err{ GTBIDI_SUCCESS };
	gtbidiprv_printer_t* p = gtbidiprv_open_printer(name, &err);
	if (err.code != GTBIDI_SUCCESS) {
		return err.code;
	}

	gtbidi_history_information_t history = GTBIDI_HISTORY_INFORMATION_BATTERY;
	gtbidiprv_reset_history_information(p, history, &err);
	gtbidiprv_close_printer(p);

	return err.code;
}

int CBGJServToolApp::ResetTubeClearning()
{
	CT2UTF8 name(GetPrinterName());
	gtbidi_error_t err{ GTBIDI_SUCCESS };
	gtbidiprv_printer_t* p = gtbidiprv_open_printer(name, &err);
	if (err.code != GTBIDI_SUCCESS) {
		return err.code;
	}

	gtbidi_history_information_t history = GTBIDI_HISTORY_INFORMATION_TUBE_CLEARNING;
	gtbidiprv_reset_history_information(p, history, &err);
	gtbidiprv_close_printer(p);

	return err.code;
}

int CBGJServToolApp::ResetTubePump()
{
	CT2UTF8 name(GetPrinterName());
	gtbidi_error_t err{ GTBIDI_SUCCESS };
	gtbidiprv_printer_t* p = gtbidiprv_open_printer(name, &err);
	if (err.code != GTBIDI_SUCCESS) {
		return err.code;
	}

	gtbidi_history_information_t history = GTBIDI_HISTORY_INFORMATION_PUMP_TUBE;
	gtbidiprv_reset_history_information(p, history, &err);
	gtbidiprv_close_printer(p);

	return err.code;
}

int CBGJServToolApp::AdjustCRSpeed()
{
	CT2UTF8 name(GetPrinterName());
	gtbidi_error_t err{ GTBIDI_SUCCESS };
	gtbidi_printer_t* p = gtbidi_open_printer(name, &err);
	if (err.code != GTBIDI_SUCCESS) {
		return err.code;
	}

	gtbidi_execute_carriage_speed_adjustment(p, false, &err);
	gtbidi_close_printer(p);

	return err.code;
}

int CBGJServToolApp::SetTemperature(DWORD dwTemperature)
{
	CT2UTF8 name(GetPrinterName());
	gtbidi_error_t err{ GTBIDI_SUCCESS };
	gtbidiprv_printer_t* p = gtbidiprv_open_printer(name, &err);
	if (err.code != GTBIDI_SUCCESS) {
		return err.code;
	}

	uint16_t fahrenheit = static_cast<uint16_t>(dwTemperature);
	gtbidiprv_update_temperature_sensor_correction(p, fahrenheit, &err);
	gtbidiprv_close_printer(p);

	return err.code;
}

int CBGJServToolApp::SetRTC( DWORD dwInternal )
{
	CT2UTF8 name(GetPrinterName());
	gtbidi_error_t err{ GTBIDI_SUCCESS };
	gtbidiprv_printer_t* p = gtbidiprv_open_printer(name, &err);
	if (err.code != GTBIDI_SUCCESS) {
		return err.code;
	}

	time_t utc_time = static_cast<time_t>(dwInternal);
	gtbidiprv_update_realtime_clock(p, utc_time, &err);
	gtbidiprv_close_printer(p);

	return err.code;
}

int CBGJServToolApp::SetEighteenCode( CString csCode )
{
	CT2UTF8 name(GetPrinterName());
	gtbidi_error_t err{ GTBIDI_SUCCESS };
	gtbidiprv_printer_t* p = gtbidiprv_open_printer(name, &err);
	if (err.code != GTBIDI_SUCCESS) {
		return err.code;
	}

	CT2UTF8 code(csCode);
	gtbidiprv_update_18digit_code(p, code, &err);
	gtbidiprv_close_printer(p);

	return err.code;
}

int CBGJServToolApp::SetSerialCode( CString csCode )
{
	CT2UTF8 name(GetPrinterName());
	gtbidi_error_t err{ GTBIDI_SUCCESS };
	gtbidiprv_printer_t* p = gtbidiprv_open_printer(name, &err);
	if (err.code != GTBIDI_SUCCESS) {
		return err.code;
	}

	CT2UTF8 number(csCode);
	gtbidiprv_update_serial_number(p, number, &err);
	gtbidiprv_close_printer(p);

	return err.code;
}

int CBGJServToolApp::RestoreEEPROMAndSetRTCAndBackup(DWORD dwInternal)
{
	CT2UTF8 name(GetPrinterName());
	gtbidi_error_t err{ GTBIDI_SUCCESS };
	gtbidiprv_printer_t* p = gtbidiprv_open_printer(name, &err);
	if (err.code != GTBIDI_SUCCESS) {
		return err.code;
	}

	gtbidiprv_restore_eeprom(p, &err);
	if (err.code != GTBIDI_SUCCESS) {
		gtbidiprv_close_printer(p);
		return err.code;
	}

	time_t utc_time = static_cast<time_t>(dwInternal);
	gtbidiprv_update_realtime_clock(p, utc_time, &err);
	if (err.code != GTBIDI_SUCCESS) {
		gtbidiprv_close_printer(p);
		return err.code;
	}

	gtbidiprv_backup_eeprom(p, &err);
	gtbidiprv_close_printer(p);

	return err.code;
}

int CBGJServToolApp::SetRTCAndResetEEPROM8014( DWORD dwInternal )
{
	CT2UTF8 name(GetPrinterName());
	gtbidi_error_t err{ GTBIDI_SUCCESS };
	gtbidiprv_printer_t* p = gtbidiprv_open_printer(name, &err);
	if (err.code != GTBIDI_SUCCESS) {
		return err.code;
	}

	time_t utc_time = static_cast<time_t>(dwInternal);
	gtbidiprv_update_realtime_clock(p, utc_time, &err);
	if (err.code != GTBIDI_SUCCESS) {
		gtbidiprv_close_printer(p);
		return err.code;
	}

	gtbidi_history_information_t history = GTBIDI_HISTORY_INFORMATION_EEPROM_ALL;
	gtbidiprv_reset_history_information(p, history, &err);
	gtbidiprv_close_printer(p);

	return err.code;
}

int CBGJServToolApp::SetRTCAndBattery( DWORD dwInternal )
{
	CT2UTF8 name(GetPrinterName());
	gtbidi_error_t err{ GTBIDI_SUCCESS };
	gtbidiprv_printer_t* p = gtbidiprv_open_printer(name, &err);
	if (err.code != GTBIDI_SUCCESS) {
		return err.code;
	}

	time_t utc_time = static_cast<time_t>(dwInternal);
	gtbidiprv_update_realtime_clock(p, utc_time, &err);
	if (err.code != GTBIDI_SUCCESS) {
		gtbidiprv_close_printer(p);
		return err.code;
	}

	gtbidi_history_information_t history = GTBIDI_HISTORY_INFORMATION_BATTERY;
	gtbidiprv_reset_history_information(p, history, &err);
	gtbidiprv_close_printer(p);

	return err.code;
}

int CBGJServToolApp::BackupEEPROM()
{
	CT2UTF8 name(GetPrinterName());
	gtbidi_error_t err{ GTBIDI_SUCCESS };
	gtbidiprv_printer_t* p = gtbidiprv_open_printer(name, &err);
	if (err.code != GTBIDI_SUCCESS) {
		return err.code;
	}

	gtbidiprv_backup_eeprom(p, &err);
	gtbidiprv_close_printer(p);

	return err.code;
}

int CBGJServToolApp::SetInitInkState(DWORD K, DWORD YCM, DWORD W1, DWORD W2W4)
{
	CT2UTF8 name(GetPrinterName());
	gtbidi_error_t err{ GTBIDI_SUCCESS };
	gtbidiprv_printer_t* p = gtbidiprv_open_printer(name, &err);
	if (err.code != GTBIDI_SUCCESS) {
		return err.code;
	}

	uint8_t w1   = static_cast<uint8_t>(W1);
	uint8_t w123 = static_cast<uint8_t>(W2W4);
	uint8_t k    = static_cast<uint8_t>(K);
	uint8_t cmy  = static_cast<uint8_t>(YCM);
	gtbidiprv_update_initial_ink_installation_flags(p, w1, w123, k, cmy, &err);
	gtbidiprv_close_printer(p);

	return err.code;
}

int CBGJServToolApp::SetAssembleFlag(DWORD dwParam)
{
	CT2UTF8 name(GetPrinterName());
	gtbidi_error_t err{ GTBIDI_SUCCESS };
	gtbidiprv_printer_t* p = gtbidiprv_open_printer(name, &err);
	if (err.code != GTBIDI_SUCCESS) {
		return err.code;
	}

	uint8_t flag = static_cast<uint8_t>(dwParam);
	gtbidiprv_update_assembly_flag(p, flag, &err);
	gtbidiprv_close_printer(p);

	return err.code;
}

int CBGJServToolApp::SetWhiteHalt(DWORD dwParam)
{
	CT2UTF8 name(GetPrinterName());
	gtbidi_error_t err{ GTBIDI_SUCCESS };
	gtbidiprv_printer_t* p = gtbidiprv_open_printer(name, &err);
	if (err.code != GTBIDI_SUCCESS) {
		return err.code;
	}

	uint8_t flag = static_cast<uint8_t>(dwParam);
	gtbidiprv_update_white_ink_pause_flags(p, flag, &err);
	gtbidiprv_close_printer(p);

	return err.code;
}

int CBGJServToolApp::ResetHumidFanFilter()
{
	CT2UTF8 name(GetPrinterName());
	gtbidi_error_t err{ GTBIDI_SUCCESS };
	gtbidiprv_printer_t* p = gtbidiprv_open_printer(name, &err);
	if (err.code != GTBIDI_SUCCESS) {
		return err.code;
	}

	gtbidiprv_reset_cleaning_replacement_parts(p, (gtbidi_cleaning_replacement_type_t)GTBIDI_CLEANING_REPLACEMENT_TYPE_HUMID_FAN_FILTER, &err);
	gtbidiprv_close_printer(p);

	return err.code;
}

void CBGJServToolApp::SetDemo()
{
	m_bOffTest = true;
}