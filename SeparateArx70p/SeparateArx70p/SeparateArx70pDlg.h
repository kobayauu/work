// SeparateArx70pDlg.h : ヘッダー ファイル
//

#pragma once


// SeparateArx70pDlg ダイアログ
class CSeparateArx70pDlg : public CDialog
{
// コンストラクション
public:
	CSeparateArx70pDlg(CWnd* pParent = NULL);	// 標準コンストラクタ

// ダイアログ データ
	enum { IDD = IDD_SEPARATEW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV サポート


// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	int SeparateArx70polor(CString FileName);
};
