#pragma once


// CPlatenFeeding �_�C�A���O

class CPlatenFeeding : public CPropertyPage
{
	DECLARE_DYNAMIC(CPlatenFeeding)

public:
	CPlatenFeeding();
	virtual ~CPlatenFeeding();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_PLANTEN_FEEDING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	int m_nPrevIDD;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
	afx_msg void OnBnClickedCheckPlatenFeedingDone();
	afx_msg void OnBnClickedBtnOpenGtmainte();
private:
	BOOL m_bDone;
};
