// AdjThermis.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "AdjThermis.h"
#include "Language.h"
#include ".\adjthermis.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdjThermis プロパティ ページ

IMPLEMENT_DYNCREATE(CAdjThermis, CPropertyPage)

CAdjThermis::CAdjThermis() : CPropertyPage(CAdjThermis::IDD)
, m_bWait5Minutes(FALSE)
{
	//{{AFX_DATA_INIT(CAdjThermis)
	//}}AFX_DATA_INIT
}

CAdjThermis::~CAdjThermis()
{
}

void CAdjThermis::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdjThermis)
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_CHECK_5MINUTES, m_bWait5Minutes);
}


BEGIN_MESSAGE_MAP(CAdjThermis, CPropertyPage)
	//{{AFX_MSG_MAP(CAdjThermis)
		// メモ: ClassWizard はこの位置に DDX および DDV の呼び出しコードを追加します。
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECK_5MINUTES, OnBnClickedCheck5minutes)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdjThermis メッセージ ハンドラ

BOOL CAdjThermis::OnSetActive() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	//pApp->Log( _T("Adj Thermistor Step 1 Page") );
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

	LangSetWndTxt( GetDlgItem( IDC_ADJ_THERMIS01_01 ) , IDS_ADJ_THERMIS01_01 );

	if( pApp->GetCourse() == COURSE_MAIN_BOARD_CHANGE )
	{//Main基板交換
		LangSetWndTxt( GetDlgItem( IDC_CHECK_5MINUTES ) , IDS_ADJ_THERMIS01_DONE_CR );
	}else
	{//CR基板交換
		LangSetWndTxt( GetDlgItem( IDC_CHECK_5MINUTES ) , IDS_ADJ_THERMIS01_CHECK );
	}

	pSheet->SetWizardButtons( PSWIZB_BACK );

	m_bWait5Minutes = FALSE;

	UpdateData( FALSE );
	return CPropertyPage::OnSetActive();
}

LRESULT CAdjThermis::OnWizardNext() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	UpdateData( TRUE );
	LRESULT nNextID = IDD_SERV_ADJ_THERMIS02;
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	
	return pApp->IDDPush( nNextID );

}

LRESULT CAdjThermis::OnWizardBack() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

BOOL CAdjThermis::OnQueryCancel() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	BOOL bRet = FALSE;
	if( LangCancelYesNoMsgBox() == IDYES )
	{
		bRet = TRUE;
	}
	return bRet;
}

void CAdjThermis::OnBnClickedCheck5minutes()
{
	UpdateData( TRUE );

	CPropertySheet* pSheet = (CPropertySheet*)GetParent();

	if( m_bWait5Minutes )
	{
		pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT );
	}else
	{
		pSheet->SetWizardButtons( PSWIZB_BACK );
	}
}
