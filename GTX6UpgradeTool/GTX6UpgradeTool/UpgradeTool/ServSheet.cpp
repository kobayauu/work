// ServSheet.cpp : インプリメンテーション ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "ServSheet.h"
#include "ServFirst.h"
#include "Language.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CServSheet

IMPLEMENT_DYNAMIC(CServSheet, CPropertySheet)

CServSheet::CServSheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage)
{
	// 小林追加
	AddPageNoHelp( &m_UpgPSel        );
	AddPageNoHelp( &m_UpdateFirm     );
	AddPageNoHelp(&m_WaitAction      );
	AddPageNoHelp(&m_Set18Code       );

	AddPageNoHelp( &m_ServSelOpe	 );
	AddPageNoHelp( &m_ServFirst      );
	AddPageNoHelp( &m_ServPSel		 );
	AddPageNoHelp( &m_ServChgParts   );
	AddPageNoHelp( &m_AdjThermis	 );
	AddPageNoHelp( &m_AdjThermis2	 );
	AddPageNoHelp( &m_AdjThermis3	 );
	AddPageNoHelp( &m_ResetVoltage	 );
	AddPageNoHelp( &m_AdjCRSpeed1	 );
	AddPageNoHelp( &m_AdjCRSpeed2	 );
	AddPageNoHelp( &m_SetDate		 );
	AddPageNoHelp( &m_SetDate2		 );
	AddPageNoHelp( &m_BatteryChg1	 );
	AddPageNoHelp( &m_BatteryChg2	 );
	AddPageNoHelp( &m_PumpChg1	     );
	AddPageNoHelp( &m_PumpChg2	     );
	AddPageNoHelp( &m_ChkLog1		 );
	AddPageNoHelp( &m_ViewLogFile	 );
	AddPageNoHelp( &m_CRMotorChg1	 );
	AddPageNoHelp( &m_FirePage	     );
	AddPageNoHelp( &m_InAdvanceMain  );
	AddPageNoHelp( &m_SetPosPage     );
	AddPageNoHelp( &m_SetIpPage      );
	AddPageNoHelp( &m_ResetTube		 );
	AddPageNoHelp( &m_ResetTube2	 );
	AddPageNoHelp( &m_CROrigin   	 );
	AddPageNoHelp( &m_Vrating   	 );
	AddPageNoHelp( &m_MBBranch   	 );
	AddPageNoHelp( &m_EEPROMRestore  );
	AddPageNoHelp( &m_Backup		 );
	AddPageNoHelp( &m_HumidFanFilter );
	AddPageNoHelp( &m_RTCSetAndResetEEPROM		 );
	AddPageNoHelp( &m_IPClear		 );
	AddPageNoHelp( &m_BarCode		 );
	AddPageNoHelp( &m_InitInkState	 );
	AddPageNoHelp( &m_WhiteHalt		 );
	AddPageNoHelp( &m_PlatenFeeding	 );
	AddPageNoHelp( &m_RTCSetAndBattery);

	m_psh.dwFlags &= (~PSH_HASHELP);
	m_psh.dwFlags |= PSH_USEHICON;
	m_psh.hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bBack4 = FALSE;
}

CServSheet::CServSheet(LPCTSTR pszCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(pszCaption, pParentWnd, iSelectPage)
{
	m_bBack4 = FALSE;
}

CServSheet::~CServSheet()
{
}

void CServSheet::AddPageNoHelp(CPropertyPage *pPage)
{
	pPage->m_psp.dwFlags &= (~PSP_HASHELP);
	AddPage( pPage );
}


BEGIN_MESSAGE_MAP(CServSheet, CPropertySheet)
	//{{AFX_MSG_MAP(CServSheet)
		// メモ - ClassWizard はこの位置にマッピング用のマクロを追加または削除します。
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CServSheet メッセージ ハンドラ

void CServSheet::SetAdj4( BOOL bBack4 )
{
	m_bBack4 = bBack4;
}

BOOL CServSheet::GetAdj4()
{
	return m_bBack4;
}

BOOL CServSheet::OnInitDialog() 
{
	BOOL bResult = CPropertySheet::OnInitDialog();

	return bResult;
}

void CServSheet::ChangeFontSize( CWnd* pWnd , int iSize , int iWeight /* = FW_NORMAL */ )
{
	m_FontSize.ChangeFontSize( pWnd , iSize , iWeight );
}
