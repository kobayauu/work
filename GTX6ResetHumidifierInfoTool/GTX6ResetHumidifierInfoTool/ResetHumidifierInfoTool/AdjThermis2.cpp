// AdjThermis2.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "AdjThermis2.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdjThermis2 プロパティ ページ

IMPLEMENT_DYNCREATE(CAdjThermis2, CPropertyPage)

CAdjThermis2::CAdjThermis2() : CPropertyPage(CAdjThermis2::IDD)
{
	//{{AFX_DATA_INIT(CAdjThermis2)
	m_fCTemp = 0.0;
	m_fFTemp = 0.0;
	//}}AFX_DATA_INIT
}

CAdjThermis2::~CAdjThermis2()
{
}

void CAdjThermis2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdjThermis2)
	DDX_Text(pDX, IDC_EDIT_CTEMP, m_fCTemp);
	DDX_Text(pDX, IDC_EDIT_FTEMP, m_fFTemp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdjThermis2, CPropertyPage)
	//{{AFX_MSG_MAP(CAdjThermis2)
	ON_BN_CLICKED(IDC_RADIO_FAHRENHEIGHT, OnRadioFahrenheight)
	ON_BN_CLICKED(IDC_RADIO_CELSIUS, OnRadioCelsius)
	ON_EN_CHANGE(IDC_EDIT_CTEMP, OnChangeEditCtemp)
	ON_EN_CHANGE(IDC_EDIT_FTEMP, OnChangeEditFtemp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdjThermis2 メッセージ ハンドラ

BOOL CAdjThermis2::OnSetActive() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	ASSERT_KINDOF(CPropertySheet, pSheet);
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT);
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	m_nPrevIDD = pApp->SetPrevIDD( IDD );

	LangSetWndTxt( GetDlgItem( IDC_ADJ_THERMIS02_01 )	, IDS_ADJ_THERMIS02_01 );
	LangSetWndTxt( GetDlgItem( IDC_RADIO_FAHRENHEIGHT ) , IDS_FAHRENHEIGHT	   );
	LangSetWndTxt( GetDlgItem( IDC_RADIO_CELSIUS )		, IDS_CELSIUS	   	   );
	LangSetWndTxt( GetDlgItem( IDC_TEMPERATURE )		, IDS_TEMPERATURE	   );
	
	m_fCTemp = 20.0;
	m_fFTemp = 68.0;
	m_bFahrenheit = false;

	if( pApp->GetProfileInt( cszServSection, cszTempUnit, 0 ) == 0 ){
		m_bFahrenheit = true;
	}

	CheckRadioButton( IDC_RADIO_FAHRENHEIGHT, IDC_RADIO_CELSIUS,
		((m_bFahrenheit)?IDC_RADIO_FAHRENHEIGHT:IDC_RADIO_CELSIUS) );

	UpdateData( FALSE );
	OnChangeTemperature();
	return CPropertyPage::OnSetActive();
}

LRESULT CAdjThermis2::OnWizardNext() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	LRESULT nNextPage = -1;
	LRESULT nOKNextID = IDD_SERV_ADJ_THERMIS03; //IDD_SERV_ADJ_CR_SPEED1;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	switch( pApp->GetCourse() )
	{
	case COURSE_MAIN_BOARD_CHANGE:
	//	nOKNextID = IDD_SERV_ADJ_CR_SPEED1;
		nOKNextID = IDD_FIRE1;
		break;
	}

	CWaitCursor wc;

	UpdateData( TRUE );
	
	m_bFahrenheit = false;
	if( GetCheckedRadioButton( IDC_RADIO_FAHRENHEIGHT, IDC_RADIO_CELSIUS ) == IDC_RADIO_FAHRENHEIGHT )
	{
		m_bFahrenheit = true;
	}
	pApp->WriteProfileInt( cszServSection, cszTempUnit, ((m_bFahrenheit)?0:1) );

	int nTempF;
	if( m_bFahrenheit ){
		nTempF = ChangeTempUnit( m_fFTemp, m_bFahrenheit );
	}else{
		nTempF = ChangeTempUnit( m_fCTemp, m_bFahrenheit );
	}

	if( 50 <= nTempF && nTempF <= 95 )
	{
		if( pApp->IsOnline() )
		{
			if( pApp->SetTemperature( nTempF ) ) {
				nNextPage = nOKNextID;
			}
			else
			{
				LangAfxMsgBox( IDS_ERR_SETRANGE );
			}
		}
		else
		{
			nNextPage = nOKNextID;
		}
	}
	else
	{
		LangAfxMsgBox_OutOfRange( nTempF , -61 );
	}

	return pApp->IDDPush( nNextPage );
}

LRESULT CAdjThermis2::OnWizardBack() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
	//return IDD_SERV_ADJ_THERMIS01;
}

int CAdjThermis2::ChangeTempUnit(double fTemp, bool bF)
{
	int iTempF = (int)(fTemp+0.5);
	if( ! bF )
	{
		double f = fTemp * 1.8 + 32.0;
		iTempF = (int)(f + 0.5);
	}
	return iTempF;
}

void CAdjThermis2::OnRadioFahrenheight() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnChangeTemperature();
}

void CAdjThermis2::OnRadioCelsius() 
{
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnChangeTemperature();
}

void CAdjThermis2::OnChangeEditCtemp() 
{
	// TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
	// 内での論理和の ENM_CHANGE フラグ付きで CRichEditCrtl().SetEventMask()
	// メッセージをコントロールへ送るために CPropertyPage::OnInitDialog() 関数をオーバー
	// ライドしない限りこの通知を送りません。
	
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnChangeTemperature();
}

void CAdjThermis2::OnChangeEditFtemp() 
{
	// TODO: これが RICHEDIT コントロールの場合、コントロールは、 lParam マスク
	// 内での論理和の ENM_CHANGE フラグ付きで CRichEditCrtl().SetEventMask()
	// メッセージをコントロールへ送るために CPropertyPage::OnInitDialog() 関数をオーバー
	// ライドしない限りこの通知を送りません。
	
	// TODO: この位置にコントロール通知ハンドラ用のコードを追加してください
	OnChangeTemperature();
}

void CAdjThermis2::OnChangeTemperature()
{
	CString cs;
	m_bFahrenheit = false;
	if( GetCheckedRadioButton( IDC_RADIO_FAHRENHEIGHT, IDC_RADIO_CELSIUS ) == IDC_RADIO_FAHRENHEIGHT ){
		m_bFahrenheit = true;
	}
	if( m_bFahrenheit ){
		GetDlgItem( IDC_EDIT_FTEMP )->GetWindowText( cs );
		GetDlgItem( IDC_EDIT_FTEMP )->EnableWindow( TRUE );
		GetDlgItem( IDC_EDIT_CTEMP )->EnableWindow( FALSE );
	}else{
		GetDlgItem( IDC_EDIT_CTEMP )->GetWindowText( cs );
		GetDlgItem( IDC_EDIT_FTEMP )->EnableWindow( FALSE );
		GetDlgItem( IDC_EDIT_CTEMP )->EnableWindow( TRUE );
	}
	if( !cs.IsEmpty() ){
		UpdateData( TRUE );
		if( m_bFahrenheit ){
			m_fCTemp = (m_fFTemp - 32.0) / 1.8;
			m_fCTemp = int( m_fCTemp * 100 ) / 100.0;
		}else{
			m_fFTemp = m_fCTemp * 1.8 + 32.0;
			m_fFTemp = int( m_fFTemp * 100 ) / 100.0;
		}
		UpdateData( FALSE );
	}

}

BOOL CAdjThermis2::OnQueryCancel() 
{
	// TODO: この位置に固有の処理を追加するか、または基本クラスを呼び出してください
	BOOL bRet = FALSE;
	if( LangCancelYesNoMsgBox() == IDYES )
	{
		bRet = TRUE;
	}
	return bRet;
}
