// InAdvanceMain.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "InAdvanceMain.h"
#include ".\inadvancemain.h"
#include "Language.h"

// CInAdvanceMain �_�C�A���O

IMPLEMENT_DYNAMIC(CInAdvanceMain, CPropertyPage)
CInAdvanceMain::CInAdvanceMain()
	: CPropertyPage(CInAdvanceMain::IDD)
{
}

CInAdvanceMain::~CInAdvanceMain()
{
}

void CInAdvanceMain::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInAdvanceMain, CPropertyPage)
END_MESSAGE_MAP()


// CInAdvanceMain ���b�Z�[�W �n���h��

BOOL CInAdvanceMain::OnSetActive()
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT );

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

	LangSetWndTxt( GetDlgItem( IDC_IN_ADVANCE_MAIN_1_1 ) , IDS_IN_ADVANCE_MAIN_1_1 );

	return CPropertyPage::OnSetActive();
}

LRESULT CInAdvanceMain::OnWizardBack()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	return pApp->IDDPop();
}

LRESULT CInAdvanceMain::OnWizardNext()
{
	int nNextPage = IDD_SERV_FIRST;//IDD_LEFT_OR_RIGHT;

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	return pApp->IDDPush( nNextPage );
}
