#pragma once


// CBackup ダイアログ

class CBackup : public CPropertyPage
{
	DECLARE_DYNAMIC(CBackup)

public:
	CBackup();
	virtual ~CBackup();

// ダイアログ データ
	enum { IDD = IDD_BACKUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual LRESULT OnWizardNext();
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
private:
	CString m_csBackupMsg1;
};
