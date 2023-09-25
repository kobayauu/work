// BarCode.cpp : 実装ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "BarCode.h"
#include "Language.h"
#include "SelectRegionPopupDlg.h"
#include "afxdlgs.h"

// CBarCode ダイアログ

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


// CBarCode メッセージ ハンドラ

BOOL CBarCode::OnSetActive()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
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
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CBarCode::OnWizardNext()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
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
		// 15桁コードの入力がない場合
		//
		else
		{
			// 仕向け選択ダイアログの表示
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
		// 入力がない場合は、エラー判定しない
		//
		return 0;
	} else if(csCode.GetLength() != 15){
		//
		// 入力がある場合は、15桁以外の入力はエラー判定する
		//
		return -201;
	}

	// 
	// 15桁の各桁の入力情報のエラー判定
	//
	for(int i = 0; i < 15; i++){
		// ASCIIコード 33～126が有効値
		if(csCode[i] < 33 && 126 < csCode[i]){
			return -204;
		}

		// 7桁目の入力域が正しいことを判断する（テクニカル保守点検のデフォルト設定に用いるため）
		if (i == 6)
		{
			if (!ChkModelValue(csCode[i]))
			{
				return -204;
			}
		}

		// 9桁目の入力域が正しいことを判断する（テクニカル保守点検のデフォルト設定に用いるため）
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
	/* シリアルに文字列を入力するということで、チェックを外すよう依頼があった
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
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	int a = ChkSerialCode(_T("12345678"));
}
