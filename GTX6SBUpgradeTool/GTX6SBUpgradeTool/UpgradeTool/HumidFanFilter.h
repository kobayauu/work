#pragma once

// HumidFanFilter �_�C�A���O

class CHumidFanFilter : public CPropertyPage
{
	DECLARE_DYNAMIC(CHumidFanFilter)

public:
	CHumidFanFilter();
	virtual ~CHumidFanFilter();

	// �_�C�A���O �f�[�^
	enum { IDD = IDD_HUMIDFAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	virtual LRESULT OnWizardNext();
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
};


