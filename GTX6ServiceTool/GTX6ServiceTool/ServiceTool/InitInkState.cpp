// InitInkState.cpp : 実装ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "InitInkState.h"
#include "Language.h"

// CInitInkState ダイアログ

IMPLEMENT_DYNAMIC(CInitInkState, CPropertyPage)

CInitInkState::CInitInkState()
	: CPropertyPage(CInitInkState::IDD)
	, m_rdbtnInkStateSelect(0)
{

}

CInitInkState::~CInitInkState()
{
}

void CInitInkState::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_cmbbxK);
	DDX_Control(pDX, IDC_COMBO2, m_cmbbxYCM);
	DDX_Control(pDX, IDC_COMBO3, m_cmbbxW1);
	DDX_Control(pDX, IDC_COMBO4, m_cmbbxW2W4);
	DDX_Radio(pDX, IDC_RADIO1, m_rdbtnInkStateSelect);
}


BEGIN_MESSAGE_MAP(CInitInkState, CPropertyPage)
END_MESSAGE_MAP()


// CInitInkState メッセージ ハンドラ

BOOL CInitInkState::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  ここに初期化を追加してください
	//InitComboBox();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}


BOOL CInitInkState::OnSetActive()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	pApp->SetPrevIDD( IDD_INIT_INK_STATE );


	LangSetWndTxt(GetDlgItem(IDC__INIT_INK_STATE), IDS_INIT_INK_STATE1);
/*
	LangSetWndTxt( GetDlgItem( IDC_INIT_INK_K ) , IDS_INIT_INK_STATE2 );
	LangSetWndTxt( GetDlgItem( IDC_INIT_INK_YCM ) , IDS_INIT_INK_STATE3 );
	LangSetWndTxt( GetDlgItem( IDC_INIT_INK_W1 ) , IDS_INIT_INK_STATE4 );
	LangSetWndTxt( GetDlgItem( IDC_INIT_INK_W2W4 ) , IDS_INIT_INK_STATE5 );
*/

	LangSetWndTxt(GetDlgItem( IDC_RADIO1 ) , IDS_INK_STATE6 );
	LangSetWndTxt(GetDlgItem( IDC_RADIO2 ) , IDS_INK_STATE7 );


	return CPropertyPage::OnSetActive();
}

LRESULT CInitInkState::OnWizardBack()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CInitInkState::OnWizardNext()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	//int nNextID = IDD_WHITE_HALT2;
	int nNextID = IDD_IP_CLEAR;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	bool bRet = TRUE;
	bool bRet2 = TRUE;
	int iErr1 = 0;
	int iErr2 = 0;

    UpdateData(TRUE);

	if (pApp->IsOnline())
	{
		//iErr1 = pApp->SetInitInkState(m_cmbbxK.GetCurSel(), m_cmbbxYCM.GetCurSel(), m_cmbbxW1.GetCurSel(), m_cmbbxW2W4.GetCurSel());
		if (m_rdbtnInkStateSelect == 0) {
			iErr1 = pApp->SetInitInkState(0, 0, 0, 0);
		}
		else if (m_rdbtnInkStateSelect == 1) {
			iErr1 = pApp->SetInitInkState(1, 1, 1, 1);
		}

		iErr2 = pApp->SetAssembleFlag(0x05);

		if (iErr1 != 0  || iErr2 != 0){
			nNextID = -1;
			LangAfxMsgBox(IDS_EER_COMMUNICATION, -191);
		}
	}

/*
	if(!bRet){
		LangAfxMsgBox( IDS_EER_COMMUNICATION , -191 );
	}else {
//		nNextID = IDD_SERV_ADJ_CR_SPEED1;
		nNextID = IDD_IP_CLEAR;
	}
*/
	return pApp->IDDPush( nNextID );
}

int CInitInkState::InitComboBox(){
	CString csMsg = _T("");

	LangGetString(IDS_INIT_INK_STATE6, &csMsg);
	m_cmbbxK.InsertString(-1, csMsg);
	LangGetString(IDS_INIT_INK_STATE7, &csMsg);
	m_cmbbxK.InsertString(1, csMsg);
	m_cmbbxK.SetCurSel(0);

	LangGetString(IDS_INIT_INK_STATE6, &csMsg);
	m_cmbbxYCM.InsertString(0, csMsg);
	LangGetString(IDS_INIT_INK_STATE7, &csMsg);
	m_cmbbxYCM.InsertString(1, csMsg);
	m_cmbbxYCM.SetCurSel(0);

	LangGetString(IDS_INIT_INK_STATE6, &csMsg);
	m_cmbbxW1.InsertString(0, csMsg);
	LangGetString(IDS_INIT_INK_STATE7, &csMsg);
	m_cmbbxW1.InsertString(1, csMsg);
	m_cmbbxW1.SetCurSel(0);

	LangGetString(IDS_INIT_INK_STATE6, &csMsg);
	m_cmbbxW2W4.InsertString(0, csMsg);
	LangGetString(IDS_INIT_INK_STATE7, &csMsg);
	m_cmbbxW2W4.InsertString(1, csMsg);
	m_cmbbxW2W4.SetCurSel(0);

	UpdateData(FALSE);

	return 0;
}
