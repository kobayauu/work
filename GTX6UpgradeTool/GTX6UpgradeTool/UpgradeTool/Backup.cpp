// Backup.cpp : 実装ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "Backup.h"
#include "Language.h"

// CBackup ダイアログ

IMPLEMENT_DYNAMIC(CBackup, CPropertyPage)

CBackup::CBackup()
	: CPropertyPage(CBackup::IDD)
	, m_csBackupMsg1(_T(""))
{

}

CBackup::~CBackup()
{
}

void CBackup::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BACKUP_MSG1, m_csBackupMsg1);
}


BEGIN_MESSAGE_MAP(CBackup, CPropertyPage)
END_MESSAGE_MAP()


// CBackup メッセージ ハンドラ
BOOL CBackup::OnSetActive()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	if (pApp->IDDPeek() == IDD_EEPROM_RESTORE1){
		LangSetWndTxt(GetDlgItem(IDC_BACKUP_MSG1), IDS_EERPOM_BACKUP);
	}else if (pApp->IDDPeek() == IDD_SET_IP || pApp->GetCourse() == COURSE_LCD_BOARD){
		LangSetWndTxt(GetDlgItem(IDC_BACKUP_MSG1), IDS_EEPROM_BACKUP1_2);
	}

	UpdateData(TRUE);

	return CPropertyPage::OnSetActive();
}

LRESULT CBackup::OnWizardBack()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}


LRESULT CBackup::OnWizardNext()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	int nNextID = IDD_SERV_SEL_OPE;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	BOOL bRet = FALSE;
	int iErr = 0;

	if (pApp->IsOnline()) {
		iErr = pApp->BackupEEPROM();
		if (iErr < 0) {
			nNextID = -1;
			LangAfxMsgBox(IDS_EER_COMMUNICATION, -191);
		}
	}

	return pApp->IDDPush( nNextID );
}

