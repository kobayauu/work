// ServPSel.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include <winspool.h>
#include "bgjservtool.h"
#include "ServPSel.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const TCHAR cszBrMatCheck[] = _T("BrMatCheck");

/////////////////////////////////////////////////////////////////////////////
// CServPSel プロパティ ページ

IMPLEMENT_DYNCREATE(CServPSel, CPropertyPage)

CServPSel::CServPSel() : CPropertyPage(CServPSel::IDD)
{
	//{{AFX_DATA_INIT(CServPSel)
		// メモ - ClassWizard はこの位置にメンバの初期化処理を追加します。
	//}}AFX_DATA_INIT
}

CServPSel::~CServPSel()
{
}

void CServPSel::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServPSel)
	DDX_Control(pDX, IDC_CBX_PRINTER, m_cbxPrinterName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CServPSel, CPropertyPage)
	//{{AFX_MSG_MAP(CServPSel)
	ON_CBN_SELCHANGE(IDC_CBX_PRINTER, OnSelchangeCbxPrinter)
	ON_BN_CLICKED(IDC_BTN_RESCAN, OnBtnRescan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServPSel メッセージ ハンドラ

BOOL CServPSel::OnSetActive() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	//pApp->Log( _T("Serv Select Printer") );
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	m_nPrevIDD = pApp->SetPrevIDD( IDD );
	if( InitPrinterList() ){
		OnSelchangeCbxPrinter();
		pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	}

	LangSetWndTxt( GetDlgItem( IDC_SERV_PSEL1_1 )	, IDS_SERV_PSEL1_1	 );
	LangSetWndTxt( GetDlgItem( IDC_SELECT_PRINTER ) , IDS_SELECT_PRINTER );
	LangSetWndTxt( GetDlgItem( IDC_BTN_RESCAN )		, IDS_RESCAN		 );

	return CPropertyPage::OnSetActive();
}

LRESULT CServPSel::OnWizardBack() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CServPSel::OnWizardNext() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	LRESULT nNextID = -1;
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	pApp->SetPrinterName( m_csPrinterName );
	//pApp->Log( _T("Printer Select = %s"), (LPCTSTR)m_csPrinterName );
	
	switch( pApp->GetCourse() )
	{
	case COURCE_FIRING_ADJUST:
//		nNextID = IDD_SERV_FIRE_ADJ1;
		nNextID = IDD_VRATING;
		break;
	case COURSE_PARTS_CHANGE:
		nNextID = IDD_SERV_PARTS_CHG;
		break;
	case COURSE_CR_ADJ:
		nNextID = IDD_SERV_ADJ_CR_SPEED1;
		break;
	case COURSE_BATTERY_CHANGE:
		//nNextID = IDD_SERV_SET_DATE;
		nNextID = IDD_RTC_AND_BATTERY;
		break;
	case COURSE_CR_BOARD_CHANGE:
		nNextID = IDD_SERV_CR_ORIGIN;
		break;
	case COURSE_POWER_BOARD_CHANGE:
		nNextID = IDD_SERV_HEAD_VOLT01;
		break;
	case COURSE_MAIN_BOARD_CHANGE:
//		nNextID = IDD_SERV_CR_ORIGIN;
		nNextID = IDD_MAIN_BOARD_BRANCH;
		break;
	case COURSE_PUMP_CHANGE:
		nNextID = IDD_SERV_CHNAGE_PUMP1;
		break;
	case COURSE_CR_MOTOR:
		nNextID = IDD_SERV_CR_CHANGE;
		break;
	case COURSE_SET_DATE:
		nNextID = IDD_SERV_SET_DATE;
		break;
	case COURSE_RESET_TUBE:
		nNextID = IDD_SERV_RESET_TUBE1;
		break;
	case COURSE_LCD_BOARD:
		nNextID = IDD_BACKUP;
		break;
	case COURSE_HUMID_FAN:
		nNextID = IDD_HUMIDFAN;
		break;
	}
	
	return pApp->IDDPush( nNextID );
	//return CPropertyPage::OnWizardNext();
}

bool CServPSel::InitPrinterList()
{
	m_cbxPrinterName.ResetContent();

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	if( ! pApp->IsOnline() )
	{
		m_cbxPrinterName.AddString( _T("Demonstration mode") );
		m_cbxPrinterName.SetCurSel( 0 );
		return true;
	}
	else
	{
		int iRet = pApp->GetGTPrinters( &m_cbxPrinterName );
		if( iRet >= 0 )
		{
			m_cbxPrinterName.SetCurSel( 0 );
			return true;
		}
		else
		{
			LangAfxMsgBox( IDS_OFFLINE );
			return false;
		}
	}
}

void CServPSel::OnSelchangeCbxPrinter() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	int nSel = m_cbxPrinterName.GetCurSel();
	if( CB_ERR != nSel ){
		m_cbxPrinterName.GetLBText( nSel, m_csPrinterName );
		//AfxGetApp()->WriteProfileString( cszServSection, cszPrinterName, (LPCTSTR)m_csPrinterName );
	}	
}

void CServPSel::OnBtnRescan() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	if( InitPrinterList() )
	{
		OnSelchangeCbxPrinter();
		pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	}else{
		pSheet->SetWizardButtons( PSWIZB_BACK );
	}
}

