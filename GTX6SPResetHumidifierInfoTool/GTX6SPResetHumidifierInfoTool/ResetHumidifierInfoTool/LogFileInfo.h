#if !defined(AFX_LOGFILEINFO_H__86B9BEB2_CF68_415D_A7F3_53CC6D639A85__INCLUDED_)
#define AFX_LOGFILEINFO_H__86B9BEB2_CF68_415D_A7F3_53CC6D639A85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogFileInfo.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CLogFileInfo �_�C�A���O

class CLogFileInfo : public CDialog
{
// �R���X�g���N�V����
public:
	CLogFileInfo(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CLogFileInfo)
	enum { IDD = IDD_DLG_LOG_INFO };
	CString	m_csFileName;
	CString	m_Edit;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CLogFileInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CLogFileInfo)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_LOGFILEINFO_H__86B9BEB2_CF68_415D_A7F3_53CC6D639A85__INCLUDED_)
