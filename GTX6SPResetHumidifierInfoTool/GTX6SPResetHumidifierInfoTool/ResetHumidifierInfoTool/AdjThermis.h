#if !defined(AFX_ADJTHERMIS_H__CCD75752_A2AD_4C42_A92F_7CB993738860__INCLUDED_)
#define AFX_ADJTHERMIS_H__CCD75752_A2AD_4C42_A92F_7CB993738860__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdjThermis.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CAdjThermis ダイアログ

class CAdjThermis : public CPropertyPage
{
	DECLARE_DYNCREATE(CAdjThermis)

// コンストラクション
public:
	CAdjThermis();
	~CAdjThermis();

// ダイアログ データ
	//{{AFX_DATA(CAdjThermis)
	enum { IDD = IDD_SERV_ADJ_THERMIS01 };
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CAdjThermis)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual LRESULT OnWizardBack();
	virtual BOOL OnQueryCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	int m_nPrevIDD;
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CAdjThermis)
		// メモ: ClassWizard はこの位置にメンバ関数を追加します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedCheck5minutes();
	BOOL m_bWait5Minutes;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ADJTHERMIS_H__CCD75752_A2AD_4C42_A92F_7CB993738860__INCLUDED_)
