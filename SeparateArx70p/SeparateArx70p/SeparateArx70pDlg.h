// SeparateArx70pDlg.h : �w�b�_�[ �t�@�C��
//

#pragma once


// SeparateArx70pDlg �_�C�A���O
class CSeparateArx70pDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CSeparateArx70pDlg(CWnd* pParent = NULL);	// �W���R���X�g���N�^

// �_�C�A���O �f�[�^
	enum { IDD = IDD_SEPARATEW_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �T�|�[�g


// ����
protected:
	HICON m_hIcon;

	// �������ꂽ�A���b�Z�[�W���蓖�Ċ֐�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDropFiles(HDROP hDropInfo);
	int SeparateArx70polor(CString FileName);
};
