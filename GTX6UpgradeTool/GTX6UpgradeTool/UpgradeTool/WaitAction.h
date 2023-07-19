#pragma once


// CWaitAction ダイアログ

class CWaitAction : public CPropertyPage
{
	DECLARE_DYNAMIC(CWaitAction)

public:
	CWaitAction();
	virtual ~CWaitAction();

// ダイアログ データ
	enum { IDD = IDD_WAIT_ACTION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual LRESULT OnWizardNext();
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual BOOL OnWizardFinish();
private:
	CString m_csWaitActionMsg1;
};
