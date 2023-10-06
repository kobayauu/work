#if !defined(AFX_LOGANAL_H__41C692FE_076A_4B33_8373_E6DAB0D5DE1E__INCLUDED_)
#define AFX_LOGANAL_H__41C692FE_076A_4B33_8373_E6DAB0D5DE1E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogAnal.h : �w�b�_�[ �t�@�C��
//
#include "GTLogEntry.h"

/////////////////////////////////////////////////////////////////////////////
// CLogAnal �_�C�A���O

class CLogAnal : public CDialog
{
// �R���X�g���N�V����
public:
	CString m_csLogFile;
	CLogAnal(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CLogAnal)
	enum { IDD = IDD_LOG_ANALYZE };
	CComboBox	m_cbxLimit;
	CComboBox	m_cbxSelect;
	CString	m_csInfo;
	CString	m_csTimeZone;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CLogAnal)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	void DeleteAllElements();
	bool CheckAllElements( CGTLogFile& cf, int iType, const DWORD* pdwCode, int* pnCount );
	CArray<CGTLogEntry,CGTLogEntry&> m_Array;
	bool ConvertToCString( int nCount, CString& cs, int nLimit );
	bool CreateAndDispInformation( int iType, const DWORD* pdwCode, int nLimit );
	void MoveRect(int nID, int nLeft, int nTop, int nRight, int nBottom);

	int  m_iSelectSel;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CLogAnal)
	afx_msg void OnBtnDisp();
	virtual BOOL OnInitDialog();
	afx_msg void OnCbnSelchangeCbxSelect();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_LOGANAL_H__41C692FE_076A_4B33_8373_E6DAB0D5DE1E__INCLUDED_)
