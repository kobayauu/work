#pragma once
#include "afxwin.h"


// CRTCSetAndResetEEPROM ダイアログ

class CRTCSetAndResetEEPROM : public CPropertyPage
{
	DECLARE_DYNAMIC(CRTCSetAndResetEEPROM)

public:
	CRTCSetAndResetEEPROM();
	virtual ~CRTCSetAndResetEEPROM();
	BOOL WriteDateToPrinter();
	void ViewDateType();
	void UpdateTimeDisp();

// ダイアログ データ
	enum { IDD = IDD_RTC_SET_AND_RESET_EEPROM };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
private:
	CString m_txtRTCSetAndResetEEPROMMsg1;
	CButton m_chkUsePC;
	UINT m_nMonth;
	UINT m_nDay;
	UINT m_nYear;
	UINT m_nHour;
	UINT m_nMinute;
	UINT m_nSecond;
	CString	m_csDateType;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedUsePc();
};
