#if !defined(AFX_PUMPCHG2_H__FCE21E40_8259_4310_93A4_15E666E2B65B__INCLUDED_)
#define AFX_PUMPCHG2_H__FCE21E40_8259_4310_93A4_15E666E2B65B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PumpChg2.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CPumpChg2 ダイアログ

class CPumpChg2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPumpChg2)

// コンストラクション
public:
	CPumpChg2();
	~CPumpChg2();

// ダイアログ データ
	//{{AFX_DATA(CPumpChg2)
	enum { IDD = IDD_SERV_CHNAGE_PUMP2 };
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CPumpChg2)
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
	int m_nPrevIDD;
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CPumpChg2)
		// メモ: ClassWizard はこの位置にメンバ関数を追加します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_PUMPCHG2_H__FCE21E40_8259_4310_93A4_15E666E2B65B__INCLUDED_)
