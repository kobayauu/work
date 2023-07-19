// BatteryChg1.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "BatteryChg1.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBatteryChg1 �v���p�e�B �y�[�W

IMPLEMENT_DYNCREATE(CBatteryChg1, CPropertyPage)

CBatteryChg1::CBatteryChg1() : CPropertyPage(CBatteryChg1::IDD)
{
	//{{AFX_DATA_INIT(CBatteryChg1)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�̏�����������ǉ����܂��B
	//}}AFX_DATA_INIT
}

CBatteryChg1::~CBatteryChg1()
{
}

void CBatteryChg1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBatteryChg1)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBatteryChg1, CPropertyPage)
	//{{AFX_MSG_MAP(CBatteryChg1)
		// ����: ClassWizard �͂��̈ʒu�� DDX ����� DDV �̌Ăяo���R�[�h��ǉ����܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBatteryChg1 ���b�Z�[�W �n���h��

BOOL CBatteryChg1::OnQueryCancel() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	BOOL bRet = FALSE;
	if( LangCancelYesNoMsgBox() == IDYES )
	{
		bRet = TRUE;
	}
	return bRet;
}

BOOL CBatteryChg1::OnSetActive() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	//pApp->Log( _T("Battery Change Step 1 Page") );
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

	LangSetWndTxt( GetDlgItem( IDC_CHANGE_BATTERY1_1 ) , IDS_CHANGE_BATTERY1_1 );

	return CPropertyPage::OnSetActive();
}

LRESULT CBatteryChg1::OnWizardBack() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CBatteryChg1::OnWizardNext() 
{
	LRESULT nNextID = IDD_SERV_CHNAGE_BATTERY2;

	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	CWaitCursor wc;

	m_dwChangedDate = (DWORD)pApp->GetCurrentGMTSecond();

	if( pApp->IsOnline())
	{
		int iRet = BatteryChangedInfoSetToPrinter();

		if( iRet < 0 )
		{
			LangAfxMsgBox( IDS_EER_COMMUNICATION , iRet );
			nNextID = -1;
		}
	}

	return pApp->IDDPush( nNextID );
}

//�o�b�e���[�������̃Z�b�g
int CBatteryChg1::BatteryChangedInfoSetToPrinter()
{
	int iRet = 0;

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	iRet = pApp->ResetBattery();

	return iRet;
}


