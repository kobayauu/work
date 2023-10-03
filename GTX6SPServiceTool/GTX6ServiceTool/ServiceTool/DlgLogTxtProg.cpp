// DlgLogTxtProg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "bgjservtool.h"
#include "DlgLogTxtProg.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLogTxtProg �_�C�A���O


CDlgLogTxtProg::CDlgLogTxtProg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogTxtProg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLogTxtProg)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}


void CDlgLogTxtProg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLogTxtProg)
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLogTxtProg, CDialog)
	//{{AFX_MSG_MAP(CDlgLogTxtProg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLogTxtProg ���b�Z�[�W �n���h��

BOOL CDlgLogTxtProg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	LangSetWndTxt( this , IDS_TITLE_LOGTXTPROG );	
	LangSetWndTxt( GetDlgItem( IDC_LOGTXT_PROG1_1 ) , IDS_LOGTXT_PROG1_1 );

	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void CDlgLogTxtProg::OnCancel()
{

}

void CDlgLogTxtProg::OnOK()
{

}
