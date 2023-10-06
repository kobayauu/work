#if !defined(AFX_SETDATE2_H__3169F621_3F0C_4AC7_858C_C014BBF318C0__INCLUDED_)
#define AFX_SETDATE2_H__3169F621_3F0C_4AC7_858C_C014BBF318C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetDate2.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CSetDate2 ダイアログ

class CSetDate2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CSetDate2)

// コンストラクション
public:
	CSetDate2();
	~CSetDate2();

// ダイアログ データ
	//{{AFX_DATA(CSetDate2)
	enum { IDD = IDD_SERV_SET_DATE2 };
		// メモ - ClassWizard はこの位置にデータ メンバを追加します。
		//    この位置に生成されるコードを編集しないでください。
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CSetDate2)
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
	//{{AFX_MSG(CSetDate2)
		// メモ: ClassWizard はこの位置にメンバ関数を追加します。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SETDATE2_H__3169F621_3F0C_4AC7_858C_C014BBF318C0__INCLUDED_)
