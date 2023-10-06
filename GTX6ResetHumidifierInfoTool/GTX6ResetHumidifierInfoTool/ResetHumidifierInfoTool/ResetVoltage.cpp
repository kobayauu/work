// ResetVoltage.cpp : �����t�@�C��
//

#include "stdafx.h"
#include "BGJServTool.h"
//#include "BGJPrinter.h"
#include "ResetVoltage.h"
#include "Language.h"

// CResetVoltage �_�C�A���O

IMPLEMENT_DYNAMIC(CResetVoltage, CPropertyPage)
CResetVoltage::CResetVoltage()
	: CPropertyPage(CResetVoltage::IDD)
{
}

CResetVoltage::~CResetVoltage()
{
}

void CResetVoltage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CResetVoltage, CPropertyPage)
END_MESSAGE_MAP()


// CResetVoltage ���b�Z�[�W �n���h��

BOOL CResetVoltage::OnSetActive()
{
	CPropertySheet* pSheet = (CPropertySheet*)GetParent();
	pSheet->SetWizardButtons( PSWIZB_BACK | PSWIZB_NEXT );

	LangSetWndTxt( GetDlgItem( IDC_RESET_VOLRAGE_1 ) , IDS_RESET_VOLRAGE_1 );
	LangSetWndTxt( GetDlgItem( IDC_RESET_VOLRAGE_2 ) , IDS_CLICK_NEXT      );

	return CPropertyPage::OnSetActive();
}

LRESULT CResetVoltage::OnWizardBack()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	return pApp->IDDPop();
}

LRESULT CResetVoltage::OnWizardNext()
{
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	CWaitCursor wc;

	int nNextIDD = -1;

	if( pApp->IsOnline() )
	{
		if( pApp->ResetEEPROM8014() )	//���v���̃��Z�b�g
		{
			if( pApp->ResetIpAddress() )	//IP�A�h���X�̃��Z�b�g
			{
				nNextIDD = IDD_SERV_ADJ_CR_SPEED1;
			}
			else
			{
				LangAfxMsgBox( IDS_EER_COMMUNICATION , -67 );
			}
		}
		else
		{
			LangAfxMsgBox( IDS_EER_COMMUNICATION , -66 );
		}
	}else
	{
	//	nNextIDD = IDD_SERV_ADJ_THERMIS01;
		nNextIDD = IDD_SERV_ADJ_CR_SPEED1;
	}

	return pApp->IDDPush( nNextIDD );
}
