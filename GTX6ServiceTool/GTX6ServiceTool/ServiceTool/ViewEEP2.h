#if !defined(AFX_VIEWEEP2_H__81B5A2CF_7DC5_42D5_B096_DA5F9206D9B2__INCLUDED_)
#define AFX_VIEWEEP2_H__81B5A2CF_7DC5_42D5_B096_DA5F9206D9B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewEEP2.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CViewEEP2 ダイアログ

class CViewEEP2 : public CDialog
{
// コンストラクション
public:
	CString m_csSaveAsFile;
	CEEPFile* m_pRefEEP;
	CEEPFile* m_pEEP;
	CViewEEP2(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CViewEEP2)
	enum { IDD = IDD_VIEW_EEP };
	CListCtrl	m_MemList;
	CString	m_csBlockID;
	CString	m_csHeadVersion;
	CString	m_csVersion;
	CString	m_csHeadComment;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CViewEEP2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	bool CheckDiff( CMemEntry* pEntry, CMemEntry* pRefEntry );
	bool InitImageList();
	CImageList m_ImageListSmall;
	void ChangeDataStrForm(CString &s, CMemEntry *pEntry);
	void UpdateListCtrl();
	void InitListCtrl();
	void MoveRect(int nID, int nLeft, int nTop, int nRight, int nBottom);

	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CViewEEP2)
	virtual BOOL OnInitDialog();
	afx_msg void OnGetdispinfoList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnSaveas();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_VIEWEEP2_H__81B5A2CF_7DC5_42D5_B096_DA5F9206D9B2__INCLUDED_)
