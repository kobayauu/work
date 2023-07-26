// Vrating.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "Vrating.h"
#include "Language.h"

// CVrating �_�C�A���O

IMPLEMENT_DYNAMIC(CVrating, CPropertyPage)

CVrating::CVrating()
	: CPropertyPage(CVrating::IDD)
{

}

CVrating::~CVrating()
{
}

void CVrating::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CHECK_VRATING_DONE, m_chkbxVratingConfirm);
}


BEGIN_MESSAGE_MAP(CVrating, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_OPEN_VRATING, &CVrating::OnBnClickedBtnOpenVrating)
	ON_BN_CLICKED(IDC_CHECK_VRATING_DONE, &CVrating::OnBnClickedCheckVratingDone)
END_MESSAGE_MAP()


// CVrating ���b�Z�[�W �n���h��

BOOL CVrating::OnSetActive()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons( PSWIZB_BACK);

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	LangSetWndTxt( GetDlgItem( IDC_VRATING1 ) , IDS_VRATING1 );
	LangSetWndTxt( GetDlgItem( IDC_VRATING2 ) , IDS_VRATING2 );
	LangSetWndTxt( GetDlgItem( IDC_VRATING3 ) , IDS_VRATING3 );
	LangSetWndTxt( GetDlgItem( IDC_BTN_OPEN_VRATING ) , IDS_BTN_OPEN_GTMAINTE );
	LangSetWndTxt( GetDlgItem( IDC_CHECK_VRATING_DONE ) , IDS_VRATING4 );

	m_chkbxVratingConfirm.SetCheck(FALSE);

	UpdateData( FALSE );

	return CPropertyPage::OnSetActive();
}

LRESULT CVrating::OnWizardBack()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CVrating::OnWizardNext()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	int nNextID = IDD_FIRE1;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	return pApp->IDDPush( nNextID );
}

void CVrating::OnBnClickedBtnOpenVrating()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	pApp->RunMaintenanceTool();
}

void CVrating::OnBnClickedCheckVratingDone()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	UpdateData( TRUE );

	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	
	if( m_chkbxVratingConfirm.GetCheck() )
	{
		pSheet->SetWizardButtons( PSWIZB_NEXT | PSWIZB_BACK );
	}else
	{
		pSheet->SetWizardButtons( PSWIZB_BACK );
	}
}
