// LogFileInfo.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "bgjservtool.h"
#include "LogFileInfo.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogFileInfo ダイアログ


CLogFileInfo::CLogFileInfo(CWnd* pParent /*=NULL*/)
	: CDialog(CLogFileInfo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogFileInfo)
	m_csFileName = _T("");
	m_Edit = _T("");
	//}}AFX_DATA_INIT
}


void CLogFileInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogFileInfo)
	DDX_Text(pDX, IDC_FILE_NAME, m_csFileName);
	DDX_Text(pDX, IDC_EDIT_INFO, m_Edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogFileInfo, CDialog)
	//{{AFX_MSG_MAP(CLogFileInfo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogFileInfo メッセージ ハンドラ

BOOL CLogFileInfo::OnInitDialog() 
{
	CDialog::OnInitDialog();

	LangSetWndTxt( this                             , IDS_TITLE_LOGFILEINFO );
	LangSetWndTxt( GetDlgItem( IDC_LOGFILE_INFO_1 ) , IDS_LOGFILE_INFO_1 );
	LangSetWndTxt( GetDlgItem( IDCANCEL )			, IDS_CLOSE );

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	CGTLogFile cfLog;
	CString csDate;
	int iRet = cfLog.Open( m_csFileName, csDate );
	if( iRet == 1 ){
		m_Edit.Empty();
		CString cs;
		BYTE b[64];
		long dwSize;
		//顧客名 & コメント & PC情報
		if( cfLog.ReadTagString(_T("Cust"), cs ) )
		{
			m_Edit += _T("Customer :\t\t") + cs + _T("\r\n");
		}
		if( cfLog.ReadTagString(_T("Comm"), cs ) )
		{
			m_Edit += _T("Comment :\t\t") + cs + _T("\r\n");
		}
		if( cfLog.ReadTagString(_T("PCDT"), cs ) )
		{
			m_Edit += _T("PC Information :\t\t") + cs + _T("\r\n");
			// csDate is DDMMYYYYHHMM
			cs.Format(_T("Saved Date (PC) :\t\t%s/%s/%s %s:%s\r\n"),
					csDate.Mid(6,2), csDate.Mid(4,2), csDate.Mid(0,4),
					csDate.Mid(8,2), csDate.Mid(10,2) );
			m_Edit += cs +  _T("\r\n\r\n");
		}
		//プリンタ時刻
		if( cfLog.ReadTagData(_T("Date"), 4, b, &dwSize ) && dwSize >= 4 )
		{
			CTime ct( 2000, 1, 1, 0, 0, 0, 0 );
			ct += CTimeSpan( (b[0]<<24)|(b[1]<<16)|(b[2]<<8)|(b[3]) - pApp->GetTimeZoneDiff() );
			cs.Format(_T("Saved Date (Printer) :\t%s (UTC=%s)\r\n"),
				ct.Format(_T("%d/%m/%Y %H:%M:%S") ), ct.FormatGmt(_T("%d/%m/%Y %H:%M:%S") ) );
			m_Edit += cs;
		}
		//バージョン情報
		if( cfLog.ReadTagData(_T("Vers"), 48, b, &dwSize ) && dwSize >= 48 )
		{
#define VERS(x) b[x],b[x+1],(b[x+2]<<8)|b[x+3]
			cs.Format( _T("Versions :"
				"\t\t\tMain=%X.%02X.%04X, Actuator=%X.%02X.%04X, LCD=%X.%02X.%04X,\r\n"
				"\t\t\tHead C=%X.%02X.%04X,%X.%02X.%04X,\r\n"
				"\t\t\tHead W=%X.%02X.%04X,%X.%02X.%04X,\r\n"
				"\t\t\tMessage=%X.%02X.%04X, Font=%X.%02X.%04X, TestData=%X.%02X.%04X\r\n"),
					VERS( 0), VERS( 4), VERS(44),
					VERS(20), VERS(24),
					VERS(28), VERS(32),
					VERS( 8), VERS(12), VERS(16));
#undef VERS
			m_Edit += cs;
		}
		//製品番号 & ISM統一コード & MACアドレス
		if( cfLog.ReadTagString(_T("Prod"), cs ) )
		{
			m_Edit += _T("\r\nProduct Number:\t\t") + cs + _T("\r\n");
		}
		if( cfLog.ReadTagString(_T("18Cd"), cs ) )
		{
			m_Edit += _T("ISM Integrated Code :\t") + cs + _T("\r\n");
		}
		if( cfLog.ReadTagData(_T("MACa"), 8, b, &dwSize ) && dwSize >= 6 )
		{
			cs.Format(_T("MAC address :\t\t%02X-%02X-%02X-%02X-%02X-%02X\r\n"),
				b[0],b[1],b[2],b[3],b[4],b[5] );
			m_Edit += cs;
		}
	}
	UpdateData( FALSE );
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}
