#if !defined(AFX_CRMOTORCHG1_H__6E2BCA31_EDE3_42B8_AE88_90E9192EAA86__INCLUDED_)
#define AFX_CRMOTORCHG1_H__6E2BCA31_EDE3_42B8_AE88_90E9192EAA86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CRMotorChg1.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CCRMotorChg1 �_�C�A���O

class CCRMotorChg1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CCRMotorChg1)

// �R���X�g���N�V����
public:
	int m_nPrevIDD;
	CCRMotorChg1();
	~CCRMotorChg1();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CCRMotorChg1)
	enum { IDD = IDD_SERV_CR_CHANGE };
		// ���� - ClassWizard �͂��̈ʒu�Ƀf�[�^ �����o��ǉ����܂��B
		//    ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CCRMotorChg1)
	public:
	virtual BOOL OnSetActive();
	virtual BOOL OnQueryCancel();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	DWORD m_dwChangedDate;
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CCRMotorChg1)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_CRMOTORCHG1_H__6E2BCA31_EDE3_42B8_AE88_90E9192EAA86__INCLUDED_)
