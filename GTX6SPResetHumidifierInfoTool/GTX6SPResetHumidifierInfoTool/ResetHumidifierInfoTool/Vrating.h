#pragma once
#include "afxwin.h"


// CVrating �_�C�A���O

class CVrating : public CPropertyPage
{
	DECLARE_DYNAMIC(CVrating)

public:
	CVrating();
	virtual ~CVrating();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_VRATING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOpenVrating();
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
	afx_msg void OnBnClickedCheckVratingDone();
private:
	CButton m_chkbxVratingConfirm;
};
