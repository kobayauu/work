#pragma once


// CCROrigin ダイアログ

class CCROrigin : public CPropertyPage
{
	DECLARE_DYNAMIC(CCROrigin)

public:
	CCROrigin();
	virtual ~CCROrigin();

// ダイアログ データ
	enum { IDD = IDD_SERV_CR_ORIGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bDone;
	afx_msg void OnBnClickedCheckDone();
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual LRESULT OnWizardBack();
};
