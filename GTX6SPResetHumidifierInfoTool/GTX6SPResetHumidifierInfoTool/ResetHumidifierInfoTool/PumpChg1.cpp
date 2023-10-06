// PumpChg1.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "PumpChg1.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPumpChg1 プロパティ ページ

IMPLEMENT_DYNCREATE(CPumpChg1, CPropertyPage)

CPumpChg1::CPumpChg1() : CPropertyPage(CPumpChg1::IDD)
{
	//{{AFX_DATA_INIT(CPumpChg1)
		// メモ - ClassWizard はこの位置にメンバの初期化処理を追加します。
	//}}AFX_DATA_INIT
}

CPumpChg1::~CPumpChg1()
{
}

void CPumpChg1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPumpChg1)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPumpChg1, CPropertyPage)
	//{{AFX_MSG_MAP(CPumpChg1)
		// メモ: ClassWizard はこの位置に DDX および DDV の呼び出しコードを追加します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPumpChg1 メッセージ ハンドラ

BOOL CPumpChg1::OnQueryCancel() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	BOOL bRet = FALSE;
	if( LangCancelYesNoMsgBox() == IDYES )
	{
		bRet = TRUE;
	}
	return bRet;
}

BOOL CPumpChg1::OnSetActive() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	//pApp->Log( _T("Pump Change Step 1 Page") );
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

	LangSetWndTxt( GetDlgItem( IDC_CHANGE_PUMP1_1 ) , IDS_CHANGE_PUMP1_1 );

	return CPropertyPage::OnSetActive();
}

LRESULT CPumpChg1::OnWizardBack() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CPumpChg1::OnWizardNext() 
{
	LRESULT nNextID = IDD_SERV_CHNAGE_PUMP2;

	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	CWaitCursor wc;

	m_dwChangedDate = (DWORD)pApp->GetCurrentGMTSecond();

	if( pApp->IsOnline())
	{
		int iRet = PumpChangedInfoSetToPrinter();
		if( iRet < 0 ) {
			LangAfxMsgBox( IDS_EER_COMMUNICATION , iRet );
			return -1;
		}
	}

	return pApp->IDDPush( nNextID );
}

//バッテリー交換情報のセット
int CPumpChg1::PumpChangedInfoSetToPrinter()
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	int iRet = 0;

	if (pApp->IsOnline())
	{
		CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
		iRet = pApp->ResetTubePump();
		if (iRet < 0){
			LangAfxMsgBox(IDS_EER_COMMUNICATION, iRet);
			return iRet;
		}
	}

	return iRet;
}


