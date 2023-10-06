#if !defined(AFX_ADJTHERMIS3_H__0F9604C7_86E2_4699_9894_F7BEA9A92FBC__INCLUDED_)
#define AFX_ADJTHERMIS3_H__0F9604C7_86E2_4699_9894_F7BEA9A92FBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdjThermis3.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CAdjThermis3 �_�C�A���O

class CAdjThermis3 : public CPropertyPage
{
	DECLARE_DYNCREATE(CAdjThermis3)

// �R���X�g���N�V����
public:
	CAdjThermis3();
	~CAdjThermis3();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAdjThermis3)
	enum { IDD = IDD_SERV_ADJ_THERMIS03 };
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CAdjThermis3)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardNext();
	virtual LRESULT OnWizardBack();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	int m_nPrevIDD;
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CAdjThermis3)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_ADJTHERMIS3_H__0F9604C7_86E2_4699_9894_F7BEA9A92FBC__INCLUDED_)
