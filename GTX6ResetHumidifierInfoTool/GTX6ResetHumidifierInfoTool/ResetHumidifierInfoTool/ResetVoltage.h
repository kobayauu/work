#pragma once


// CResetVoltage ダイアログ

class CResetVoltage : public CPropertyPage
{
	DECLARE_DYNAMIC(CResetVoltage)

public:
	CResetVoltage();
	virtual ~CResetVoltage();

// ダイアログ データ
	enum { IDD = IDD_RESET_VOLTAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
};
