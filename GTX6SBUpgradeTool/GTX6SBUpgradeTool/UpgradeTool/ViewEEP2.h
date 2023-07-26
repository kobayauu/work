#if !defined(AFX_VIEWEEP2_H__81B5A2CF_7DC5_42D5_B096_DA5F9206D9B2__INCLUDED_)
#define AFX_VIEWEEP2_H__81B5A2CF_7DC5_42D5_B096_DA5F9206D9B2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewEEP2.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CViewEEP2 �_�C�A���O

class CViewEEP2 : public CDialog
{
// �R���X�g���N�V����
public:
	CString m_csSaveAsFile;
	CEEPFile* m_pRefEEP;
	CEEPFile* m_pEEP;
	CViewEEP2(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CViewEEP2)
	enum { IDD = IDD_VIEW_EEP };
	CListCtrl	m_MemList;
	CString	m_csBlockID;
	CString	m_csHeadVersion;
	CString	m_csVersion;
	CString	m_csHeadComment;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CViewEEP2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	bool CheckDiff( CMemEntry* pEntry, CMemEntry* pRefEntry );
	bool InitImageList();
	CImageList m_ImageListSmall;
	void ChangeDataStrForm(CString &s, CMemEntry *pEntry);
	void UpdateListCtrl();
	void InitListCtrl();
	void MoveRect(int nID, int nLeft, int nTop, int nRight, int nBottom);

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CViewEEP2)
	virtual BOOL OnInitDialog();
	afx_msg void OnGetdispinfoList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnSaveas();
	afx_msg void OnGetMinMaxInfo(MINMAXINFO* lpMMI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_VIEWEEP2_H__81B5A2CF_7DC5_42D5_B096_DA5F9206D9B2__INCLUDED_)
