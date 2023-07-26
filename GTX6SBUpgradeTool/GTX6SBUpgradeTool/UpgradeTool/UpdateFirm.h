#pragma once
#include "afxwin.h"

#define VALID_FIRM_VER 0x02000000

// CUpdateFirm ダイアログ

class CUpdateFirm : public CPropertyPage
{
	DECLARE_DYNAMIC(CUpdateFirm)

public:
	CUpdateFirm();
	virtual ~CUpdateFirm();

// ダイアログ データ
	enum { IDD = IDD_UPDATE_FIRM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnOpenFirmUpdate();
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
	afx_msg void OnBnClickedCheckUpdateFirmDone();
private:
	CButton m_chkbxUpdateFirmConfirm;
};
