#if !defined(AFX_SERVCHGPARTS_H__5C045A89_3A22_4270_86FA_BCC02A882882__INCLUDED_)
#define AFX_SERVCHGPARTS_H__5C045A89_3A22_4270_86FA_BCC02A882882__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServChgParts.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CServChgParts �_�C�A���O

class CServChgParts : public CPropertyPage
{
	DECLARE_DYNCREATE(CServChgParts)

// �R���X�g���N�V����
public:
	CServChgParts();
	~CServChgParts();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CServChgParts)
	enum { IDD = IDD_SERV_PARTS_CHG };
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CServChgParts)
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

	int GetCheckedRadioID();

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SERVCHGPARTS_H__5C045A89_3A22_4270_86FA_BCC02A882882__INCLUDED_)
