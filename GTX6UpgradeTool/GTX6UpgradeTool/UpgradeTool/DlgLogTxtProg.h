#if !defined(AFX_DLGLOGTXTPROG_H__058E8FD7_1EDD_4D78_B0E2_1A806FDC53DF__INCLUDED_)
#define AFX_DLGLOGTXTPROG_H__058E8FD7_1EDD_4D78_B0E2_1A806FDC53DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLogTxtProg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLogTxtProg ダイアログ

class CDlgLogTxtProg : public CDialog
{
// コンストラクション
public:
	CDlgLogTxtProg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDlgLogTxtProg)
	enum { IDD = IDD_DLG_LOGTXT_PROGRESS };
	CProgressCtrl	m_Progress;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlgLogTxtProg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	virtual void OnCancel();
	virtual void OnOK();
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlgLogTxtProg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DLGLOGTXTPROG_H__058E8FD7_1EDD_4D78_B0E2_1A806FDC53DF__INCLUDED_)
