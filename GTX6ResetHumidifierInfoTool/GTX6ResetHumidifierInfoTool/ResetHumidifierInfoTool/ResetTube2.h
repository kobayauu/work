#pragma once


// CResetTube2 �_�C�A���O

class CResetTube2 : public CPropertyPage
{
	DECLARE_DYNAMIC(CResetTube2)

public:
	CResetTube2();
	virtual ~CResetTube2();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_SERV_RESET_TUBE2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual LRESULT OnWizardBack();
};
