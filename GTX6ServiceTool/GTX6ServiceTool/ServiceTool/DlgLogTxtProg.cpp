// DlgLogTxtProg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "bgjservtool.h"
#include "DlgLogTxtProg.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLogTxtProg ダイアログ


CDlgLogTxtProg::CDlgLogTxtProg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogTxtProg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLogTxtProg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CDlgLogTxtProg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLogTxtProg)
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLogTxtProg, CDialog)
	//{{AFX_MSG_MAP(CDlgLogTxtProg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLogTxtProg メッセージ ハンドラ

BOOL CDlgLogTxtProg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	LangSetWndTxt( this , IDS_TITLE_LOGTXTPROG );	
	LangSetWndTxt( GetDlgItem( IDC_LOGTXT_PROG1_1 ) , IDS_LOGTXT_PROG1_1 );

	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CDlgLogTxtProg::OnCancel()
{

}

void CDlgLogTxtProg::OnOK()
{

}
