#pragma once
#include "afxcmn.h"



// ヘッドデータ 構造体

struct HEADDATA {
	CHAR	szName[ 8 ];
	DWORD	dwStart;
	DWORD	dwUpdate;
    DWORD   dwPrint;
    DWORD   dwOperate;
};
using CHeadArray = CArray <HEADDATA>;


// CHeadHistory ダイアログ

class CHeadHistory : public CDialog
{
	DECLARE_DYNAMIC(CHeadHistory)

public:
	CHeadHistory(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CHeadHistory();

// ダイアログ データ
	enum { IDD = IDD_VIEW_HEAD };

	CString m_csLogFile;
	CGTLogFile m_LogF;

    CHeadArray m_WhiteHead;
    CHeadArray m_ColorHead;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	// 生成されたメッセージ マップ関数
	//{{AFX_MSG(CEEPDispSel)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool ReadTagData(CByteArray* pBuf, LPCTSTR pTagName);
	bool DispTotalPrints(CByteArray* pBuf);
	bool InitListHead(CListCtrl* pList, BOOL bOperVer);
	bool DispListHead(CListCtrl* pList, CHeadArray* pHead);
	bool GetWhiteData(CByteArray* pBuf, CHeadArray* pHead, BOOL bOperVer);
	bool GetColorData(CByteArray* pBuf, CHeadArray* pHead, BOOL bOperVer);


public:
	CListCtrl m_WhiteList;
	CListCtrl m_ColorList;
	afx_msg void OnBnClickedBtnCheck();
};
