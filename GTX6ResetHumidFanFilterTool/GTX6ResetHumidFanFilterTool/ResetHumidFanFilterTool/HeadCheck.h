#pragma once
#include "afxdtctl.h"


// CHeadCheck ダイアログ

class CHeadCheck : public CDialog
{
	DECLARE_DYNAMIC(CHeadCheck)

public:
	CHeadCheck(CWnd* pParent = NULL);   // 標準コンストラクター
	virtual ~CHeadCheck();

// ダイアログ データ
	enum { IDD = IDD_VIEW_HEADCHECK };

    CHeadArray* m_pWhiteHead;
    CHeadArray* m_pColorHead;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCheck();
	virtual BOOL OnInitDialog();
	CDateTimeCtrl m_DatePicker;

private:
    int CheckHead( CTime* pDate, CHeadArray* pHead );
};
