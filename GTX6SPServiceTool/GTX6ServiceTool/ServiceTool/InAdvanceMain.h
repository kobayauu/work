#pragma once


// CInAdvanceMain �_�C�A���O

class CInAdvanceMain : public CPropertyPage
{
	DECLARE_DYNAMIC(CInAdvanceMain)

public:
	CInAdvanceMain();
	virtual ~CInAdvanceMain();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_IN_ADVANCE_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	int m_nPrevIDD;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
};
