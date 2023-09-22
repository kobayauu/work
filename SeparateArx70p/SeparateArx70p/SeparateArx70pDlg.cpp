// SeparateArx70pDlg.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "SeparateArx70p.h"
#include "SeparateArx70pDlg.h"
#include "ArpProcess.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSeparateArx70pDlg �_�C�A���O




CSeparateArx70pDlg::CSeparateArx70pDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSeparateArx70pDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSeparateArx70pDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSeparateArx70pDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CSeparateArx70pDlg ���b�Z�[�W �n���h��

BOOL CSeparateArx70pDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// "�o�[�W�������..." ���j���[���V�X�e�� ���j���[�ɒǉ����܂��B

	// ���̃_�C�A���O�̃A�C�R����ݒ肵�܂��B�A�v���P�[�V�����̃��C�� �E�B���h�E���_�C�A���O�łȂ��ꍇ�A
	//  Framework �́A���̐ݒ�������I�ɍs���܂��B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R���̐ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R���̐ݒ�

	// TODO: �������������ɒǉ����܂��B

	return TRUE;  // �t�H�[�J�X���R���g���[���ɐݒ肵���ꍇ�������ATRUE ��Ԃ��܂��B
}

void CSeparateArx70pDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	CDialog::OnSysCommand(nID, lParam);
}

// �_�C�A���O�ɍŏ����{�^����ǉ�����ꍇ�A�A�C�R����`�悷�邽�߂�
//  ���̃R�[�h���K�v�ł��B�h�L�������g/�r���[ ���f�����g�� MFC �A�v���P�[�V�����̏ꍇ�A
//  ����́AFramework �ɂ���Ď����I�ɐݒ肳��܂��B

void CSeparateArx70pDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N���C�A���g�̎l�p�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R���̕`��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// ���[�U�[���ŏ��������E�B���h�E���h���b�O���Ă���Ƃ��ɕ\������J�[�\�����擾���邽�߂ɁA
//  �V�X�e�������̊֐����Ăяo���܂��B
HCURSOR CSeparateArx70pDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CSeparateArx70pDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �����Ƀ��b�Z�[�W �n���h�� �R�[�h��ǉ����邩�A����̏������Ăяo���܂��B
	int		nFiles;				//�h���b�v���ꂽ�t�@�C����
	int		nLoop;				//for���[�v�p
	TCHAR	buff[MAX_PATH];		//������o�b�t�@
	CString	FileName;			//�h���b�v���ꂽ�t�@�C����
	CString	FileExt;			//�t�@�C���g���q
	int		nArpFiles = 0;		//ARP�t�@�C����

	//�J�[�\����҂���Ԃɂ���
	BeginWaitCursor();

	//�`�F�b�N��Ԃ̎擾
	UpdateData(TRUE);

	//�t�@�C�����̎擾
	nFiles = DragQueryFile(hDropInfo, -1, NULL, 0);
	for( nLoop = 0; nLoop < nFiles; ++nLoop )
	{
		//�t�@�C�����̎擾
		DragQueryFile(hDropInfo, nLoop, buff, MAX_PATH);
		FileName = buff;

		//�g���q����
		FileExt		= FileName.Mid ( FileName.ReverseFind('.') ).MakeLower();
		if( FileExt == ".arx4" || FileExt == ".arxp" || FileExt == ".arx6" || FileExt == ".arx70p" ) {	//ARX�t�@�C��
			nArpFiles++;
			SeparateArx70polor( FileName );
		}
		else {						//���̑��̃t�@�C��
			;
		}
	}

	//�J�[�\���̑҂���Ԃ�߂�
	EndWaitCursor();

	//���b�Z�[�W�\��
	CString	Msg;
	if( nArpFiles == 0 )
		Msg = "The ARX file is only accepted.";
	else
		Msg.Format( "The %d ARX file separated Color.", nArpFiles );
	AfxMessageBox( Msg );

	CDialog::OnDropFiles(hDropInfo);
}

int CSeparateArx70pDlg::SeparateArx70polor(CString FileName)
{
	CSplitArp	ArpData;

	ArpData.Open( FileName, FileName + "_w1.arx70p", FileName + "_w2.arx70p", FileName + "_c.arx70p", FileName + "_ff.arx70p");
	ArpData.Process();
	ArpData.Close();

	return 0;
}
