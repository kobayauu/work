#if !defined(AFX_SERVFIRST_H__75A39002_BC91_4891_B243_ADF3778EA540__INCLUDED_)
#define AFX_SERVFIRST_H__75A39002_BC91_4891_B243_ADF3778EA540__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServFirst.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CServFirst �_�C�A���O

class CServFirst : public CPropertyPage
{
	DECLARE_DYNCREATE(CServFirst)

// �R���X�g���N�V����
public:
	int m_nPrevIDD;
	CServFirst();
	~CServFirst();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CServFirst)
	enum { IDD = IDD_SERV_FIRST };
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CServFirst)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual LRESULT OnWizardBack();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CServFirst)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SERVFIRST_H__75A39002_BC91_4891_B243_ADF3778EA540__INCLUDED_)
