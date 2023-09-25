// MainBoardBranch.cpp : 実装ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "MainBoardBranch.h"
#include "Language.h"

// CMainBoardBranch ダイアログ

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


// CMainBoardBranch メッセージ ハンドラ
BOOL CMainBoardBranch::OnSetActive()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
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
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CMainBoardBranch::OnWizardNext()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
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


