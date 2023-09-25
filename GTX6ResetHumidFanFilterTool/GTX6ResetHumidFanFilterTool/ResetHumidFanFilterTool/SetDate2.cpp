// SetDate2.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "SetDate2.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define RESTORE_EEPROM 0
#define NEW_SETTING 1

/////////////////////////////////////////////////////////////////////////////
// CSetDate2 プロパティ ページ

IMPLEMENT_DYNCREATE(CSetDate2, CPropertyPage)

CSetDate2::CSetDate2() : CPropertyPage(CSetDate2::IDD)
{
	//{{AFX_DATA_INIT(CSetDate2)
		// メモ - ClassWizard はこの位置にメンバの初期化処理を追加します。
	//}}AFX_DATA_INIT
}

CSetDate2::~CSetDate2()
{
}

void CSetDate2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSetDate2)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSetDate2, CPropertyPage)
	//{{AFX_MSG_MAP(CSetDate2)
		// メモ: ClassWizard はこの位置に DDX および DDV の呼び出しコードを追加します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSetDate2 メッセージ ハンドラ

BOOL CSetDate2::OnQueryCancel() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	BOOL bRet = FALSE;
	if( LangCancelYesNoMsgBox() == IDYES )
	{
		bRet = TRUE;
	}
	return bRet;
}

BOOL CSetDate2::OnSetActive() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	//pApp->Log( _T("Set Date and Time Step 2 Page") );
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

	LangSetWndTxt( GetDlgItem( IDC_SET_DATE2_1 ) , IDS_SET_DATE2_1 );

	return CPropertyPage::OnSetActive();
}

LRESULT CSetDate2::OnWizardBack() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CSetDate2::OnWizardNext() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	LRESULT nNextID = -1;
	LRESULT nOKNextID = -1;
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	pApp->BeginWaitCursor();
	//pApp->Log( _T("Set Date and Time Step2: go to Next") );
	switch( pApp->GetCourse() )
	{
	case COURSE_INIT_SETTING:
		nOKNextID = IDD_SERV_ADJ_CR_SPEED1;
		break;
	default:
	case COURSE_BATTERY_CHANGE:
		nOKNextID = IDD_SERV_CHNAGE_BATTERY1;
		break;
	case COURSE_MAIN_BOARD_CHANGE:
	//	nOKNextID = IDD_SERV_HEAD_VOLT01;//電圧調整は行わない
//		nOKNextID = IDD_RESET_VOLTAGE;
//		nOKNextID = IDD_MAIN_BOARD_BRANCH;
		if(pApp->m_iMBChangeFlag == RESTORE_EEPROM){
			nOKNextID = IDD_BACKUP;
		}else if(pApp->m_iMBChangeFlag == NEW_SETTING){
			nOKNextID = IDD_RESET_VOLTAGE;
		}

		break;
	case COURSE_SET_DATE:
		nOKNextID = IDD_SERV_SEL_OPE;
		break;
	}
	nNextID = nOKNextID;
	pApp->EndWaitCursor();
	return pApp->IDDPush( nNextID );
}
