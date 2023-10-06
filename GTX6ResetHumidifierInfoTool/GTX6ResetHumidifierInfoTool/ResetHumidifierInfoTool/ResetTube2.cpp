// ResetTube2.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "ResetTube2.h"
#include "Language.h"
#include ".\resettube2.h"


// CResetTube2 �_�C�A���O

IMPLEMENT_DYNAMIC(CResetTube2, CPropertyPage)
CResetTube2::CResetTube2()
	: CPropertyPage(CResetTube2::IDD)
{
}

CResetTube2::~CResetTube2()
{
}

void CResetTube2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CResetTube2, CPropertyPage)
END_MESSAGE_MAP()


// CResetTube2 ���b�Z�[�W �n���h��

BOOL CResetTube2::OnSetActive()
{
	LangSetWndTxt( GetDlgItem( IDC_RESET_TUBE_2_1 ) , IDS_RESET_TUBE_2_1  );
	LangSetWndTxt( GetDlgItem( IDC_RESET_TUBE_2_2 ) , IDS_CLICK_NEXT );

	return CPropertyPage::OnSetActive();
}

LRESULT CResetTube2::OnWizardNext()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	
	return pApp->IDDPush( IDD_SERV_SEL_OPE );
}

LRESULT CResetTube2::OnWizardBack()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}
