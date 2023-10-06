// SetIpPage.cpp : 実装ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "SetIpPage.h"
#include "Language.h"


// CSetIpPage ダイアログ

IMPLEMENT_DYNAMIC(CSetIpPage, CPropertyPage)

CSetIpPage::CSetIpPage()
	: CPropertyPage(CSetIpPage::IDD)
	, m_bDone(FALSE)
{

}

CSetIpPage::~CSetIpPage()
{
}

void CSetIpPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_SETIP_DONE, m_bDone);
}


BEGIN_MESSAGE_MAP(CSetIpPage, CPropertyPage)
	ON_BN_CLICKED(IDC_CHECK_SETIP_DONE, OnBnClickedCheckSetipDone)
	ON_BN_CLICKED(IDC_BTN_OPEN_GTMAINTE, OnBnClickedBtnOpenGtmainte)
END_MESSAGE_MAP()


// CSetIpPage メッセージ ハンドラ


BOOL CSetIpPage::OnSetActive()
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons( PSWIZB_BACK );

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	LangSetWndTxt( GetDlgItem( IDC_SETIP_1 )		   , IDS_SETIP_1 );
	LangSetWndTxt( GetDlgItem( IDC_SETIP_2 )		   , IDS_SETIP_2 );

	LangSetWndTxt( GetDlgItem( IDC_BTN_OPEN_GTMAINTE ) , IDS_BTN_OPEN_GTMAINTE );
	LangSetWndTxt( GetDlgItem( IDC_CHECK_SETIP_DONE )  , IDS_CHECK_SETIP_DONE );

	m_bDone = FALSE;
	UpdateData( FALSE );

	return CPropertyPage::OnSetActive();
}

LRESULT CSetIpPage::OnWizardBack()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CSetIpPage::OnWizardNext()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	
	return pApp->IDDPush( IDD_BACKUP );
}

void CSetIpPage::OnBnClickedCheckSetipDone()
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

void CSetIpPage::OnBnClickedBtnOpenGtmainte()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	pApp->RunMaintenanceTool();
}
