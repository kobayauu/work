// WhiteHalt.cpp : 実装ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "WhiteHalt.h"
#include "Language.h"

// CWhiteHalt ダイアログ

IMPLEMENT_DYNAMIC(CWhiteHalt, CPropertyPage)

CWhiteHalt::CWhiteHalt()
	: CPropertyPage(CWhiteHalt::IDD)
	, m_rdbtnWhiteUse(0)
{

}

CWhiteHalt::~CWhiteHalt()
{
}

void CWhiteHalt::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_HALT1, m_rdbtnWhiteUse);
}


BEGIN_MESSAGE_MAP(CWhiteHalt, CPropertyPage)
END_MESSAGE_MAP()


// CWhiteHalt メッセージ ハンドラ

BOOL CWhiteHalt::OnSetActive()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	LangSetWndTxt( GetDlgItem( IDC_WHITE_HALT_MSG1 ) , IDS_WHITE_HALT1 );
	LangSetWndTxt( GetDlgItem( IDC_WHITE_HALT_MSG2 ) , IDS_WHITE_HALT2 );
	LangSetWndTxt( GetDlgItem( IDC_RADIO_HALT1 ) , IDS_WHITE_HALT3 );
	LangSetWndTxt( GetDlgItem( IDC_RADIO_HALT2 ) , IDS_WHITE_HALT4 );

	return CPropertyPage::OnSetActive();
}

LRESULT CWhiteHalt::OnWizardBack()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

	return CPropertyPage::OnWizardBack();
}

LRESULT CWhiteHalt::OnWizardNext()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	int nNextID = IDD_IP_CLEAR;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	bool bRet = FALSE;
	int iErr = 0;

	UpdateData(TRUE);

	if (pApp->IsOnline())
	{

		iErr = pApp->SetWhiteHalt(m_rdbtnWhiteUse);
		if (iErr < 0){
			nNextID = -1;
			LangAfxMsgBox(IDS_EER_COMMUNICATION, iErr);
		}

	}
	return pApp->IDDPush( nNextID );
}
