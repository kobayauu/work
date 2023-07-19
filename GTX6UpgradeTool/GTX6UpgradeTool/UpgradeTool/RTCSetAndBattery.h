#pragma once
#include "afxwin.h"


// CRTCSetAndBattery ダイアログ

class CRTCSetAndBattery : public CPropertyPage
{
	DECLARE_DYNAMIC(CRTCSetAndBattery)

public:
	CRTCSetAndBattery();
	virtual ~CRTCSetAndBattery();
	BOOL WriteDateToPrinter();
	void ViewDateType();
	void UpdateTimeDisp();

// ダイアログ データ
	enum { IDD = IDD_RTC_AND_BATTERY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedUsePc();
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
private:
	CString m_txtRTCSetAndResetEEPROMMsg1;
	CButton m_chkUsePC;
	UINT m_Month;
	UINT m_Day;
	UINT m_Year;
	UINT m_Hour;
	UINT m_Minute;
	UINT m_Second;
	CString	m_csDateType;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
