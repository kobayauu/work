// BarCode.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "BarCode.h"
#include "Language.h"
#include "SelectRegionPopupDlg.h"
#include "afxdlgs.h"

// CBarCode �_�C�A���O

IMPLEMENT_DYNAMIC(CBarCode, CPropertyPage)

CBarCode::CBarCode()
	: CPropertyPage(CBarCode::IDD)
	, m_txtBarCodeMsg1(_T(""))
	, m_txtBarCodeMsg2(_T(""))
	, m_txtBarCodeMsg3(_T(""))
{

}

CBarCode::~CBarCode()
{
}

void CBarCode::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_BARCODE_MSG1, m_txtBarCodeMsg1);
	DDX_Text(pDX, IDC_BARCODE_MSG2, m_txtBarCodeMsg2);
	DDX_Text(pDX, IDC_BARCODE_MSG3, m_txtBarCodeMsg3);
	DDX_Control(pDX, IDC_BARCODE_EDIT1, m_edtctrl18Code);
	DDX_Control(pDX, IDC_BARCODE_EDIT2, m_edtctrlSerialCode);
}


BEGIN_MESSAGE_MAP(CBarCode, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, &CBarCode::OnBnClickedButton1)
END_MESSAGE_MAP()


// CBarCode ���b�Z�[�W �n���h��

BOOL CBarCode::OnSetActive()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	m_edtctrl18Code.SetWindowText(_T(""));
	m_edtctrlSerialCode.SetWindowText(_T(""));
	UpdateData(FALSE);

	LangSetWndTxt( GetDlgItem( IDC_BARCODE_MSG1 )		   , IDS_BARCODE1 );
	LangSetWndTxt( GetDlgItem( IDC_BARCODE_MSG2 )		   , IDS_BARCODE2 );
	LangSetWndTxt( GetDlgItem( IDC_BARCODE_MSG3 )		   , IDS_BARCODE3 );
	LangSetWndTxt(GetDlgItem(IDC_BARCODE_MSG4), IDS_EXAM1);
	LangSetWndTxt(GetDlgItem(IDC_BARCODE_MSG5), IDS_EXAM2);

	UpdateData(TRUE);

	return CPropertyPage::OnSetActive();
}

LRESULT CBarCode::OnWizardBack()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CBarCode::OnWizardNext()
{
	// TODO: �����ɓ���ȃR�[�h��ǉ����邩�A�������͊�{�N���X���Ăяo���Ă��������B
	int nNextID = IDD_SERV_ADJ_CR_SPEED1;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	CString csCode;
	bool bRet = TRUE;
	bool bRet2 = TRUE;
	int iErr = 0;

	UpdateData(TRUE);

	if (pApp->IsOnline())
	{
		m_edtctrl18Code.GetWindowText(csCode);
		iErr = Chk18Code(csCode);
		if (iErr < 0){
			LangAfxMsgBox(IDS_ERR_EIGHTEEN_CODE, iErr);
			return -1;
		}

		if (csCode.GetLength() != 0){
			iErr = pApp->SetEighteenCode(csCode);
			if (iErr < 0){
				LangAfxMsgBox(IDS_EER_COMMUNICATION, -191);
				return -1;
			}
		}
		//
		// 15���R�[�h�̓��͂��Ȃ��ꍇ
		//
		else
		{
			// �d�����I���_�C�A���O�̕\��
			SelectRegionPopupDlg dlg;
			INT_PTR nResponse = dlg.DoModal();
			if (nResponse == IDOK)
			{
				csCode = dlg.m_str15Code;
			}
			else if (nResponse == IDCANCEL)
			{
				csCode = _T("");
			}
		
			if (csCode.GetLength() != 0)
			{
				iErr = pApp->SetEighteenCode(csCode);
				if (iErr < 0) {
					LangAfxMsgBox(IDS_EER_COMMUNICATION, -191);
					return -1;
				}
			}
		}

		m_edtctrlSerialCode.GetWindowText(csCode);
		iErr = ChkSerialCode(csCode);
		if (iErr < 0){
			LangAfxMsgBox(IDS_ERR_SERIAL_CODE, iErr);
			return -1;
		}

		iErr = pApp->SetSerialCode(csCode);
		if (iErr < 0){
			LangAfxMsgBox(IDS_EER_COMMUNICATION, -191);
			return -1;
		}
		/*
			if(bRet && bRet2){
			//		nNextID = IDD_INIT_INK_STATE;
			nNextID = IDD_SERV_ADJ_CR_SPEED1;
			}
			*/
	}

	return pApp->IDDPush( nNextID );
}

int CBarCode::Chk18Code(CString csCode){
	if (csCode.GetLength() == 0){
		//
		// ���͂��Ȃ��ꍇ�́A�G���[���肵�Ȃ�
		//
		return 0;
	} else if(csCode.GetLength() != 15){
		//
		// ���͂�����ꍇ�́A15���ȊO�̓��͂̓G���[���肷��
		//
		return -201;
	}

	// 
	// 15���̊e���̓��͏��̃G���[����
	//
	for(int i = 0; i < 15; i++){
		// ASCII�R�[�h 33�`126���L���l
		if(csCode[i] < 33 && 126 < csCode[i]){
			return -204;
		}

		// 7���ڂ̓��͈悪���������Ƃ𔻒f����i�e�N�j�J���ێ�_���̃f�t�H���g�ݒ�ɗp���邽�߁j
		if (i == 6)
		{
			if (!ChkModelValue(csCode[i]))
			{
				return -204;
			}
		}

		// 9���ڂ̓��͈悪���������Ƃ𔻒f����i�e�N�j�J���ێ�_���̃f�t�H���g�ݒ�ɗp���邽�߁j
		if (i == 8)
		{
			if (!ChkRegionValue(csCode[i]))
			{
				return -204;
			}
		}
	}

	return 0;
}

bool CBarCode::ChkRegionValue(const int nInputAsciicode)
{
	if (49 <= nInputAsciicode && nInputAsciicode <= 53)
	{
		return true;
	}

	return false;
}

bool CBarCode::ChkModelValue(const int nInputAsciicode)
{
	if (nInputAsciicode == 51 || nInputAsciicode == 52)
	{
		return true;
	}

	return false;
}

int CBarCode::ChkSerialCode(CString csCode){
	if(csCode.GetLength() != 8){
		return -202;
	}
	/* �V���A���ɕ��������͂���Ƃ������ƂŁA�`�F�b�N���O���悤�˗���������
	for(int i = 0; i < 8; i++){
		if(csCode[i] < 48 || 57 < csCode[i]){
			return -203;
		}
	}
	*/

	return 0;
}
void CBarCode::OnBnClickedButton1()
{
	// TODO: �����ɃR���g���[���ʒm�n���h�� �R�[�h��ǉ����܂��B
	int a = ChkSerialCode(_T("12345678"));
}
