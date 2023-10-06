#if !defined(AFX_SERVSHEET_H__6A3E74B7_3783_4D0D_8AE7_F5348F46E92A__INCLUDED_)
#define AFX_SERVSHEET_H__6A3E74B7_3783_4D0D_8AE7_F5348F46E92A__INCLUDED_

#include "ServFirst.h"	
#include "ServChgParts.h"	
#include "AdjThermis.h"	
#include "AdjThermis2.h"	
#include "AdjThermis3.h"	
#include "AdjCRSpeed1.h"
#include "AdjCRSpeed2.h"
#include "ServSelOpe.h"
#include "SetDate.h"
#include "SetDate2.h"
#include "BatteryChg1.h"
#include "BatteryChg2.h"
#include "PumpChg1.h"
#include "PumpChg2.h"
#include "ChkLog1.h"
#include "ServPSel.h"
#include "ViewLogFile.h"
#include "CRMotorChg1.h"
#include "FirePage.h"
#include "InAdvanceMain.h"
#include "SetPosPage.h"
#include "SetIpPage.h"
#include "Fontsize.h"
#include "ResetVoltage.h"
#include "ResetTube.h"
#include "ResetTube2.h"
#include "CROrigin.h"
#include "Vrating.h"
#include "MainBoardBranch.h"
#include "EEPROMRestore.h"
#include "Backup.h"
#include "HumidFanFilter.h"
#include "RTCSetAndResetEEPROM.h"
#include "IPClear.h"
#include "BarCode.h"
#include "InitInkState.h"
#include "WhiteHalt.h"
#include "PlatenFeeding.h"
#include "RTCSetAndBattery.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServSheet.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CServSheet

static const int iPAGE_NUM = 28;//�R���X�g���N�^��AddPage�̐�

class CServSheet : public CPropertySheet
{
	DECLARE_DYNAMIC(CServSheet)

// �R���X�g���N�V����
public:
	CServSheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);
	CServSheet(LPCTSTR pszCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CServSheet)
	public:
	virtual BOOL OnInitDialog();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:

	CServSelOpe		  m_ServSelOpe;
	CServFirst		  m_ServFirst;
	CServPSel		  m_ServPSel;
	CServChgParts	  m_ServChgParts;
	CAdjThermis		  m_AdjThermis;
	CAdjThermis2	  m_AdjThermis2;
	CAdjThermis3	  m_AdjThermis3;
	CResetVoltage	  m_ResetVoltage;
	CAdjCRSpeed1	  m_AdjCRSpeed1;
	CAdjCRSpeed2	  m_AdjCRSpeed2;	
	CSetDate		  m_SetDate;
	CSetDate2		  m_SetDate2;
	CBatteryChg1      m_BatteryChg1;
	CBatteryChg2	  m_BatteryChg2;
	CPumpChg1         m_PumpChg1;
	CPumpChg2         m_PumpChg2;
	CChkLog1		  m_ChkLog1;
	CViewLogFile	  m_ViewLogFile;
	CCRMotorChg1	  m_CRMotorChg1;
	CFirePage		  m_FirePage;
	CInAdvanceMain    m_InAdvanceMain;
	CSetPosPage		  m_SetPosPage;
	CSetIpPage		  m_SetIpPage;
	CResetTube		  m_ResetTube;
	CResetTube2		  m_ResetTube2;
	CCROrigin         m_CROrigin;

	CFontSize        m_FontSize;

	CVrating		  m_Vrating;
	CMainBoardBranch  m_MBBranch;
	CEEPROMRestore	  m_EEPROMRestore;
	CBackup			  m_Backup;
	CHumidFanFilter   m_HumidFanFilter;
	CRTCSetAndResetEEPROM	m_RTCSetAndResetEEPROM;
	CIPClear		  m_IPClear;
	CBarCode		  m_BarCode;
	CInitInkState	  m_InitInkState;
	CWhiteHalt		  m_WhiteHalt;
	CPlatenFeeding	  m_PlatenFeeding;
	CRTCSetAndBattery m_RTCSetAndBattery;

	virtual ~CServSheet();

	void SetAdj4( BOOL bBack4 );
	BOOL GetAdj4();
	void ChangeFontSize( CWnd* pWnd , int iSize , int iWeight = FW_NORMAL );

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:

	void AddPageNoHelp(CPropertyPage *pPage);

	CString m_strTitle[iPAGE_NUM];
	BOOL m_bBack4;
	//{{AFX_MSG(CServSheet)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_SERVSHEET_H__6A3E74B7_3783_4D0D_8AE7_F5348F46E92A__INCLUDED_)
