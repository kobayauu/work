#if !defined(AFX_SETDATE2_H__3169F621_3F0C_4AC7_858C_C014BBF318C0__INCLUDED_)
#define AFX_SETDATE2_H__3169F621_3F0C_4AC7_858C_C014BBF318C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetDate2.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CSetDate2 �_�C�A���O

class CSetDate2 : public CPropertyPage
{
	DECLARE_DYNCREATE(CSetDate2)

// �R���X�g���N�V����
public:
	CSetDate2();
	~CSetDate2();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CSetDate2)
	enum { IDD = IDD_SERV_SET_DATE2 };
		// ���� - ClassWizard �͂��̈ʒu�Ƀf�[�^ �����o��ǉ����܂��B
		//    ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CSetDate2)
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
	//{{AFX_MSG(CSetDate2)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SETDATE2_H__3169F621_3F0C_4AC7_858C_C014BBF318C0__INCLUDED_)
