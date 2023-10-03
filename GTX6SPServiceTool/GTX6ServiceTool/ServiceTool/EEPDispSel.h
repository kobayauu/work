#if !defined(AFX_EEPDISPSEL_H__7AE0AA2C_39C2_4281_A7D7_8E69808C7E68__INCLUDED_)
#define AFX_EEPDISPSEL_H__7AE0AA2C_39C2_4281_A7D7_8E69808C7E68__INCLUDED_

#include "GTLogFile.h"	// ClassView によって追加されました。
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// EEPDispSel.h : ヘッダー ファイル
//

#include "EEPVerManage.h"

#define MAX_EEPROM_DATA_COUNT 16

/////////////////////////////////////////////////////////////////////////////
// CEEPDispSel ダイアログ

class CEEPDispSel : public CDialog
{
// コンストラクション
public:
	CGTLogFile m_LogF;
	CString m_csLogFile;
	CEEPDispSel(CWnd* pParent = NULL);   // 標準のコンストラクタ

// ダイアログ データ
	//{{AFX_DATA(CEEPDispSel)
	enum { IDD = IDD_EEPROM_SEL_DISP };
	CListBox	m_List;
	//}}AFX_DATA


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CEEPDispSel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	//}}AFX_VIRTUAL

// インプリメンテーション
protected:
	BOOL GetEEPManageVer( EEP_MANAGE_VER* pManagaVer );

	int		m_nResID[MAX_EEPROM_DATA_COUNT];
	long	m_nSize[MAX_EEPROM_DATA_COUNT];
	LPBYTE	m_pData[MAX_EEPROM_DATA_COUNT];
	BOOL	m_bText[MAX_EEPROM_DATA_COUNT];

	BYTE* GetJustData( BYTE* pAllData , long nAllSize , long* pnJustDataSize );
	void  ReadEEPData();


	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CEEPDispSel)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnView();
	afx_msg void OnBtnClose();
	afx_msg void OnDestroy();
	afx_msg void OnDblclkList();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_EEPDISPSEL_H__7AE0AA2C_39C2_4281_A7D7_8E69808C7E68__INCLUDED_)
