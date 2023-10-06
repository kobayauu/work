// AdjCRSpeed2.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "AdjCRSpeed2.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdjCRSpeed2 プロパティ ページ

IMPLEMENT_DYNCREATE(CAdjCRSpeed2, CPropertyPage)

CAdjCRSpeed2::CAdjCRSpeed2() : CPropertyPage(CAdjCRSpeed2::IDD)
{
	//{{AFX_DATA_INIT(CAdjCRSpeed2)
		// メモ - ClassWizard はこの位置にメンバの初期化処理を追加します。
	//}}AFX_DATA_INIT
}

CAdjCRSpeed2::~CAdjCRSpeed2()
{
}

void CAdjCRSpeed2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdjCRSpeed2)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdjCRSpeed2, CPropertyPage)
	//{{AFX_MSG_MAP(CAdjCRSpeed2)
		// メモ: ClassWizard はこの位置に DDX および DDV の呼び出しコードを追加します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdjCRSpeed2 メッセージ ハンドラ

BOOL CAdjCRSpeed2::OnSetActive() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

	LangSetWndTxt( GetDlgItem( IDC_ADJ_CR_SPEED2_1 ) , IDS_ADJ_CR_SPEED2_1 );
	
	UpdateData( FALSE );
	return CPropertyPage::OnSetActive();
}

LRESULT CAdjCRSpeed2::OnWizardBack() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CAdjCRSpeed2::OnWizardNext() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	LRESULT nNextID = IDD_SERV_SEL_OPE;
	switch( pApp->GetCourse() )
	{
	case COURSE_INIT_SETTING:
		//nNextID = IDD_SERV_SET_LOG1;
		break;
	case COURSE_MAIN_BOARD_CHANGE:
	//	nNextID = IDD_FIRE1;
		nNextID = IDD_VRATING;
		break;
	default:
		nNextID = IDD_SERV_SEL_OPE;
		break;
	}
	return pApp->IDDPush( nNextID );
}
