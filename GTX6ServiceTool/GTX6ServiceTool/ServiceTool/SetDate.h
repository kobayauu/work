#if !defined(AFX_SETDATE_H__6465DBFF_3E42_4585_8AE3_CABB67509F7D__INCLUDED_)
#define AFX_SETDATE_H__6465DBFF_3E42_4585_8AE3_CABB67509F7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetDate.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CSetDate ダイアログ

class CSetDate : public CPropertyPage
{
	DECLARE_DYNCREATE(CSetDate)

// コンストラクション
public:
	CSetDate();
	~CSetDate();

// ダイアログ データ
	//{{AFX_DATA(CSetDate)
	enum { IDD = IDD_SERV_SET_DATE };
	CButton	m_chkUsePC;
	UINT	m_nDay;
	UINT	m_nHour;
	UINT	m_nMinute;
	UINT	m_nMonth;
	UINT	m_nSecond;
	UINT	m_nYear;
	CString	m_csDateType;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CSetDate)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
	virtual BOOL OnQueryCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	void ViewDateType();
	CTime m_cTimeManufacture;
	BOOL SetLotNumber(int nNumber);
	BOOL m_bClear;
	BOOL WriteDateToPrinter();
	void UpdateTimeDisp();
	int m_nPrevIDD;
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CSetDate)
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnUsePc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_SETDATE_H__6465DBFF_3E42_4585_8AE3_CABB67509F7D__INCLUDED_)
