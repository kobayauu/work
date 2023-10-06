#pragma once


// CComplete ダイアログ

class CComplete : public CPropertyPage
{
	DECLARE_DYNAMIC(CComplete)

public:
	CComplete();
	virtual ~CComplete();

// ダイアログ データ
	enum { IDD = IDD_COMPLETE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual BOOL OnWizardFinish();
private:
	CString m_csCompleteMsg;
};
