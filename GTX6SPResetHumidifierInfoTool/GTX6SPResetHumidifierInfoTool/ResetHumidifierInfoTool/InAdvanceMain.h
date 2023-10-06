#pragma once


// CInAdvanceMain ダイアログ

class CInAdvanceMain : public CPropertyPage
{
	DECLARE_DYNAMIC(CInAdvanceMain)

public:
	CInAdvanceMain();
	virtual ~CInAdvanceMain();

// ダイアログ データ
	enum { IDD = IDD_IN_ADVANCE_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	int m_nPrevIDD;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
};
