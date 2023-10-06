/**
 * StatisticsDay.cpp
 */

#include "stdafx.h"
#include "StatisticsDay.h"
#include "LogCode_LogReader.h"

/**
 * CStatisticsDay.
 */
CStatisticsDay::CStatisticsDay()
{
	m_cntMenuTestPrint = 0;
	m_iMenuTestPrintFlag = 0;
	m_date.setDate(0, 0, 0);
	m_cntPrintStart = 0;
	m_cntPrintEnd = 0;
	m_cntJobStart = 0;
	m_cntAutoPurgeStart = 0;
	m_cntPowerOn = 0;
	// m_cntWiperC = 0;
	// m_cntWiperW = 0;
	// m_cntFlushC = 0;
	// m_cntFlushW = 0;
	m_iResolution = 1200;

	for(int i = 0; i < 10; i++) m_cntInkVolume[i] = 0.0;
	for(int i = 0; i <  3; i++) m_cntPurgeStart[i] = 0;
}

/**
 * ~CStatisticsDay.
 */
CStatisticsDay::~CStatisticsDay()
{

}

/**
 * ����J�n�̐��𓾂�.
 * @return ����J�n�̐�
 */
unsigned long CStatisticsDay::getCountPrintStart() const
{
	return m_cntPrintStart;
}

/**
 * ����I���̐��𓾂�.
 * @return ����I���̐�
 */
unsigned long CStatisticsDay::getCountPrintEnd() const
{
	return m_cntPrintEnd;
}

/**
 * ����W���u�i�f�[�^�]���j�J�n�̐��𓾂�
 * @return ����W���u�i�f�[�^�]���j�J�n
 */
unsigned long CStatisticsDay::getCountJobStart() const
{
	return m_cntJobStart;
}

/**
 * �d��ON�̐��𓾂�.
 * @return �d��ON�̐�
 */
unsigned long CStatisticsDay::getCountPowerOn() const
{
	return m_cntPowerOn;
}

/**
 * ��������e�i���X�񐔂𓾂�.
 * @return ��������e�i���X��
 */
// unsigned long CStatisticsDay::getCountMainteWiperC() const
// {
// 	return m_cntWiperC;
// }
// unsigned long CStatisticsDay::getCountMainteWiperW() const
// {
// 	return m_cntWiperW;
// }
// unsigned long CStatisticsDay::getCountMainteFlushC() const
// {
// 	return m_cntFlushC;
// }
// unsigned long CStatisticsDay::getCountMaintePlushW() const
// {
// 	return m_cntFlushW;
// }

/**
 * �e�F�̃h�b�g�J�E���g�𓾂�.
 * @param dot[] [out]�@�h�b�g�J�E���g�@KMCY�̏�
 */
/*
void CStatisticsDay::getCountDot(unsigned long dot[]) const
{
	for(int i = 0; i < 8; i++)
		dot[i] = m_cntDot[i];
}
*/
/**
 * �I�[�g�p�[�W�񐔂𓾂�.
 * @return �I�[�g�p�[�W��
 */
unsigned long CStatisticsDay::getCountAutoPurgeStart() const
{
	return m_cntAutoPurgeStart;
}

/**
 * ���j���[����̃e�X�g�v�����g.
 * @return ���j���[����̃e�X�g�v�����g��
 */
unsigned long CStatisticsDay::getMenuTestPrint() const
{
	return m_cntMenuTestPrint;
}


/**
 * �e�F�̃p�[�W�񐔂𓾂�.
 * @param purge[] [out]�@�p�[�W�񐔁@KMCY�̏�
 */
void CStatisticsDay::getCountPurgeStart(unsigned long purge[]) const
{
	for(int i = 0; i < 3; i++)
		purge[i] = m_cntPurgeStart[i];
}

/**
 * �e���O�𐔂���.
 * @param pRecord ���O
 */
void CStatisticsDay::count(CLogRecord* pRecord, BOOL* pbOverNight)
{
	*pbOverNight = FALSE;

	if(pRecord->isMatched(CODE_PRINTSTART))
	{
		m_cntPrintStart += 1;
		if( m_iMenuTestPrintFlag )
		{
			m_iMenuTestPrintFlag--;
		}
	}
	else if(pRecord->isMatched(CODE_PRINTEND) || pRecord->isMatched(CODE_PRINTSTOP))
	{
		if( m_cntPrintStart == 0 )
		{
			*pbOverNight = TRUE;
		}else
		{
			unsigned long dot[24];
			((CLogAnalyze*)pRecord)->getCountDot(dot);
			for(int i = 0; i < 8; i++) {
				m_cntInkVolume[i] += CLogAnalyze::dotToCC( dot[i*3+2], dot[i*3+1], dot[i*3],  m_iResolution, i >= 4 );
			}

			if( pRecord->isMatched(CODE_PRINTEND) )
			{
				m_cntPrintEnd += 1;
				if( m_iMenuTestPrintFlag == 1 )
				{//�e�X�g�v�����g�ł���B 
					m_cntMenuTestPrint++;
				}
			}
		}
	}
	//����I��/��~(���F)
	else if( pRecord->isMatched(CODE_PRINTEND_SP) || pRecord->isMatched(CODE_PRINTSTOP_SP) )
	{
		if( m_cntPrintStart == 0 )
		{
			*pbOverNight = TRUE;
		}else
		{
			unsigned long dot[30];
			((CLogAnalyze*)pRecord)->getCountDotSp(dot);
			for(int i = 0; i < 10; i++) {
				m_cntInkVolume[i] += CLogAnalyze::dotToCC( dot[i*3+2], dot[i*3+1], dot[i*3],  m_iResolution, 4 <= i && i < 8 );
			}

			if( pRecord->isMatched(CODE_PRINTEND_SP) )
			{
				m_cntPrintEnd += 1;
				if( m_iMenuTestPrintFlag == 1 )
				{//�e�X�g�v�����g�ł���B 
					m_cntMenuTestPrint++;
				}
			}
		}
	}
	else if(pRecord->isMatched(CODE_GRAPHIC))
	{
		char cColor, cWhite, cMultipass, cEnhance;
		((CLogAnalyze*)pRecord)->GetGraphics(&cColor, &cWhite, &m_iResolution, &cMultipass, &cEnhance);
	}
	else if(pRecord->isMatched(CODE_JOBALL) || pRecord->isMatched(CODE_JOBALL_SP))
	{
		m_cntJobStart += 1;
	}
	else if(pRecord->isMatched(CODE_POWERON))
	{
		m_cntPowerOn += 1;
	}
	else if(pRecord->isMatched(CODE_TESTPRINT))
	{
		m_iMenuTestPrintFlag = 2;//�e�X�g�v�����g�̃��O������΁A�Q���Z�b�g����
									//�v�����g�X�^�[�g��������A���̃t���O���P���炷
									//�e�X�g�v�����g�̎��́A�v�����g�G���h�ɂ�����
									//���̃t���O�͂P�ƂȂ��Ă���B�O�̓e�X�g�v�����g�ł͂Ȃ�
	}
	else if(pRecord->isMatched(CODE_AUTOPURGE))
	{
		m_cntAutoPurgeStart += 1;
	}
	else if(pRecord->isMatched(CODE_PURGESTART))
	{
		unsigned long type, color;
		((CLogAnalyze*)pRecord)->GetPurge(&type, &color);

		if(type==0 || type==1 || type==2 || type==4)
		{
			if(color==0x01 || color==0x02)	m_cntPurgeStart[0] += 1;
			if(color==0x01 || color==0x03)	m_cntPurgeStart[1] += 1;
			if(color==0x01 || color==0x14)	m_cntPurgeStart[2] += 1;
		}
	}
	// else if(pRecord->isMatched(CODE_MNT_WIPER_C))
	// {
	// 	m_cntWiperC += 1;
	// }
	// else if(pRecord->isMatched(CODE_MNT_WIPER_W))
	// {
	// 	m_cntWiperW += 1;
	// }
	// else if(pRecord->isMatched(CODE_MNT_FLUSH_C))
	// {
	// 	m_cntFlushC += 1;
	// }
	// else if(pRecord->isMatched(CODE_MNT_FLUSH_W))
	// {
	// 	m_cntFlushW += 1;
	// }
}

/**
 * ���O�̓��t�����ꏏ�H.
 * @param pRecord ���O
 * @return true:Yes , false:No 
 */
bool CStatisticsDay::isSameDay(CLogRecord* pRecord)
{
	return m_date.isSameDay(pRecord->getDate());
}

/**
 * ���t���擾����.
 * @return ���t
 */
const CLogDate& CStatisticsDay::getDate() const
{
	return m_date;
}

/**
 * ���t��ݒ肷��.
 * @param date ���t
 */
void CStatisticsDay::setDate(const CLogDate& date)
{
	m_date = date;
}

/**
 * ������ɕϊ�����.
 * @param dateFormat ���t�̃t�H�[�}�b�g
 * @param machine �}�V����
 * @return �ϊ�����������
 */
CString CStatisticsDay::toString( int dateFormat , int typeSeparate ) const
{
	CString format;
	CString string;

	format	=	"%s,%d,%u,%u,"						//���t, �������,
//				"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,"	//�h�b�g��(�e,�v)
				"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,"	//�C���N��(�e,�v)
				"%d,%d,%d,%d,"						//�p�[�W��(�I�[�g,�e)
				"%d,%d,%d";							//Job��M��, �d��������, �L�����Z����
//				"%u,%u,%u,%u,%u,%u,%u,%u,%u",		//������(�e,��������e)
//				"%u,%u,%u,%u";						//��������e
	if( typeSeparate == 1 )
		format.Replace( _T(","), _T(";") );

	string.Format( format, 
		m_date.toString(dateFormat), m_cntPrintEnd - m_cntMenuTestPrint , m_cntMenuTestPrint , m_cntPrintEnd ,
//			m_cntDot[0], m_cntDot[1], m_cntDot[2], m_cntDot[3], m_cntDot[4], m_cntDot[5], m_cntDot[6], m_cntDot[7], 
//			m_cntDot[0]+m_cntDot[1]+m_cntDot[2]+m_cntDot[3], m_cntDot[4]+m_cntDot[5]+m_cntDot[6]+m_cntDot[7], 
			m_cntInkVolume[0], m_cntInkVolume[1], m_cntInkVolume[2], m_cntInkVolume[3], 
			m_cntInkVolume[4], m_cntInkVolume[5], m_cntInkVolume[6], m_cntInkVolume[7], 
			m_cntInkVolume[8], m_cntInkVolume[9], 
			m_cntInkVolume[0]+m_cntInkVolume[1]+m_cntInkVolume[2]+m_cntInkVolume[3]+m_cntInkVolume[8]+m_cntInkVolume[9],
			m_cntInkVolume[4]+m_cntInkVolume[5]+m_cntInkVolume[6]+m_cntInkVolume[7], 
		m_cntAutoPurgeStart,
		m_cntPurgeStart[0], m_cntPurgeStart[1], m_cntPurgeStart[2], 
			m_cntJobStart, m_cntPowerOn, m_cntPrintStart-m_cntPrintEnd);
//		m_cntInkEmpty[0],m_cntInkEmpty[1],m_cntInkEmpty[2],m_cntInkEmpty[3],
//		m_cntInkEmpty[4],m_cntInkEmpty[5],m_cntInkEmpty[6],m_cntInkEmpty[7],
//		m_cntWiperC, m_cntWiperW, m_cntFlushC, m_cntFlushW);

	return string;
}

/**
 * �^�C�g�����擾����.
 * @return �^�C�g���̕�����
*/
void CStatisticsDayList::title(CArchive& ar, int separate)
{
	CString strHeader = 
			"date,print,menu test print,print sum,"
//			"dotK,dotM,dotC,dotY,dotW1,dotW2,dotW3,dotW4,dotCMYK,dotW,"
			"inkK,inkY,inkC,inkM,inkW1,inkW2,inkW3,inkW4,inkSp1,inkSp2,inkCMYK,inkW,"
			"autopurge,purgeC,purgeW,purgeSP,"
			"Job,powerON,cancel"
//			"inkEmpK,inkEmpM,inkEmpC,inkEmpY,inkEmpW1,inkEmpW2,inkEmpW3,inkEmpW4,"
			// "MntWiperC,MntWiperW,MntFlushC,MntFlushW"
			"\r\n";

	if( separate == 1 )
		strHeader.Replace(_T(","), _T(";") );

	ar.WriteString(strHeader);
}

/**
 * ����ȑO�̓��t�͖���
 */
CLogDate CStatisticsDayList::m_dateActivated(2004, 1, 1);

/**
 * CStatisticsDayList.
 */
CStatisticsDayList::CStatisticsDayList()
{
	m_dateFormat = CLogDate::DATE_FORMAT_ENGLISH_DETAIL;
	m_separateType = 0;
	m_machine = "";
}

/**
 * ~CStatisticsDayList.
 */
CStatisticsDayList::~CStatisticsDayList()
{

}

/**
 * ���t�̃t�H�[�}�b�g��ݒ肷��.
 * @param format �t�H�[�}�b�g
 */
void CStatisticsDayList::setDateFormat(int format)
{
	m_dateFormat = format;
}

/**
 * �}�V������ݒ肷��.
 * @param machine 
 */
void CStatisticsDayList::setMachineName(const CString& machine)
{
	m_machine = machine;
}

/**
 * ��؂蕶����ݒ肷��.
 * @param type 
 */
void CStatisticsDayList::setSeparateType(int separate)
{
	m_separateType = separate;
}

/**
 * ���v�����쐬����.
 * @param records ���O
 * @param date1 �J�n�����i�܂ށj
 * @param date2 �I�������i�܂܂Ȃ��j
 */
void CStatisticsDayList::create(const CLogList& records,
	const CLogDate& date1, const CLogDate& date2)
{
	CStatisticsDay* pStatDay = NULL;
	POSITION pos = records.GetHeadPosition();
	if(date1 != date2)
	{
		while(NULL != pos)
		{
			CLogRecord* pRecord = records.GetNext(pos);

			if(pRecord->getDate() < date1 || date2 <= pRecord->getDate())
				continue;

			pStatDay = countStatistics(pStatDay, pRecord);
		}
	}
	else
	{
		while(NULL != pos)
		{
			CLogRecord* pRecord = records.GetNext(pos);
			pStatDay = countStatistics(pStatDay, pRecord);
		}
	}
	AddTail(pStatDay);
}

/**
 * ���O�𐔂���.
 * @param pStatDay ���v���
 * @param pRecord ���O
 * @return ���v���
 */
CStatisticsDay* CStatisticsDayList::countStatistics(CStatisticsDay* pStatDay, CLogRecord* pRecord)
{
	if(NULL != pStatDay &&
	   !pStatDay->isSameDay(pRecord))
	{
		AddTail(pStatDay);
		pStatDay = NULL;
	}
	if(NULL == pStatDay)
	{
		pStatDay = new CStatisticsDay;
		pStatDay->setDate(pRecord->getDate());
	}
	BOOL bOverNight;
	pStatDay->count( pRecord , &bOverNight );
	if( bOverNight && !IsEmpty())
	{//������ߑO�O�����܂�������
		CStatisticsDay* pStatYesterDay = GetTail();
		pStatYesterDay->count( pRecord , &bOverNight );	
	}
	return pStatDay;
}

/**
 * �ۑ�����.
 * @param ar 
 */
void CStatisticsDayList::store(CArchive& ar)
{
	CLogDate date , AfterMonthDate;

	CTime ct = CTime::GetCurrentTime();
	AfterMonthDate.setDate( ct.GetYear() , ct.GetMonth() , ct.GetDay() );
	AfterMonthDate.afterMonth();//�����ꃖ����̓��t�@���̓��܂ł̃��O�����ǂ܂Ȃ�

	// �ŏ���1����ۑ�
	POSITION pos = GetHeadPosition();
	while(NULL != pos)
	{
		CStatisticsDay* pStatDay = GetNext(pos);
		if( pStatDay )
		{
			if(pStatDay->getDate() < m_dateActivated || pStatDay->getDate() > AfterMonthDate )
			{
				continue;				// �Â����t�ƍ����ꃖ����ȍ~�͖���
			}

			CString string = pStatDay->toString(m_dateFormat, m_separateType);
			ar.WriteString(string);
			ar.WriteString(_T("\r\n"));

			date = pStatDay->getDate();
			date.afterDay();
			break;
		}
	}

	// �c��̓���ۑ�
	while(NULL != pos)
	{
		CStatisticsDay* pStatDay = GetNext(pos);
		if(pStatDay->getDate() < m_dateActivated || pStatDay->getDate() > AfterMonthDate )
		{
			continue;				// �Â����t�ƍ����ꃖ����ȍ~�͖���
		}

		if(date < pStatDay->getDate())
		{
			// ���t����΂Ȃ��悤�ɖ��߂�
			while(!date.isSameDay(pStatDay->getDate()))
			{
				CStatisticsDay statDay;
				statDay.setDate(date);
				CString string = statDay.toString(m_dateFormat, m_separateType);
				ar.WriteString(string);
				ar.WriteString(_T("\r\n"));
				date.afterDay();
			}
		}

		CString string = pStatDay->toString(m_dateFormat, m_separateType);
		ar.WriteString(string);
		ar.WriteString(_T("\r\n"));

		date = pStatDay->getDate();
		date.afterDay();
	}
}
