#if !defined(AFX_CHKLOG1_H__C330186D_1870_489E_83DB_52562BB80BBE__INCLUDED_)
#define AFX_CHKLOG1_H__C330186D_1870_489E_83DB_52562BB80BBE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChkLog1.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CChkLog1 �_�C�A���O

class CChkLog1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CChkLog1)

// �R���X�g���N�V����
public:
	CChkLog1();
	~CChkLog1();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CChkLog1)
	enum { IDD = IDD_SERV_LOG_CHECK1 };
	CString	m_csLogFileName;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CChkLog1)
	public:
	virtual BOOL OnQueryCancel();
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	bool m_bFirst;
	int m_nPrevIDD;
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CChkLog1)
	afx_msg void OnBrowse();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_CHKLOG1_H__C330186D_1870_489E_83DB_52562BB80BBE__INCLUDED_)
