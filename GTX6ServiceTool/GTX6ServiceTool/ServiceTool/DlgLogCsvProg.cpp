// DlgLogCsvProg.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "bgjservtool.h"
#include "DlgLogCsvProg.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLogCsvProg ダイアログ


CDlgLogCsvProg::CDlgLogCsvProg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogCsvProg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLogCsvProg)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_DATA_INIT
}


void CDlgLogCsvProg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLogCsvProg)
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLogCsvProg, CDialog)
	//{{AFX_MSG_MAP(CDlgLogCsvProg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLogCsvProg メッセージ ハンドラ

BOOL CDlgLogCsvProg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	LangSetWndTxt( this , IDS_TITLE_LOGCSVPROG );
	LangSetWndTxt( GetDlgItem( IDC_LOGCSV_PROG1_1 ) , IDS_LOGCSV_PROG1_1 );
	
	return TRUE;  // コントロールにフォーカスを設定しないとき、戻り値は TRUE となります
	              // 例外: OCX プロパティ ページの戻り値は FALSE となります
}

void CDlgLogCsvProg::OnCancel()
{

}

void CDlgLogCsvProg::OnOK()
{

}
