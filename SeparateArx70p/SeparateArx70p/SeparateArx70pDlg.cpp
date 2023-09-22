// SeparateArx70pDlg.cpp : 実装ファイル
//

#include "stdafx.h"
#include "SeparateArx70p.h"
#include "SeparateArx70pDlg.h"
#include "ArpProcess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSeparateArx70pDlg ダイアログ




CSeparateArx70pDlg::CSeparateArx70pDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSeparateArx70pDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSeparateArx70pDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSeparateArx70pDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CSeparateArx70pDlg メッセージ ハンドラ

BOOL CSeparateArx70pDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CSeparateArx70pDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CSeparateArx70pDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CSeparateArx70pDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSeparateArx70pDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ここにメッセージ ハンドラ コードを追加するか、既定の処理を呼び出します。
	int		nFiles;				//ドロップされたファイル数
	int		nLoop;				//forループ用
	TCHAR	buff[MAX_PATH];		//文字列バッファ
	CString	FileName;			//ドロップされたファイル名
	CString	FileExt;			//ファイル拡張子
	int		nArpFiles = 0;		//ARPファイル数

	//カーソルを待ち状態にする
	BeginWaitCursor();

	//チェック状態の取得
	UpdateData(TRUE);

	//ファイル数の取得
	nFiles = DragQueryFile(hDropInfo, -1, NULL, 0);
	for( nLoop = 0; nLoop < nFiles; ++nLoop )
	{
		//ファイル名の取得
		DragQueryFile(hDropInfo, nLoop, buff, MAX_PATH);
		FileName = buff;

		//拡張子判定
		FileExt		= FileName.Mid ( FileName.ReverseFind('.') ).MakeLower();
		if( FileExt == ".arx4" || FileExt == ".arxp" || FileExt == ".arx6" || FileExt == ".arx70p" ) {	//ARXファイル
			nArpFiles++;
			SeparateArx70polor( FileName );
		}
		else {						//その他のファイル
			;
		}
	}

	//カーソルの待ち状態を戻す
	EndWaitCursor();

	//メッセージ表示
	CString	Msg;
	if( nArpFiles == 0 )
		Msg = "The ARX file is only accepted.";
	else
		Msg.Format( "The %d ARX file separated Color.", nArpFiles );
	AfxMessageBox( Msg );

	CDialog::OnDropFiles(hDropInfo);
}

int CSeparateArx70pDlg::SeparateArx70polor(CString FileName)
{
	CSplitArp	ArpData;

	ArpData.Open( FileName, FileName + "_w1.arx70p", FileName + "_w2.arx70p", FileName + "_c.arx70p", FileName + "_ff.arx70p");
	ArpData.Process();
	ArpData.Close();

	return 0;
}
