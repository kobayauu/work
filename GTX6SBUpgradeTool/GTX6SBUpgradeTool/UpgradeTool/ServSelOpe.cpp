// ServSelOpe.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "ServSelOpe.h"
#include "FVerInfo.h"
#include "Language.h"
#include ".\servselope.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServSelOpe プロパティ ページ

IMPLEMENT_DYNCREATE(CServSelOpe, CPropertyPage)

CServSelOpe::CServSelOpe() : CPropertyPage(CServSelOpe::IDD)
{
	//{{AFX_DATA_INIT(CServSelOpe)
	m_csVersion = _T("");
	m_csCopyRight = _T("");
	//}}AFX_DATA_INIT
}

CServSelOpe::~CServSelOpe()
{
}

void CServSelOpe::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServSelOpe)
	DDX_Text(pDX, IDC_VERSION, m_csVersion);
	DDX_Text(pDX, IDC_COPYRIGHT, m_csCopyRight);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CServSelOpe, CPropertyPage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServSelOpe メッセージ ハンドラ

BOOL CServSelOpe::OnSetActive() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();

	m_nPrevIDD = pApp->SetPrevIDD( IDD );
	pSheet->SetWizardButtons( PSWIZB_NEXT );

	LangSetWndTxt( GetDlgItem( IDC_SEL_OPE_1 )				  , IDS_SEL_OPE_1			);
	LangSetWndTxt( GetDlgItem( IDC_SEL_OPE_2 )				  , IDS_SEL_OPE_2			);
	LangSetWndTxt( GetDlgItem( IDC_SELECT_OPE )				  , IDS_SELECT_OPE			);
	LangSetWndTxt( GetDlgItem( IDC_RADIO_PARTS_CHANGE )		  , IDS_RADIO_PARTS_CHANGE	);
	LangSetWndTxt( GetDlgItem( IDC_RADIO_LOG )				  , IDS_RADIO_VIEW_LOG		);
	LangSetWndTxt( GetDlgItem( IDC_RADIO_SET_DATE )			  , IDS_RADIO_SET_DATE		);
//	LangSetWndTxt( GetDlgItem( IDC_RADIO_SET_LR )		      , IDS_RADIO_SET_LR	    );
//	LangSetWndTxt( GetDlgItem( IDC_RADIO_RESET_TUBE_WORNING ) , IDS_RADIO_RESET_TUBE_WORNING );

	CFVerInfo Ver;
	Ver.LoadFileVersion();
	CString cs = Ver.GetFileVersionStr();

	m_csVersion = _T("GTX-6 Service Tool : Version ");
	m_csVersion += cs;

	LangGetString( IDS_COPYRIGHTS , &m_csCopyRight );

	pApp->IDDClear();
	pApp->IDDPush( IDD );
	pApp->SetCourse( COURSE_NONE );
	pApp->SetSide( SIDE_NONE );
	UpdateData(FALSE);
	return CPropertyPage::OnSetActive();
}


LRESULT CServSelOpe::OnWizardNext() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	LRESULT nNextID = -1;
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	if( ((CButton*)GetDlgItem(IDC_RADIO_SET_DATE))->GetCheck() )
	{
		pApp->SetCourse( COURSE_SET_DATE );
		nNextID = IDD_SERV_FIRST;
	}else if( ((CButton*)GetDlgItem(IDC_RADIO_LOG))->GetCheck() )
	{
		//SetCourse()はしない
		nNextID = IDD_SERV_LOG_CHECK1;
/*	}else if( ((CButton*)GetDlgItem(IDC_RADIO_SET_LR))->GetCheck() )
	{
		pApp->SetCourse( COURSE_SET_LR );
		nNextID = IDD_SERV_FIRST;	*/
/*	}else if( ((CButton*)GetDlgItem(IDC_RADIO_RESET_TUBE_WORNING))->GetCheck() )
	{
		pApp->SetCourse( COURSE_RESET_TUBE );
		nNextID = IDD_SERV_FIRST;*/
	}else
	{
		pApp->SetCourse( COURSE_PARTS_CHANGE );
		nNextID = IDD_SERV_PARTS_CHG;
	}

	return pApp->IDDPush( nNextID );
	//return CPropertyPage::OnWizardNext();
}


BOOL CServSelOpe::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	CheckDlgButton( IDC_RADIO_PARTS_CHANGE , BST_CHECKED );

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}
