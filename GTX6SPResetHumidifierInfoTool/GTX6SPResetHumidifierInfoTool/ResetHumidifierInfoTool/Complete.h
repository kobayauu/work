#pragma once


// CComplete �_�C�A���O

class CComplete : public CPropertyPage
{
	DECLARE_DYNAMIC(CComplete)

public:
	CComplete();
	virtual ~CComplete();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_COMPLETE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual BOOL OnWizardFinish();
private:
	CString m_csCompleteMsg;
};
