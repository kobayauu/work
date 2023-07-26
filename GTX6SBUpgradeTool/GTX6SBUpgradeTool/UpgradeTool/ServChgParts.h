#if !defined(AFX_SERVCHGPARTS_H__5C045A89_3A22_4270_86FA_BCC02A882882__INCLUDED_)
#define AFX_SERVCHGPARTS_H__5C045A89_3A22_4270_86FA_BCC02A882882__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServChgParts.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CServChgParts ダイアログ

class CServChgParts : public CPropertyPage
{
	DECLARE_DYNCREATE(CServChgParts)

// コンストラクション
public:
	CServChgParts();
	~CServChgParts();

// ダイアログ データ
	//{{AFX_DATA(CServChgParts)
	enum { IDD = IDD_SERV_PARTS_CHG };
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CServChgParts)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	int m_nPrevIDD;

	int GetCheckedRadioID();

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SERVCHGPARTS_H__5C045A89_3A22_4270_86FA_BCC02A882882__INCLUDED_)
