#pragma once
#include "afxwin.h"

#define GTX_HEAD_641_SP	_T("BGT60SBJ2000042")

// CSetEighteenCode ダイアログ

class CSetEighteenCode : public CPropertyPage
{
	DECLARE_DYNAMIC(CSetEighteenCode)

public:
	CSetEighteenCode();
	virtual ~CSetEighteenCode();
	int Chk18Code(CString csCode);
// ダイアログ データ
	enum { IDD = IDD_SET_18CODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
private:
	CString m_txt18CodeMsg1;
	CString m_txt18CodeMsg2;
	CEdit m_edtctrl18Code;
public:
	afx_msg void OnBnClickedUseFixed18Code();
private:
	CButton m_chkUseFixed18Code;
};
