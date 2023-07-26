#if !defined(AFX_PUMPCHG1_H__024C926E_8172_4E1B_B583_E7BC4FFE8463__INCLUDED_)
#define AFX_PUMPCHG1_H__024C926E_8172_4E1B_B583_E7BC4FFE8463__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PumpChg1.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CPumpChg1 ダイアログ

class CPumpChg1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPumpChg1)

// コンストラクション
public:
	CPumpChg1();
	~CPumpChg1();

// ダイアログ データ
	//{{AFX_DATA(CPumpChg1)
	enum { IDD = IDD_SERV_CHNAGE_PUMP1 };
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CPumpChg1)
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
	bool SetPumpChgDate();
	bool ChangeDataAll();
	int  PumpChangedInfoSetToPrinter();
	int m_nPrevIDD;
	DWORD m_dwChangedDate;
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CPumpChg1)
		// メモ: ClassWizard はこの位置にメンバ関数を追加します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_PUMPCHG1_H__024C926E_8172_4E1B_B583_E7BC4FFE8463__INCLUDED_)
