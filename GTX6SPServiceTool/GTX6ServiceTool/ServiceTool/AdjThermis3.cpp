// AdjThermis3.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "AdjThermis3.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdjThermis3 プロパティ ページ

IMPLEMENT_DYNCREATE(CAdjThermis3, CPropertyPage)

CAdjThermis3::CAdjThermis3() : CPropertyPage(CAdjThermis3::IDD)
{
	//{{AFX_DATA_INIT(CAdjThermis3)
		// メモ - ClassWizard はこの位置にメンバの初期化処理を追加します。
	//}}AFX_DATA_INIT
}

CAdjThermis3::~CAdjThermis3()
{
}

void CAdjThermis3::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdjThermis3)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdjThermis3, CPropertyPage)
	//{{AFX_MSG_MAP(CAdjThermis3)
		// メモ: ClassWizard はこの位置に DDX および DDV の呼び出しコードを追加します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdjThermis3 メッセージ ハンドラ

BOOL CAdjThermis3::OnSetActive() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

	LangSetWndTxt( GetDlgItem( IDC_ADJ_THERMIS03_01 ) , IDS_ADJ_THERMIS03_01 );

	UpdateData( FALSE );
	return CPropertyPage::OnSetActive();
}

LRESULT CAdjThermis3::OnWizardNext() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	LRESULT nNextID = -1;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	switch( pApp->GetCourse() )
	{
	case COURSE_MAIN_BOARD_CHANGE:
		nNextID = IDD_SERV_HEAD_VOLT01;
		break;
	default:
		nNextID = IDD_SERV_SEL_OPE;
		break;
	}
	return pApp->IDDPush( nNextID );
}

LRESULT CAdjThermis3::OnWizardBack() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
	//return IDD_SERV_ADJ_THERMIS02;
}
