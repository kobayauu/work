// AdjThermis.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "AdjThermis.h"
#include "Language.h"
#include ".\adjthermis.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdjThermis �v���p�e�B �y�[�W

IMPLEMENT_DYNCREATE(CAdjThermis, CPropertyPage)

CAdjThermis::CAdjThermis() : CPropertyPage(CAdjThermis::IDD)
, m_bWait5Minutes(FALSE)
{
	//{{AFX_DATA_INIT(CAdjThermis)
	//}}AFX_DATA_INIT
}

CAdjThermis::~CAdjThermis()
{
}

void CAdjThermis::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdjThermis)
	//}}AFX_DATA_MAP
	DDX_Check(pDX, IDC_CHECK_5MINUTES, m_bWait5Minutes);
}


BEGIN_MESSAGE_MAP(CAdjThermis, CPropertyPage)
	//{{AFX_MSG_MAP(CAdjThermis)
		// ����: ClassWizard �͂��̈ʒu�� DDX ����� DDV �̌Ăяo���R�[�h��ǉ����܂��B
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_CHECK_5MINUTES, OnBnClickedCheck5minutes)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdjThermis ���b�Z�[�W �n���h��

BOOL CAdjThermis::OnSetActive() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	//pApp->Log( _T("Adj Thermistor Step 1 Page") );
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

	LangSetWndTxt( GetDlgItem( IDC_ADJ_THERMIS01_01 ) , IDS_ADJ_THERMIS01_01 );

	if( pApp->GetCourse() == COURSE_MAIN_BOARD_CHANGE )
	{//Main�����
		LangSetWndTxt( GetDlgItem( IDC_CHECK_5MINUTES ) , IDS_ADJ_THERMIS01_DONE_CR );
	}else
	{//CR�����
		LangSetWndTxt( GetDlgItem( IDC_CHECK_5MINUTES ) , IDS_ADJ_THERMIS01_CHECK );
	}

	pSheet->SetWizardButtons( PSWIZB_BACK );

	m_bWait5Minutes = FALSE;

	UpdateData( FALSE );
	return CPropertyPage::OnSetActive();
}

LRESULT CAdjThermis::OnWizardNext() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	UpdateData( TRUE );
	LRESULT nNextID = IDD_SERV_ADJ_THERMIS02;
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	
	return pApp->IDDPush( nNextID );

}

LRESULT CAdjThermis::OnWizardBack() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

BOOL CAdjThermis::OnQueryCancel() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	BOOL bRet = FALSE;
	if( LangCancelYesNoMsgBox() == IDYES )
	{
		bRet = TRUE;
	}
	return bRet;
}

void CAdjThermis::OnBnClickedCheck5minutes()
{
	UpdateData( TRUE );

	CPropertySheet* pSheet = (CPropertySheet*)GetParent();

	if( m_bWait5Minutes )
	{
		pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT );
	}else
	{
		pSheet->SetWizardButtons( PSWIZB_BACK );
	}
}
