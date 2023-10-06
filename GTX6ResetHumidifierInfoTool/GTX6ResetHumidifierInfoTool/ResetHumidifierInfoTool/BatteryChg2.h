#if !defined(AFX_BATTERYCHG2_H__FCE21E40_8259_4310_93A4_15E666E2B65B__INCLUDED_)
#define AFX_BATTERYCHG2_H__FCE21E40_8259_4310_93A4_15E666E2B65B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BatteryChg2.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CBatteryChg2 �_�C�A���O

class CBatteryChg2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CBatteryChg2)

// �R���X�g���N�V����
public:
	CBatteryChg2();
	~CBatteryChg2();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CBatteryChg2)
	enum { IDD = IDD_SERV_CHNAGE_BATTERY2 };
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CBatteryChg2)
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
	//{{AFX_MSG(CBatteryChg2)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_BATTERYCHG2_H__FCE21E40_8259_4310_93A4_15E666E2B65B__INCLUDED_)
