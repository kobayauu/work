#if !defined(AFX_SERVFIRST_H__75A39002_BC91_4891_B243_ADF3778EA540__INCLUDED_)
#define AFX_SERVFIRST_H__75A39002_BC91_4891_B243_ADF3778EA540__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServFirst.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CServFirst ダイアログ

class CServFirst : public CPropertyPage
{
	DECLARE_DYNCREATE(CServFirst)

// コンストラクション
public:
	int m_nPrevIDD;
	CServFirst();
	~CServFirst();

// ダイアログ データ
	//{{AFX_DATA(CServFirst)
	enum { IDD = IDD_SERV_FIRST };
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CServFirst)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual LRESULT OnWizardBack();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CServFirst)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SERVFIRST_H__75A39002_BC91_4891_B243_ADF3778EA540__INCLUDED_)
