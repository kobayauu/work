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
	DDX_Control(pDX, IDC_LIST , m_White1List);
	DDX_Control(pDX, IDC_LIST2, m_White2List);
	DDX_Control(pDX, IDC_LIST3, m_Color1List);
	DDX_Control(pDX, IDC_LIST4, m_Color2List);
	DDX_Control(pDX, IDC_LIST5, m_Special1List);
	DDX_Control(pDX, IDC_LIST6, m_Special2List);
}


BEGIN_MESSAGE_MAP(CHeadHistory, CDialog)
	ON_BN_CLICKED(IDC_BTN_CHECK, &CHeadHistory::OnBnClickedBtnCheck)
END_MESSAGE_MAP()

BOOL CHeadHistory::OnInitDialog()
{
	CDialog::OnInitDialog();

	ModifyStyleEx( 0, WS_EX_DLGMODALFRAME );
	// ヘッドチェック機能はGTX-4と基準が異なるため、無効にしておく
    GetDlgItem(IDC_BTN_CHECK)->ShowWindow( SW_HIDE );

	// set language
	LangSetWndTxt( this							, IDS_BTN_HEAD		);
	LangSetWndTxt( GetDlgItem( IDOK )			, IDS_CLOSE			);
	LangSetWndTxt( GetDlgItem( IDC_BLOCKID )	, IDS_TOTALPRINTS	);
	LangSetWndTxt( GetDlgItem( IDC_WHITE )		, IDS_WHITEHEAD		);
	LangSetWndTxt( GetDlgItem( IDC_COLOR )		, IDS_COLORHEAD		);
	LangSetWndTxt( GetDlgItem( IDC_SPECIAL )	, IDS_SPECIALHEAD	);

	// read EEPROM from log file

	if( ! m_LogF.Open( m_csLogFile ) )
		return	FALSE;

	CByteArray buf14;
	if( ! ReadTagData( &buf14, _T("EP14") ) )
		return	FALSE;

	CByteArray buf19;
	if( ! ReadTagData( &buf19, _T("EP19") ) )
		return	FALSE;

	m_LogF.Close();

	// display data

	DispTotalPrints( &buf14 );

	InitListHead( &m_White1List );
	InitListHead( &m_White2List );
	InitListHead( &m_Color1List );
	InitListHead( &m_Color2List );
	InitListHead( &m_Special1List );
	InitListHead( &m_Special2List );

	GetHeadData( &buf19, 0, &m_White1Head );
	GetHeadData( &buf19, 1, &m_White2Head );
	GetHeadData( &buf19, 2, &m_Color1Head );
	GetHeadData( &buf19, 3, &m_Color2Head );
	GetHeadData( &buf19, 4, &m_Special1Head );
	GetHeadData( &buf19, 5, &m_Special2Head );

	DispListHead( &m_White1List  , &m_White1Head );
	DispListHead( &m_White2List  , &m_White2Head );
	DispListHead( &m_Color1List  , &m_Color1Head );
	DispListHead( &m_Color2List  , &m_Color2Head );
	DispListHead( &m_Special1List, &m_Special1Head );
	DispListHead( &m_Special2List, &m_Special2Head );

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CHeadHistory::OnBnClickedBtnCheck()
{
    CHeadCheck dlg;
    dlg.m_pWhiteHead = &m_White1Head;
    dlg.m_pColorHead = &m_Color1Head;
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
bool CHeadHistory::InitListHead(CListCtrl* pList)
{
	const int	COUNT			= 4;
	const int	WIDTH[COUNT]	= { 30,			75,		135,			75			};
	const int	TEXT [COUNT]	= { IDS_NO,		IDS_HEADNO,	IDS_STARTDATE,	IDS_PRINTS	};

	pList->ModifyStyle( 0, LVS_SINGLESEL | LVS_REPORT );
	pList->SetExtendedStyle( LVS_EX_FULLROWSELECT );

	CString		msg;
	LV_COLUMN	lvc		= {0};
		lvc.mask		= LVCF_TEXT | LVCF_WIDTH;

	for( int i = 0; i < COUNT; ++i )
	{
		LangGetString( TEXT[i], &msg );

		lvc.iSubItem	= i;
		lvc.cx			= WIDTH[i];
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
	}

	return	TRUE;
}

//データの取得

#define	GET_BYTE(p)			(*(p))
#define	GET_WORD(p)			(*(p)<<8 | *(p+1))
#define	GET_DWORD(p)		(*(p)<<24 | *(p+1)<<16 | *(p+2)<<8 | *(p+3))

#define	EP14_PRINTS		0x0004

const DWORD EP19_HEAD[6][5] = {
	//Number, Name, Start, Update, Prints
	{ 8, 0x0020, 0x0000, 0x0080, 0x0060 },	//White
	{ 8, 0x00C0, 0x00A0, 0x0120, 0x0100 },
	{ 4, 0x0150, 0x0140, 0x0180, 0x0170 },	//Color
	{ 4, 0x01A0, 0x0190, 0x01D0, 0x01C0 },
	{ 4, 0x01F0, 0x01E0, 0x0220, 0x0210 },	//Special
	{ 4, 0x0240, 0x0230, 0x0270, 0x0260 }
};

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
bool CHeadHistory::GetHeadData(CByteArray* pBuf, int nNo, CHeadArray* pHead)
{
	HEADDATA	data	= {0};
	BYTE		*p		= pBuf->GetData();

	for( int i = 0; i < EP19_HEAD[nNo][0]; ++i )
	{
		memcpy( data.szName,         p + EP19_HEAD[nNo][1] + i * 8 , 8 );
		data.dwStart	= GET_DWORD( p + EP19_HEAD[nNo][2] + i * 4 );
		data.dwUpdate	= GET_DWORD( p + EP19_HEAD[nNo][3] + i * 4 );
		data.dwPrint	= GET_DWORD( p + EP19_HEAD[nNo][4] + i * 4 );
		if( data.dwPrint > 0 || data.dwStart > 0 )
			pHead->Add( data );
	}

	qsort_s( pHead->GetData(), pHead->GetCount(), sizeof(HEADDATA), compareHeadData, NULL );

	return	TRUE;
}
