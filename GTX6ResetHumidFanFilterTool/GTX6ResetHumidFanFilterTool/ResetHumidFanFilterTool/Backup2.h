#pragma once


// CBackup2 �_�C�A���O

class CBackup2 : public CPropertyPage
{
	DECLARE_DYNAMIC(CBackup2)

public:
	CBackup2();
	virtual ~CBackup2();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_BACKUP2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
};
