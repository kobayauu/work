#pragma once


// CIPClear ダイアログ

class CIPClear : public CPropertyPage
{
	DECLARE_DYNAMIC(CIPClear)

public:
	CIPClear();
	virtual ~CIPClear();

// ダイアログ データ
	enum { IDD = IDD_IP_CLEAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
private:
	CString m_txtIPClear;
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
};
