#if !defined(AFX_DLGLOGCSVPROG_H__0BE91D8B_61D0_458D_BC13_8B9DFE4065A0__INCLUDED_)
#define AFX_DLGLOGCSVPROG_H__0BE91D8B_61D0_458D_BC13_8B9DFE4065A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLogCsvProg.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLogCsvProg ダイアログ

class CDlgLogCsvProg : public CDialog
{
// コンストラクション
public:
	CDlgLogCsvProg(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CDlgLogCsvProg)
	enum { IDD = IDD_DLG_LOGCSV_PROGRESS };
	CProgressCtrl	m_Progress;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CDlgLogCsvProg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	virtual void OnCancel();
	virtual void OnOK();

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CDlgLogCsvProg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_DLGLOGCSVPROG_H__0BE91D8B_61D0_458D_BC13_8B9DFE4065A0__INCLUDED_)
