// UpdateFirm.cpp : 実装ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "UpdateFirm.h"
#include "Language.h"

// CUpdateFirm ダイアログ

IMPLEMENT_DYNAMIC(CUpdateFirm, CPropertyPage)

CUpdateFirm::CUpdateFirm()
	: CPropertyPage(CUpdateFirm::IDD)
{

}

CUpdateFirm::~CUpdateFirm()
{
}

void CUpdateFirm::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_UPD_FIRM_DONE, m_chkbxUpdateFirmConfirm);
}


BEGIN_MESSAGE_MAP(CUpdateFirm, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_OPEN_FIRMUPDATE, &CUpdateFirm::OnBnClickedBtnOpenFirmUpdate)
	ON_BN_CLICKED(IDC_CHECK_UPD_FIRM_DONE, &CUpdateFirm::OnBnClickedCheckUpdateFirmDone)
END_MESSAGE_MAP()


// CUpdateFirm メッセージ ハンドラ

BOOL CUpdateFirm::OnSetActive()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons( PSWIZB_BACK);

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	if (pApp->IDDPeek() == IDD_UPG_PSEL) {
		LangSetWndTxt( GetDlgItem( IDC_UPD_FIRM_MSG1 ) , IDS_UPD_FIRM_MSG1_1 );
		LangSetWndTxt( GetDlgItem( IDC_UPD_FIRM_MSG2 ) , IDS_UPD_FIRM_MSG2_1 );
		LangSetWndTxt( GetDlgItem( IDC_BTN_OPEN_FIRMUPDATE ) , IDS_BTN_OPEN_GTFIRM1_1 );
		LangSetWndTxt( GetDlgItem( IDC_CHECK_UPD_FIRM_DONE ) , IDS_UPD_FIRM_MSG3_1 );
	}
	else if (pApp->IDDPeek() == IDD_WAIT_ACTION) {
		LangSetWndTxt( GetDlgItem( IDC_UPD_FIRM_MSG1 ), IDS_UPD_FIRM_MSG1_2 );
		LangSetWndTxt( GetDlgItem( IDC_UPD_FIRM_MSG2 ), IDS_UPD_FIRM_MSG2_2 );
		LangSetWndTxt( GetDlgItem( IDC_BTN_OPEN_FIRMUPDATE ), IDS_BTN_OPEN_GTFIRM1_2 );
		LangSetWndTxt( GetDlgItem( IDC_CHECK_UPD_FIRM_DONE ), IDS_UPD_FIRM_MSG3_2 );
	}

	m_chkbxUpdateFirmConfirm.SetCheck(FALSE);

	UpdateData( FALSE );

	return CPropertyPage::OnSetActive();
}

LRESULT CUpdateFirm::OnWizardBack()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CUpdateFirm::OnWizardNext()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	int nNextID = IDD_EEPROM_RESTORE1;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	if (pApp->IDDPeek() == IDD_UPG_PSEL) {
		nNextID = IDD_EEPROM_RESTORE1;

		// Ver2.00以上でないと次へ進めない
		if (pApp->IsOnline()) {
			int iRet = pApp->CheckVersion(VALID_FIRM_VER);

			if (iRet != 0) {
				if (iRet == -1) {
					LangAfxMsgBox(IDS_EER_FIRM_VER, -101);
					return -1;
				}
				else {
					LangAfxMsgBox(IDS_EER_COMMUNICATION, -191);
					return -1;
				}
			}
		}
	}
	else if (pApp->IDDPeek() == IDD_WAIT_ACTION) {
		nNextID = IDD_WAIT_ACTION;
	}

	return pApp->IDDPush( nNextID );
}

void CUpdateFirm::OnBnClickedBtnOpenFirmUpdate()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	if (pApp->IDDPeek() == IDD_UPG_PSEL) {
		pApp->RunFirmUpdate_GTX6();
	}
	else if (pApp->IDDPeek() == IDD_WAIT_ACTION) {
		pApp->RunFirmUpdate_GTX6SP();
	}
}

void CUpdateFirm::OnBnClickedCheckUpdateFirmDone()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	UpdateData( TRUE );

	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	
	if( m_chkbxUpdateFirmConfirm.GetCheck() )
	{
		pSheet->SetWizardButtons( PSWIZB_NEXT | PSWIZB_BACK );
	}else
	{
		pSheet->SetWizardButtons( PSWIZB_BACK );
	}
}

