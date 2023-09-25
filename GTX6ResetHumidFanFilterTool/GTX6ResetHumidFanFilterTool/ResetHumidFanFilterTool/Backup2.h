#pragma once


// CBackup2 ダイアログ

class CBackup2 : public CPropertyPage
{
	DECLARE_DYNAMIC(CBackup2)

public:
	CBackup2();
	virtual ~CBackup2();

// ダイアログ データ
	enum { IDD = IDD_BACKUP2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
};
