#pragma once
#include "afxwin.h"


// CInitInkState ダイアログ

class CInitInkState : public CPropertyPage
{
	DECLARE_DYNAMIC(CInitInkState)

public:
	CInitInkState();
	virtual ~CInitInkState();
	int InitComboBox();

// ダイアログ データ
	enum { IDD = IDD_INIT_INK_STATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
private:
	CComboBox m_cmbbxK;
	CComboBox m_cmbbxYCM;
	CComboBox m_cmbbxW1;
	CComboBox m_cmbbxW2W4;
	int m_rdbtnInkStateSelect;
public:
	virtual BOOL OnInitDialog();
};
