#pragma once


// CIPClear �_�C�A���O

class CIPClear : public CPropertyPage
{
	DECLARE_DYNAMIC(CIPClear)

public:
	CIPClear();
	virtual ~CIPClear();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_IP_CLEAR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
private:
	CString m_txtIPClear;
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
};
