#if !defined(AFX_SETDATE_H__6465DBFF_3E42_4585_8AE3_CABB67509F7D__INCLUDED_)
#define AFX_SETDATE_H__6465DBFF_3E42_4585_8AE3_CABB67509F7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetDate.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CSetDate �_�C�A���O

class CSetDate : public CPropertyPage
{
	DECLARE_DYNCREATE(CSetDate)

// �R���X�g���N�V����
public:
	CSetDate();
	~CSetDate();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CSetDate)
	enum { IDD = IDD_SERV_SET_DATE };
	CButton	m_chkUsePC;
	UINT	m_nDay;
	UINT	m_nHour;
	UINT	m_nMinute;
	UINT	m_nMonth;
	UINT	m_nSecond;
	UINT	m_nYear;
	CString	m_csDateType;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B

	//{{AFX_VIRTUAL(CSetDate)
	public:
	virtual BOOL OnSetActive();
	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
	virtual BOOL OnQueryCancel();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	void ViewDateType();
	CTime m_cTimeManufacture;
	BOOL SetLotNumber(int nNumber);
	BOOL m_bClear;
	BOOL WriteDateToPrinter();
	void UpdateTimeDisp();
	int m_nPrevIDD;
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CSetDate)
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnUsePc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SETDATE_H__6465DBFF_3E42_4585_8AE3_CABB67509F7D__INCLUDED_)
