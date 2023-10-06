#pragma once

// HumidFanFilter ダイアログ

class CHumidFanFilter : public CPropertyPage
{
	DECLARE_DYNAMIC(CHumidFanFilter)

public:
	CHumidFanFilter();
	virtual ~CHumidFanFilter();

	// ダイアログ データ
	enum { IDD = IDD_HUMIDFAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual LRESULT OnWizardNext();
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
};


