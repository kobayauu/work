#if !defined(AFX_CRMOTORCHG1_H__6E2BCA31_EDE3_42B8_AE88_90E9192EAA86__INCLUDED_)
#define AFX_CRMOTORCHG1_H__6E2BCA31_EDE3_42B8_AE88_90E9192EAA86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CRMotorChg1.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CCRMotorChg1 ダイアログ

class CCRMotorChg1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CCRMotorChg1)

// コンストラクション
public:
	int m_nPrevIDD;
	CCRMotorChg1();
	~CCRMotorChg1();

// ダイアログ データ
	//{{AFX_DATA(CCRMotorChg1)
	enum { IDD = IDD_SERV_CR_CHANGE };
		// メモ - ClassWizard はこの位置にデータ メンバを追加します。
		//    この位置に生成されるコードを編集しないでください。
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CCRMotorChg1)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnQueryCancel();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	DWORD m_dwChangedDate;
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CCRMotorChg1)
		// メモ: ClassWizard はこの位置にメンバ関数を追加します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_CRMOTORCHG1_H__6E2BCA31_EDE3_42B8_AE88_90E9192EAA86__INCLUDED_)
