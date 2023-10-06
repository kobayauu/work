#if !defined(AFX_VIEWLOGFILE_H__A1D184A2_0F1A_4775_A550_26143E0982E3__INCLUDED_)
#define AFX_VIEWLOGFILE_H__A1D184A2_0F1A_4775_A550_26143E0982E3__INCLUDED_

#include "GTLogFile.h"	// ClassView によって追加されました。
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewLogFile.h : ヘッダー ファイル
//

/////////////////////////////////////////////////////////////////////////////
// CViewLogFile ダイアログ

class CViewLogFile : public CPropertyPage
{
	DECLARE_DYNCREATE(CViewLogFile)

// コンストラクション
public:
	CViewLogFile();
	~CViewLogFile();

// ダイアログ データ
	//{{AFX_DATA(CViewLogFile)
	enum { IDD = IDD_SERV_VIEW_LOG };
	CString	m_csLogFile;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。

	//{{AFX_VIRTUAL(CViewLogFile)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	bool CheckLogFile();
	CGTLogFile m_LogFile;
	int m_nPrevIDD;
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CViewLogFile)
	afx_msg void OnBtnSettings();
	afx_msg void OnBtnLog();
	afx_msg void OnBtnInfo();
	afx_msg void OnBtnLogAnal();
	afx_msg void OnBtnStat();
	afx_msg void OnBtnHead();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_VIEWLOGFILE_H__A1D184A2_0F1A_4775_A550_26143E0982E3__INCLUDED_)
