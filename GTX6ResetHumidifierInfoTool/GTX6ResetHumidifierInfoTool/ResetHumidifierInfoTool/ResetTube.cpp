// ResetTube.cpp : 実装ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
//#include "BGJPrinter.h"
#include "ResetTube.h"
#include "Language.h"


// CResetTube ダイアログ

IMPLEMENT_DYNAMIC(CResetTube, CPropertyPage)
CResetTube::CResetTube()
	: CPropertyPage(CResetTube::IDD)
{
}

CResetTube::~CResetTube()
{
}

void CResetTube::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CResetTube, CPropertyPage)
END_MESSAGE_MAP()


// CResetTube メッセージ ハンドラ

BOOL CResetTube::OnSetActive()
{
	LangSetWndTxt( GetDlgItem( IDC_RESET_TUBE_1 ) , IDS_RESET_TUBE_1  );
	LangSetWndTxt( GetDlgItem( IDC_RESET_TUBE_2 ) , IDS_CLICK_NEXT );

	return CPropertyPage::OnSetActive();
}

LRESULT CResetTube::OnWizardNext()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	int nNextIDD = -1;

	if( pApp->IsOnline() )
	{
		if( pApp->ResetTubeClearning() )
		{
			nNextIDD = IDD_SERV_RESET_TUBE2;
		}
		else
		{
			LangAfxMsgBox( IDS_EER_COMMUNICATION , -69 );
		}
	}else
	{
		nNextIDD = IDD_SERV_RESET_TUBE2;
	}
	
	return pApp->IDDPush( nNextIDD );
}

LRESULT CResetTube::OnWizardBack()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}
