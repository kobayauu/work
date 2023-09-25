// HumidFanFilter.cpp : 実装ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "HumidFanFilter.h"
#include "Language.h"

// HumidFanFilter ダイアログ

IMPLEMENT_DYNAMIC(CHumidFanFilter, CPropertyPage)

CHumidFanFilter::CHumidFanFilter() : CPropertyPage(CHumidFanFilter::IDD)
{

}

CHumidFanFilter::~CHumidFanFilter()
{
}

void CHumidFanFilter::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHumidFanFilter, CPropertyPage)
END_MESSAGE_MAP()


// CHumidFanFilter メッセージ ハンドラ
BOOL CHumidFanFilter::OnSetActive()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	//CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);

	LangSetWndTxt(GetDlgItem(IDC_HUMIDFAN_MSG1), IDS_HUMIDFAN_MSG1);

	UpdateData(TRUE);

	return CPropertyPage::OnSetActive();
}

LRESULT CHumidFanFilter::OnWizardBack()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}


LRESULT CHumidFanFilter::OnWizardNext()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	//int nNextID = IDD_SERV_SEL_OPE;
	int nNextID = IDD_COMPLETE;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	BOOL bRet = FALSE;
	int iErr = 0;

	if (pApp->IsOnline()) {
		iErr = pApp->ResetHumidFanFilter();
		if (iErr != 0) {
			nNextID = -1;
			LangAfxMsgBox(IDS_EER_COMMUNICATION, -191);
		}
	}
	return pApp->IDDPush(nNextID);
}


