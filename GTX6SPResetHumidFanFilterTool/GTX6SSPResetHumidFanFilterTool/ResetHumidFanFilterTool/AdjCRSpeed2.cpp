// AdjCRSpeed2.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "AdjCRSpeed2.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdjCRSpeed2 �v���p�e�B �y�[�W

IMPLEMENT_DYNCREATE(CAdjCRSpeed2, CPropertyPage)

CAdjCRSpeed2::CAdjCRSpeed2() : CPropertyPage(CAdjCRSpeed2::IDD)
{
	//{{AFX_DATA_INIT(CAdjCRSpeed2)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�̏�����������ǉ����܂��B
	//}}AFX_DATA_INIT
}

CAdjCRSpeed2::~CAdjCRSpeed2()
{
}

void CAdjCRSpeed2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdjCRSpeed2)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdjCRSpeed2, CPropertyPage)
	//{{AFX_MSG_MAP(CAdjCRSpeed2)
		// ����: ClassWizard �͂��̈ʒu�� DDX ����� DDV �̌Ăяo���R�[�h��ǉ����܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdjCRSpeed2 ���b�Z�[�W �n���h��

BOOL CAdjCRSpeed2::OnSetActive() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

	LangSetWndTxt( GetDlgItem( IDC_ADJ_CR_SPEED2_1 ) , IDS_ADJ_CR_SPEED2_1 );
	
	UpdateData( FALSE );
	return CPropertyPage::OnSetActive();
}

LRESULT CAdjCRSpeed2::OnWizardBack() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CAdjCRSpeed2::OnWizardNext() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	LRESULT nNextID = IDD_SERV_SEL_OPE;
	switch( pApp->GetCourse() )
	{
	case COURSE_INIT_SETTING:
		//nNextID = IDD_SERV_SET_LOG1;
		break;
	case COURSE_MAIN_BOARD_CHANGE:
	//	nNextID = IDD_FIRE1;
		nNextID = IDD_VRATING;
		break;
	default:
		nNextID = IDD_SERV_SEL_OPE;
		break;
	}
	return pApp->IDDPush( nNextID );
}
