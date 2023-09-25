#if !defined(AFX_ADJTHERMIS3_H__0F9604C7_86E2_4699_9894_F7BEA9A92FBC__INCLUDED_)
#define AFX_ADJTHERMIS3_H__0F9604C7_86E2_4699_9894_F7BEA9A92FBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdjThermis3.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CAdjThermis3 ダイアログ

class CAdjThermis3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CAdjThermis3)

// コンストラクション
public:
	CAdjThermis3();
	~CAdjThermis3();

// ダイアログ データ
	//{{AFX_DATA(CAdjThermis3)
	enum { IDD = IDD_SERV_ADJ_THERMIS03 };
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CAdjThermis3)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual LRESULT OnWizardBack();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	int m_nPrevIDD;
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CAdjThermis3)
		// メモ: ClassWizard はこの位置にメンバ関数を追加します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ADJTHERMIS3_H__0F9604C7_86E2_4699_9894_F7BEA9A92FBC__INCLUDED_)
