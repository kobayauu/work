#pragma once


// CFirePage ダイアログ

class CFirePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CFirePage)

public:
	CFirePage();
	virtual ~CFirePage();

// ダイアログ データ
	enum { IDD = IDD_FIRE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	int m_nPrevIDD;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
	BOOL m_bDone;
	afx_msg void OnBnClickedCheckFireDone();
	afx_msg void OnBnClickedBtnOpenGtmainte();
	afx_msg void OnStnClickedFire11();
};
