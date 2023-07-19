// ViewEEP2.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "ViewEEP2.h"
#include "Language.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define CN_NUMBER 0
#define CN_ADDR	1
#define CN_SIZE 2
#define CN_DATA 3
#define CN_NAME 4

/////////////////////////////////////////////////////////////////////////////
// CViewEEP2 ダイアログ


CViewEEP2::CViewEEP2(CWnd* pParent /*=NULL*/)
	: CDialog(CViewEEP2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CViewEEP2)
	m_csBlockID = _T("");
	m_csHeadVersion = _T("");
	m_csVersion = _T("");
	m_csHeadComment = _T("");
	//}}AFX_DATA_INIT
}


void CViewEEP2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewEEP2)
	DDX_Control(pDX, IDC_LIST, m_MemList);
	DDX_Text(pDX, IDC_BLOCK_ID, m_csBlockID);
	DDX_Text(pDX, IDC_STR_VERSION, m_csHeadVersion);
	DDX_Text(pDX, IDC_VIRSION, m_csVersion);
	DDX_Text(pDX, IDC_COMMENT, m_csHeadComment);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewEEP2, CDialog)
	//{{AFX_MSG_MAP(CViewEEP2)
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LIST, OnGetdispinfoList)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, OnDblclkList)
	ON_BN_CLICKED(IDC_BTN_SAVEAS, OnBtnSaveas)
	ON_WM_GETMINMAXINFO()
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewEEP2 メッセージ ハンドラ

BOOL CViewEEP2::OnInitDialog() 
{
	CDialog::OnInitDialog();

	ModifyStyleEx(0, WS_EX_DLGMODALFRAME);

	LangSetWndTxt( this							, IDS_TITLE_EEP_DISP );
	LangSetWndTxt( GetDlgItem( IDC_BLOCKID )    , IDS_BLOCKID		 );
	LangSetWndTxt( GetDlgItem( IDC_VERSION )    , IDS_VERSION		 );
	LangSetWndTxt( GetDlgItem( IDC_BTN_SAVEAS ) , IDC_SAVEAS		 );
	LangSetWndTxt( GetDlgItem( IDOK )		    , IDS_CLOSE			 );

	m_MemList.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	if( m_pEEP )
	{
		DWORD dwID, dwVersion;
		if( m_pEEP->GetHeaderInfo( &dwID, &dwVersion, m_csHeadVersion, m_csHeadComment ) )
		{
			m_csBlockID.Format( _T("0x%04X"), dwID );
			m_csVersion.Format( _T("0x%04X"), dwVersion );
			m_csSaveAsFile.Format(_T("EEPROM-%04X.csv"), dwID );
			InitListCtrl();
			UpdateListCtrl();
		}
	}

	UpdateData( FALSE );

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CViewEEP2::InitListCtrl()
{
	LV_COLUMN lvc;

	m_MemList.ModifyStyle( 0, LVS_SINGLESEL | LVS_REPORT | LVS_OWNERDATA );
	
	InitImageList();

	lvc.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH;

	lvc.iSubItem = CN_NUMBER;
	lvc.pszText = _T("No.");
	lvc.iImage = 0;
	lvc.cx = 45;
	m_MemList.InsertColumn(CN_NUMBER,&lvc);

	lvc.mask = LVCF_TEXT | LVCF_SUBITEM | LVCF_WIDTH;

	lvc.iSubItem = CN_ADDR;
	lvc.pszText = _T("Addr");
	lvc.cx = 55;
	m_MemList.InsertColumn(CN_ADDR,&lvc);
	lvc.iSubItem = CN_SIZE;
	lvc.pszText = _T("Size");
	lvc.cx = 40;
	m_MemList.InsertColumn(CN_SIZE,&lvc);
	lvc.iSubItem = CN_DATA;
	lvc.pszText = _T("Data");
	lvc.cx = 160;
	m_MemList.InsertColumn(CN_DATA,&lvc);
	lvc.iSubItem = CN_NAME;
	lvc.pszText = _T("Name");
	lvc.cx = 400;
	m_MemList.InsertColumn(CN_NAME,&lvc);
}

void CViewEEP2::UpdateListCtrl()
{
	m_MemList.DeleteAllItems();
	m_MemList.SetItemCountEx( m_pEEP->GetCount() );

	Invalidate();
}

void CViewEEP2::OnGetdispinfoList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_DISPINFO* pDispInfo = (LV_DISPINFO*)pNMHDR;
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	LVITEM* pItem = &pDispInfo->item;

	int iItemIndx= pItem->iItem;
	CMemEntry* pEntry = m_pEEP->GetMemEntry( iItemIndx );
	CMemEntry* pRefEntry = NULL;
	if( m_pRefEEP ){
		pRefEntry = m_pRefEEP->GetMemEntry( iItemIndx );
	}
	bool bDiff = CheckDiff( pEntry, pRefEntry );
	if( pEntry != NULL ){
		pItem->iImage = -1;
		if (pItem->mask & LVIF_TEXT) //valid text buffer?
		{
			CString s;
			switch(pItem->iSubItem){
			case CN_NUMBER:
				s.Format(_T("%d"), pEntry->m_iNumber );
				lstrcpy(pItem->pszText, (LPCTSTR)s );
				break;
			case CN_ADDR: 
				s.Format(_T("0x%04X"), pEntry->m_dwAddr );
				lstrcpy(pItem->pszText, (LPCTSTR)s );
				break;
			case CN_SIZE: 
				s.Format(_T("%d"), pEntry->m_nSize );
				lstrcpy(pItem->pszText, (LPCTSTR)s );
				break;
			case CN_DATA: 
				ChangeDataStrForm( s, pEntry );
				lstrcpy(pItem->pszText, (LPCTSTR)s );
					//m_Items[iItemIndx].m_strSubItem2Text);
				break;
			case CN_NAME: //fill in sub item 2 text
				lstrcpy(pItem->pszText, (LPCTSTR)(pEntry->m_csName) );
					//m_Items[iItemIndx].m_strSubItem3Text);
				break;
			}
		}
		if( pItem->mask & LVIF_IMAGE ){
			switch(pItem->iSubItem){
			case CN_NUMBER:
				if( bDiff ){
					pItem->iImage = 1;
				}
				break;
			}
		}
	}
	*pResult = 0;
}

void CViewEEP2::ChangeDataStrForm(CString &s, CMemEntry *pEntry)
{
	int n;
	char sc[3] = { 0,0,0 };
	BYTE b1, b2;
	switch( pEntry->m_iType ){
	case 0: //Hex
		s = "0x";
		for( n=0; n<pEntry->m_nSize; ++n ){
			b1 = b2 = pEntry->GetDataByte( n );
			b1 >>= 4;
			sc[0] = (b1 > 0x09)? (b1-0x0A+'A'):(b1+'0');
			b2 &= 0x0F;
			sc[1] = (b2 > 0x09)? (b2-0x0A+'A'):(b2+'0');
			s += sc;
			if( (n % 2)==1) s += ' ';
		}
		break;
	case 1: // unsigned decimal
		s.Format(_T("%u"), pEntry->m_dwData1 );
		break;
	case 2:
		s.Format(_T("%d"), pEntry->m_dwData1 );
		break;
	case 3:
//		s = pEntry->m_csDate;
		{
			CTime ct( 2000, 1, 1, 0, 0, 0, 0 );
			ct += CTimeSpan( pEntry->m_dwData1 );
			s = ct.Format(_T("%d/%m/%Y %H:%M:%S") );
		}
		break;
	}
}

bool CViewEEP2::InitImageList()
{
	bool bRet = true;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	m_ImageListSmall.Create( 16, 16, ILC_COLORDDB | ILC_MASK, 2, 1);
	HICON hIcon1 = LoadIcon( pApp->m_hInstance, MAKEINTRESOURCE( IDI_ICON_NONE ) );
	HICON hIcon2 = LoadIcon( pApp->m_hInstance, MAKEINTRESOURCE( IDI_ICON_DIFF ) );
	m_ImageListSmall.Add( hIcon1 );
	m_ImageListSmall.Add( hIcon2 );
	m_MemList.SetImageList( &m_ImageListSmall, LVSIL_SMALL );
	return bRet;
}

bool CViewEEP2::CheckDiff(CMemEntry *pEntry, CMemEntry *pRefEntry)
{
	bool bRet = true;
	if( pRefEntry ){
		if( pEntry->m_dwAddr == pRefEntry->m_dwAddr ){
			if( pEntry->m_nSize == pRefEntry->m_nSize ){
				if( pEntry->m_dwData1 == pRefEntry->m_dwData1 ){
					if( pEntry->m_dwData2 == pRefEntry->m_dwData2 ){
						bRet = false;
					}
				}
			}
		}
	}else{
		bRet = false;
	}
	return bRet;
}

void CViewEEP2::OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	
	*pResult = 0;
}

void CViewEEP2::OnBtnSaveas() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	CString FilterStr;
	FilterStr = "CSV Files (*.csv)|*.csv|All Files (*.*)|*.*||";
	CFileDialog dlg(  FALSE, _T("csv"), m_csSaveAsFile, OFN_OVERWRITEPROMPT|OFN_HIDEREADONLY,
		FilterStr, NULL );
	dlg.m_ofn.lpstrInitialDir = pApp->GetExeFolder();
	if( dlg.DoModal() == IDOK ){
		m_csSaveAsFile = dlg.GetPathName();
		m_pEEP->SaveAsTemplate( (LPCTSTR)m_csSaveAsFile );
		//m_nFileExtSelected = dlg.m_ofn.nFilterIndex;
	}
}

void CViewEEP2::OnGetMinMaxInfo(MINMAXINFO* lpMMI)
{
	lpMMI->ptMinTrackSize.x = 480;
	lpMMI->ptMinTrackSize.y = 360;

	CDialog::OnGetMinMaxInfo(lpMMI);
}

void CViewEEP2::MoveRect(int nID, int nLeft, int nTop, int nRight, int nBottom)
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
void CViewEEP2::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	MoveRect( IDC_BTN_SETTINGS, cx-214, 0, cx-116,     0 );
	MoveRect( IDOK            , cx-109, 0, cx- 11,     0 );
	MoveRect( IDC_STR_VERSION ,      0, 0, cx- 11,     0 );
	MoveRect( IDC_COMMENT     ,      0, 0, cx- 11,     0 );
	MoveRect( IDC_LIST        ,      0, 0, cx- 11, cy-14 );
}
