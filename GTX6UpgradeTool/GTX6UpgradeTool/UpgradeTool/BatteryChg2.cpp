// BatteryChg2.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "BatteryChg2.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBatteryChg2 プロパティ ページ

IMPLEMENT_DYNCREATE(CBatteryChg2, CPropertyPage)

CBatteryChg2::CBatteryChg2() : CPropertyPage(CBatteryChg2::IDD)
{
	//{{AFX_DATA_INIT(CBatteryChg2)
		// メモ - ClassWizard はこの位置にメンバの初期化処理を追加します。
	//}}AFX_DATA_INIT
}

CBatteryChg2::~CBatteryChg2()
{
}

void CBatteryChg2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBatteryChg2)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBatteryChg2, CPropertyPage)
	//{{AFX_MSG_MAP(CBatteryChg2)
		// メモ: ClassWizard はこの位置に DDX および DDV の呼び出しコードを追加します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBatteryChg2 メッセージ ハンドラ

BOOL CBatteryChg2::OnQueryCancel() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	BOOL bRet = FALSE;
	if( LangCancelYesNoMsgBox() == IDYES )
	{
		bRet = TRUE;
	}
	return bRet;
}

BOOL CBatteryChg2::OnSetActive() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	//pApp->Log( _T("Battery Change Step 2 Page") );
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

	LangSetWndTxt( GetDlgItem( IDC_CHANGE_BATTERY2_1 ) , IDS_CHANGE_BATTERY2_1 );

	return CPropertyPage::OnSetActive();
}

LRESULT CBatteryChg2::OnWizardBack() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CBatteryChg2::OnWizardNext() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	LRESULT nNextID = -1;
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	switch( pApp->GetCourse() ){
	case COURSE_BATTERY_CHANGE:
		nNextID = IDD_SERV_SEL_OPE;
		break;
	case COURSE_MAIN_BOARD_CHANGE:
		nNextID = IDD_SERV_ADJ_CR_SPEED1;
		// nNextID = IDD_SERV_HEAD_VOLT01;
		break;
	default:
		nNextID = IDD_SERV_SEL_OPE;
		break;
	}
	return pApp->IDDPush( nNextID );
}
