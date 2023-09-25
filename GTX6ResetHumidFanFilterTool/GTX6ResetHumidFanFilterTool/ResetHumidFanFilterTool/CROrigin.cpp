// CROrigin.cpp : 実装ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "CROrigin.h"
#include ".\crorigin.h"
#include "Language.h"

// CCROrigin ダイアログ

IMPLEMENT_DYNAMIC(CCROrigin, CPropertyPage)
CCROrigin::CCROrigin()
	: CPropertyPage(CCROrigin::IDD)
	, m_bDone(FALSE)
{
}

CCROrigin::~CCROrigin()
{
}

void CCROrigin::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK_DONE, m_bDone);
}


BEGIN_MESSAGE_MAP(CCROrigin, CPropertyPage)
	ON_BN_CLICKED(IDC_CHECK_DONE, OnBnClickedCheckDone)
END_MESSAGE_MAP()


// CCROrigin メッセージ ハンドラ

void CCROrigin::OnBnClickedCheckDone()
{
	UpdateData( TRUE );

	CPropertySheet* pSheet = (CPropertySheet*)GetParent();

	if( m_bDone )
	{
		pSheet->SetWizardButtons( PSWIZB_NEXT | PSWIZB_BACK );
	}else
	{
		pSheet->SetWizardButtons( PSWIZB_BACK );
	}
}

BOOL CCROrigin::OnSetActive()
{
	LangSetWndTxt( GetDlgItem( IDC_CR_ORIGIN_1_1  ) , IDS_CR_ORIGIN_1_1        );
	LangSetWndTxt( GetDlgItem( IDC_CHECK_DONE )     , IDS_CHECK_CR_ORIGIN_DONE );

	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons( PSWIZB_BACK );

	m_bDone = FALSE;

	UpdateData( FALSE );

	return CPropertyPage::OnSetActive();
}


LRESULT CCROrigin::OnWizardNext()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	int nNextID = IDD_SERV_SET_DATE;//Main PCB の　交換

	if( pApp->GetCourse() == COURSE_CR_BOARD_CHANGE )
	{
		nNextID = IDD_SERV_ADJ_THERMIS01;//CR PCB の　交換
	}
	
	return pApp->IDDPush( nNextID );
}


LRESULT CCROrigin::OnWizardBack()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}
