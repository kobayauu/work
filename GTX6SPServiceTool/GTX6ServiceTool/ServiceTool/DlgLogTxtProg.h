#if !defined(AFX_DLGLOGTXTPROG_H__058E8FD7_1EDD_4D78_B0E2_1A806FDC53DF__INCLUDED_)
#define AFX_DLGLOGTXTPROG_H__058E8FD7_1EDD_4D78_B0E2_1A806FDC53DF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLogTxtProg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLogTxtProg �_�C�A���O

class CDlgLogTxtProg : public CDialog
{
// �R���X�g���N�V����
public:
	CDlgLogTxtProg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgLogTxtProg)
	enum { IDD = IDD_DLG_LOGTXT_PROGRESS };
	CProgressCtrl	m_Progress;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgLogTxtProg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	virtual void OnCancel();
	virtual void OnOK();
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgLogTxtProg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGLOGTXTPROG_H__058E8FD7_1EDD_4D78_B0E2_1A806FDC53DF__INCLUDED_)
