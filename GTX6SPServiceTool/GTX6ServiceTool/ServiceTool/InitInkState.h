#pragma once
#include "afxwin.h"


// CInitInkState �_�C�A���O

class CInitInkState : public CPropertyPage
{
	DECLARE_DYNAMIC(CInitInkState)

public:
	CInitInkState();
	virtual ~CInitInkState();
	int InitComboBox();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_INIT_INK_STATE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

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
