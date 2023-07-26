#if !defined(AFX_ADJTHERMIS_H__CCD75752_A2AD_4C42_A92F_7CB993738860__INCLUDED_)
#define AFX_ADJTHERMIS_H__CCD75752_A2AD_4C42_A92F_7CB993738860__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdjThermis.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CAdjThermis �_�C�A���O

class CAdjThermis : public CPropertyPage
{
	DECLARE_DYNCREATE(CAdjThermis)

// �R���X�g���N�V����
public:
	CAdjThermis();
	~CAdjThermis();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAdjThermis)
	enum { IDD = IDD_SERV_ADJ_THERMIS01 };
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CAdjThermis)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual LRESULT OnWizardBack();
	virtual BOOL OnQueryCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	int m_nPrevIDD;
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CAdjThermis)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedCheck5minutes();
	BOOL m_bWait5Minutes;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_ADJTHERMIS_H__CCD75752_A2AD_4C42_A92F_7CB993738860__INCLUDED_)
