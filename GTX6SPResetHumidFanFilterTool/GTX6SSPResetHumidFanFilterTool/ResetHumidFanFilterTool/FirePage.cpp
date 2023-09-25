// FirePage.cpp : 実装ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "FirePage.h"
#include ".\firepage.h"
#include "Language.h"

// CFirePage ダイアログ

IMPLEMENT_DYNAMIC(CFirePage, CPropertyPage)
CFirePage::CFirePage()
	: CPropertyPage(CFirePage::IDD)
	, m_bDone(FALSE)
{
}

CFirePage::~CFirePage()
{
}

void CFirePage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_FIRE_DONE, m_bDone);
}


BEGIN_MESSAGE_MAP(CFirePage, CPropertyPage)
	ON_BN_CLICKED(IDC_CHECK_FIRE_DONE, OnBnClickedCheckFireDone)
	ON_BN_CLICKED(IDC_BTN_OPEN_GTMAINTE, OnBnClickedBtnOpenGtmainte)
END_MESSAGE_MAP()


// CFirePage メッセージ ハンドラ

BOOL CFirePage::OnSetActive()
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons( PSWIZB_BACK );

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

/*	if( pApp->GetSide() == SIDE_LEFT )
	{
		LangSetWndTxt( GetDlgItem( IDC_FIRE_1_1 ) , IDS_FIRE_1_1_LEFT );

	}else if( pApp->GetSide() == SIDE_RIGHT ) 
	{
		LangSetWndTxt( GetDlgItem( IDC_FIRE_1_1 ) , IDS_FIRE_1_1_RIGHT );

	}else	*/
	{//Both
		LangSetWndTxt( GetDlgItem( IDC_FIRE_1_1 ) , IDS_FIRE_1_1_BOTH );
	}

	
	LangSetWndTxt( GetDlgItem( IDC_FIRE_1_2 )		   , IDS_FIRE_1_2 );
	LangSetWndTxt( GetDlgItem( IDC_FIRE_1_3 )		   , IDS_FIRE_1_3 );
	LangSetWndTxt( GetDlgItem( IDC_BTN_OPEN_GTMAINTE ) , IDS_BTN_OPEN_GTMAINTE );
	LangSetWndTxt( GetDlgItem( IDC_CHECK_FIRE_DONE )   , IDS_CHECK_FIRE_DONE );

	m_bDone = FALSE;
	UpdateData( FALSE );

	return CPropertyPage::OnSetActive();
}

LRESULT CFirePage::OnWizardBack()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CFirePage::OnWizardNext()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	return pApp->IDDPush( IDD_SET_SAME );
}

void CFirePage::OnBnClickedCheckFireDone()
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

void CFirePage::OnBnClickedBtnOpenGtmainte()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	pApp->RunMaintenanceTool();
}
