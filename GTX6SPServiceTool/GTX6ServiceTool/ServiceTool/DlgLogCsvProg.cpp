// DlgLogCsvProg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "bgjservtool.h"
#include "DlgLogCsvProg.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgLogCsvProg �_�C�A���O


CDlgLogCsvProg::CDlgLogCsvProg(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLogCsvProg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgLogCsvProg)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}


void CDlgLogCsvProg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgLogCsvProg)
	DDX_Control(pDX, IDC_PROGRESS1, m_Progress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgLogCsvProg, CDialog)
	//{{AFX_MSG_MAP(CDlgLogCsvProg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgLogCsvProg ���b�Z�[�W �n���h��

BOOL CDlgLogCsvProg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	LangSetWndTxt( this , IDS_TITLE_LOGCSVPROG );
	LangSetWndTxt( GetDlgItem( IDC_LOGCSV_PROG1_1 ) , IDS_LOGCSV_PROG1_1 );
	
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void CDlgLogCsvProg::OnCancel()
{

}

void CDlgLogCsvProg::OnOK()
{

}
