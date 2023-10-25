// IPClear.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "IPClear.h"
#include "Language.h"

// CIPClear �_�C�A���O

IMPLEMENT_DYNAMIC(CIPClear, CPropertyPage)

CIPClear::CIPClear()
	: CPropertyPage(CIPClear::IDD)
	, m_txtIPClear(_T(""))
{

}

CIPClear::~CIPClear()
{
}

void CIPClear::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_IP_CLEAR_MSG1, m_txtIPClear);
}


BEGIN_MESSAGE_MAP(CIPClear, CPropertyPage)
END_MESSAGE_MAP()


// CIPClear ���b�Z�[�W �n���h��

BOOL CIPClear::OnSetActive()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);

	LangSetWndTxt( GetDlgItem( IDC_IP_CLEAR_MSG1 ) , IDS_IP_CLEAR1 );
	return CPropertyPage::OnSetActive();
}

LRESULT CIPClear::OnWizardBack()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CIPClear::OnWizardNext()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	int nNextID = IDD_BARCODE;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	bool bRet = false;
	int iErr = 0;

	if (pApp->IsOnline())
	{
		iErr = pApp->ResetIpAddress();

		if (iErr != 0)
		{
			nNextID = -1;
			LangAfxMsgBox(IDS_EER_COMMUNICATION, -191);
		}
		else {
			nNextID = IDD_BARCODE;
		}
	}
	return pApp->IDDPush( nNextID );
}
