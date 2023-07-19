#if !defined(AFX_LOGFILEINFO_H__86B9BEB2_CF68_415D_A7F3_53CC6D639A85__INCLUDED_)
#define AFX_LOGFILEINFO_H__86B9BEB2_CF68_415D_A7F3_53CC6D639A85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogFileInfo.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CLogFileInfo ダイアログ

class CLogFileInfo : public CDialog
{
// コンストラクション
public:
	CLogFileInfo(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CLogFileInfo)
	enum { IDD = IDD_DLG_LOG_INFO };
	CString	m_csFileName;
	CString	m_Edit;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CLogFileInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CLogFileInfo)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_LOGFILEINFO_H__86B9BEB2_CF68_415D_A7F3_53CC6D639A85__INCLUDED_)
