// EEPDispSel.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "bgjservtool.h"
#include "EEPDispSel.h"
#include "ViewEEP2.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


static const TCHAR* pTagList_Text[EEP_NUM] = 
{
	_T("8011"),
	_T("8012"),
	_T("8013"),
	_T("8014"),
	_T("8015"),
	_T("8016"),
	_T("8017"),
	_T("8018"),
	_T("8019"),
	_T("8020"),
	_T("8021"),
	_T("8022"),
};


static const TCHAR* pTagList_Bynari[EEP_NUM] = 
{
	_T("EP11"),
	_T("EP12"),
	_T("EP13"),
	_T("EP14"),
	_T("EP15"),
	_T("EP16"),
	_T("EP17"),
	_T("EP18"),
	_T("EP19"),
	_T("EP20"),
	_T("EP21"),
	_T("EP22"),
};

static const TCHAR* pTagExplanation[EEP_NUM] = 
{
	_T("Parameters"),
	_T("Servo"),
	_T("Correction"),
	_T("Statistics"),
	_T("Device Data"),
	_T("Wavy"),
	_T("Wavy"),
	_T("Status"),
	_T("History"),
	_T("Schedule"),
	_T("Reserve"),
	_T("Reserve"),
};

/////////////////////////////////////////////////////////////////////////////
// CEEPDispSel �_�C�A���O


CEEPDispSel::CEEPDispSel(CWnd* pParent /*=NULL*/)
	: CDialog(CEEPDispSel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CEEPDispSel)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}


void CEEPDispSel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEEPDispSel)
	DDX_Control(pDX, IDC_LIST, m_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CEEPDispSel, CDialog)
	//{{AFX_MSG_MAP(CEEPDispSel)
	ON_BN_CLICKED(IDC_BTN_VIEW, OnBtnView)
	ON_BN_CLICKED(IDC_BTN_CLOSE, OnBtnClose)
	ON_WM_DESTROY()
	ON_LBN_DBLCLK(IDC_LIST, OnDblclkList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CEEPDispSel ���b�Z�[�W �n���h��

BOOL CEEPDispSel::OnInitDialog() 
{
	CDialog::OnInitDialog();

	LangSetWndTxt( this , IDS_TITLE_EEPDISPSEL );
	
	// TODO: ���̈ʒu�ɏ������̕⑫������ǉ����Ă�������
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	m_List.ResetContent();
	int i;
	for( i=0; i<MAX_EEPROM_DATA_COUNT; ++i )
	{
		m_nSize[i] = 0;
		m_pData[i] = NULL;
		m_bText[i] = TRUE;
	}

	LangSetWndTxt( GetDlgItem( IDC_EEPROM_VIEW1_1 ) , IDS_EEPROM_VIEW1_1 );
	LangSetWndTxt( GetDlgItem( IDC_EEPROM_VIEW1_2 ) , IDS_EEPROM_VIEW1_2 );
	LangSetWndTxt( GetDlgItem( IDC_BTN_VIEW )		, IDS_DISPLAY );
	LangSetWndTxt( GetDlgItem( IDC_BTN_CLOSE )		, IDS_CLOSE			 );
	LangSetWndTxt( GetDlgItem( IDC_CHK_COMPARE )	, IDS_CHK_COMPARE	 );

	ReadEEPData();
	
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void CEEPDispSel::ReadEEPData()
{
	if( m_LogF.Open( m_csLogFile ) )
	{
		EEP_MANAGE_VER ManageVer;
		if( GetEEPManageVer( &ManageVer ) )
		{
			int nIndex = 0;
			const TCHAR* pTaglist;
			for( int i=0; i < EEP_NUM ; ++i )
			{
				long nSize = 0;
				
				m_LogF.ReadTagData( pTagList_Bynari[i], 0, NULL, &nSize );//�o�C�i���ŒT��
				m_bText[nIndex] = FALSE;
				
				if( nSize > 0 )
				{
					m_nSize[nIndex] = nSize;
					m_nResID[nIndex] = TEMPLATE_RES_IDs[ManageVer][i];
					CString cs = pTagList_Text[i];
					cs += _T(" : ");
					cs += pTagExplanation[i];
					m_pData[nIndex] = new BYTE[nSize + 16];
					if( m_pData[nIndex] != NULL )
					{
						pTaglist = pTagList_Text[i];
						if( !m_bText[nIndex] )
						{
							pTaglist = pTagList_Bynari[i];
						}
						if( m_LogF.ReadTagData( pTaglist , nSize, m_pData[nIndex], &nSize ) )
						{
							nIndex += 1;
							m_List.AddString( cs );
						}
					}
				}
			}
		}
	}
}

BOOL CEEPDispSel::GetEEPManageVer( EEP_MANAGE_VER* pManageVer )
{
	*pManageVer = EEP_MANAGE_VER_FIRST;

	return TRUE;
/*
	BOOL bRet = TRUE;
	BYTE b[16];
	long lSize;

	if( m_LogF.ReadTagData( "Vers", 16, b, &lSize ) )
	{
		if( lSize >= 16 )
		{
			DWORD dwSH      = (b[3] <<24)|(b[2] <<16)|(b[1] <<8)|(b[0]);
			DWORD dwBY      = (b[7] <<24)|(b[6] <<16)|(b[5] <<8)|(b[4]);
			DWORD dwMainte  = (b[11]<<24)|(b[10]<<16)|(b[9] <<8)|(b[8]);
			DWORD dwMainPCB = (b[15]<<24)|(b[14]<<16)|(b[13]<<8)|(b[12]);
			
			//SH�̃o�[�W������1.70�ȏ�ł���΁AEEP_MANEGE_VER_200�Ƃ���
			//SH�̃o�[�W������3.98�ȏ�ł���΁AEEP_MANEGE_VER_400�Ƃ���
			*pManageVer = EEP_MANAGE_VER_UNDER_160;
			if( dwSH >= 0x01700000 ) *pManageVer = EEP_MANAGE_VER_200;
			if( dwSH >= 0x03980000 ) *pManageVer = EEP_MANAGE_VER_400;
		}
	}else
	{
		bRet = FALSE;
	}
	return bRet;
	*/
}


void CEEPDispSel::OnBtnView() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	/*int nIndex = m_List.GetCurSel();
	CString cs;
	m_List.GetText( nIndex, cs );
	if( m_pData[nIndex] != NULL ){
		CEEPDisp dlg;
		dlg.m_pData = m_pData[nIndex];
		dlg.m_nSize = m_nSize[nIndex];
		dlg.m_csTitle = cs;
		dlg.m_csLogFile = m_csLogFile;
		dlg.DoModal();
	}*/

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	int nSel = m_List.GetCurSel();
	if( nSel != CB_ERR ){
		CString cs;
		m_List.GetWindowText( cs );
		CViewEEP2 dlg;
		CEEPFile EEP;
		CEEPFile RefEEP;
		dlg.m_pEEP = NULL;
		dlg.m_pRefEEP = NULL;
		if( IsDlgButtonChecked( IDC_CHK_COMPARE ) != 0 )
		{
			if( RefEEP.Open( m_nResID[nSel] ) ){
				dlg.m_pRefEEP = &RefEEP;
			}
		}
		BOOL bRet = FALSE;
		if( m_bText[nSel] )
		{//�e�L�X�g
			bRet = EEP.Open( m_pData[nSel], m_nSize[nSel] );
		}else
		{//�o�C�i��
			BYTE* pJustData = NULL;
			long  nJustDataSize;
			//m_pData[nSel]����{����Data�̕����̃A�h���X�����o��
			pJustData = GetJustData( m_pData[nSel] , m_nSize[nSel] , &nJustDataSize );
			if( pJustData )
			{	//�_���u���b�N�̃o�C�i���f�[�^��EEP��Open����
				bRet = EEP.Open_Bynari( m_nResID[nSel] , pJustData , nJustDataSize );
			}
		}
		if( bRet )
		{
			dlg.m_pEEP = &EEP;
			dlg.DoModal();
		}

		if( dlg.m_pEEP ){
			dlg.m_pEEP->Close();
		}
		if( dlg.m_pRefEEP ){
			dlg.m_pRefEEP->Close();
		}
	}
}

BYTE* CEEPDispSel::GetJustData( BYTE* pAllData , long nAllSize , long* pnJustDataSize )
{
	BYTE* pJustData = pAllData+12;//�{���̃f�[�^��12�o�C�g�ڂ���@LogFileSpec.doc�Q��

	//�{���̃f�[�^�̃T�C�Y��8�o�C�g�ڂ���@�r�b�O�G���f�B�A��
	*pnJustDataSize = (pAllData[8] << 24) + (pAllData[9] << 16) + (pAllData[10] << 8) + pAllData[11];

	if( nAllSize == *pnJustDataSize + 16 && *pnJustDataSize % 4 == 0 )
	{
		DWORD dwSumLittleEndian = 0, dwSumBigEndian = 0;
		for( int i=0 ; i < *pnJustDataSize / 4 ; i++ )
		{//�`�F�b�N�T���̌v�Z
			dwSumLittleEndian += (pJustData[4*i] << 24) + (pJustData[4*i+1] << 16)
					+ (pJustData[4*i+2] << 8) + (pJustData[4*i+3]);
			dwSumBigEndian += (pJustData[4 * i]) + (pJustData[4 * i + 1] << 8)
				+ (pJustData[4 * i + 2] << 16) + (pJustData[4 * i + 3] << 24);
		}
		//�`�F�b�N�T���l�̓ǂݍ��݁@pAllData�̍Ō�S�o�C�g
		DWORD dwSumData = (pAllData[nAllSize-4] << 24) + (pAllData[nAllSize-3] << 16) 
					    	+ (pAllData[nAllSize-2] << 8) + pAllData[nAllSize-1];
		if( dwSumLittleEndian != dwSumData && dwSumBigEndian != dwSumData )
		{
			pJustData = NULL;
		}
	}else
	{
		pJustData = NULL;
	}
	return pJustData;
}

void CEEPDispSel::OnBtnClose() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	OnCancel();
}

void CEEPDispSel::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����Ă�������
	for( int i=0; i<MAX_EEPROM_DATA_COUNT; ++i ){
		if( m_pData[i] != NULL ){
			delete [] m_pData[i];
			m_pData[i] = NULL;
		}
	}
}

void CEEPDispSel::OnDblclkList() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	OnBtnView();
}
