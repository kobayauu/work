#if !defined(AFX_SERVSELOPE_H__BA8E64D2_F45D_4ABD_A26F_96F514D808DC__INCLUDED_)
#define AFX_SERVSELOPE_H__BA8E64D2_F45D_4ABD_A26F_96F514D808DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServSelOpe.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CServSelOpe ダイアログ

class CServSelOpe : public CPropertyPage
{
	DECLARE_DYNCREATE(CServSelOpe)

// コンストラクション
public:
	CServSelOpe();
	~CServSelOpe();

// ダイアログ データ
	//{{AFX_DATA(CServSelOpe)
	enum { IDD = IDD_SERV_SEL_OPE };
	CString	m_csVersion;
	CString	m_csCopyRight;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CServSelOpe)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	int m_nPrevIDD;

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SERVSELOPE_H__BA8E64D2_F45D_4ABD_A26F_96F514D808DC__INCLUDED_)
