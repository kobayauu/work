// StatDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "bgjservtool.h"
#include "StatDlg.h"
#include "LogDate.h"
#include "zlib/zlib.h"
#include "FolderDialog.h"
#include "StatisticsJob.h"
#include "StatisticsDay.h"
#include "Language.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define SIZE_FILE_ID	8

/////////////////////////////////////////////////////////////////////////////
// CStatDlg �_�C�A���O


CStatDlg::CStatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStatDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStatDlg)
	m_bDate    = FALSE;
	m_bMachine = FALSE;
	m_bSeparate= FALSE;
	m_day1     = 0;
	m_day2     = 0;
	m_machine  = _T("");
	m_folder   = _T("");
	m_month1   = 0;
	m_month2   = 0;
	m_statday  = _T("");
	m_statjob  = _T("");
	m_year1    = 0;
	m_year2    = 0;
	//}}AFX_DATA_INIT

/*	CLogDate date1, date2;
	CLogReaderDoc* pDoc = (CLogReaderDoc*) GetDocument();
	pDoc->getDate(date1, date2);

	unsigned long year, month, day, hour, min, sec, msec;
	date1.getDate(year, month, day, hour, min, sec, msec);
	m_year1 = year; m_month1 = month; m_day1 = day;
	date2.getDate(year, month, day, hour, min, sec, msec);
	m_year2 = year; m_month2 = month; m_day2 = day;

	CString strFile = pDoc->GetTitle().SpanExcluding(".");
	m_statday = strFile + "_D" + ".csv";
	m_statjob = strFile + "_J" + ".csv";*/
}

CStatDlg::~CStatDlg()
{
	while(!m_records.IsEmpty())
		delete m_records.RemoveHead();
}


void CStatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStatDlg)
	DDX_Check(pDX, IDC_CHECK_DATE, m_bDate);
	DDX_Check(pDX, IDC_CHECK_MACHINE, m_bMachine);
	DDX_Check(pDX, IDC_CHECK_SEPARATE, m_bSeparate);
	DDX_Text(pDX, IDC_EDIT_DAY1, m_day1);
	DDV_MinMaxUInt(pDX, m_day1, 1, 31);
	DDX_Text(pDX, IDC_EDIT_DAY2, m_day2);
	DDV_MinMaxUInt(pDX, m_day2, 1, 31);
	DDX_Text(pDX, IDC_EDIT_MACHINE, m_machine);
	DDX_Text(pDX, IDC_EDIT_FOLDER, m_folder);
	DDX_Text(pDX, IDC_EDIT_MONTH1, m_month1);
	DDV_MinMaxUInt(pDX, m_month1, 1, 12);
	DDX_Text(pDX, IDC_EDIT_MONTH2, m_month2);
	DDV_MinMaxUInt(pDX, m_month2, 1, 12);
	DDX_Text(pDX, IDC_EDIT_STATDAY, m_statday);
	DDX_Text(pDX, IDC_EDIT_STATJOB, m_statjob);
	DDX_Text(pDX, IDC_EDIT_YEAR1, m_year1);
	DDV_MinMaxUInt(pDX, m_year1, 2020, 2100);
	DDX_Text(pDX, IDC_EDIT_YEAR2, m_year2);
	DDV_MinMaxUInt(pDX, m_year2, 2020, 2100);
	//}}AFX_DATA_MAP
}




BEGIN_MESSAGE_MAP(CStatDlg, CDialog)
	//{{AFX_MSG_MAP(CStatDlg)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnButtonCancel)
	ON_EN_CHANGE(IDC_EDIT_YEAR1, OnChangeEditYear1)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, OnButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_FOLDER, OnButtonFolder)
	ON_BN_CLICKED(IDC_CHECK_DATE, OnCheckDate)
	ON_BN_CLICKED(IDC_CHECK_MACHINE, OnCheckMachine)
	ON_EN_CHANGE(IDC_EDIT_MONTH1, OnChangeEditMonth1)
	ON_EN_CHANGE(IDC_EDIT_DAY1, OnChangeEditDay1)
	ON_EN_CHANGE(IDC_EDIT_YEAR2, OnChangeEditYear2)
	ON_EN_CHANGE(IDC_EDIT_MONTH2, OnChangeEditMonth2)
	ON_EN_CHANGE(IDC_EDIT_DAY2, OnChangeEditDay2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStatDlg ���b�Z�[�W �n���h��

void CStatDlg::OnOK() 
{
	// TODO: ���̈ʒu�ɂ��̑��̌��ؗp�̃R�[�h��ǉ����Ă�������
}

void CStatDlg::OnButtonCancel() 
{
	OnCancel();	
}

void CStatDlg::OnChangeEditYear1() 
{
	updateFileName();
}

BOOL CStatDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	LangSetWndTxt( this , IDS_TITLE_STAT );
	LangSetWndTxt( GetDlgItem( IDC_CHECK_DATE )	   , IDS_CHECK_DATE	   );
	LangSetWndTxt( GetDlgItem( IDC_CHECK_MACHINE ) , IDS_CHECK_MACHINE );
	LangSetWndTxt( GetDlgItem( IDC_CHECK_SEPARATE ), IDS_CHECK_SEPARATE);
	LangSetWndTxt( GetDlgItem( IDC_PL_DOT )		   , IDS_PL_DOT		   );
	LangSetWndTxt( GetDlgItem( IDC_FOLDER )		   , IDS_FOLDER		   );
	LangSetWndTxt( GetDlgItem( IDC_DAY1 )		   , IDS_DAY1		   );
	LangSetWndTxt( GetDlgItem( IDC_JOB )		   , IDS_JOB		   );
	LangSetWndTxt( GetDlgItem( IDC_BUTTON_FOLDER ) , IDS_BROWSE		   );
	LangSetWndTxt( GetDlgItem( IDC_BUTTON_SAVE )   , IDS_SAVE		   );
	LangSetWndTxt( GetDlgItem( IDC_BUTTON_CANCEL ) , IDS_CANCEL		   );

	int iRet = ReadLogFile();

	//2020/1/1���獡���܂�
	m_year1 = 2020; m_month1 = 1; m_day1 = 1;
	CLogDate NowDate;
	CTime ct = CTime::GetCurrentTime();
	NowDate.setDate( ct.GetYear() , ct.GetMonth() , ct.GetDay() );
	unsigned long year, month, day, hour, min, sec, msec;
	NowDate.getDate(year, month, day, hour, min, sec, msec);
	m_year2 = year; m_month2 = month; m_day2 = day;

	TCHAR drive[_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];
	TCHAR fname[_MAX_FNAME];
	TCHAR ext[_MAX_EXT];
	_tsplitpath(m_csLogFile, drive, dir, fname, ext);

	m_statday = (CString)fname + "_D" + ".csv";
	m_statjob = (CString)fname + "_J" + ".csv";

	if( drive[0] == 0 )
	{
		TCHAR cCurrentFolder[MAX_PATH];
		GetCurrentDirectory( MAX_PATH , cCurrentFolder );
		m_folder = cCurrentFolder;
	}
	else
	{
		CString strDir = dir;
		if( strDir != "\\" )
		{
			strDir = strDir.Left( strDir.GetLength() - 1 );//�Ō��\�̏���
		}
		m_folder  = drive + strDir;
	}

	CWinApp* pApp = AfxGetApp();

	EnableDate( m_bDate );
	GetDlgItem(IDC_EDIT_MACHINE)->EnableWindow( m_bMachine );

	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_YEAR1 ))->SetRange(2020, 2100);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_MONTH1))->SetRange(   1,   12);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DAY1  ))->SetRange(   1,   31);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_YEAR2 ))->SetRange(2020, 2100);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_MONTH2))->SetRange(   1,   12);
	((CSpinButtonCtrl*)GetDlgItem(IDC_SPIN_DAY2  ))->SetRange(   1,   31);

	UpdateData( FALSE );

	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

/**
 * �t�@�C�������X�V����
 */
void CStatDlg::updateFileName()
{
	CWnd* pItem1 = GetDlgItem(IDC_EDIT_STATDAY);
	CWnd* pItem2 = GetDlgItem(IDC_EDIT_STATJOB);
	if(NULL == pItem1 || NULL == pItem2)
		return;

	TCHAR drive[_MAX_DRIVE];
	TCHAR dir[_MAX_DIR];
	TCHAR fname[_MAX_FNAME];
	TCHAR ext[_MAX_EXT];
	_tsplitpath(m_csLogFile, drive, dir, fname, ext);

	CString strDay, strJob;
	strDay = (CString)fname + "_D";
	strJob = (CString)fname + "_J";


	CString strAdd = createDateString();
	strDay += strAdd;
	strJob += strAdd;
	

	pItem1->SetWindowText( strDay );
	pItem2->SetWindowText( strJob );

}

/**
 * ���t�͈̔͂̕���������.
 * @return "���t.csv"
 */
CString CStatDlg::createDateString()
{
	if(!m_bDate)
		return ".csv";

	CString strDate;

	CDataExchange dx(this, TRUE);

	unsigned long year1, month1, day1;
	DDX_Text(&dx, IDC_EDIT_YEAR1, year1);
	DDX_Text(&dx, IDC_EDIT_MONTH1, month1);
	DDX_Text(&dx, IDC_EDIT_DAY1, day1);

	unsigned long year2, month2, day2;
	DDX_Text(&dx, IDC_EDIT_YEAR2, year2);
	DDX_Text(&dx, IDC_EDIT_MONTH2, month2);
	DDX_Text(&dx, IDC_EDIT_DAY2, day2);

	strDate.Format(_T("_%d_%02d%02d-%d_%02d%02d.csv"),
			year1, month1, day1, year2, month2, day2);
	
	return strDate;
}

int CStatDlg::ReadLogFile()
{
	int iRet = GetUnCompFile();
	if( iRet >= 0 )
	{
		iRet = m_records.load( m_csUnCompFile );
	}
	if( m_csUnCompFile != m_csLogFile )
	{//�𓀃t�@�C���̍폜
		DeleteFile( m_csUnCompFile );
	}

	return iRet;
}

//���O�t�@�C���̃I�[�v��
int CStatDlg::GetUnCompFile()
{
	m_csUnCompFile = ""; 
	int iRet = -1; // 1:�m�[�}��, 0:Not Log File, 2:Zlib -1:Error

	FILE* fp = _tfopen( m_csLogFile , _T("rb") );
	if( fp != NULL )
	{
		iRet = 0;
		m_csUnCompFile = m_csLogFile;
		char cID[SIZE_FILE_ID+1];
		for( int i=0; i<sizeof(cID); ++i ){
			cID[i] = 0;
		}
		size_t nSize = fread( cID, 1, SIZE_FILE_ID, fp );
		if( nSize == SIZE_FILE_ID )
		{
			CString cs = cID;
			if( cs == "GTXLG1XX" )
			{//�m�[�}��
				iRet = 1;
			}else if( cs == "GTXLG1ZL" )
			{//���k�`��
				iRet = UnCompZlgFile( fp ); //��
			}
		}
		fclose( fp );
	}
	return iRet;
}

//Zlg�t�@�C�����𓀂���
int CStatDlg::UnCompZlgFile( FILE* fp )
{
	int iRet = 1;// 1:OK, 0:Not Log File, -1:Error
	FILE* fpTmp = _tfopen( m_csLogFile + _T(".tjg") , _T("wb") );//tjg�͔��Ȃ����낤�g���q
	if( fpTmp == NULL )
	{
		iRet = -2;
	}else
	{
		//�t�@�C������ID"GT782LZ1"��̃f�[�^�����o���ā@m_csFileName + ".tjg"�̃t�@�C�����쐬����
		//m_pFile�̈ʒu�̓t�@�C������ID�̌���w���Ă���
		BYTE byBuff[1000];
		size_t nLen;
		for( ;iRet >= 0 ; )
		{
			nLen = fread( byBuff, 1, sizeof(byBuff), fp );
			if( ferror(fp) )
			{
				iRet = -3;
			}else if( nLen == 0 )
			{
				break;
			}else
			{
				if( fwrite( byBuff , 1 , (unsigned)nLen , fpTmp ) != (int)nLen )
				{
					iRet = -4;
				}
			}
		}
		fclose( fpTmp );
	
		if( iRet >= 0 )
		{//�t�@�C������ID�Ȃ��̏�����Zlib�t�@�C�����𓀂���@�𓀌�̃t�@�C������m_csFileName + ".bgl"
			iRet = UnCompZlib( m_csLogFile + ".tjg" , m_csLogFile + ".bgl" );//bgl�����Ȃ����낤�g���q
		}
		DeleteFile( m_csLogFile + ".tjg" );//Zlib�t�@�C���̍폜
		if( iRet >= 0 )
		{
			m_csUnCompFile = m_csLogFile + ".bgl";
		}
	}
	return iRet;
}

#define COMP_BUFF_SIZE 16384
//Zlib�t�@�C�����𓀂��A���OstrUnZlib�̃t�@�C�������
int CStatDlg::UnCompZlib( CString strMoto , CString strUnZlib )
{
	ATL::CW2A szMoto(strMoto);
	ATL::CW2A szUnZlib(strUnZlib);
	int iRet = 0;
    FILE  *fpDst;
    gzFile pgzSrc;
    pgzSrc = gzopen( szMoto, "rb" );
    if( pgzSrc != NULL ){
		fpDst = fopen( szUnZlib , "wb" );
		if( fpDst != NULL ){
			char bBuff[ COMP_BUFF_SIZE ];
			int nLen;
			for(;iRet >= 0 ; ){
				nLen = gzread( pgzSrc, bBuff, sizeof(bBuff) );//�𓀂��ēǂݍ���
				if( nLen < 0 ){
					iRet = -5;
				}else if( nLen == 0 ){
					break;
				}else{
					if( (int)fwrite( bBuff, 1, (unsigned)nLen, fpDst ) != nLen ){
						iRet = -6;
					}
				}
			}
			fclose( fpDst );
			if( gzclose( pgzSrc ) != Z_OK){
				iRet = -7;
			}
		}else iRet = -8;
	}else iRet = -9;

	return iRet;
}

void CStatDlg::OnButtonSave() 
{
	UpdateData(TRUE);

	if( 2020 <= m_year1  && 2100 >= m_year1  &&
		   1 <= m_month1 &&   12 >= m_month1 && 
		   1 <= m_day1   &&   31 >= m_day1   &&
		2020 <= m_year2  && 2100 >= m_year2  &&
		   1 <= m_month2 &&   12 >= m_month2 && 
		   1 <= m_day2   &&   31 >= m_day2  )
	{
	
		CWaitCursor cursor;
		int cntSave = 0;

		CLogDate date1(0, 0, 0);
		CLogDate date2(0, 0, 0);
		if(m_bDate)
		{
			date1.setDate(m_year1, m_month1, m_day1);
			date2.setDate(m_year2, m_month2, m_day2);
			date2.afterDay();
		}

		CString strPathDay = m_folder + "\\" + m_statday;
		if(m_statday.SpanExcluding(_T("\\/:*?\"<>|")) == m_statday && m_statday != "" )
		{
			if(canSave(strPathDay))
			{
				storeStatisticsDays(
					date1, date2,
				//	(m_dateFormat) ? 
				//		CLogDate::DATE_FORMAT_JAPANESE:
						CLogDate::DATE_FORMAT_ENGLISH,
					m_bSeparate ? 1 : 0,
					(m_bMachine) ? m_machine : "",
					strPathDay
				);
				cntSave++;
			}
		}else
		{
			LangAccessDeniedMsgBox( strPathDay , -60 );
		}

		CString strPathJob = m_folder + "\\" + m_statjob;
		if(m_statjob.SpanExcluding(_T("\\/:*?\"<>|")) == m_statjob && m_statjob != "")
		{
			if(canSave(strPathJob))
			{
				storeStatisticsJobs(
					date1, date2,
				//	(m_dateFormat) ? 
				//		CLogDate::DATE_FORMAT_JAPANESE_DETAIL:
						CLogDate::DATE_FORMAT_ENGLISH_DETAIL,
	//				(m_timeFormat) ?
					CElapsedTime::TIME_FORMAT_HHMMSS ,
	//					CElapsedTime::TIME_FORMAT_MINUTE,
					m_bSeparate ? 1 : 0,
					(m_bMachine) ? m_machine : "",
					strPathJob
				);
				cntSave++;
			}
		}else
		{
			LangAccessDeniedMsgBox( strPathJob , -61 );
		}

		if(1 <= cntSave)
			EndDialog(IDOK);
	}
}


/**
 * �����Ɠ��v��ۑ�����.
 * @param date1 �ۑ��J�n����
 * @param date2 �ۑ��I������
 * @param dateFormat ���t�t�H�[�}�b�g
 * @param machine �}�V����
 * @param strPath �ۑ���
 * @return true:���� , false:���s 
 */
BOOL CStatDlg::storeStatisticsDays(
			const CLogDate& date1, const CLogDate& date2, 
			int dateFormat, int typeSeparate, const CString& machine,
			const CString& strPath) const
{
	BOOL bRet = TRUE;
	CFile file;
	if(file.Open(strPath, CFile::modeCreate|CFile::modeWrite))
	{
		CStatisticsDayList statDays;
		statDays.setDateFormat(dateFormat);
		statDays.setSeparateType(typeSeparate);
		statDays.setMachineName(machine);
		statDays.create(m_records, date1, date2);

		CArchive ar(&file, CArchive::store);
		ar.Write( "\xff\xfe", 2 );

		if("" != machine)//�R�����g
		{
			ar.WriteString(machine+"\r\n");
		}

		statDays.title(ar, typeSeparate);
		statDays.store(ar);

		ar.Close();
		file.Close();

		while(!statDays.IsEmpty())
			delete statDays.RemoveHead();
	}
	else
	{
		LangAccessDeniedMsgBox( strPath , -62 );
		bRet = FALSE;

	}
	return bRet;
}


/**
 * JOB���Ɠ��v��ۑ�����.
 * @param date1 �ۑ��J�n����
 * @param date2 �ۑ��I������
 * @param dateFormat ���t�t�H�[�}�b�g
 * @param timeFormat �W���u���ԃt�H�[�}�b�g
 * @param machine �}�V����
 * @param strPath �ۑ���
 * @return true:���� , false:���s 
 */
BOOL CStatDlg::storeStatisticsJobs(
			const CLogDate& date1, const CLogDate& date2, 
			int dateFormat, int timeFormat, int typeSeparate, const CString& machine,
			const CString& strPath) const
{
	BOOL bRet = TRUE;
	CFile file;
	if(file.Open(strPath, CFile::modeCreate|CFile::modeWrite))
	{
		CStatisticsJobList statJobs;
		statJobs.setDateFormat(dateFormat);
		statJobs.setTimeFormat(timeFormat);
		statJobs.setSeparateType(typeSeparate);
		statJobs.setMachineName(machine);
		statJobs.create(m_records, date1, date2);

		CArchive ar(&file, CArchive::store);
		ar.Write( "\xff\xfe", 2 );

		if("" != machine)//�R�����g
		{
			ar.WriteString(machine+"\r\n");
		}

		statJobs.title(ar, typeSeparate);
		statJobs.store(ar);

		ar.Close();
		file.Close();

		while(!statJobs.IsEmpty())
			delete statJobs.RemoveHead();
	}
	else
	{
		LangAccessDeniedMsgBox( strPath , -63 );
		bRet = FALSE;
	}
	return bRet;
}

void CStatDlg::OnButtonFolder() 
{
	CFolderDialog dlg(m_folder);
	dlg.setTitle(_T("Select Folder"));
	if(IDOK == dlg.doModal())
	{
		m_folder = dlg.getFolderPath();
		GetDlgItem(IDC_EDIT_FOLDER)->SetWindowText(m_folder);
	}
}

/**
 * �t�@�C����ۑ��ł���H.
 * @param strPath �p�X
 * @return true:Yes , false:No 
 */
bool CStatDlg::canSave(const CString& strPath) const
{
	CFileFind finder;
	if(!finder.FindFile(strPath))
		return true;

	CString strFormat = "%s already exists.\nDo you want to override it?";
	CString strText;
	strText.Format(strFormat, strPath);
	return (IDYES == AfxMessageBox(strText, MB_YESNO)) ? true : false;
}

void CStatDlg::OnCheckDate() 
{
	UpdateData( TRUE );
	EnableDate( m_bDate );
	updateFileName();
	
}

void CStatDlg::OnCheckMachine() 
{
	UpdateData( TRUE );
	GetDlgItem(IDC_EDIT_MACHINE)->EnableWindow( m_bMachine );	
}

void CStatDlg::EnableDate(BOOL bEnable)
{
	GetDlgItem(IDC_EDIT_YEAR1)->EnableWindow(bEnable);
	GetDlgItem(IDC_SPIN_YEAR1)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MONTH1)->EnableWindow(bEnable);
	GetDlgItem(IDC_SPIN_MONTH1)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_DAY1)->EnableWindow(bEnable);
	GetDlgItem(IDC_SPIN_DAY1)->EnableWindow(bEnable);

	GetDlgItem(IDC_EDIT_YEAR2)->EnableWindow(bEnable);
	GetDlgItem(IDC_SPIN_YEAR2)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_MONTH2)->EnableWindow(bEnable);
	GetDlgItem(IDC_SPIN_MONTH2)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_DAY2)->EnableWindow(bEnable);
	GetDlgItem(IDC_SPIN_DAY2)->EnableWindow(bEnable);
}

void CStatDlg::OnChangeEditMonth1() 
{
	updateFileName();	
}

void CStatDlg::OnChangeEditDay1() 
{
	updateFileName();	
}

void CStatDlg::OnChangeEditYear2() 
{
	updateFileName();	
}

void CStatDlg::OnChangeEditMonth2() 
{
	updateFileName();
}

void CStatDlg::OnChangeEditDay2() 
{
	updateFileName();	
}
