#pragma once


// CResetTube ダイアログ

class CResetTube : public CPropertyPage
{
	DECLARE_DYNAMIC(CResetTube)

public:
	CResetTube();
	virtual ~CResetTube();

// ダイアログ データ
	enum { IDD = IDD_SERV_RESET_TUBE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual LRESULT OnWizardBack();
};
