#if !defined(AFX_ADJCRSPEED2_H__BB0A8B8A_49AE_4BA0_B71C_47795AFE896B__INCLUDED_)
#define AFX_ADJCRSPEED2_H__BB0A8B8A_49AE_4BA0_B71C_47795AFE896B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdjCRSpeed2.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CAdjCRSpeed2 ダイアログ

class CAdjCRSpeed2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CAdjCRSpeed2)

// コンストラクション
public:
	CAdjCRSpeed2();
	~CAdjCRSpeed2();

// ダイアログ データ
	//{{AFX_DATA(CAdjCRSpeed2)
	enum { IDD = IDD_SERV_ADJ_CR_SPEED2 };
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CAdjCRSpeed2)
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
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CAdjCRSpeed2)
		// メモ: ClassWizard はこの位置にメンバ関数を追加します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ADJCRSPEED2_H__BB0A8B8A_49AE_4BA0_B71C_47795AFE896B__INCLUDED_)
