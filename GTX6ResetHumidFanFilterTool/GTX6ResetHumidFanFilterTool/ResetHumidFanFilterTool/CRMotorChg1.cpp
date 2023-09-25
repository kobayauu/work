// CRMotorChg1.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "bgjservtool.h"
#include "CRMotorChg1.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCRMotorChg1 プロパティ ページ

IMPLEMENT_DYNCREATE(CCRMotorChg1, CPropertyPage)

CCRMotorChg1::CCRMotorChg1() : CPropertyPage(CCRMotorChg1::IDD)
{
	//{{AFX_DATA_INIT(CCRMotorChg1)
		// メモ - ClassWizard はこの位置にメンバの初期化処理を追加します。
	//}}AFX_DATA_INIT
}

CCRMotorChg1::~CCRMotorChg1()
{
}

void CCRMotorChg1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCRMotorChg1)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCRMotorChg1, CPropertyPage)
	//{{AFX_MSG_MAP(CCRMotorChg1)
		// メモ: ClassWizard はこの位置に DDX および DDV の呼び出しコードを追加します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCRMotorChg1 メッセージ ハンドラ

BOOL CCRMotorChg1::OnSetActive() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	m_nPrevIDD = pApp->SetPrevIDD( IDD );
	
	LangSetWndTxt( GetDlgItem( IDC_CR_CHANGE1_1 ) , IDS_CR_CHANGE1_1 );

	return CPropertyPage::OnSetActive();
}

BOOL CCRMotorChg1::OnQueryCancel() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	BOOL bRet = FALSE;
	if( LangCancelYesNoMsgBox() == IDYES )
	{
		bRet = TRUE;
	}
	return bRet;
}

LRESULT CCRMotorChg1::OnWizardBack() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CCRMotorChg1::OnWizardNext() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	LRESULT nNextID = -1;
	LRESULT nOKNextID = IDD_SERV_ADJ_CR_SPEED1;
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	CWaitCursor wc;
	
	m_dwChangedDate = (DWORD)pApp->GetCurrentGMTSecond();

	if( pApp->IsOnline())
	{
		if( pApp->ResetMoter() < 0 )
		{
			nNextID = -1;
			LangAfxMsgBox(IDS_EER_COMMUNICATION, -191);
		}
		else
		{
			nNextID = nOKNextID;
		}
		
	}else{
		nNextID = nOKNextID;
	}
	
	return pApp->IDDPush( nNextID );
}
