// Complete.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "Complete.h"
#include "Language.h"

// CComplete �_�C�A���O

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


// CComplete ���b�Z�[�W �n���h��
BOOL CComplete::OnSetActive()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_FINISH);

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	LangSetWndTxt(GetDlgItem(IDC_COMPLETE_MSG), IDS_COMPLETE_MSG);

	UpdateData(TRUE);

	return CPropertyPage::OnSetActive();
}

LRESULT CComplete::OnWizardBack()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}


BOOL CComplete::OnWizardFinish()
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	return CPropertyPage::OnWizardFinish();
}


