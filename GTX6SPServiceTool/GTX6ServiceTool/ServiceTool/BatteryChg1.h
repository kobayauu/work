#if !defined(AFX_BATTERYCHG1_H__024C926E_8172_4E1B_B583_E7BC4FFE8463__INCLUDED_)
#define AFX_BATTERYCHG1_H__024C926E_8172_4E1B_B583_E7BC4FFE8463__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BatteryChg1.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CBatteryChg1 �_�C�A���O

class CBatteryChg1 : public CPropertyPage
{
	DECLARE_DYNCREATE(CBatteryChg1)

// �R���X�g���N�V����
public:
	CBatteryChg1();
	~CBatteryChg1();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CBatteryChg1)
	enum { IDD = IDD_SERV_CHNAGE_BATTERY1 };
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CBatteryChg1)
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
	bool SetBatteryChgDate();
	bool ChangeDataAll();
	int  BatteryChangedInfoSetToPrinter();
	int m_nPrevIDD;
	DWORD m_dwChangedDate;
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CBatteryChg1)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_BATTERYCHG1_H__024C926E_8172_4E1B_B583_E7BC4FFE8463__INCLUDED_)
