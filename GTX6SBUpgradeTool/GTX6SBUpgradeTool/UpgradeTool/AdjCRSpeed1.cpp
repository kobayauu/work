// AdjCRSpeed1.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "AdjCRSpeed1.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdjCRSpeed1 �v���p�e�B �y�[�W

IMPLEMENT_DYNCREATE(CAdjCRSpeed1, CPropertyPage)

CAdjCRSpeed1::CAdjCRSpeed1() : CPropertyPage(CAdjCRSpeed1::IDD)
{
	//{{AFX_DATA_INIT(CAdjCRSpeed1)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�̏�����������ǉ����܂��B
	//}}AFX_DATA_INIT
}

CAdjCRSpeed1::~CAdjCRSpeed1()
{
}

void CAdjCRSpeed1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdjCRSpeed1)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdjCRSpeed1, CPropertyPage)
	//{{AFX_MSG_MAP(CAdjCRSpeed1)
		// ����: ClassWizard �͂��̈ʒu�� DDX ����� DDV �̌Ăяo���R�[�h��ǉ����܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdjCRSpeed1 ���b�Z�[�W �n���h��

BOOL CAdjCRSpeed1::OnQueryCancel() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	BOOL bRet = FALSE;
	if( LangCancelYesNoMsgBox() == IDYES )
	{
		bRet = TRUE;
	}
	return bRet;
}

BOOL CAdjCRSpeed1::OnSetActive() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

	LangSetWndTxt( GetDlgItem( IDC_ADJ_CR_SPEED1_1 ) , IDS_ADJ_CR_SPEED1_1 );
	
	UpdateData( FALSE );
	return CPropertyPage::OnSetActive();
}

LRESULT CAdjCRSpeed1::OnWizardBack() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CAdjCRSpeed1::OnWizardNext() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	UpdateData( TRUE );
	LRESULT nNextID = IDD_SERV_ADJ_CR_SPEED2;
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	int iErr = 0;

	if( pApp->IsOnline() )
	{
		iErr = pApp->AdjustCRSpeed();
		if( iErr < 0 ){
			LangAfxMsgBox(IDS_EER_COMMUNICATION, -191);
			return -1;
		}
	}
	return pApp->IDDPush( nNextID );
	//return CPropertyPage::OnWizardNext();
}
