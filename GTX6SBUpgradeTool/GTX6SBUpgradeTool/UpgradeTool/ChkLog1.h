#if !defined(AFX_CHKLOG1_H__C330186D_1870_489E_83DB_52562BB80BBE__INCLUDED_)
#define AFX_CHKLOG1_H__C330186D_1870_489E_83DB_52562BB80BBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChkLog1.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CChkLog1 ダイアログ

class CChkLog1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CChkLog1)

// コンストラクション
public:
	CChkLog1();
	~CChkLog1();

// ダイアログ データ
	//{{AFX_DATA(CChkLog1)
	enum { IDD = IDD_SERV_LOG_CHECK1 };
	CString	m_csLogFileName;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CChkLog1)
	public:
	virtual BOOL OnQueryCancel();
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	bool m_bFirst;
	int m_nPrevIDD;
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CChkLog1)
	afx_msg void OnBrowse();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CHKLOG1_H__C330186D_1870_489E_83DB_52562BB80BBE__INCLUDED_)
