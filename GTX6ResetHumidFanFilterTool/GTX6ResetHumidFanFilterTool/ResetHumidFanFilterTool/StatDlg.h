#if !defined(AFX_STATDLG_H__F3D58FF9_DAEC_4350_9880_8B97E7D68604__INCLUDED_)
#define AFX_STATDLG_H__F3D58FF9_DAEC_4350_9880_8B97E7D68604__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StatDlg.h : �w�b�_�[ �t�@�C��
//
#include "LogList.h"

/////////////////////////////////////////////////////////////////////////////
// CStatDlg �_�C�A���O

class CStatDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CStatDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

	~CStatDlg();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CStatDlg)
	enum { IDD = IDD_SERV_VIEW_STAT };
	BOOL	m_bDate;
	BOOL	m_bMachine;
	BOOL	m_bSeparate;
	UINT	m_day1;
	UINT	m_day2;
	CString	m_machine;
	CString	m_folder;
	UINT	m_month1;
	UINT	m_month2;
	CString	m_statday;
	CString	m_statjob;
	UINT	m_year1;
	UINT	m_year2;
	//}}AFX_DATA

	CString m_csLogFile;
	CString m_csUnCompFile;


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CStatDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	int UnCompZlib( CString strMoto , CString strUnZlib );
	int UnCompZlgFile( FILE* fp );
	int GetUnCompFile();
	int ReadLogFile();
	bool canSave(const CString& strPath) const;

	BOOL storeStatisticsDays(
			const CLogDate& date1, const CLogDate& date2, 
			int dateFormat, int typeSeparate, const CString& machine,
			const CString& strPath) const;

	BOOL storeStatisticsJobs(
			const CLogDate& date1, const CLogDate& date2, 
			int dateFormat, int timeFormat, int typeSeparate, const CString& machine,
			const CString& strPath) const;

	void EnableDate(BOOL bEnable);
	CString createDateString();
	void updateFileName();

	CLogList m_records;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CStatDlg)
	virtual void OnOK();
	afx_msg void OnButtonCancel();
	afx_msg void OnChangeEditYear1();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSave();
	afx_msg void OnButtonFolder();
	afx_msg void OnCheckDate();
	afx_msg void OnCheckMachine();
	afx_msg void OnChangeEditMonth1();
	afx_msg void OnChangeEditDay1();
	afx_msg void OnChangeEditYear2();
	afx_msg void OnChangeEditMonth2();
	afx_msg void OnChangeEditDay2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_STATDLG_H__F3D58FF9_DAEC_4350_9880_8B97E7D68604__INCLUDED_)
