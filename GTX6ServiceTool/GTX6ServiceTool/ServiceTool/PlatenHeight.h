#pragma once


// CPlatenHeight �_�C�A���O

class CPlatenHeight : public CPropertyPage
{
	DECLARE_DYNAMIC(CPlatenHeight)

public:
	CPlatenHeight();
	virtual ~CPlatenHeight();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_PLANTEN_HEIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	int m_nPrevIDD;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
	afx_msg void OnBnClickedCheckPlatenHeightDone();
private:
	BOOL m_bDone;
};
