#if !defined(AFX_PUMPCHG1_H__024C926E_8172_4E1B_B583_E7BC4FFE8463__INCLUDED_)
#define AFX_PUMPCHG1_H__024C926E_8172_4E1B_B583_E7BC4FFE8463__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PumpChg1.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CPumpChg1 �_�C�A���O

class CPumpChg1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CPumpChg1)

// �R���X�g���N�V����
public:
	CPumpChg1();
	~CPumpChg1();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CPumpChg1)
	enum { IDD = IDD_SERV_CHNAGE_PUMP1 };
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CPumpChg1)
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
	bool SetPumpChgDate();
	bool ChangeDataAll();
	int  PumpChangedInfoSetToPrinter();
	int m_nPrevIDD;
	DWORD m_dwChangedDate;
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CPumpChg1)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_PUMPCHG1_H__024C926E_8172_4E1B_B583_E7BC4FFE8463__INCLUDED_)
