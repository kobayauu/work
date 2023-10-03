#if !defined(AFX_ADJTHERMIS2_H__CEE24965_BE0F_4EA9_956C_1CD7EB1A8E0B__INCLUDED_)
#define AFX_ADJTHERMIS2_H__CEE24965_BE0F_4EA9_956C_1CD7EB1A8E0B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdjThermis2.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CAdjThermis2 ダイアログ

class CAdjThermis2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CAdjThermis2)

// コンストラクション
public:
	CAdjThermis2();
	~CAdjThermis2();

// ダイアログ データ
	//{{AFX_DATA(CAdjThermis2)
	enum { IDD = IDD_SERV_ADJ_THERMIS02 };
	double	m_fCTemp;
	double	m_fFTemp;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CAdjThermis2)
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
	void OnChangeTemperature();
	int  ChangeTempUnit( double fTemp, bool bF );
	bool m_bFahrenheit;
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CAdjThermis2)
	afx_msg void OnRadioFahrenheight();
	afx_msg void OnRadioCelsius();
	afx_msg void OnChangeEditCtemp();
	afx_msg void OnChangeEditFtemp();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_ADJTHERMIS2_H__CEE24965_BE0F_4EA9_956C_1CD7EB1A8E0B__INCLUDED_)
