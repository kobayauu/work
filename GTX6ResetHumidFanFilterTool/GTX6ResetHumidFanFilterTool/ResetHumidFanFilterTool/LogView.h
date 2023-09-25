#if !defined(AFX_LOGVIEW_H__B9B0B5E7_45EA_4934_88AA_BB6DB0C89979__INCLUDED_)
#define AFX_LOGVIEW_H__B9B0B5E7_45EA_4934_88AA_BB6DB0C89979__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogView.h : ヘッダー ファイル
//

#define LOGCODE_MAX		80

/////////////////////////////////////////////////////////////////////////////
// CLogView ダイアログ

class CLogView : public CDialog
{
// コンストラクション
public:
	bool ConvertToText( CGTLogFile& cf, CFile& File );
	CString m_csTextFile;
	bool ConvertToCsv( CGTLogFile& cf, CFile& File, int* p_iRecordCount, DWORD dwStartTime = 0, DWORD dwEndTime = 0xFFFFFFFF );
	CString m_csCsvFile;
	CString m_csLogFile;
	CLogView(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CLogView)
	enum { IDD = IDD_LOG_VIEW };
	BOOL	m_bErr;
	BOOL	m_bWrn;
	BOOL	m_bInf;
	BOOL	m_bParam;
	CString	m_csTimeZone;
	CString	m_csZoneTitle;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CLogView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	long m_lLogEntryCount;
	bool CheckSaveFileName( CString& csFileName );
	bool CheckSaveFileNameCsv( CString& csFileName );
	bool ChoiceSaveLogCsv( CGTLogEntry* p_cEntry, DWORD dwStartTime, DWORD dwEndTime );
	BOOL ConvertLogToText();
	BOOL CanIMakeFile( CString strFile );

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CLogView)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnDisp();
	afx_msg void OnBtnDispCsv();
	afx_msg void OnBtnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_LOGVIEW_H__B9B0B5E7_45EA_4934_88AA_BB6DB0C89979__INCLUDED_)
