#pragma once


// CSetSamePage �_�C�A���O

class CSetSamePage : public CPropertyPage
{
	DECLARE_DYNAMIC(CSetSamePage)

public:
	CSetSamePage();
	virtual ~CSetSamePage();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_SET_SAME };

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
