// PlatenHeight.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "PlatenHeight.h"
#include "Language.h"

// CPlatenHeight �_�C�A���O

IMPLEMENT_DYNAMIC(CPlatenHeight, CPropertyPage)

CPlatenHeight::CPlatenHeight()
	: CPropertyPage(CPlatenHeight::IDD)
	, m_bDone(FALSE)
{

}

CPlatenHeight::~CPlatenHeight()
{
}

void CPlatenHeight::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_PLATEN_HEIGHT_DONE, m_bDone);
}


BEGIN_MESSAGE_MAP(CPlatenHeight, CPropertyPage)
	ON_BN_CLICKED(IDC_CHECK_PLATEN_HEIGHT_DONE, &CPlatenHeight::OnBnClickedCheckPlatenHeightDone)
END_MESSAGE_MAP()


// CPlatenHeight ���b�Z�[�W �n���h��

BOOL CPlatenHeight::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �����ɏ�������ǉ����Ă�������


	return TRUE;  // return TRUE unless you set the focus to a control
	// ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}

BOOL CPlatenHeight::OnSetActive()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons( PSWIZB_BACK );

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

	LangSetWndTxt( GetDlgItem( IDC_PLATEN_HEIGHT_MSG1 ) , IDS_PLATEN_HEIGHT1 );
	LangSetWndTxt( GetDlgItem( IDC_CHECK_PLATEN_HEIGHT_DONE ) , IDS_PLATEN_HEGIHT2 );
	
	m_bDone = FALSE;
	UpdateData( FALSE );

	return CPropertyPage::OnSetActive();
}

LRESULT CPlatenHeight::OnWizardBack()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CPlatenHeight::OnWizardNext()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	int nNextID = IDD_VRATING;

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	return pApp->IDDPush( nNextID );
}

void CPlatenHeight::OnBnClickedCheckPlatenHeightDone()
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

