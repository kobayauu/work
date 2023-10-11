#include "SelectRegionPopupDlg.h"
#include "stdafx.h"
#include "BGJServTool.h"
#include "Language.h"

IMPLEMENT_DYNAMIC(SelectRegionPopupDlg, CDialog)

////////////////////////////////////////////////////////////////////////////////
// SelectRegionPopupDlg::SelectRegionPopupDlg(CWnd* pParent /*=NULL*/)
//	@brief		コンストラクタ
//
//	@param		CWnd* pParent
//	@return		なし
////////////////////////////////////////////////////////////////////////////////
SelectRegionPopupDlg::SelectRegionPopupDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SelectRegionPopupDlg::IDD, pParent)
{

}

////////////////////////////////////////////////////////////////////////////////
// void ActivateSettingDlg::DoDataExchange(CDataExchange* pDX)
//	@brief		コントロールで表示される値と対応するコントロール変数の間で値を交換するとき利用される関数
//
//	@param		CDataExchange* pDX
//	@return		なし
////////////////////////////////////////////////////////////////////////////////
void SelectRegionPopupDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO_REGION_JPN, m_nRegionRadio);
	DDX_Radio(pDX, IDC_RADIO_MODEL_PRO, m_nModelRadio);
}

////////////////////////////////////////////////////////////////////////////////
// BEGIN_MESSAGE_MAP(CDeviceInformationDlg, CDialog)
//	@brief		メッセージから呼び出される関数を定義するマクロ
//
//	@param		ActivateSettingDlg, CDialog
//	@return		なし
////////////////////////////////////////////////////////////////////////////////
BEGIN_MESSAGE_MAP(SelectRegionPopupDlg, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()

////////////////////////////////////////////////////////////////////////////////
// ActivateSettingDlg::OnInitDialog()
//	@brief		ダイアログ起動時の初期動作
//
//	@param		なし
//	@return		BOOL	：	関数の可否
////////////////////////////////////////////////////////////////////////////////
BOOL SelectRegionPopupDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	UpdateData(FALSE);

	((CButton*)GetDlgItem(IDC_RADIO_REGION_JPN))->SetCheck(BST_CHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_MODEL_PRO))->SetCheck(BST_CHECKED);

	LangSetWndTxt(GetDlgItem(IDC_RADIO_REGION_JPN), IDS_RADIO_REGION_JPN);
	LangSetWndTxt(GetDlgItem(IDC_RADIO_REGION_US), IDS_RADIO_REGION_US);
	LangSetWndTxt(GetDlgItem(IDC_RADIO_REGION_EUR), IDS_RADIO_REGION_EUR);
	LangSetWndTxt(GetDlgItem(IDC_RADIO_REGION_AUS), IDS_RADIO_REGION_AUS);
	LangSetWndTxt(GetDlgItem(IDC_RADIO_REGION_CHN), IDS_RADIO_REGION_CHN);

	UpdateData(TRUE);

	return TRUE;
}

////////////////////////////////////////////////////////////////////////////////
// ActivateSettingDlg::OnBnClickedOk()
//	@brief		Okボタンを押されたときの処理
//
//	@param		なし
//	@return		なし
////////////////////////////////////////////////////////////////////////////////
void SelectRegionPopupDlg::OnBnClickedOk()
{
	SetModel();
	SetRegion();
	SetAttach();

	m_str15Code = _T("BGT60NBJ");
	//m_str15Code += m_strModel;
	//m_str15Code += _T(" ");
	m_str15Code += m_strRegion;
	m_str15Code += _T("00003");
	m_str15Code += m_strAttach;

	OnOK();
}

void SelectRegionPopupDlg::SetRegion()
{
	m_strRegion = _T("");

	if (IsDlgButtonChecked(IDC_RADIO_REGION_JPN) == BST_CHECKED)
	{
		m_strRegion = _T("1");
	}
	else if (IsDlgButtonChecked(IDC_RADIO_REGION_US) == BST_CHECKED)
	{
		m_strRegion = _T("2");
	}
	else if (IsDlgButtonChecked(IDC_RADIO_REGION_EUR) == BST_CHECKED)
	{
		m_strRegion = _T("3");
	}
	else if (IsDlgButtonChecked(IDC_RADIO_REGION_AUS) == BST_CHECKED)
	{
		m_strRegion = _T("4");
	}
	else if (IsDlgButtonChecked(IDC_RADIO_REGION_CHN) == BST_CHECKED)
	{
		m_strRegion = _T("5");
	}
}

void SelectRegionPopupDlg::SetModel()
{
	m_strModel = _T("");

	if (IsDlgButtonChecked(IDC_RADIO_MODEL_PRO) == BST_CHECKED)
	{
		m_strModel = _T("3");
	}
	else if (IsDlgButtonChecked(IDC_RADIO_MODEL_PROB) == BST_CHECKED)
	{
		m_strModel = _T("4");
	}
}

void SelectRegionPopupDlg::SetAttach()
{
	m_strAttach = _T("");

	if (IsDlgButtonChecked(IDC_RADIO_REGION_JPN) == BST_CHECKED)
	{
		m_strAttach = _T("1");
	}
	else
	{
		m_strAttach = _T("2");
	}
}