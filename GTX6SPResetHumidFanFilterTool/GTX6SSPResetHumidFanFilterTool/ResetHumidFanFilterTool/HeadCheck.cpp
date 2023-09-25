// HeadCheck.cpp : 実装ファイル
//

#include "stdafx.h"
#include<assert.h>
#include "BGJServTool.h"
#include "HeadHistory.h"
#include "HeadCheck.h"
#include "Language.h"


// CHeadCheck ダイアログ

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


// CHeadCheck メッセージ ハンドラー


BOOL CHeadCheck::OnInitDialog()
{
	CDialog::OnInitDialog();

	ModifyStyleEx( 0, WS_EX_DLGMODALFRAME );

	// set language
	LangSetWndTxt( this							, IDS_HEADCHECKER	);
	LangSetWndTxt( GetDlgItem( IDC_INSTALLDATE ), IDS_INSTALLDATE	);
	LangSetWndTxt( GetDlgItem( IDC_WHITEHEAD )	, IDS_WHITEHEAD		);
	LangSetWndTxt( GetDlgItem( IDC_COLORHEAD )	, IDS_COLORHEAD		);

	// TODO: ここに初期化を追加してください
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
	// 例外 : OCX プロパティ ページは必ず FALSE を返します。
}

void CHeadCheck::OnBnClickedBtnCheck()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
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
        //一覧新しいヘッド
        if( p->dwUpdate > q->dwUpdate ) {
            index = i;
        }
        //設置日以降の累計
        if( p->dwStart >= dwDate ) {
            count += 1;
            total += p->dwOperate;
        }
    }

    //ヘッドなし
    if( count == 0 )
    {
        return  0;
    }
    //ヘッド交換あり
    else if( count > 1 )
    {
        if( dwSpan > 730 || total > 25000 )
            return  1;
        // else
        //     return  2;
    }
    // //ヘッド交換なし、その他
    // else
    {
        DWORD operate = pHead->ElementAt( index ).dwOperate;
        if( dwSpan > 365 || operate > 15000 )
            return  1;
        else
            return  2;
    }
}
