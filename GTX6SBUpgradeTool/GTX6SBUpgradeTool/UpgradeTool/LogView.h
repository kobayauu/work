#if !defined(AFX_LOGVIEW_H__B9B0B5E7_45EA_4934_88AA_BB6DB0C89979__INCLUDED_)
#define AFX_LOGVIEW_H__B9B0B5E7_45EA_4934_88AA_BB6DB0C89979__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogView.h : �w�b�_�[ �t�@�C��
//

#define LOGCODE_MAX		80

/////////////////////////////////////////////////////////////////////////////
// CLogView �_�C�A���O

class CLogView : public CDialog
{
// �R���X�g���N�V����
public:
	bool ConvertToText( CGTLogFile& cf, CFile& File );
	CString m_csTextFile;
	bool ConvertToCsv( CGTLogFile& cf, CFile& File, int* p_iRecordCount, DWORD dwStartTime = 0, DWORD dwEndTime = 0xFFFFFFFF );
	CString m_csCsvFile;
	CString m_csLogFile;
	CLogView(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CLogView)
	enum { IDD = IDD_LOG_VIEW };
	BOOL	m_bErr;
	BOOL	m_bWrn;
	BOOL	m_bInf;
	BOOL	m_bParam;
	CString	m_csTimeZone;
	CString	m_csZoneTitle;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CLogView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	long m_lLogEntryCount;
	bool CheckSaveFileName( CString& csFileName );
	bool CheckSaveFileNameCsv( CString& csFileName );
	bool ChoiceSaveLogCsv( CGTLogEntry* p_cEntry, DWORD dwStartTime, DWORD dwEndTime );
	BOOL ConvertLogToText();
	BOOL CanIMakeFile( CString strFile );

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CLogView)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnDisp();
	afx_msg void OnBtnDispCsv();
	afx_msg void OnBtnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_LOGVIEW_H__B9B0B5E7_45EA_4934_88AA_BB6DB0C89979__INCLUDED_)
