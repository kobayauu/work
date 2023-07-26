// HeadHistory.cpp : 実装ファイル
//

#include "stdafx.h"
#include<assert.h>
#include "BGJServTool.h"
#include "HeadHistory.h"
#include "HeadCheck.h"
#include "Language.h"


// CHeadHistory ダイアログ

IMPLEMENT_DYNAMIC(CHeadHistory, CDialog)

CHeadHistory::CHeadHistory(CWnd* pParent /*=NULL*/)
	: CDialog(CHeadHistory::IDD, pParent)
{
}

CHeadHistory::~CHeadHistory()
{
}

void CHeadHistory::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_WhiteList);
	DDX_Control(pDX, IDC_LIST2, m_ColorList);
}


BEGIN_MESSAGE_MAP(CHeadHistory, CDialog)
	ON_BN_CLICKED(IDC_BTN_CHECK, &CHeadHistory::OnBnClickedBtnCheck)
END_MESSAGE_MAP()

BOOL CHeadHistory::OnInitDialog()
{
	CDialog::OnInitDialog();

	ModifyStyleEx( 0, WS_EX_DLGMODALFRAME );

	// set language
	LangSetWndTxt( this							, IDS_BTN_HEAD		);
	LangSetWndTxt( GetDlgItem( IDOK )			, IDS_CLOSE			);
	LangSetWndTxt( GetDlgItem( IDC_BLOCKID )	, IDS_TOTALPRINTS	);
	LangSetWndTxt( GetDlgItem( IDC_WHITE )		, IDS_WHITEHEAD		);
	LangSetWndTxt( GetDlgItem( IDC_COLOR )		, IDS_COLORHEAD		);

	// read EEPROM from log file

	if( ! m_LogF.Open( m_csLogFile ) )
		return	FALSE;

    CByteArray bufvers;
	if( ! ReadTagData( &bufvers, _T("Vers") ) )
		return	FALSE;

	CByteArray buf14;
	if( ! ReadTagData( &buf14, _T("EP14") ) )
		return	FALSE;

	CByteArray buf15;
	if( ! ReadTagData( &buf15, _T("EP15") ) )
		return	FALSE;

	m_LogF.Close();

	// display data

	DispTotalPrints( &buf14 );

    BOOL  bOperVer = bufvers[0] > 0x01 || (bufvers[0] == 0x01 && bufvers[1] >= 0x00);
    BOOL  bChecKey = (GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000);

	InitListHead( &m_WhiteList, bOperVer );
	InitListHead( &m_ColorList, bOperVer );

	// CHeadArray	WhiteHead;
	// CHeadArray	ColorHead;

	GetWhiteData( &buf15, &m_WhiteHead, bOperVer );
	GetColorData( &buf15, &m_ColorHead, bOperVer );

	DispListHead( &m_WhiteList, &m_WhiteHead );
	DispListHead( &m_ColorList, &m_ColorHead );

    GetDlgItem(IDC_BTN_CHECK)->ShowWindow( bChecKey ? SW_SHOW : SW_HIDE );
    GetDlgItem(IDC_BTN_CHECK)->EnableWindow( FALSE ); // ヘッドチェック機能はGTX-4と基準が異なるため、無効にしておく

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CHeadHistory::OnBnClickedBtnCheck()
{
    CHeadCheck dlg;
    dlg.m_pWhiteHead = &m_WhiteHead;
    dlg.m_pColorHead = &m_ColorHead;
    dlg.DoModal();
}


//タグデータの取得
bool CHeadHistory::ReadTagData(CByteArray* pBuf, LPCTSTR pTagName)
{
	assert( pBuf );
	assert( pTagName );

	//メモリ確保
	long nSize = 0;
	if( ! m_LogF.ReadTagData( pTagName, 0, NULL, &nSize ) )
		return	FALSE;

	if( nSize <= 0 )
		return	FALSE;

	pBuf->SetSize( nSize );

	//データ
	if( ! m_LogF.ReadTagData( pTagName , nSize, pBuf->GetData(), &nSize ) )
		return	FALSE;

	pBuf->RemoveAt(0, 12);
	return	TRUE;
}

//リストの表示
bool CHeadHistory::InitListHead(CListCtrl* pList, BOOL bOperVer)
{
	const int	COUNT			= 5;
	const int	WIDTH[COUNT]	= { 60,			120,		180,			120,		120             };
	const int	TEXT [COUNT]	= { IDS_NO,		IDS_HEADNO,	IDS_STARTDATE,	IDS_PRINTS, IDS_OPERATIONS  };

	pList->ModifyStyle( 0, LVS_SINGLESEL | LVS_REPORT );
	pList->SetExtendedStyle( LVS_EX_FULLROWSELECT );

	CString		msg;
	LV_COLUMN	lvc		= {0};
		lvc.mask		= LVCF_TEXT | LVCF_WIDTH;

	int zeroNo = bOperVer ? 3 : 4;

	for( int i = 0; i < COUNT; ++i )
	{
		LangGetString( TEXT[i], &msg );

		lvc.iSubItem	= i;
		lvc.cx			= ( i == zeroNo ? 0 : WIDTH[i] );
		lvc.pszText		= (LPTSTR)(LPCTSTR) msg;
		pList->InsertColumn( i, &lvc );
	}

	return	TRUE;
}

bool CHeadHistory::DispListHead(CListCtrl* pList, CHeadArray* pHead)
{
	TCHAR		szText[32]	= {0};
	LVITEM		lvi			= {0};
		lvi.mask			= LVIF_TEXT;
		lvi.pszText			= szText;

	for( int i = 0; i < pHead->GetSize(); ++i )
	{
		HEADDATA	*p	= &pHead->ElementAt( i );
		lvi.iItem		= i;

		wsprintf( szText, _T("%d"), i+1 );
		lvi.iSubItem	= 0;
		pList->InsertItem( &lvi );

        ATL::CA2W szName(p->szName);
		wsprintf( szText, _T("%s"), (LPCTSTR)szName );
		lvi.iSubItem	= 1;
		pList->SetItem( &lvi );

		CTime ct( 2000, 1, 1, 0, 0, 0, 0 );
		ct += CTimeSpan( p->dwStart );
		lstrcpy( szText, ct.Format( "%d/%m/%Y %H:%M:%S" ) );
		lvi.iSubItem	= 2;
		pList->SetItem( &lvi );

		wsprintf( szText, _T("%d"), p->dwPrint );
		lvi.iSubItem	= 3;
		pList->SetItem( &lvi );

        if( p->dwOperate == -1 )
            wsprintf( szText, _T("-") );
        else
    		wsprintf( szText, _T("%d"), p->dwOperate );
		lvi.iSubItem	= 4;
		pList->SetItem( &lvi );
	}

	return	TRUE;
}

//データの取得

#define	GET_BYTE(p)			(*(p))
#define	GET_WORD(p)			(*(p)<<8 | *(p+1))
#define	GET_DWORD(p)		(*(p)<<24 | *(p+1)<<16 | *(p+2)<<8 | *(p+3))

#define	EP14_PRINTS		0x01EC
#define EP15_WNUMBER	8
#define	EP15_WNAME		0x00CC
#define	EP15_WSTART		0x00AC
#define	EP15_WUPDATE	0x012C
#define	EP15_WPRINTS	0x010C
#define EP15_WOPERS     0x01E0
#define EP15_CNUMBER	4
#define	EP15_CNAME		0x015C
#define	EP15_CSTART		0x014C
#define	EP15_CUPDATE	0x018C
#define	EP15_CPRINTS	0x017C
#define EP15_COPERS     0x0200

bool CHeadHistory::DispTotalPrints(CByteArray* pBuf)
{
	BYTE	*p			= pBuf->GetData();
	DWORD	dwPrints	= GET_DWORD( p + EP14_PRINTS );
	SetDlgItemInt( IDC_BLOCK_ID, dwPrints );

	return	TRUE;
}

int compareHeadData( void* context, const void* a1, const void* a2 )
{
	HEADDATA	*p1 = (HEADDATA *) a1;
	HEADDATA	*p2 = (HEADDATA *) a2;

	if( p2->dwStart != p1->dwStart )
		return	p2->dwStart - p1->dwStart;

	return	0;
}
bool CHeadHistory::GetWhiteData(CByteArray* pBuf, CHeadArray* pHead, BOOL bOperVer )
{
	HEADDATA	data	= {0};
	BYTE		*p		= pBuf->GetData();

	for( int i = 0; i < EP15_WNUMBER; ++i )
	{
		memcpy( data.szName,         p + EP15_WNAME   + i * 8 , 8 );
		data.dwStart	= GET_DWORD( p + EP15_WSTART  + i * 4 );
		data.dwUpdate	= GET_DWORD( p + EP15_WUPDATE + i * 4 );
		data.dwPrint	= GET_DWORD( p + EP15_WPRINTS + i * 4 );
        data.dwOperate  = GET_DWORD( p + EP15_WOPERS  + i * 4 );
        if( data.dwOperate == 0 && bOperVer == FALSE )
            data.dwOperate = -1;

		if( data.dwPrint > 0 || data.dwStart > 0 )
			pHead->Add( data );
	}

	qsort_s( pHead->GetData(), pHead->GetCount(), sizeof(HEADDATA), compareHeadData, NULL );

	return	TRUE;
}
bool CHeadHistory::GetColorData(CByteArray* pBuf, CHeadArray* pHead, BOOL bOperVer)
{
	HEADDATA	data	= {0};
	BYTE		*p		= pBuf->GetData();

	for( int i = 0; i < EP15_CNUMBER; ++i )
	{
		memcpy( data.szName,         p + EP15_CNAME   + i * 8 , 8 );
		data.dwStart	= GET_DWORD( p + EP15_CSTART  + i * 4 );
		data.dwUpdate	= GET_DWORD( p + EP15_CUPDATE + i * 4 );
		data.dwPrint	= GET_DWORD( p + EP15_CPRINTS + i * 4 );
        data.dwOperate  = GET_DWORD( p + EP15_COPERS  + i * 4 );
        if( data.dwOperate == 0 && bOperVer == FALSE )
            data.dwOperate = -1;

		if( data.dwPrint > 0 || data.dwStart > 0 )
			pHead->Add( data );
	}

	qsort_s( pHead->GetData(), pHead->GetCount(), sizeof(HEADDATA), compareHeadData, NULL );

	return	TRUE;
}
