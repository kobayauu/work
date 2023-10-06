#pragma once
#include "afxwin.h"


// CEEPROMRestore ダイアログ

class CEEPROMRestore : public CPropertyPage
{
	DECLARE_DYNAMIC(CEEPROMRestore)

public:
	CEEPROMRestore();
	virtual ~CEEPROMRestore();
	BOOL WriteDateToPrinter();
	void ViewDateType();
	void UpdateTimeDisp();

// ダイアログ データ
	enum { IDD = IDD_EEPROM_RESTORE1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	int m_nPrevIDD;
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
	afx_msg void OnBnClickedCheckRestoreEepromComfirmation();
private:
	BOOL m_bDone;
	UINT m_nMonth;
	UINT m_nDay;
	UINT m_nYear;
	UINT m_nHour;
	UINT m_nMinute;
	UINT m_nSecond;
	CString	m_csDateType;
public:
	afx_msg void OnBnClickedUsePc();
private:
	CButton m_chkUsePC;
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
