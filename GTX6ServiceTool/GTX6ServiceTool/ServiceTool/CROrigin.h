#pragma once


// CCROrigin �_�C�A���O

class CCROrigin : public CPropertyPage
{
	DECLARE_DYNAMIC(CCROrigin)

public:
	CCROrigin();
	virtual ~CCROrigin();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_SERV_CR_ORIGIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bDone;
	afx_msg void OnBnClickedCheckDone();
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual LRESULT OnWizardBack();
};
