// HeadCheck.cpp : �����t�@�C��
//

#include "stdafx.h"
#include<assert.h>
#include "BGJServTool.h"
#include "HeadHistory.h"
#include "HeadCheck.h"
#include "Language.h"


// CHeadCheck �_�C�A���O

IMPLEMENT_DYNAMIC(CHeadCheck, CDialog)

CHeadCheck::CHeadCheck(CWnd* pParent /*=NULL*/)
	: CDialog(CHeadCheck::IDD, pParent)
{

}

CHeadCheck::~CHeadCheck()
{
}

void CHeadCheck::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATEPICKER, m_DatePicker);
}


BEGIN_MESSAGE_MAP(CHeadCheck, CDialog)
	ON_BN_CLICKED(IDC_BTN_CHECK, OnBnClickedBtnCheck)
END_MESSAGE_MAP()


// CHeadCheck ���b�Z�[�W �n���h���[


BOOL CHeadCheck::OnInitDialog()
{
	CDialog::OnInitDialog();

	ModifyStyleEx( 0, WS_EX_DLGMODALFRAME );

	// set language
	LangSetWndTxt( this							, IDS_HEADCHECKER	);
	LangSetWndTxt( GetDlgItem( IDC_INSTALLDATE ), IDS_INSTALLDATE	);
	LangSetWndTxt( GetDlgItem( IDC_WHITEHEAD )	, IDS_WHITEHEAD		);
	LangSetWndTxt( GetDlgItem( IDC_COLORHEAD )	, IDS_COLORHEAD		);

	// TODO: �����ɏ�������ǉ����Ă�������
    DWORD dwStart = -1;
	for( int i = 0; i < m_pWhiteHead->GetSize(); ++i )
	{
		HEADDATA	*p	= &m_pWhiteHead->ElementAt( i );
        if( dwStart > p->dwStart && p->dwStart != 0 ) {
            dwStart = p->dwStart;
        }
    }
	for( int i = 0; i < m_pColorHead->GetSize(); ++i )
	{
		HEADDATA	*p	= &m_pColorHead->ElementAt( i );
        if( dwStart > p->dwStart && p->dwStart != 0 ) {
            dwStart = p->dwStart;
        }
    }
    if( dwStart != -1 ) {
		CTime ct( 2000, 1, 1, 0, 0, 0, 0 );
		ct += CTimeSpan( dwStart );
        m_DatePicker.SetTime( &ct );
    }

	return TRUE;  // return TRUE unless you set the focus to a control
	// ��O : OCX �v���p�e�B �y�[�W�͕K�� FALSE ��Ԃ��܂��B
}

void CHeadCheck::OnBnClickedBtnCheck()
{
	// TODO: �����ɃR���g���[���ʒm�n���h���[ �R�[�h��ǉ����܂��B
    CTime ct;
    m_DatePicker.GetTime( ct );

    int result = CheckHead( &ct, m_pWhiteHead );
    SetDlgItemInt( IDC_EDIT_WHITE, result );

        result = CheckHead( &ct, m_pColorHead );
    SetDlgItemInt( IDC_EDIT_COLOR, result );
}

int CHeadCheck::CheckHead( CTime* pDate, CHeadArray* pHead )
{
    CTime ct( 2000, 1, 1, 0, 0, 0, 0 );
    DWORD dwDate = ( *pDate - ct ).GetTotalSeconds();
    DWORD dwSpan = ( CTime::GetCurrentTime() - *pDate ).GetDays();

    int index = 0;
    int count = 0;
    int total = 0;
	for( int i = 0; i < pHead->GetSize(); ++i )
	{
		HEADDATA	*p	= &pHead->ElementAt( i );
        HEADDATA    *q  = &pHead->ElementAt( index );
        //�ꗗ�V�����w�b�h
        if( p->dwUpdate > q->dwUpdate ) {
            index = i;
        }
        //�ݒu���ȍ~�̗݌v
        if( p->dwStart >= dwDate ) {
            count += 1;
            total += p->dwOperate;
        }
    }

    //�w�b�h�Ȃ�
    if( count == 0 )
    {
        return  0;
    }
    //�w�b�h��������
    else if( count > 1 )
    {
        if( dwSpan > 730 || total > 25000 )
            return  1;
        // else
        //     return  2;
    }
    // //�w�b�h�����Ȃ��A���̑�
    // else
    {
        DWORD operate = pHead->ElementAt( index ).dwOperate;
        if( dwSpan > 365 || operate > 15000 )
            return  1;
        else
            return  2;
    }
}
