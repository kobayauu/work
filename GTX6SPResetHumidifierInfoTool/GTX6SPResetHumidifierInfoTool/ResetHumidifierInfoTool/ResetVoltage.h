#pragma once


// CResetVoltage �_�C�A���O

class CResetVoltage : public CPropertyPage
{
	DECLARE_DYNAMIC(CResetVoltage)

public:
	CResetVoltage();
	virtual ~CResetVoltage();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_RESET_VOLTAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
};
