// SetColorPage.cpp : 実装ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "SetColorPage.h"
#include "Language.h"


// CSetColorPage ダイアログ

IMPLEMENT_DYNAMIC(CSetColorPage, CPropertyPage)

CSetColorPage::CSetColorPage()
	: CPropertyPage(CSetColorPage::IDD)
	, m_bDone(FALSE)
{
}

CSetColorPage::~CSetColorPage()
{
}

void CSetColorPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_SETPOS_DONE, m_bDone);
}


BEGIN_MESSAGE_MAP(CSetColorPage, CPropertyPage)
	ON_BN_CLICKED(IDC_CHECK_SETPOS_DONE, OnBnClickedCheckSetposDone)
	ON_BN_CLICKED(IDC_BTN_OPEN_GTMAINTE, OnBnClickedBtnOpenGtmainte)
END_MESSAGE_MAP()


// CSetColorPage メッセージ ハンドラ


BOOL CSetColorPage::OnSetActive()
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons( PSWIZB_BACK );

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

	LangSetWndTxt( GetDlgItem( IDC_SETPOS_1 )		   , IDS_SETCOLOR_1 );
	LangSetWndTxt( GetDlgItem( IDC_SETPOS_2 )		   , IDS_SETCOLOR_2 );
	LangSetWndTxt( GetDlgItem( IDC_SETPOS_3 )		   , IDS_SETCOLOR_3 );

	LangSetWndTxt( GetDlgItem( IDC_BTN_OPEN_GTMAINTE ) , IDS_BTN_OPEN_GTMAINTE );
	LangSetWndTxt( GetDlgItem( IDC_CHECK_SETPOS_DONE ) , IDS_CHECK_SETCOLOR_DONE );

	m_bDone = FALSE;
	UpdateData( FALSE );

	return CPropertyPage::OnSetActive();
}

LRESULT CSetColorPage::OnWizardBack()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CSetColorPage::OnWizardNext()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	return pApp->IDDPush( IDD_FIRE1 );
}

void CSetColorPage::OnBnClickedCheckSetposDone()
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

void CSetColorPage::OnBnClickedBtnOpenGtmainte()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	pApp->RunMaintenanceTool();
}
