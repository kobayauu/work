#if !defined(AFX_ADJCRSPEED1_H__8F800026_4FFE_4918_B5A3_A531FB6F5EE8__INCLUDED_)
#define AFX_ADJCRSPEED1_H__8F800026_4FFE_4918_B5A3_A531FB6F5EE8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdjCRSpeed1.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CAdjCRSpeed1 �_�C�A���O

class CAdjCRSpeed1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CAdjCRSpeed1)

// �R���X�g���N�V����
public:
	CAdjCRSpeed1();
	~CAdjCRSpeed1();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAdjCRSpeed1)
	enum { IDD = IDD_SERV_ADJ_CR_SPEED1 };
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CAdjCRSpeed1)
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
	int m_nPrevIDD;
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CAdjCRSpeed1)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_ADJCRSPEED1_H__8F800026_4FFE_4918_B5A3_A531FB6F5EE8__INCLUDED_)
