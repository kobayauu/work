#pragma once


// CWhiteHalt �_�C�A���O

class CWhiteHalt : public CPropertyPage
{
	DECLARE_DYNAMIC(CWhiteHalt)

public:
	CWhiteHalt();
	virtual ~CWhiteHalt();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_WHITE_HALT2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
private:
	int m_rdbtnWhiteUse;
};
