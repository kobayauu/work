#pragma once


// CSetColorPage �_�C�A���O

class CSetColorPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CSetColorPage)

public:
	CSetColorPage();
	virtual ~CSetColorPage();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_SET_COLOR };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	int m_nPrevIDD;

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bDone;

	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
	afx_msg void OnBnClickedCheckSetposDone();
	afx_msg void OnBnClickedBtnOpenGtmainte();
};
