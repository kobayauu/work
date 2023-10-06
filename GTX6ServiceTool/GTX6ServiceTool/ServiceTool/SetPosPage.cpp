// SetPosPage.cpp : 実装ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "SetPosPage.h"
#include "Language.h"


// CSetPosPage ダイアログ

IMPLEMENT_DYNAMIC(CSetPosPage, CPropertyPage)

CSetPosPage::CSetPosPage()
	: CPropertyPage(CSetPosPage::IDD)
	, m_bDone(FALSE)
{
}

CSetPosPage::~CSetPosPage()
{
}

void CSetPosPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_SETPOS_DONE, m_bDone);
}


BEGIN_MESSAGE_MAP(CSetPosPage, CPropertyPage)
	ON_BN_CLICKED(IDC_CHECK_SETPOS_DONE, OnBnClickedCheckSetposDone)
	ON_BN_CLICKED(IDC_BTN_OPEN_GTMAINTE, OnBnClickedBtnOpenGtmainte)
END_MESSAGE_MAP()


// CSetPosPage メッセージ ハンドラ


BOOL CSetPosPage::OnSetActive()
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons( PSWIZB_BACK );

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

	LangSetWndTxt( GetDlgItem( IDC_SETPOS_1 )		   , IDS_SETPOS_1 );
	LangSetWndTxt( GetDlgItem( IDC_SETPOS_2 )		   , IDS_SETPOS_2 );
	LangSetWndTxt( GetDlgItem( IDC_SETPOS_3 )		   , IDS_SETPOS_3 );

	LangSetWndTxt( GetDlgItem( IDC_BTN_OPEN_GTMAINTE ) , IDS_BTN_OPEN_GTMAINTE );
	LangSetWndTxt( GetDlgItem( IDC_CHECK_SETPOS_DONE ) , IDS_CHECK_SETPOS_DONE );

	m_bDone = FALSE;
	UpdateData( FALSE );

	return CPropertyPage::OnSetActive();
}

LRESULT CSetPosPage::OnWizardBack()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CSetPosPage::OnWizardNext()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	LRESULT nNextID = -1;
	switch( pApp->GetCourse() )
	{
	case COURCE_FIRING_ADJUST:
	default:
		nNextID = IDD_SERV_SEL_OPE;
		break;

	case COURSE_MAIN_BOARD_CHANGE:
		nNextID = IDD_SET_IP;
		break;
	}

	return pApp->IDDPush( nNextID );
}

void CSetPosPage::OnBnClickedCheckSetposDone()
{
	UpdateData( TRUE );

	CPropertySheet* pSheet = (CPropertySheet*)GetParent();

	if( m_bDone )
	{
		pSheet->SetWizardButtons( PSWIZB_NEXT | PSWIZB_BACK );
	}else
	{
		pSheet->SetWizardButtons( PSWIZB_BACK );
	}
	
}

void CSetPosPage::OnBnClickedBtnOpenGtmainte()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	pApp->RunMaintenanceTool();
}
