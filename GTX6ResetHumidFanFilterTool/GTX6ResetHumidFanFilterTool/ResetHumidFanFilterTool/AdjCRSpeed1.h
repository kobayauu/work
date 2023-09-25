#if !defined(AFX_ADJCRSPEED1_H__8F800026_4FFE_4918_B5A3_A531FB6F5EE8__INCLUDED_)
#define AFX_ADJCRSPEED1_H__8F800026_4FFE_4918_B5A3_A531FB6F5EE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdjCRSpeed1.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CAdjCRSpeed1 ダイアログ

class CAdjCRSpeed1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CAdjCRSpeed1)

// コンストラクション
public:
	CAdjCRSpeed1();
	~CAdjCRSpeed1();

// ダイアログ データ
	//{{AFX_DATA(CAdjCRSpeed1)
	enum { IDD = IDD_SERV_ADJ_CR_SPEED1 };
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CAdjCRSpeed1)
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
	//{{AFX_MSG(CAdjCRSpeed1)
		// メモ: ClassWizard はこの位置にメンバ関数を追加します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ADJCRSPEED1_H__8F800026_4FFE_4918_B5A3_A531FB6F5EE8__INCLUDED_)
