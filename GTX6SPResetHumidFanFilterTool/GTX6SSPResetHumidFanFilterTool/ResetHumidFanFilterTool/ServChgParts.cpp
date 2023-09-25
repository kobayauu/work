// ServChgParts.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "ServChgParts.h"
#include ".\servchgparts.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServChgParts �v���p�e�B �y�[�W

IMPLEMENT_DYNCREATE(CServChgParts, CPropertyPage)

CServChgParts::CServChgParts() : CPropertyPage(CServChgParts::IDD)
{
	//{{AFX_DATA_INIT(CServChgParts)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�̏�����������ǉ����܂��B
	//}}AFX_DATA_INIT
}

CServChgParts::~CServChgParts()
{
}

void CServChgParts::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServChgParts)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CServChgParts, CPropertyPage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServChgParts ���b�Z�[�W �n���h��

BOOL CServChgParts::OnSetActive() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	//pApp->Log( _T("Serv Change Parts select Page") );
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

	LangSetWndTxt( GetDlgItem( IDC_SELECTMENU )		   , IDS_SELECTMENU		);
	LangSetWndTxt( GetDlgItem( IDC_RADIO_HEAD )		   , IDS_HEADS			);
	LangSetWndTxt( GetDlgItem( IDC_RADIO_CR_ADJ )	   , IDS_CR_ADJ			);
	LangSetWndTxt( GetDlgItem( IDC_RADIO_BATTERY )	   , IDS_BATTERY		);
	LangSetWndTxt( GetDlgItem( IDC_RADIO_CR_BOARD )    , IDS_CR_BOARD		);
	LangSetWndTxt( GetDlgItem( IDC_RADIO_MAIN_BOARD )  , IDS_MAIN_BOARD		);
	LangSetWndTxt( GetDlgItem( IDC_RADIO_CR_MOTOR2 )   , IDS_RADIO_CR_MOTOR );
	LangSetWndTxt( GetDlgItem( IDC_RADIO_PUMP )        , IDS_TUBE_PUMP      );
	LangSetWndTxt( GetDlgItem( IDC_RADIO_LCD_BOARD)	   , IDS_LCD_BOARD		);
	LangSetWndTxt( GetDlgItem( IDC_RADIO_HUMID_FAN)    , IDS_HUMID_FAN		);

	return CPropertyPage::OnSetActive();
}

LRESULT CServChgParts::OnWizardBack() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
	//return CPropertyPage::OnWizardBack();
}

LRESULT CServChgParts::OnWizardNext() 
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	LRESULT nNextID = -1;
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	TCHAR* pszSelect = _T("");

	switch( GetCheckedRadioID() )
	{
	case IDC_RADIO_HEAD:
		pApp->SetCourse( COURCE_FIRING_ADJUST );
		nNextID = IDD_SERV_FIRST;	//IDD_LEFT_OR_RIGHT;
		break;
/*	case IDC_RADIO_CR_BOARD:
		pApp->SetCourse( COURSE_CR_BOARD_CHANGE );
		nNextID = IDD_SERV_FIRST;//���E�w��͖���
		break;*/
	case IDC_RADIO_MAIN_BOARD:
		pApp->SetCourse( COURSE_MAIN_BOARD_CHANGE );
//		nNextID = IDD_IN_ADVANCE_MAIN;
		nNextID = IDD_SERV_FIRST;
		break;
	case IDC_RADIO_BATTERY:
		pApp->SetCourse( COURSE_BATTERY_CHANGE );
		nNextID = IDD_SERV_FIRST;//IDD_LEFT_OR_RIGHT;
		break;
	case IDC_RADIO_CR_ADJ:
		pApp->SetCourse( COURSE_CR_ADJ );
		nNextID = IDD_SERV_FIRST;//���E�w��͖���
		break;
/*	case IDC_RADIO_CR_MOTOR2:
		pApp->SetCourse( COURSE_CR_MOTOR );
		nNextID = IDD_SERV_FIRST;//IDD_LEFT_OR_RIGHT;
		break;*/
	case IDC_RADIO_PUMP:
		pApp->SetCourse( COURSE_PUMP_CHANGE );
		nNextID = IDD_SERV_FIRST;
		break;
	case IDC_RADIO_LCD_BOARD:
		pApp->SetCourse( COURSE_LCD_BOARD );
		nNextID = IDD_SERV_FIRST;
		break;
	case IDC_RADIO_HUMID_FAN:
		pApp->SetCourse(COURSE_HUMID_FAN);
		nNextID = IDD_SERV_FIRST;
		break;
	}
	return pApp->IDDPush( nNextID );	
}

int CServChgParts::GetCheckedRadioID()
{
	int iID = IDC_RADIO_HEAD;

//	if( ((CButton*)GetDlgItem(IDC_RADIO_CR_BOARD))->GetCheck() )	iID = IDC_RADIO_CR_BOARD;
	if( ((CButton*)GetDlgItem(IDC_RADIO_MAIN_BOARD))->GetCheck() )	iID = IDC_RADIO_MAIN_BOARD;
	if( ((CButton*)GetDlgItem(IDC_RADIO_BATTERY))->GetCheck() )		iID = IDC_RADIO_BATTERY;
	if( ((CButton*)GetDlgItem(IDC_RADIO_CR_ADJ))->GetCheck() )		iID = IDC_RADIO_CR_ADJ;
//	if( ((CButton*)GetDlgItem(IDC_RADIO_CR_MOTOR2))->GetCheck() )	iID = IDC_RADIO_CR_MOTOR2;
//	if( ((CButton*)GetDlgItem(IDC_RADIO_PUMP))->GetCheck() )		iID = IDC_RADIO_PUMP;
	if( ((CButton*)GetDlgItem(IDC_RADIO_LCD_BOARD))->GetCheck() )	iID = IDC_RADIO_LCD_BOARD;
	if (((CButton*)GetDlgItem(IDC_RADIO_HUMID_FAN))->GetCheck())	iID = IDC_RADIO_HUMID_FAN;

	return iID;
}


BOOL CServChgParts::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	CheckDlgButton( IDC_RADIO_HEAD , BST_CHECKED );

	return TRUE;  // return TRUE unless you set the focus to a control
	// ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}
