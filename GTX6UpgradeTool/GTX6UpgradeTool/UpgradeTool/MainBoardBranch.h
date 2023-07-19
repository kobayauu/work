#pragma once


// CMainBoardBranch ダイアログ

class CMainBoardBranch : public CPropertyPage
{
	DECLARE_DYNAMIC(CMainBoardBranch)

public:
	CMainBoardBranch();
	virtual ~CMainBoardBranch();

// ダイアログ データ
	enum { IDD = IDD_MAIN_BOARD_BRANCH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート
	int m_nPrevIDD;
	DECLARE_MESSAGE_MAP()
public:
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
	virtual BOOL OnSetActive();
private:
	int m_rdbtnMBBranchSelect;
};
