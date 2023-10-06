#if !defined(AFX_SERVPSEL_H__800ED690_3A34_4D10_8EE5_DDCA8FDB315B__INCLUDED_)
#define AFX_SERVPSEL_H__800ED690_3A34_4D10_8EE5_DDCA8FDB315B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServPSel.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CServPSel �_�C�A���O

class CServPSel : public CPropertyPage
{
	DECLARE_DYNCREATE(CServPSel)

// �R���X�g���N�V����
public:
	CServPSel();
	~CServPSel();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CServPSel)
	enum { IDD = IDD_SERV_PSEL };
	CComboBox	m_cbxPrinterName;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CServPSel)
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

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SERVPSEL_H__800ED690_3A34_4D10_8EE5_DDCA8FDB315B__INCLUDED_)
