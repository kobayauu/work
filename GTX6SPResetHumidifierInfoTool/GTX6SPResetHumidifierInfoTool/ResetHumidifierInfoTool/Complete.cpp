// Complete.cpp : 実装ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "Complete.h"
#include "Language.h"

// CComplete ダイアログ

IMPLEMENT_DYNAMIC(CComplete, CPropertyPage)

CComplete::CComplete()
	: CPropertyPage(CComplete::IDD)
	, m_csCompleteMsg(_T(""))
{

}

CComplete::~CComplete()
{
}

void CComplete::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_COMPLETE_MSG, m_csCompleteMsg);
}


BEGIN_MESSAGE_MAP(CComplete, CPropertyPage)
END_MESSAGE_MAP()


// CComplete メッセージ ハンドラ
BOOL CComplete::OnSetActive()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	LangSetWndTxt(GetDlgItem(IDC_COMPLETE_MSG), IDS_COMPLETE_MSG);

	UpdateData(TRUE);

	return CPropertyPage::OnSetActive();
}

LRESULT CComplete::OnWizardBack()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}


BOOL CComplete::OnWizardFinish()
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	return CPropertyPage::OnWizardFinish();
}


