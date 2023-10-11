// PlatenHeight.cpp : 実装ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "PlatenHeight.h"
#include "Language.h"

// CPlatenHeight ダイアログ

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


// CPlatenHeight メッセージ ハンドラ

BOOL CPlatenHeight::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  ここに初期化を追加してください


	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

BOOL CPlatenHeight::OnSetActive()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	
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
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CPlatenHeight::OnWizardNext()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。
	int nNextID = IDD_VRATING;

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	return pApp->IDDPush( nNextID );
}

void CPlatenHeight::OnBnClickedCheckPlatenHeightDone()
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

