// LogView.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "bgjservtool.h"
#include "LogView.h"
#include "DlgLogTxtProg.h"
#include "DlgLogCsvProg.h"
#include "logcode.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogView ダイアログ


CLogView::CLogView(CWnd* pParent /*=NULL*/)
	: CDialog(CLogView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogView)
	m_bErr = FALSE;
	m_bWrn = FALSE;
	m_bInf = FALSE;
	m_csTimeZone = _T("");
	m_csZoneTitle = _T("");
	//}}AFX_DATA_INIT
}


void CLogView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogView)
	DDX_Check(pDX, IDC_CHK_ERR, m_bErr);
	DDX_Check(pDX, IDC_CHK_WRN, m_bWrn);
	DDX_Check(pDX, IDC_CHK_INF, m_bInf);
	DDX_Check(pDX, IDC_CHK_PARAM, m_bParam);
	DDX_Text(pDX, IDC_TIMEZONE, m_csTimeZone);
	DDX_Text(pDX, IDC_ZONE_TITLE, m_csZoneTitle);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogView, CDialog)
	//{{AFX_MSG_MAP(CLogView)
	ON_BN_CLICKED(IDC_BTN_DISP, OnBtnDisp)
	ON_BN_CLICKED(IDC_BTN_CLOSE, OnBtnClose)
	ON_BN_CLICKED(IDC_BTN_CSV, OnBtnDispCsv)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogView メッセージ ハンドラ

BOOL CLogView::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: この位置に初期化の補足処理を追加してください
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	m_bErr = TRUE;
	m_bWrn = TRUE;
	m_bInf = TRUE;
	m_bParam = FALSE;

	LangSetWndTxt( this							  , IDS_TITLE_LOGVIEW	);
	LangSetWndTxt( GetDlgItem( IDC_LOG_CHECK2_1 ) , IDS_LOG_CHECK2_1	);
	LangSetWndTxt( GetDlgItem( IDC_LOG_CHECK2_2 ) , IDS_LOG_CHECK2_2	);
	LangSetWndTxt( GetDlgItem( IDC_ZONE_TITLE )	  , IDS_ZONE_TITLE		);
	LangSetWndTxt( GetDlgItem( IDC_BTN_DISP )	  , IDS_CONVERT_TO_TEXT );
	LangSetWndTxt( GetDlgItem( IDC_BTN_CLOSE )	  , IDS_CLOSE			);

	pApp->GetTimeZoneInfoStr( m_csTimeZone );
	LangGetString( IDS_ZONE_TITLE , &m_csZoneTitle );

	UpdateData( FALSE );
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}


//strFileが存在するかチェックし、存在する時は上書きするかどうかを聞く
//ファイルを作成しない時は、FALSEを返す
BOOL CLogView::CanIMakeFile( CString strFile )
{
	BOOL bMakeFile = TRUE;

	if( GetFileAttributes( strFile ) != -1 )
	{//存在した
		CString strTmp;
		LangGetString( IDS_FILE_EXIST , &strTmp );
		CString strExist = strFile + "\n" + strTmp;
		if( MessageBox( strExist , _T("GTX-6 Extra Colors ORGR Service Tool") , MB_YESNO ) != IDYES )
		{
			bMakeFile = FALSE;
		}
	}

	return bMakeFile;
}

BOOL CLogView::ConvertLogToText()
{
	BOOL bRet = FALSE;

	CString strTxt = ".txt";

	if( CanIMakeFile( m_csLogFile + strTxt ) )//ファイルが存在する時は、上書きするか確認する
	{
		CFile TxtF;
		if( TxtF.Open( m_csLogFile + strTxt , CFile::modeCreate|CFile::modeWrite|CFile::shareDenyWrite ) )
		{
			CGTLogFile cf;
			BOOL bLogOpenOK = FALSE;
			int iRet = cf.Open( m_csLogFile );
			if( iRet == 1 )
			{
				if( cf.OpenLog() )
				{
					bLogOpenOK = TRUE;
				}
			}else if( iRet == 0 )
			{
				if( cf.OpenLogDirectDebug( m_csLogFile ) )
				{
					bLogOpenOK = TRUE;
				}
			}

			if( bLogOpenOK )
			{
				if( ConvertToText( cf, TxtF ) )
				{
					bRet = TRUE;
				}
			}
			cf.Close();
			TxtF.Close();
		}
	}else
	{
		bRet = TRUE;
	}

	return bRet;
}

void CLogView::OnBtnDisp() 
{
	BOOL bOK = FALSE;

	CWaitCursor wc;

	UpdateData( TRUE );

	bOK = ConvertLogToText();

	if( bOK )
	{
#if 0
		char drive[_MAX_DRIVE];
		char dir[_MAX_DIR];
		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];
		_splitpath( m_csLogFile , drive , dir , fname , ext );
		CString strFolder = drive;
		strFolder += dir;
		ShellExecute( m_hWnd , "open" , strFolder , NULL , NULL , SW_SHOWNORMAL ); //フォルダを開く
#else
		CString strTxt = ".txt";
		ShellExecute( m_hWnd , _T("open") , m_csLogFile + strTxt , NULL , NULL , SW_SHOWNORMAL ); //ログファイルを開く
#endif
	}else
	{		
		LangAfxMsgBox( IDS_EER_FILE_IO , -166 , m_csTextFile );
	}
}

void CLogView::OnBtnDispCsv()	// Mizutani
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	bool bOK = false;
	int iRecNum = 0;
	if( UpdateData( TRUE ) ){
		CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
		if( CheckSaveFileNameCsv( m_csCsvFile ) ){
			CFile CsvF;
			if( CsvF.Open( m_csCsvFile, CFile::modeCreate|CFile::modeWrite|CFile::shareDenyWrite ) ){
				pApp->BeginWaitCursor();
				CGTLogFile cf;
				bool bLogOpenOK = false;
				int iRet = cf.Open( m_csLogFile );
				if( iRet == 1 ){
					if( cf.OpenLog( /*TRUE*/ ) )
					{
						bLogOpenOK = true;
					}
				}else if( iRet == 0 ){
					if( cf.OpenLogDirectDebug( m_csLogFile ) ){
						bLogOpenOK = true;
					}
				}
				if( bLogOpenOK ){
					if( ConvertToCsv( cf, CsvF, &iRecNum ) ){
						bOK = true;
					}
				}
				cf.Close();
				pApp->EndWaitCursor();
				CsvF.Close();
			}else
			{
				LangAfxMsgBox( IDS_EER_FILE_IO , -167 , m_csTextFile );
			}
		}
		if( bOK )
		{
			::ShellExecute( m_hWnd, _T("open"), (LPCTSTR)m_csCsvFile, NULL, NULL, SW_SHOWNORMAL );
		}
	}	
}

bool CLogView::CheckSaveFileNameCsv(CString &csFileName)	// Mizutani
{
	bool bRet = true;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	CString cs = m_csLogFile;
	CString csCsvFile;
	int iIndex = cs.ReverseFind( _T('.') );
	if( iIndex > 0 ){
		csCsvFile = cs.Left( iIndex );
	}else{
		csCsvFile = cs;
	}
	csCsvFile += _T(".csv");
	CString FilterStr;
	FilterStr = "Csv Files (*.csv)|*.csv|All Files (*.*)|*.*||";
	CFileDialog dlg(  FALSE, _T("csv"), csCsvFile, OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,
		FilterStr, NULL );
	//dlg.m_ofn.lpstrInitialDir = pApp->GetExeFolder();
	if( dlg.DoModal() == IDOK ){
		csFileName = dlg.GetPathName();
	}else{
		bRet = FALSE;
	}
	return bRet;
}

void CLogView::OnBtnClose() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnCancel();
}

//#pragma optimize("",off)
bool CLogView::ConvertToText(CGTLogFile &cf, CFile& File )
{
    // #define WriteString(FI, ST) FI.Write(ST, ST.GetLength()*sizeof(TCHAR))
    #define WriteString(FI, ST) { ATL::CW2A buf(ST); FI.Write(buf, strlen(buf)); }

	bool bRet = true;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	CGTLogEntry cEntry;
	bool bCont = true;
	int iNumber = 0;
	long lEntryCount = cf.GetLogEntryCount();
	CDlgLogTxtProg dlg;
	dlg.Create( CDlgLogTxtProg::IDD, (CWnd*)this );
	dlg.m_Progress.SetRange( 0, short( lEntryCount/1000 ) );
	dlg.m_Progress.SetPos( 0 );
	CString csLine;
	CString csTimeZone;
	pApp->GetTimeZoneInfoStr( csTimeZone );
	CString csTZInfo;
	csTZInfo.Format( _T("Log date in this file is based on %s\r\n"), (LPCTSTR)csTimeZone );
    WriteString( File, csTZInfo );
	// File.Write( (const void*)(LPCTSTR)csTZInfo, csTZInfo.GetLength() );
	CString csTitle = _T("Number:    Date      Time     Code     (Type) Description   \r\n"); 
    WriteString( File, csTitle );
	// File.Write( (const void*)(LPCTSTR)csTitle, csTitle.GetLength() );

	while( bCont && bRet ){
		int iRet = cf.ReadLogEntry( cEntry );
		if( iRet == 1 ){
			if( ( m_bErr && (cEntry.m_nLevel==LVL_FATAL  || cEntry.m_nLevel==LVL_MIDDLE) )
			||	( m_bWrn && (cEntry.m_nLevel==LVL_WARNING                              ) )
			||	( m_bInf && (cEntry.m_nLevel==LVL_EVENT1 || cEntry.m_nLevel==LVL_EVENT2) ) )
			{
				cEntry.MakeLogLine1( csLine, iNumber );
				int iLength = csLine.GetLength();
                WriteString( File, csLine );
				// File.Write( (const void*)(LPCTSTR)csLine, iLength * sizeof(TCHAR));
              { ATL::CW2A line(csLine);
                iLength = strlen(line); }
				csLine = "";
				int iOffset = 0;
				if( m_bParam )
					cEntry.MakeLogLineExtDat( csLine );
				else
					cEntry.MakeLogLineExtParam( csLine );
				if( csLine.GetLength() > 0 ) {
					CString csAdd(' ', LOGCODE_MAX+47 - iLength);
					csLine = csAdd + csLine;
				}
				csLine += "\r\n";
                WriteString( File, csLine );
				// File.Write( (const void*)(LPCTSTR)csLine, csLine.GetLength() );
			}
			iNumber += 1;
			if( (iNumber % 1000) == 0 ){
				dlg.m_Progress.SetPos( iNumber / 1000 );
				pApp->LocalMessageLoopExec();
			}
		}else{
			bCont = false;
		}
	}
	dlg.DestroyWindow();
	return bRet;
}

bool CLogView::ConvertToCsv(CGTLogFile &cf, CFile& File, int* p_iRecordCount, DWORD dwStartTime, DWORD dwEndTime )	// Mizutani
{
	int iRecordCount = 0;
	bool bRet = true;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	CGTLogEntry cEntry;
	bool bCont = true;
	int iNumber = 0;
	long lEntryCount = cf.GetLogEntryCount();
	CDlgLogCsvProg dlg;
	dlg.Create( CDlgLogCsvProg::IDD, (CWnd*)this );
	dlg.m_Progress.SetRange( 0, short( lEntryCount/1000 ) );
	dlg.m_Progress.SetPos( 0 );
	CString csLine;
	CString csTimeZone;
	pApp->GetTimeZoneInfoStr( csTimeZone );
	CString csTZInfo;
	csTZInfo.Format( _T("Log date in this file is based on %s\r\n"), (LPCTSTR)csTimeZone );
	File.Write( (const void*)(LPCTSTR)csTZInfo, csTZInfo.GetLength() );
	++iRecordCount;
	CString	csTitle = _T("Number,Date,Time,Code,Type,Description,Param1,Param2,Param3,Param4,Param5,Param6,Param7,Param8,Param9,Param10,Param11,Param12\r\n");
	File.Write( (const void*)(LPCTSTR)csTitle, csTitle.GetLength() );
	++iRecordCount;

	while( bCont && bRet ){
		int iRet = cf.ReadLogEntry( cEntry );
		if( iRet == 1 ){
			if( ChoiceSaveLogCsv( &cEntry, dwStartTime, dwEndTime ) ){
				cEntry.MakeLogLine1Csv( csLine, iNumber );
				csLine += "\r\n";
				File.Write( (const void*)(LPCTSTR)csLine, csLine.GetLength() );
				++iRecordCount;
			}
			iNumber += 1;
			if( (iNumber % 1000) == 0 ){
				dlg.m_Progress.SetPos( iNumber / 1000 );
				pApp->LocalMessageLoopExec();
			}
		}else{
			bCont = false;
		}
	}
	dlg.DestroyWindow();
	*p_iRecordCount = iRecordCount;
	return bRet;
}

bool CLogView::ChoiceSaveLogCsv( CGTLogEntry* p_cEntry, DWORD dwStartTime, DWORD dwEndTime )	// mizutani
{
	if( p_cEntry->m_dwTime < dwStartTime
	||	p_cEntry->m_dwTime > dwEndTime   )
	{
		return false;
	}

	if( ( !m_bErr && (p_cEntry->m_nLevel==LVL_FATAL  || p_cEntry->m_nLevel==LVL_MIDDLE) )
	||	( !m_bWrn && (p_cEntry->m_nLevel==LVL_WARNING                                 ) )
	||	( !m_bInf && (p_cEntry->m_nLevel==LVL_EVENT1 || p_cEntry->m_nLevel==LVL_EVENT2) ) )
	{
		return false;
	}
#if 0
	if( p_cEntry->m_nLevel >= LVL_EVENT3 )
		return false;

	//                               ↓※注意！ここだけFFFFじゃないよ！※※※※※
	if( ((p_cEntry->m_nCode & 0x0000FF00) == MNT_PARM_SH0) && 
		(p_cEntry->m_nType == MNT_PARM_SH0_CLS) )		// EEPROMブロック更新
		return false;

	if( ((p_cEntry->m_nCode & 0x0000FFFF) == INF_FROM_LG_SAVE) && 
		(p_cEntry->m_nType == INF_FROM_LG_SAVE_CLS) )	// Log Saved
		return false;

	if( ((p_cEntry->m_nCode & 0x0000FFFF) == STS_SUR_TEMP) && 
		(p_cEntry->m_nType == STS_SUR_TEMP_CLS) )		// 温度センサの状態（印字保証温度）
		return false;

	if( ((p_cEntry->m_nCode & 0x0000FFFF) >= OP_PW_LOGT_CMPLT) &&
		((p_cEntry->m_nCode & 0x0000FFFF) <= OP_PW_RCV_INIT_CMPLT) && 
		(p_cEntry->m_nType == LG_OPE) )					// タスク起動完了
		return false;

	if(	((p_cEntry->m_nCode & 0x0000FFFF) == PC_CMD_JOB_RESOLUTION) && 
		(p_cEntry->m_nType == LG_OPE) )					// 解像度
		return false;
#endif

	return true;
}

bool CLogView::CheckSaveFileName(CString &csFileName)
{
	bool bRet = true;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	CString cs = m_csLogFile;
	CString csTextFile;
	int iIndex = cs.ReverseFind( _T('.') );
	if( iIndex > 0 ){
		csTextFile = cs.Left( iIndex );
	}else{
		csTextFile = cs;
	}
	csTextFile += _T(".txt");
	CString FilterStr;
	FilterStr = "Text Files (*.txt)|*.txt|All Files (*.*)|*.*||";
	CFileDialog dlg(  FALSE, _T("txt"), csTextFile, OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,
		FilterStr, NULL );
	//dlg.m_ofn.lpstrInitialDir = pApp->GetExeFolder();
	if( dlg.DoModal() == IDOK ){
		csFileName = dlg.GetPathName();
	}else
	{
		bRet = false;
	}
	return bRet;
}

