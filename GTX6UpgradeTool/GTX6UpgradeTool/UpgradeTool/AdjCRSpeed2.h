#if !defined(AFX_ADJCRSPEED2_H__BB0A8B8A_49AE_4BA0_B71C_47795AFE896B__INCLUDED_)
#define AFX_ADJCRSPEED2_H__BB0A8B8A_49AE_4BA0_B71C_47795AFE896B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdjCRSpeed2.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CAdjCRSpeed2 �_�C�A���O

class CAdjCRSpeed2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CAdjCRSpeed2)

// �R���X�g���N�V����
public:
	CAdjCRSpeed2();
	~CAdjCRSpeed2();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAdjCRSpeed2)
	enum { IDD = IDD_SERV_ADJ_CR_SPEED2 };
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CAdjCRSpeed2)
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
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CAdjCRSpeed2)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_ADJCRSPEED2_H__BB0A8B8A_49AE_4BA0_B71C_47795AFE896B__INCLUDED_)
