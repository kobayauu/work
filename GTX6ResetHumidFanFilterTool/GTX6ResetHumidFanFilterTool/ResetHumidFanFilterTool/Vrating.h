#pragma once
#include "afxwin.h"


// CVrating ダイアログ

class CVrating : public CPropertyPage
{
	DECLARE_DYNAMIC(CVrating)

public:
	CVrating();
	virtual ~CVrating();

// ダイアログ データ
	enum { IDD = IDD_VRATING };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

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
