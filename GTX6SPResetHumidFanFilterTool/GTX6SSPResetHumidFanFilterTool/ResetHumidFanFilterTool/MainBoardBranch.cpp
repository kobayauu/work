// MainBoardBranch.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "MainBoardBranch.h"
#include "Language.h"

// CMainBoardBranch �_�C�A���O

IMPLEMENT_DYNAMIC(CMainBoardBranch, CPropertyPage)

CMainBoardBranch::CMainBoardBranch()
	: CPropertyPage(CMainBoardBranch::IDD)
	, m_rdbtnMBBranchSelect(0)
{

}

CMainBoardBranch::~CMainBoardBranch()
{
}

void CMainBoardBranch::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_rdbtnMBBranchSelect);
}


BEGIN_MESSAGE_MAP(CMainBoardBranch, CPropertyPage)
END_MESSAGE_MAP()


// CMainBoardBranch ���b�Z�[�W �n���h��
BOOL CMainBoardBranch::OnSetActive()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

	LangSetWndTxt( GetDlgItem( IDC_STATIC ) , IDS_MAIN_BOARD_BRANCH1_1 );
	LangSetWndTxt( GetDlgItem( IDC_RADIO1 ) , IDS_MAIN_BOARD_BRANCH1_2 );
	LangSetWndTxt( GetDlgItem( IDC_RADIO2 ) , IDS_MAIN_BOARD_BRANCH1_3 );

	UpdateData(FALSE);

	return CPropertyPage::OnSetActive();
}


LRESULT CMainBoardBranch::OnWizardBack()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CMainBoardBranch::OnWizardNext()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	int nNextID = IDD_MAIN_BOARD_BRANCH;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	
	UpdateData(TRUE);

	if(m_rdbtnMBBranchSelect == 0){
		nNextID = IDD_EEPROM_RESTORE1;
	}else if(m_rdbtnMBBranchSelect == 1){
		nNextID = IDD_RTC_SET_AND_RESET_EEPROM;
	}

	return pApp->IDDPush( nNextID );
}


