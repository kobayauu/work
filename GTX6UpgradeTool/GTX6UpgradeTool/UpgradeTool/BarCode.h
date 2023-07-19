#pragma once
#include "afxwin.h"


// CBarCode ダイアログ

class CBarCode : public CPropertyPage
{
	DECLARE_DYNAMIC(CBarCode)

public:
	CBarCode();
	virtual ~CBarCode();
	int Chk18Code(CString csCode);
	int ChkSerialCode(CString csCode);
// ダイアログ データ
	enum { IDD = IDD_BARCODE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
private:
	CString m_txtBarCodeMsg1;
	CString m_txtBarCodeMsg2;
	CString m_txtBarCodeMsg3;
	CEdit m_edtctrl18Code;
	CEdit m_edtctrlSerialCode;

	bool CBarCode::ChkRegionValue(const int nInputAsciicode);
	bool CBarCode::ChkModelValue(const int nInputAsciicode);
public:
	afx_msg void OnBnClickedButton1();
};
