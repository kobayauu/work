#if !defined(AFX_VIEWLOGFILE_H__A1D184A2_0F1A_4775_A550_26143E0982E3__INCLUDED_)
#define AFX_VIEWLOGFILE_H__A1D184A2_0F1A_4775_A550_26143E0982E3__INCLUDED_

#include "GTLogFile.h"	// ClassView �ɂ���Ēǉ�����܂����B
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewLogFile.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CViewLogFile �_�C�A���O

class CViewLogFile : public CPropertyPage
{
	DECLARE_DYNCREATE(CViewLogFile)

// �R���X�g���N�V����
public:
	CViewLogFile();
	~CViewLogFile();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CViewLogFile)
	enum { IDD = IDD_SERV_VIEW_LOG };
	CString	m_csLogFile;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CViewLogFile)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual BOOL OnWizardFinish();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	bool CheckLogFile();
	CGTLogFile m_LogFile;
	int m_nPrevIDD;
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CViewLogFile)
	afx_msg void OnBtnSettings();
	afx_msg void OnBtnLog();
	afx_msg void OnBtnInfo();
	afx_msg void OnBtnLogAnal();
	afx_msg void OnBtnStat();
	afx_msg void OnBtnHead();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_VIEWLOGFILE_H__A1D184A2_0F1A_4775_A550_26143E0982E3__INCLUDED_)
