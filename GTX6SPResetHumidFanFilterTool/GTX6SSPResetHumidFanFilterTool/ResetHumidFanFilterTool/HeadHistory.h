#pragma once
#include "afxcmn.h"



// ヘッドデータ 構造体

struct HEADDATA {
	CHAR	szName[ 8 ];	//シリアル番号
	DWORD	dwStart;		//使用開始
	DWORD	dwUpdate;		//更新
    DWORD   dwPrint;		//印刷枚数
    DWORD   dwOperate;		//印刷動作回数
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

    CHeadArray m_White1Head;
    CHeadArray m_White2Head;
    CHeadArray m_Color1Head;
    CHeadArray m_Color2Head;
    CHeadArray m_Special1Head;
    CHeadArray m_Special2Head;

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
	bool InitListHead(CListCtrl* pList);
	bool DispListHead(CListCtrl* pList, CHeadArray* pHead);
	bool GetHeadData(CByteArray* pBuf, int nNo, CHeadArray* pHead);


public:
	CListCtrl m_White1List;
	CListCtrl m_White2List;
	CListCtrl m_Color1List;
	CListCtrl m_Color2List;
	CListCtrl m_Special1List;
	CListCtrl m_Special2List;
	afx_msg void OnBnClickedBtnCheck();
};
