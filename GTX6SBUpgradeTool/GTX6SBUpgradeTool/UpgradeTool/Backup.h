#pragma once


// CBackup �_�C�A���O

class CBackup : public CPropertyPage
{
	DECLARE_DYNAMIC(CBackup)

public:
	CBackup();
	virtual ~CBackup();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_BACKUP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	virtual LRESULT OnWizardNext();
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
private:
	CString m_csBackupMsg1;
};
