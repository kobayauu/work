#if !defined(AFX_UPGPSEL_H__800ED690_3A34_4D10_8EE5_DDCA8FDB315B__INCLUDED_)
#define AFX_UPGPSEL_H__800ED690_3A34_4D10_8EE5_DDCA8FDB315B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UpgPSel.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CUpgPSel ダイアログ

class CUpgPSel : public CPropertyPage
{
	DECLARE_DYNCREATE(CUpgPSel)

// コンストラクション
public:
	CUpgPSel();
	~CUpgPSel();

// ダイアログ データ
	//{{AFX_DATA(CUpgPSel)
	enum { IDD = IDD_UPG_PSEL };
	CComboBox	m_cbxPrinterName;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CUpgPSel)
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
	bool InitPrinterList();
	CString m_csPrinterName;
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CServPSel)
	afx_msg void OnSelchangeCbxPrinter();
	afx_msg void OnBtnRescan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CString m_csVersion;
	CString m_csCopyRight;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_UPGPSEL_H__800ED690_3A34_4D10_8EE5_DDCA8FDB315B__INCLUDED_)
