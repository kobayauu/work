// BatteryChg1.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "BatteryChg1.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBatteryChg1 プロパティ ページ

IMPLEMENT_DYNCREATE(CBatteryChg1, CPropertyPage)

CBatteryChg1::CBatteryChg1() : CPropertyPage(CBatteryChg1::IDD)
{
	//{{AFX_DATA_INIT(CBatteryChg1)
		// メモ - ClassWizard はこの位置にメンバの初期化処理を追加します。
	//}}AFX_DATA_INIT
}

CBatteryChg1::~CBatteryChg1()
{
}

void CBatteryChg1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBatteryChg1)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBatteryChg1, CPropertyPage)
	//{{AFX_MSG_MAP(CBatteryChg1)
		// メモ: ClassWizard はこの位置に DDX および DDV の呼び出しコードを追加します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBatteryChg1 メッセージ ハンドラ

BOOL CBatteryChg1::OnQueryCancel() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	BOOL bRet = FALSE;
	if( LangCancelYesNoMsgBox() == IDYES )
	{
		bRet = TRUE;
	}
	return bRet;
}

BOOL CBatteryChg1::OnSetActive() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	//pApp->Log( _T("Battery Change Step 1 Page") );
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

	LangSetWndTxt( GetDlgItem( IDC_CHANGE_BATTERY1_1 ) , IDS_CHANGE_BATTERY1_1 );

	return CPropertyPage::OnSetActive();
}

LRESULT CBatteryChg1::OnWizardBack() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CBatteryChg1::OnWizardNext() 
{
	LRESULT nNextID = IDD_SERV_CHNAGE_BATTERY2;

	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	CWaitCursor wc;

	m_dwChangedDate = (DWORD)pApp->GetCurrentGMTSecond();

	if( pApp->IsOnline())
	{
		int iRet = BatteryChangedInfoSetToPrinter();

		if( iRet < 0 )
		{
			LangAfxMsgBox( IDS_EER_COMMUNICATION , iRet );
			nNextID = -1;
		}
	}

	return pApp->IDDPush( nNextID );
}

//バッテリー交換情報のセット
int CBatteryChg1::BatteryChangedInfoSetToPrinter()
{
	int iRet = 0;

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	iRet = pApp->ResetBattery();

	return iRet;
}


