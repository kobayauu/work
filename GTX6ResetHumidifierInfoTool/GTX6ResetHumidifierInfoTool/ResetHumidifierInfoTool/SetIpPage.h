#pragma once


// CSetIpPage ダイアログ

class CSetIpPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CSetIpPage)

public:
	CSetIpPage();
	virtual ~CSetIpPage();

// ダイアログ データ
	enum { IDD = IDD_SET_IP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bDone;

	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
	afx_msg void OnBnClickedCheckSetipDone();
	afx_msg void OnBnClickedBtnOpenGtmainte();
};
