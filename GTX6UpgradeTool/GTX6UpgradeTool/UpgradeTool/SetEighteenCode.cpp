// Set18Code.cpp : 実装ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "SetEighteenCode.h"
#include "Language.h"
#include "afxdlgs.h"

// Set18Code ダイアログ

IMPLEMENT_DYNAMIC(CSetEighteenCode, CPropertyPage)

CSetEighteenCode::CSetEighteenCode()
	: CPropertyPage(CSetEighteenCode::IDD)
	, m_txt18CodeMsg1(_T(""))
	, m_txt18CodeMsg2(_T(""))
{

}

CSetEighteenCode::~CSetEighteenCode()
{
}

void CSetEighteenCode::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_18CODE_MSG1, m_txt18CodeMsg1);
	DDX_Text(pDX, IDC_18CODE_MSG2, m_txt18CodeMsg2);
	DDX_Control(pDX, IDC_18CODE_EDIT1, m_edtctrl18Code);
	DDX_Control(pDX, IDC_USE_FIXED_18CODE, m_chkUseFixed18Code);
}


BEGIN_MESSAGE_MAP(CSetEighteenCode, CPropertyPage)
	ON_BN_CLICKED(IDC_USE_FIXED_18CODE, &CSetEighteenCode::OnBnClickedUseFixed18Code)
END_MESSAGE_MAP()


// CSetEighteenCode メッセージ ハンドラ

BOOL CSetEighteenCode::OnSetActive()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons(PSWIZB_BACK | PSWIZB_NEXT);

	m_edtctrl18Code.SetWindowText(GTX_HEAD_641_SP);
	UpdateData(FALSE);

	LangSetWndTxt( GetDlgItem( IDC_18CODE_MSG1 )		   , IDS_18CODE_MSG1_1 );
	LangSetWndTxt( GetDlgItem( IDC_18CODE_MSG2 )		   , IDS_18CODE_MSG2_1 );
	LangSetWndTxt( GetDlgItem( IDC_USE_FIXED_18CODE    )   , IDS_USE_FIXED_18CODE );

	m_chkUseFixed18Code.SetCheck(1);
	OnBnClickedUseFixed18Code();

	UpdateData(TRUE);

	return CPropertyPage::OnSetActive();
}

LRESULT CSetEighteenCode::OnWizardBack()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CSetEighteenCode::OnWizardNext()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	int nNextID = IDD_WAIT_ACTION;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	CString csCode;
	int iErr = 0;

	UpdateData(TRUE);

	m_edtctrl18Code.GetWindowText(csCode);
	iErr = Chk18Code(csCode);
	if (iErr != 0) {
		LangAfxMsgBox(IDS_ERR_EIGHTEEN_CODE, iErr);
		return -1;
	}

	if (pApp->IsOnline()) {
		if (csCode.GetLength() != 0) {
			iErr = pApp->SetEighteenCode(csCode);
			if (iErr != 0) {
				LangAfxMsgBox(IDS_EER_COMMUNICATION, -191);
				return -1;
			}
		}
	}

	return pApp->IDDPush( nNextID );
}

int CSetEighteenCode::Chk18Code(CString csCode){
	if (csCode.GetLength() != 15) {
		//
		// 15桁以外の入力はエラー判定する
		//
		return -201;
	}

	// 
	// 15桁の各桁の入力情報のエラー判定
	//
	// 1～8桁目の入力域が正しいことを判断する
	CString csModelCode = csCode.Left(8);
	if (csModelCode != "BGT60SBJ") {
		return -202;
	}

	// 9桁目の入力域が正しいことを判断する(仕向け特別仕様)
	CString csRegionCode = csCode.Mid(8, 1);
	int nRegionCode = _ttoi(csRegionCode);
	if (1 > nRegionCode || nRegionCode > 5) {
		return -203;
	}

	// 10～14桁目の入力域が正しいことを判断する
	CString csOptionCode = csCode.Mid(9, 5);
	if (csOptionCode != "00004") {
		return -204;
	}

	// 15桁目の入力域が正しいことを判断する(付属区分)
	CString csAttachCode = csCode.Mid(14, 1);
	int nAttachCode = _ttoi(csAttachCode);
	if (1 > nAttachCode || nAttachCode > 2) {
		return -205;
	}

	return 0;
}

void CSetEighteenCode::OnBnClickedUseFixed18Code()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	BOOL bEnable = FALSE;
	if (m_chkUseFixed18Code.GetCheck() == 0) {
		bEnable = TRUE;
	}
	GetDlgItem(IDC_18CODE_EDIT1)->EnableWindow(bEnable);

	if (bEnable == FALSE) {
		m_edtctrl18Code.SetWindowText(GTX_HEAD_641_SP);
	}
}
