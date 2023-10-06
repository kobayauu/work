// PlatenFeeding.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "PlatenFeeding.h"
#include "Language.h"

// CPlatenFeeding �_�C�A���O

IMPLEMENT_DYNAMIC(CPlatenFeeding, CPropertyPage)

CPlatenFeeding::CPlatenFeeding()
	: CPropertyPage(CPlatenFeeding::IDD)
	, m_bDone(FALSE)
{

}

CPlatenFeeding::~CPlatenFeeding()
{
}

void CPlatenFeeding::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_PLATEN_FEEDING_DONE, m_bDone);
}


BEGIN_MESSAGE_MAP(CPlatenFeeding, CPropertyPage)
	ON_BN_CLICKED(IDC_CHECK_PLATEN_FEEDING_DONE, &CPlatenFeeding::OnBnClickedCheckPlatenFeedingDone)
	ON_BN_CLICKED(IDC_BTN_OPEN_GTMAINTE, &CPlatenFeeding::OnBnClickedBtnOpenGtmainte)
END_MESSAGE_MAP()


// CPlatenFeeding ���b�Z�[�W �n���h��

BOOL CPlatenFeeding::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �����ɏ�������ǉ����Ă�������


	return TRUE;  // return TRUE unless you set the focus to a control
	// ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}

BOOL CPlatenFeeding::OnSetActive()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons( PSWIZB_BACK );

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

	LangSetWndTxt( GetDlgItem( IDC_PLATEN_FEEDING_MSG1 ) , IDS_PLATEN_FEEDING1 );
	//LangSetWndTxt( GetDlgItem( IDC_PLATEN_FEEDING_MSG2 ) , IDS_PLATEN_FEEDING2 );
	LangSetWndTxt( GetDlgItem( IDC_PLATEN_FEEDING_MSG3 ) , IDS_PLATEN_FEEDING4);
	LangSetWndTxt( GetDlgItem( IDC_BTN_OPEN_GTMAINTE   ) , IDS_BTN_OPEN_GTMAINTE );
	LangSetWndTxt( GetDlgItem( IDC_CHECK_PLATEN_FEEDING_DONE ) , IDS_PLATEN_FEEDING3 );
	
	m_bDone = FALSE;
	UpdateData( FALSE );

	return CPropertyPage::OnSetActive();
}

LRESULT CPlatenFeeding::OnWizardBack()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CPlatenFeeding::OnWizardNext()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	int nNextID = IDD_SET_POS;

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	return pApp->IDDPush( nNextID );
}

void CPlatenFeeding::OnBnClickedCheckPlatenFeedingDone()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	UpdateData( TRUE );

	CPropertySheet* pSheet = (CPropertySheet*)GetParent();

	if( m_bDone )
	{
		pSheet->SetWizardButtons( PSWIZB_NEXT | PSWIZB_BACK );
	}else
	{
		pSheet->SetWizardButtons( PSWIZB_BACK );
	}
}

void CPlatenFeeding::OnBnClickedBtnOpenGtmainte()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	pApp->RunMaintenanceTool();
}
