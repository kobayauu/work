// WhiteHalt.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "WhiteHalt.h"
#include "Language.h"

// CWhiteHalt �_�C�A���O

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


// CWhiteHalt ���b�Z�[�W �n���h��

BOOL CWhiteHalt::OnSetActive()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	LangSetWndTxt( GetDlgItem( IDC_WHITE_HALT_MSG1 ) , IDS_WHITE_HALT1 );
	LangSetWndTxt( GetDlgItem( IDC_WHITE_HALT_MSG2 ) , IDS_WHITE_HALT2 );
	LangSetWndTxt( GetDlgItem( IDC_RADIO_HALT1 ) , IDS_WHITE_HALT3 );
	LangSetWndTxt( GetDlgItem( IDC_RADIO_HALT2 ) , IDS_WHITE_HALT4 );

	return CPropertyPage::OnSetActive();
}

LRESULT CWhiteHalt::OnWizardBack()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B

	return CPropertyPage::OnWizardBack();
}

LRESULT CWhiteHalt::OnWizardNext()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
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
