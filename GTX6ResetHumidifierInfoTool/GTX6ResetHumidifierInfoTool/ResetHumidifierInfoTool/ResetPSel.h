#if !defined(AFX_RESETPSEL_H__800ED690_3A34_4D10_8EE5_DDCA8FDB315B__INCLUDED_)
#define AFX_RESETPSEL_H__800ED690_3A34_4D10_8EE5_DDCA8FDB315B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ResetPSel.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CResetPSel �_�C�A���O

class CResetPSel : public CPropertyPage
{
	DECLARE_DYNCREATE(CResetPSel)

// �R���X�g���N�V����
public:
	CResetPSel();
	~CResetPSel();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CResetPSel)
	enum { IDD = IDD_RESET_PSEL };
	CComboBox	m_cbxPrinterName;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CUpgPSel)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	int m_nPrevIDD;
	bool InitPrinterList();
	CString m_csPrinterName;
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CServPSel)
	afx_msg void OnSelchangeCbxPrinter();
	afx_msg void OnBtnRescan();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CString m_csVersion;
	CString m_csCopyRight;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_UPGPSEL_H__800ED690_3A34_4D10_8EE5_DDCA8FDB315B__INCLUDED_)
