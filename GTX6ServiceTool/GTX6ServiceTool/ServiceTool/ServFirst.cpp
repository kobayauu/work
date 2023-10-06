// ServFirst.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include <winspool.h>
#include <winuser.h>
#include "BGJServTool.h"
#include "ServFirst.h"
#include "FVerInfo.h"
#include "Language.h"
#include ".\servfirst.h"
#include "ServSheet.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServFirst プロパティ ページ

IMPLEMENT_DYNCREATE(CServFirst, CPropertyPage)

CServFirst::CServFirst() : CPropertyPage(CServFirst::IDD)
{
	//{{AFX_DATA_INIT(CServFirst)
	//}}AFX_DATA_INIT
}

CServFirst::~CServFirst()
{
}

void CServFirst::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CServFirst)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CServFirst, CPropertyPage)
	//{{AFX_MSG_MAP(CServFirst)
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServFirst メッセージ ハンドラ


BOOL CServFirst::OnSetActive() 
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	m_nPrevIDD = pApp->SetPrevIDD( IDD );
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);

	LangSetWndTxt( GetDlgItem( IDC_SERV_FIRST_1 ) , IDS_SERV_FIRST_1 );
	LangSetWndTxt( GetDlgItem( IDC_SERV_FIRST_2 ) , IDS_SERV_FIRST_2 );

	UpdateData(FALSE);
	return CPropertyPage::OnSetActive();
}

LRESULT CServFirst::OnWizardNext() 
{
	LRESULT nNextID = IDD_SERV_PSEL;
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPush( nNextID );
	
}

LRESULT CServFirst::OnWizardBack() 
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
	return CPropertyPage::OnWizardBack();
}

BOOL CServFirst::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	//フォントサイズの変更
//	CServSheet* pSheet = (CServSheet*)GetParent();
//	pSheet->ChangeFontSize( GetDlgItem(IDC_SERV_FIRST_2) , 14 , FW_SEMIBOLD );
	GetDlgItem(IDC_SERV_FIRST_2)->ShowWindow( SW_HIDE );

	return TRUE;  // return TRUE unless you set the focus to a control
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

HBRUSH CServFirst::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	if( pWnd->m_hWnd == GetDlgItem(IDC_SERV_FIRST_2)->m_hWnd )
	{
		pDC->SetTextColor( RGB( 255, 0, 0 )) ;
	}

	return hbr;
}
