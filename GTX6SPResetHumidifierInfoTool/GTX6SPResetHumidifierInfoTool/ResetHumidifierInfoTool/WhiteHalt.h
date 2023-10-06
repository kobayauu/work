#pragma once


// CWhiteHalt ダイアログ

class CWhiteHalt : public CPropertyPage
{
	DECLARE_DYNAMIC(CWhiteHalt)

public:
	CWhiteHalt();
	virtual ~CWhiteHalt();

// ダイアログ データ
	enum { IDD = IDD_WHITE_HALT2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
private:
	int m_rdbtnWhiteUse;
};
