// WaitAction.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "WaitAction.h"
#include "Language.h"

// CWaitAction �_�C�A���O

IMPLEMENT_DYNAMIC(CWaitAction, CPropertyPage)

CWaitAction::CWaitAction()
	: CPropertyPage(CWaitAction::IDD)
	, m_csWaitActionMsg1(_T(""))
{

}

CWaitAction::~CWaitAction()
{
}

void CWaitAction::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_WAIT_ACTION_MSG1, m_csWaitActionMsg1);
}


BEGIN_MESSAGE_MAP(CWaitAction, CPropertyPage)
END_MESSAGE_MAP()


// CWaitStCWaitActionandby ���b�Z�[�W �n���h��
BOOL CWaitAction::OnSetActive()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	if (pApp->IDDPeek() == IDD_EEPROM_RESTORE1){
		LangSetWndTxt(GetDlgItem(IDC_WAIT_ACTION_MSG1), IDS_WAIT_ACTION_MSG1_1);
	}
	else if (pApp->IDDPeek() == IDD_SET_18CODE) {
		LangSetWndTxt(GetDlgItem(IDC_WAIT_ACTION_MSG1), IDS_WAIT_ACTION_MSG2_1);
	}
	else if (pApp->IDDPeek() == IDD_UPDATE_FIRM) {
		pSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);

		LangSetWndTxt(GetDlgItem(IDC_WAIT_ACTION_MSG1), IDS_WAIT_ACTION_MSG3_1);
	}

	UpdateData(TRUE);

	return CPropertyPage::OnSetActive();
}

LRESULT CWaitAction::OnWizardBack()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}


LRESULT CWaitAction::OnWizardNext()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	int nNextID = IDD_SET_18CODE;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	if (pApp->IDDPeek() == IDD_EEPROM_RESTORE1) {
		nNextID = IDD_SET_18CODE;
	}
	else if (pApp->IDDPeek() == IDD_SET_18CODE) {
		nNextID = IDD_UPDATE_FIRM;
	}

	return pApp->IDDPush( nNextID );
}

BOOL CWaitAction::OnWizardFinish()
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	return CPropertyPage::OnWizardFinish();
}


