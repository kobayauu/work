#if !defined(AFX_DLGLOGCSVPROG_H__0BE91D8B_61D0_458D_BC13_8B9DFE4065A0__INCLUDED_)
#define AFX_DLGLOGCSVPROG_H__0BE91D8B_61D0_458D_BC13_8B9DFE4065A0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLogCsvProg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLogCsvProg �_�C�A���O

class CDlgLogCsvProg : public CDialog
{
// �R���X�g���N�V����
public:
	CDlgLogCsvProg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDlgLogCsvProg)
	enum { IDD = IDD_DLG_LOGCSV_PROGRESS };
	CProgressCtrl	m_Progress;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDlgLogCsvProg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	virtual void OnCancel();
	virtual void OnOK();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDlgLogCsvProg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DLGLOGCSVPROG_H__0BE91D8B_61D0_458D_BC13_8B9DFE4065A0__INCLUDED_)
