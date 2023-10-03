// PumpChg2.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "PumpChg2.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPumpChg2 プロパティ ページ

IMPLEMENT_DYNCREATE(CPumpChg2, CPropertyPage)

CPumpChg2::CPumpChg2() : CPropertyPage(CPumpChg2::IDD)
{
	//{{AFX_DATA_INIT(CPumpChg2)
		// メモ - ClassWizard はこの位置にメンバの初期化処理を追加します。
	//}}AFX_DATA_INIT
}

CPumpChg2::~CPumpChg2()
{
}

void CPumpChg2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPumpChg2)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPumpChg2, CPropertyPage)
	//{{AFX_MSG_MAP(CPumpChg2)
		// メモ: ClassWizard はこの位置に DDX および DDV の呼び出しコードを追加します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPumpChg2 メッセージ ハンドラ

BOOL CPumpChg2::OnQueryCancel() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	BOOL bRet = FALSE;
	if( LangCancelYesNoMsgBox() == IDYES )
	{
		bRet = TRUE;
	}
	return bRet;
}

BOOL CPumpChg2::OnSetActive() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	//pApp->Log( _T("Pump Change Step 2 Page") );
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

	LangSetWndTxt( GetDlgItem( IDC_CHANGE_PUMP2_1 ) , IDS_CHANGE_PUMP2_1 );

	return CPropertyPage::OnSetActive();
}

LRESULT CPumpChg2::OnWizardBack() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CPumpChg2::OnWizardNext() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	LRESULT nNextID = -1;
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	switch( pApp->GetCourse() ){
	case COURSE_PUMP_CHANGE:
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
