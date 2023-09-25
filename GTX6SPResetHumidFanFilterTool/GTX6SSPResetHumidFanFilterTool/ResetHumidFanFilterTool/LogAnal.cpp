// LogAnal.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "bgjservtool.h"
#include "LogAnal.h"
#include "Language.h"
#include "LogAnal.h"
#include "LOGcode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define ERR_TYPE  ((const DWORD*)0x08)

#define TYPE_CODE_LIST	1
#define TYPE_LOG_TYPE	2
#define TYPE_CODE_PREV  3
#define TYPE_CODE_SPAN	4
#define TYPE_END		0

struct tagAnalList {
	int iType; // 1: code, 2:Type 0:end
	const DWORD* pdwCode;
	LPCTSTR pszDescription;
};

static const DWORD dwHeadReplace[]		 = { 
	0x12010000,0x12020000,0x12030000, 0x12040000,0x12050000,0x12060000, 0x12070000,0x12080000,0x12090000, 
	0x12110000,0x12120000,0x12130000, 0x12140000,0x12150000,0x12160000, 0x12170000,0x12180000,0x12190000, 
	0x12210000,0x12220000,0x12230000, 0x12240000,0x12250000,0x12260000, 0x12270000,0x12280000,0x12290000, 
	0x00001801,0x00001802,            0x00001803,0x00001804,            0x00001805,0x00001806, 0 };
//static const DWORD dwExcParts[]		 = { 0x15000000, 0x15010000, 0x15200000, 0x15210000, 0 };
static const DWORD dwNozzleClean[]		 = { 0x15400000, 0 };
static const DWORD dwPrintStart[]		 = { 0x91000000, 0 };
static const DWORD dwSurTemp[]			 = { 0x00001060, 0x00001061, 0 };
static const DWORD dwHumidity[]			 = { 0x00001064, 0x00001065, 0 };
static const DWORD dwMovePrn[]			 = { 0x12350000, 0x03350000, 0x03360000, 0 };
static const DWORD dwPrintON[]			 = { 0x00010000, 0 };
//static const DWORD dwInkEmpty[]		 = { 0x00002020, 0x00002021, 0x00002022, 0x00002023, 0x00002024, 0x00002025, 0x00002026, 0x00002027, 0 };
//static const DWORD dwTubeClean[]		 = { 0x10600000, 0x10610000, 0x10620000, 0x10630000, 0x10640000, 0x10650000, 0x10660000, 0 };
static const DWORD dwObstructionSensor[] = { 0x00002070, 0 };
static const DWORD dwCapWiperClean[]	 = { 0x15300000, 0x00001091, 0 };	//0x00001090
static const DWORD dwClosingPurge[]      = { 0x03200000, 0x03210000, 0x03300000, 0x03310000, 0 };
static const DWORD dwPreventiveMainte[]  = { 0x00001922, 0x00001924, 0x00001925, 0x00001926, 0 };

static const struct tagAnalList AnalList[] = 
{
	{  TYPE_LOG_TYPE  , ERR_TYPE			, _T("All Error log")					 },
	{  TYPE_CODE_LIST , dwHeadReplace		, _T("Head Replacement operation")		 },
//	{  TYPE_CODE_LIST , dwExcParts			, _T("Parts exchanging operation")		 },
	{  TYPE_CODE_LIST , dwNozzleClean		, _T("Nozzle cleaning operation")		 },
	{  TYPE_CODE_LIST , dwPrintStart		, _T("Print operation")					 },
	{  TYPE_CODE_LIST , dwSurTemp			, _T("Temparature Warning and Error")	 },
	{  TYPE_CODE_LIST , dwHumidity			, _T("Humidity Warning")				 },
	{  TYPE_CODE_LIST , dwMovePrn			, _T("Printer transport preparation")	 },
	{  TYPE_CODE_LIST , dwPrintON			, _T("Printer Power ON log")    		 },
//	{  TYPE_CODE_LIST , dwInkEmpty			, _T("Ink empty log")					 },
//	{  TYPE_CODE_LIST , dwTubeClean			, _T("White Tube cleanning log")		 },
	{  TYPE_CODE_SPAN , dwCapWiperClean		, _T("Cap/Wiper Cleaning")				 },
	{  TYPE_CODE_LIST , dwObstructionSensor , _T("Obstruction Sensor log")			 },
	{  TYPE_CODE_LIST , dwClosingPurge		, _T("Closing Purge")					 },
	{  TYPE_CODE_LIST , dwPreventiveMainte  , _T("Preventive Maintenance Warning")	 },
	{  TYPE_END, NULL , NULL },
};

#define CAP_CELAN		0
#define NOZZLE_CLEAN	1

#define CAP_CLEAN_CODE		0x00005500
#define NOZZLE_CLEAN_CODE	0x00005510

static const int nLimitValueList[] = { 1000, 5000, 10000, -1, -1 };
/////////////////////////////////////////////////////////////////////////////
// CLogAnal ダイアログ


CLogAnal::CLogAnal(CWnd* pParent /*=NULL*/)
	: CDialog(CLogAnal::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogAnal)
	m_csInfo = _T("");
	m_csTimeZone = _T("");
	//}}AFX_DATA_INIT
}


void CLogAnal::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogAnal)
	DDX_Control(pDX, IDC_CBX_LIMIT, m_cbxLimit);
	DDX_Control(pDX, IDC_CBX_SELECT, m_cbxSelect);
	DDX_Text(pDX, IDC_INFO, m_csInfo);
	DDX_Text(pDX, IDC_TIMEZONE, m_csTimeZone);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogAnal, CDialog)
	//{{AFX_MSG_MAP(CLogAnal)
	ON_BN_CLICKED(IDC_BTN_DISP, OnBtnDisp)
	ON_CBN_SELCHANGE(IDC_CBX_SELECT, OnCbnSelchangeCbxSelect)
	ON_WM_SIZE()
	ON_WM_GETMINMAXINFO()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogAnal メッセージ ハンドラ

void CLogAnal::OnBtnDisp() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	int iSel = m_cbxSelect.GetCurSel();
	int iLimitSel = m_cbxLimit.GetCurSel();
	pApp->BeginWaitCursor();
	m_csInfo.Empty();
	//int iNumber = -1;
	//for( int i=0; AnalList[i].nIndex >= 0; ++i ){
	//	if( iSel == AnalList[i].nIndex ){
	//		iNumber = i;
	//	}
	//}
	if( iSel >= 0 ){
		CreateAndDispInformation( AnalList[iSel].iType, AnalList[iSel].pdwCode, nLimitValueList[iLimitSel] );
	}
	/*switch( iSel ){
	case CAP_CLEAN:
		CreateAndDispInformation( CAP_CLEAN_CODE );
		break;
	case NOZZLE_CLEAN:
		CreateAndDispInformation( NOZZLE_CLEAN_CODE );
		break;
	}*/
	UpdateData( FALSE );
	pApp->EndWaitCursor();
}

BOOL CLogAnal::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: この位置に初期化の補足処理を追加してください
	ModifyStyleEx(0, WS_EX_DLGMODALFRAME);

	m_Array.SetSize( 64, 64 );
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	LangSetWndTxt( this							 , IDS_TITLE_LOGANAL );
	LangSetWndTxt( GetDlgItem( IDC_LOG_ANAL1_1 ) , IDS_LOG_ANAL1_1   );
	LangSetWndTxt( GetDlgItem( IDC_LOG_ANAL1_2 ) , IDS_LOG_ANAL1_2	 );
	LangSetWndTxt( GetDlgItem( IDC_LOG_ANAL1_3 ) , IDS_LOG_ANAL1_3	 );
	LangSetWndTxt( GetDlgItem( IDC_BTN_DISP )	 , IDS_DISPLAY		 );
	LangSetWndTxt( GetDlgItem( IDCANCEL )		 , IDS_CLOSE		 );

	int i;
	for( i=0; AnalList[i].iType != TYPE_END; ++i )
	{
		m_cbxSelect.InsertString( i, AnalList[i].pszDescription );
	}
	m_cbxSelect.SetCurSel( 0 );
	m_iSelectSel = 0;

	CString cs;
	for( i=0; nLimitValueList[i] > 0; ++i ){
		cs.Format(_T("%d"), nLimitValueList[i] );
		m_cbxLimit.InsertString( i, (LPCTSTR)cs );
	}
	m_cbxLimit.InsertString( i, _T("All") );
	m_cbxLimit.SetCurSel( 0 );
	pApp->GetTimeZoneInfoStr( m_csTimeZone );

	CheckDlgButton( IDC_RADIOLEFT , BST_CHECKED );

	UpdateData( FALSE );

	OnBtnDisp();

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

bool CLogAnal::CreateAndDispInformation( int iType, const DWORD* pdwCode, int nLimit)
{
	bool bRet = false;
	CGTLogFile cf;
	bool bLogOpenOK = false;
	int iRet = cf.Open( m_csLogFile );
	if( iRet == 1 )
	{
		if( cf.OpenLog() )
		{
			bLogOpenOK = true;
		}
	}else if( iRet == 0 ){
		if( cf.OpenLogDirectDebug( m_csLogFile ) ){
			bLogOpenOK = true;
		}
	}
	if( bLogOpenOK ){
		int nCount = 0;
		if( CheckAllElements( cf, iType, pdwCode, &nCount ) ){
			if( ConvertToCString( nCount, m_csInfo, nLimit ) ){
				bRet = true;
			}
		}
		DeleteAllElements();
	}
	cf.Close();
	return bRet;
}

bool CLogAnal::ConvertToCString(int nCount, CString& csList, int nLimit )
{
	bool bRet = true;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	int iNumber = 0;
	if( nCount > 0 ){
		for( int i=nCount-1; i>=0; --i ){
			CString cs;
			m_Array.ElementAt(i).MakeLogLine1( cs, nCount - i );
			csList += cs;
			cs.Empty();
			int iOffset = 0;
//			m_Array.ElementAt(i).MakeLogLineExtDat( cs );
			m_Array.ElementAt(i).MakeLogLineExtParam( cs );
			if( cs.IsEmpty() )
				csList += "\r\n";
			else
				csList += " " + cs + "\r\n";
			iNumber += 1;
			if( nLimit > 0 ){
				if( iNumber > nLimit ){
					break;
				}
			}
		}
	}else{
		csList += "No data found.\r\n";
	}
	return bRet;
}

bool CLogAnal::CheckAllElements(CGTLogFile &cf, int iType, const DWORD* pdwCode, int* pnCount)
{
	bool bRet = true;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	bool bCont = true;
	long lEntryCount = cf.GetLogEntryCount();
	CString csLine;
	*pnCount = 0;
    CGTLogEntry cPrevEntry;
	while( bCont && bRet ){
		CGTLogEntry cEntry;
		int iRet = cf.ReadLogEntry( cEntry );
		int i;
		if( iRet == 1 ){
			bool bMatch = false;
			switch( iType ){
            case TYPE_CODE_PREV:
            case TYPE_CODE_SPAN:
                // fallthrough;
			case TYPE_CODE_LIST:
				for( i=0; pdwCode[i] != 0; ++i ){
					if( cEntry.m_nCode == pdwCode[i] ){
						bMatch = true;
                        break;
					}
				}
				break;
			case TYPE_LOG_TYPE:
			//	if( cEntry.m_nType == (WORD)pdwCode ) {
				if( pdwCode == ERR_TYPE && (cEntry.m_nLevel==LVL_FATAL || cEntry.m_nLevel==LVL_MIDDLE) ) {
					bMatch = true;
				}
				break;
			}
            if( iType == TYPE_CODE_PREV ) {
    			if( bMatch ){
                    if( cPrevEntry.m_nCode != 0 ) {
                        m_Array.SetAtGrow( *pnCount, cPrevEntry );
                        *pnCount += 1;
                    }
                    cPrevEntry.m_nCode      = 0;
                    cPrevEntry.m_nLevel     = 0;
                    cPrevEntry.m_nType      = 0;
                    cPrevEntry.m_nMillisec  = 0;
                    cPrevEntry.m_dwTime     = 0;
                } else {
                    cPrevEntry.m_nCode      = cEntry.m_nCode;
                    cPrevEntry.m_nLevel     = cEntry.m_nLevel;
                    cPrevEntry.m_nType      = cEntry.m_nType;
                    cPrevEntry.m_nMillisec  = cEntry.m_nMillisec;
                    cPrevEntry.m_dwTime     = cEntry.m_dwTime;
                    // cPrevEntry.m_nDataSize  = cEntry.m_nDataSize;
                    // cPrevEntry.m_pData      = cEntry.m_pData;
                }
            }
            else if( iType == TYPE_CODE_SPAN && bMatch ) {
                if( i == 0 ) {  //スパンの期間
                    //期間の保存
                    if( cPrevEntry.m_nCode != 0 ) {
                        cEntry.m_pData      = (LPBYTE) new DWORD(cEntry.m_dwTime - cPrevEntry.m_dwTime);
                        cEntry.m_nDataSize  = sizeof(DWORD);
                    }
                    cPrevEntry.m_nCode      = 0;
                    cPrevEntry.m_nLevel     = 0;
                    cPrevEntry.m_nType      = 0;
                    cPrevEntry.m_nMillisec  = 0;
                    cPrevEntry.m_dwTime     = 0;
                }
                else {  //スパンの最初
                    //重複回避
                    if( cPrevEntry.m_nCode == 0 ) {
                        cPrevEntry.m_nCode      = cEntry.m_nCode;
                        cPrevEntry.m_nLevel     = cEntry.m_nLevel;
                        cPrevEntry.m_nType      = cEntry.m_nType;
                        cPrevEntry.m_nMillisec  = cEntry.m_nMillisec;
                        cPrevEntry.m_dwTime     = cEntry.m_dwTime;
                    }
                    bMatch  = FALSE;
                }
            }
			if( bMatch ){
				m_Array.SetAtGrow( *pnCount, cEntry );
				*pnCount += 1;
				if( cEntry.m_pData ){
					cEntry.m_pData = NULL;
				}
			}
		}else{
			bCont = false;
		}
	}
	return bRet;
}

void CLogAnal::DeleteAllElements()
{
	int nSize = m_Array.GetSize();
	for( int i=0; i<nSize; ++i ){
		if( m_Array.ElementAt(i).m_pData ){
			delete [] m_Array.ElementAt(i).m_pData;
			m_Array.ElementAt(i).m_pData = NULL;
		}
	}
}




void CLogAnal::OnCbnSelchangeCbxSelect()
{
	if( m_iSelectSel != m_cbxSelect.GetCurSel() )
	{
		m_iSelectSel = m_cbxSelect.GetCurSel();
		OnBtnDisp();
	}
}

void CLogAnal::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 480;
	lpMMI->ptMinTrackSize.y = 360;

	CDialog::OnGetMinMaxInfo(lpMMI);
}

void CLogAnal::MoveRect(int nID, int nLeft, int nTop, int nRight, int nBottom)
{
	CWnd*			pw;
	WINDOWPLACEMENT	wp;

	if( pw = GetDlgItem(nID) )
	{
		pw->GetWindowPlacement( &wp );
		if( nLeft   )	wp.rcNormalPosition.left	= nLeft;
		if( nTop    )	wp.rcNormalPosition.top		= nTop;
		if( nRight  )	wp.rcNormalPosition.right	= nRight;
		if( nBottom )	wp.rcNormalPosition.bottom	= nBottom;
		pw->SetWindowPlacement( &wp );
	}
}
void CLogAnal::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	MoveRect( IDC_CBX_SELECT ,             0,     0,        cx-144,     0 );
	MoveRect( IDC_BTN_DISP   ,        cx-137,     0,        cx- 12,     0 );
	MoveRect( IDC_INFO       ,             0,     0,        cx- 11, cy-76 );
	MoveRect( IDC_LOG_ANAL1_2,             0, cy-64,             0, cy-43 );
	MoveRect( IDC_TIMEZONE   ,             0, cy-64,             0, cy-43 );
	MoveRect( IDC_LOG_ANAL1_3,             0, cy-35,             0, cy-13 );
	MoveRect( IDC_CBX_LIMIT  ,             0, cy-36,             0, cy-14 );
	MoveRect( IDCANCEL       , (cx+303-95)/2, cy-40, (cx+303+95)/2, cy-12 );
}
