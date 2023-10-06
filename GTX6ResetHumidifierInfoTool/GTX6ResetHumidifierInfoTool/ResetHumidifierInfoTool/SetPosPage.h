#pragma once


// CSetPosPage ダイアログ

class CSetPosPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CSetPosPage)

public:
	CSetPosPage();
	virtual ~CSetPosPage();

// ダイアログ データ
	enum { IDD = IDD_SET_POS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

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
