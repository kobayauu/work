#if !defined(AFX_SERVSELOPE_H__BA8E64D2_F45D_4ABD_A26F_96F514D808DC__INCLUDED_)
#define AFX_SERVSELOPE_H__BA8E64D2_F45D_4ABD_A26F_96F514D808DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServSelOpe.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CServSelOpe �_�C�A���O

class CServSelOpe : public CPropertyPage
{
	DECLARE_DYNCREATE(CServSelOpe)

// �R���X�g���N�V����
public:
	CServSelOpe();
	~CServSelOpe();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CServSelOpe)
	enum { IDD = IDD_SERV_SEL_OPE };
	CString	m_csVersion;
	CString	m_csCopyRight;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CServSelOpe)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	int m_nPrevIDD;

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SERVSELOPE_H__BA8E64D2_F45D_4ABD_A26F_96F514D808DC__INCLUDED_)
