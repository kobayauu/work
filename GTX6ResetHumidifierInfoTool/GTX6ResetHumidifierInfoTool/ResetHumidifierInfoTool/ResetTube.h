#pragma once


// CResetTube �_�C�A���O

class CResetTube : public CPropertyPage
{
	DECLARE_DYNAMIC(CResetTube)

public:
	CResetTube();
	virtual ~CResetTube();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_SERV_RESET_TUBE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual LRESULT OnWizardBack();
};
