#pragma once

#include "afxwin.h"
#include "afxdlgs.h"
#include "resource.h"


class SelectRegionPopupDlg : public CDialog
{
	DECLARE_DYNAMIC(SelectRegionPopupDlg)

	CString m_str15Code;
	CString m_strRegion;
	CString m_strModel;
	CString m_strAttach;

public:
	SelectRegionPopupDlg(CWnd* pParent = NULL); //�W���R���X�g���N�^

	// �_�C�A���O �f�[�^
	enum { IDD = IDD_BARCODE_REGION };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g

	DECLARE_MESSAGE_MAP()

	// �_�C�A���O�N�����̏�������
	virtual BOOL OnInitDialog();

	// OK�{�^���������ꂽ�Ƃ��̏���
	afx_msg void OnBnClickedOk();

	int m_nRegionRadio = 0;
	int m_nModelRadio = 0;

	void SetRegion();
	void SetModel();
	void SetAttach();
};

