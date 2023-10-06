// ResetPSel.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include <winspool.h>
#include "bgjservtool.h"
#include "ResetPSel.h"
#include "FVerInfo.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

static const TCHAR cszBrMatCheck[] = _T("BrMatCheck");

/////////////////////////////////////////////////////////////////////////////
// CResetPSel �v���p�e�B �y�[�W

IMPLEMENT_DYNCREATE(CResetPSel, CPropertyPage)

CResetPSel::CResetPSel() : CPropertyPage(CResetPSel::IDD)
, m_csVersion(_T(""))
, m_csCopyRight(_T(""))
{
	//{{AFX_DATA_INIT(CResetPSel)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�̏�����������ǉ����܂��B
	//}}AFX_DATA_INIT
}

CResetPSel::~CResetPSel()
{
}

void CResetPSel::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUpgPSel)
	DDX_Control(pDX, IDC_CBX_PRINTER, m_cbxPrinterName);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_VERSION, m_csVersion);
	DDX_Text(pDX, IDC_COPYRIGHT, m_csCopyRight);
}


BEGIN_MESSAGE_MAP(CResetPSel, CPropertyPage)
	//{{AFX_MSG_MAP(CResetPSel)
	ON_CBN_SELCHANGE(IDC_CBX_PRINTER, OnSelchangeCbxPrinter)
	ON_BN_CLICKED(IDC_BTN_RESCAN, OnBtnRescan)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CResetPSel ���b�Z�[�W �n���h��

BOOL CResetPSel::OnSetActive()
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	m_nPrevIDD = pApp->SetPrevIDD( IDD );
	pApp->IDDPush( IDD );
	if( InitPrinterList() ){
		OnSelchangeCbxPrinter();
		pSheet->SetWizardButtons( PSWIZB_NEXT );
	}

	LangSetWndTxt( GetDlgItem( IDC_RESET_PSEL1_1 )	, IDS_RESET_PSEL1_1	 );
	LangSetWndTxt( GetDlgItem( IDC_SELECT_PRINTER ) , IDS_SELECT_PRINTER );
	LangSetWndTxt( GetDlgItem( IDC_BTN_RESCAN )		, IDS_RESCAN		 );

	CFVerInfo Ver;
	Ver.LoadFileVersion();
	CString cs = Ver.GetFileVersionStr();

	m_csVersion = _T("GTX-6 Extra Colors ORGR Reset HumidifierInfo Tool : Version ");
	m_csVersion += cs;

	LangGetString(IDS_COPYRIGHTS, &m_csCopyRight);

	UpdateData(FALSE);

	return CPropertyPage::OnSetActive();
}

LRESULT CResetPSel::OnWizardBack()
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CResetPSel::OnWizardNext()
{
	// TODO: ���̈ʒu�ɌŗL�̏�����ǉ����邩�A�܂��͊�{�N���X���Ăяo���Ă�������
	LRESULT nNextID = IDD_HUMIDFAN;
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	pApp->SetPrinterName( m_csPrinterName );
	
	return pApp->IDDPush( nNextID );
}

bool CResetPSel::InitPrinterList()
{
	m_cbxPrinterName.ResetContent();

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	if( ! pApp->IsOnline() )
	{
		m_cbxPrinterName.AddString( _T("Virtual printer") );
		m_cbxPrinterName.SetCurSel( 0 );
		return true;
	}
	else
	{
		int iRet = pApp->GetGTPrinters( &m_cbxPrinterName );
		if( iRet >= 0 )
		{
			m_cbxPrinterName.SetCurSel( 0 );
			return true;
		}
		else
		{
			LangAfxMsgBox( IDS_OFFLINE );
			return false;
		}
	}
}

void CResetPSel::OnSelchangeCbxPrinter()
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	int nSel = m_cbxPrinterName.GetCurSel();
	if( CB_ERR != nSel ){
		m_cbxPrinterName.GetLBText( nSel, m_csPrinterName );
	}	
}

void CResetPSel::OnBtnRescan()
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	//�v�����^�̌���
	if ((GetKeyState(VK_CONTROL) & 0x8000) && (GetKeyState(VK_SHIFT) & 0x8000))
	{
		CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
		pApp->SetDemo();
	}

	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	if( InitPrinterList() )
	{
		OnSelchangeCbxPrinter();
	}
}

