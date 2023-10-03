#pragma once
#include "afxcmn.h"



// �w�b�h�f�[�^ �\����

struct HEADDATA {
	CHAR	szName[ 8 ];	//�V���A���ԍ�
	DWORD	dwStart;		//�g�p�J�n
	DWORD	dwUpdate;		//�X�V
    DWORD   dwPrint;		//�������
    DWORD   dwOperate;		//��������
};
using CHeadArray = CArray <HEADDATA>;


// CHeadHistory �_�C�A���O

class CHeadHistory : public CDialog
{
	DECLARE_DYNAMIC(CHeadHistory)

public:
	CHeadHistory(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~CHeadHistory();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_VIEW_HEAD };

	CString m_csLogFile;
	CGTLogFile m_LogF;

    CHeadArray m_White1Head;
    CHeadArray m_White2Head;
    CHeadArray m_Color1Head;
    CHeadArray m_Color2Head;
    CHeadArray m_Special1Head;
    CHeadArray m_Special2Head;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CEEPDispSel)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool ReadTagData(CByteArray* pBuf, LPCTSTR pTagName);
	bool DispTotalPrints(CByteArray* pBuf);
	bool InitListHead(CListCtrl* pList);
	bool DispListHead(CListCtrl* pList, CHeadArray* pHead);
	bool GetHeadData(CByteArray* pBuf, int nNo, CHeadArray* pHead);


public:
	CListCtrl m_White1List;
	CListCtrl m_White2List;
	CListCtrl m_Color1List;
	CListCtrl m_Color2List;
	CListCtrl m_Special1List;
	CListCtrl m_Special2List;
	afx_msg void OnBnClickedBtnCheck();
};
