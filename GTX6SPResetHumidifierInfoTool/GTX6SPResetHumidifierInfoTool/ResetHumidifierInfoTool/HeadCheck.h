#pragma once
#include "afxdtctl.h"


// CHeadCheck �_�C�A���O

class CHeadCheck : public CDialog
{
	DECLARE_DYNAMIC(CHeadCheck)

public:
	CHeadCheck(CWnd* pParent = NULL);   // �W���R���X�g���N�^�[
	virtual ~CHeadCheck();

// �_�C�A���O �f�[�^
	enum { IDD = IDD_VIEW_HEADCHECK };

    CHeadArray* m_pWhiteHead;
    CHeadArray* m_pColorHead;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnCheck();
	virtual BOOL OnInitDialog();
	CDateTimeCtrl m_DatePicker;

private:
    int CheckHead( CTime* pDate, CHeadArray* pHead );
};
