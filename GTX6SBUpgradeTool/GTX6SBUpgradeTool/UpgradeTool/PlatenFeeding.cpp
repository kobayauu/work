// PlatenFeeding.cpp : 実装ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "PlatenFeeding.h"
#include "Language.h"

// CPlatenFeeding ダイアログ

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


// CPlatenFeeding メッセージ ハンドラ

BOOL CPlatenFeeding::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  ここに初期化を追加してください


	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

BOOL CPlatenFeeding::OnSetActive()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	
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
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CPlatenFeeding::OnWizardNext()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	int nNextID = IDD_SET_POS;

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	return pApp->IDDPush( nNextID );
}

void CPlatenFeeding::OnBnClickedCheckPlatenFeedingDone()
{
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
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
	// TODO: ここにコントロール通知ハンドラ コードを追加します。
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	pApp->RunMaintenanceTool();
}
