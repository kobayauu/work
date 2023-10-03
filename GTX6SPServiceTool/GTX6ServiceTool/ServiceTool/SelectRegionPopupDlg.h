#pragma once

#include "afxwin.h"
#include "afxdlgs.h"
#include "resource.h"


class SelectRegionPopupDlg : public CDialog
{
	DECLARE_DYNAMIC(SelectRegionPopupDlg)

	CString m_str15Code;
	CString m_strRegion;
	CString m_strModel;
	CString m_strAttach;

public:
	SelectRegionPopupDlg(CWnd* pParent = NULL); //標準コンストラクタ

	// ダイアログ データ
	enum { IDD = IDD_BARCODE_REGION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()

	// ダイアログ起動時の初期動作
	virtual BOOL OnInitDialog();

	// OKボタンを押されたときの処理
	afx_msg void OnBnClickedOk();

	int m_nRegionRadio = 0;
	int m_nModelRadio = 0;

	void SetRegion();
	void SetModel();
	void SetAttach();
};

