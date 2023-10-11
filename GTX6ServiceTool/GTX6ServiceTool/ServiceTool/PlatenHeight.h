#pragma once


// CPlatenHeight ダイアログ

class CPlatenHeight : public CPropertyPage
{
	DECLARE_DYNAMIC(CPlatenHeight)

public:
	CPlatenHeight();
	virtual ~CPlatenHeight();

// ダイアログ データ
	enum { IDD = IDD_PLANTEN_HEIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	int m_nPrevIDD;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
	afx_msg void OnBnClickedCheckPlatenHeightDone();
private:
	BOOL m_bDone;
};
