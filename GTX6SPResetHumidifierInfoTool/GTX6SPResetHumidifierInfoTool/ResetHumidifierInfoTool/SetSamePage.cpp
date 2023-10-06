// SetSamePage.cpp : 実装ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "SetSamePage.h"
#include "Language.h"


// CSetSamePage ダイアログ

IMPLEMENT_DYNAMIC(CSetSamePage, CPropertyPage)

CSetSamePage::CSetSamePage()
	: CPropertyPage(CSetSamePage::IDD)
	, m_bDone(FALSE)
{
}

CSetSamePage::~CSetSamePage()
{
}

void CSetSamePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_SETPOS_DONE, m_bDone);
}


BEGIN_MESSAGE_MAP(CSetSamePage, CPropertyPage)
	ON_BN_CLICKED(IDC_CHECK_SETPOS_DONE, OnBnClickedCheckSetposDone)
	ON_BN_CLICKED(IDC_BTN_OPEN_GTMAINTE, OnBnClickedBtnOpenGtmainte)
END_MESSAGE_MAP()


// CSetSamePage メッセージ ハンドラ


BOOL CSetSamePage::OnSetActive()
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons( PSWIZB_BACK );

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

	LangSetWndTxt( GetDlgItem( IDC_SETPOS_1 )		   , IDS_SETSAME_1 );
	LangSetWndTxt( GetDlgItem( IDC_SETPOS_2 )		   , IDS_SETSAME_2 );
	LangSetWndTxt( GetDlgItem( IDC_SETPOS_3 )		   , IDS_SETSAME_3 );

	LangSetWndTxt( GetDlgItem( IDC_BTN_OPEN_GTMAINTE ) , IDS_BTN_OPEN_GTMAINTE );
	LangSetWndTxt( GetDlgItem( IDC_CHECK_SETPOS_DONE ) , IDS_CHECK_SETSAME_DONE );

	m_bDone = FALSE;
	UpdateData( FALSE );

	return CPropertyPage::OnSetActive();
}

LRESULT CSetSamePage::OnWizardBack()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CSetSamePage::OnWizardNext()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	return pApp->IDDPush( IDD_PLANTEN_FEEDING );
}

void CSetSamePage::OnBnClickedCheckSetposDone()
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

void CSetSamePage::OnBnClickedBtnOpenGtmainte()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	pApp->RunMaintenanceTool();
}
