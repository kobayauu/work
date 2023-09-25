#if !defined(AFX_BATTERYCHG2_H__FCE21E40_8259_4310_93A4_15E666E2B65B__INCLUDED_)
#define AFX_BATTERYCHG2_H__FCE21E40_8259_4310_93A4_15E666E2B65B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BatteryChg2.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CBatteryChg2 ダイアログ

class CBatteryChg2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CBatteryChg2)

// コンストラクション
public:
	CBatteryChg2();
	~CBatteryChg2();

// ダイアログ データ
	//{{AFX_DATA(CBatteryChg2)
	enum { IDD = IDD_SERV_CHNAGE_BATTERY2 };
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CBatteryChg2)
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
	//{{AFX_MSG(CBatteryChg2)
		// メモ: ClassWizard はこの位置にメンバ関数を追加します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_BATTERYCHG2_H__FCE21E40_8259_4310_93A4_15E666E2B65B__INCLUDED_)
