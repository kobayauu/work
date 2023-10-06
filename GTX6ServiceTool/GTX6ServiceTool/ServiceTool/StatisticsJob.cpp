/**
 * StatisticsJob.cpp
 */

#include "stdafx.h"
#include "StatisticsJob.h"
#include "LogCode_LogReader.h"

/**
 * CStatisticsJob.
 */
CStatisticsJob::CStatisticsJob()
{
	m_date.setDate(0, 0, 0);;
	m_cntPrintStart = 0;
	m_cntPrintEnd = 0;
	m_name = "";
	m_comment = "";
	m_time.resetToZero();
	m_timePrint.resetToZero();
	m_datePrintStart.setDate(0, 0, 0);
	m_datePrintEnd.setDate(0, 0, 0);
	m_iResolution = 1200;
	m_cMultipass = 0;
	for(int i = 0; i < 10; i++) m_cntInkVolume[i] = 0.0;
	for(int i = 0; i <  3; i++) m_cntPurgeStart[i] = 0;
	m_cFile = -1;
}

/**
 * ~CStatisticsJob.
 */
CStatisticsJob::~CStatisticsJob()
{

}

/**
 * 印刷開始の数を得る.
 * @return 印刷開始の数
 */
unsigned long CStatisticsJob::getCountPrintStart() const
{
	return m_cntPrintStart;
}

/**
 * 印刷終了の数を得る.
 * @return 印刷終了の数
 */
unsigned long CStatisticsJob::getCountPrintEnd() const
{
	return m_cntPrintEnd;
}

/**
 * 各色のドットカウントを得る.
 * @param dot[] [out]　ドットカウント　KMCYの順
 */
/*
void CStatisticsJob::getCountDot(unsigned long dot[]) const
{
	for(int i = 0; i < 8; i++)
		dot[i] = m_cntDot[i];
}
*/
/**
 * 各色のパージ回数を得る.
 * @param purge[] [out]　パージ回数　KMCYの順
 */
void CStatisticsJob::getCountPurgeStart(unsigned long purge[]) const
{
	for(int i = 0; i < 3; i++)
		purge[i] = m_cntPurgeStart[i];
}

/**
 * ジョブ名を得る.
 * @return ジョブ名
 */
const CString& CStatisticsJob::getName() const
{
	return m_name;
}

/**
 * ジョブコメントを得る.
 * @return ジョブコメント
 */
const CString& CStatisticsJob::getComment() const
{
	return m_comment;
}

/**
 * ジョブ内最後の印刷までの時間を得る.
 * @param hour [out] 時
 * @param min  [out] 分
 * @param sec  [out] 秒
 * @param msec  [out] 1/100秒
 */
void CStatisticsJob::getTime(unsigned long& hour, unsigned long& min,
	unsigned long& sec, unsigned long& msec) const
{
	m_time.getTime(hour, min, sec, msec);
}

/**
 * プラテン番号を得る.
 * @return プラテン番号
 *//*
int CStatisticsJob::getPlaten() const
{
	return m_platen;
}*/

/**
 * 各ログを数える.
 * @param pRecord ログ
 */
void CStatisticsJob::count(CLogRecord* pRecord)
{
	//印刷開始
	if( pRecord->isMatched(CODE_PRINTSTART) )
	{
		m_cntPrintStart += 1;
		m_datePrintStart = pRecord->getDate();

		CElapsedTime time;
		if(m_workTime.IsEmpty())
		{
			time.compute(m_date, m_datePrintStart);//ジョブスタートから印刷開始までの時間
			m_workTime.AddTail(time);
		}
		else
		{
			if(m_datePrintEnd != CLogDate(0, 0, 0))
			{	//前のプリントエンドからこのプリントスタートまでの時間
				time.compute(m_datePrintEnd, m_datePrintStart);
				m_workTime.AddTail(time);
				m_datePrintEnd.setDate(0, 0, 0);
			}
		}
	}
	//印刷終了/停止
	else if( pRecord->isMatched(CODE_PRINTEND) || pRecord->isMatched(CODE_PRINTSTOP) )
	{
		m_datePrintEnd = pRecord->getDate();
		if( pRecord->isMatched(CODE_PRINTEND) ) {
			m_cntPrintEnd += 1;
		}

		unsigned long dot[24];
		((CLogAnalyze*)pRecord)->getCountDot(dot);
		for(int i = 0; i < 8; i++) {
			m_cntInkVolume[i] += CLogAnalyze::dotToCC( dot[i*3+2], dot[i*3+1], dot[i*3],  m_iResolution, i >= 4 );
		}

		m_time.compute(m_date, m_datePrintEnd);

		CElapsedTime time;
		if(m_datePrintStart != CLogDate(0, 0, 0))
			time.compute(m_datePrintStart, m_datePrintEnd);
		if( pRecord->isMatched(CODE_PRINTEND) ) {
			m_timePrint += time;
		}

		if( !m_workTime.IsEmpty() )
		{
			m_workTime.GetTail() += time;//ワークタイムは、印刷時間も含まれる　
											//workTime=印刷終了(はじめはジョブスタート)から印刷終了まで
		}
	}
	//印刷終了/停止(特色)
	else if( pRecord->isMatched(CODE_PRINTEND_SP) || pRecord->isMatched(CODE_PRINTSTOP_SP) )
	{
		m_datePrintEnd = pRecord->getDate();
		if( pRecord->isMatched(CODE_PRINTEND_SP) ) {
			m_cntPrintEnd += 1;
		}

		unsigned long dot[30];
		((CLogAnalyze*)pRecord)->getCountDotSp(dot);
		for(int i = 0; i < 10; i++) {
			m_cntInkVolume[i] += CLogAnalyze::dotToCC( dot[i*3+2], dot[i*3+1], dot[i*3],  m_iResolution, 4 <= i && i < 8 );
		}

		m_time.compute(m_date, m_datePrintEnd);

		CElapsedTime time;
		if(m_datePrintStart != CLogDate(0, 0, 0))
			time.compute(m_datePrintStart, m_datePrintEnd);
		if( pRecord->isMatched(CODE_PRINTEND_SP) ) {
			m_timePrint += time;
		}

		if( !m_workTime.IsEmpty() )
		{
			m_workTime.GetTail() += time;//ワークタイムは、印刷時間も含まれる　
											//workTime=印刷終了(はじめはジョブスタート)から印刷終了まで
		}
	}
	//USBメモリからの読み込みの時
	if( pRecord->isMatched(CODE_USB_FILE_LOAD) )
	{
		//m_name  = pRecord->GetFileName();
		m_name    = ((CLogAnalyze*)pRecord)->getFilename();
		m_comment = "USB_MEMORY";
	}
	//印刷中のデータ
	else if(pRecord->isMatched(CODE_PURGESTART))
	{
		unsigned long type, color;
		((CLogAnalyze*)pRecord)->GetPurge(&type, &color);
		if(type==4)
		{
			if(color==0x01 || color==0x02)	m_cntPurgeStart[0] += 1;
			if(color==0x01 || color==0x03)	m_cntPurgeStart[1] += 1;
			if(color==0x01 || color==0x14)	m_cntPurgeStart[2] += 1;
		}
	}
	else if(pRecord->isMatched(CODE_JOBNAME))
	{
		m_name = ((CLogAnalyze*)pRecord)->getString();
	}
	else if(pRecord->isMatched(CODE_JOBCOMMENT))
	{
		m_comment = ((CLogAnalyze*)pRecord)->getString();
	}
	else if(pRecord->isMatched(CODE_GRAPHIC))
	{
		char cColor, cWhite;
		((CLogAnalyze*)pRecord)->GetGraphics( &cColor, &cWhite, &m_iResolution, &m_cMultipass, &m_cEnhance );
	}
	else if( pRecord->isMatched(CODE_PCINFO) )
	{
		((CLogAnalyze*)pRecord)->GetPcInfo( &m_os, &m_cpu, m_ram, &m_cFile, &m_app, &m_ver );
	}
}
void CStatisticsJob::countJobAll(CLogRecord* pRecord)
{
	((CLogAnalyze*)pRecord)->GetJobAll(
		&m_strPlaten,
		&m_csArpTime, &m_csMachine, &m_csTranscolor, 
		&m_cSatu, &m_cBrig, &m_cCont, &m_cInkVolume, 
		&m_cUniDir, &m_cBlack, &m_cMask, &m_cHighlight, &m_cMinWhite 
	);
}
void CStatisticsJob::countJobAllSp(CLogRecord* pRecord)
{
	((CLogAnalyze*)pRecord)->GetJobAllSp(
		&m_strPlaten,
		&m_csArpTime, &m_csMachine, &m_csTranscolor, 
		&m_cSatu, &m_cBrig, &m_cCont, &m_cInkVolume, 
		&m_cUniDir, &m_cBlack, &m_cMask, &m_cHighlight, &m_cMinWhite 
	);
}


/**
 * 日付を設定する.
 * @param date 日付
 */
void CStatisticsJob::setDate(const CLogDate& date)
{
	m_date = date;
}

const CLogDate& CStatisticsJob::getDate() const
{
	return m_date;
}

void CStatisticsJob::setNumber(int nNumber)
{
	m_nNumber = nNumber;
}
int CStatisticsJob::getNumber()
{
	return m_nNumber;
}

void CStatisticsJob::SetJobName( CString strJobName )
{
	m_name = strJobName;
}

void CStatisticsJob::SetJobComment( CString strJobComment )
{
	m_comment = strJobComment;
}

/**
 * 文字列に変換する.
 * @param dateFormat 日付のフォーマット
 * @param timeFormat ジョブ時間のフォーマット
 * @param machine マシン名
 * @return 変換した文字列
 */
CString CStatisticsJob::toString(int dateFormat, int timeFormat , int typeSeparate ) const
{
	CElapsedTime ave(0, 0, 0, 0);
	if(0 != m_cntPrintEnd)
	{
		ave = m_timePrint;
		ave /= m_cntPrintEnd;
	}

	CElapsedTime work;
	m_workTime.getWorkTime(work);

	CString format;
	CString string1, string2;

	format	=	"%s,\"%s\",%d,"						//日付, ジョブ名, 印刷枚数    - ジョブコメント
				"%s,%s,"							//印刷時間(平均),稼働時間
				"%d,%d,"							//パージ回数(各)
				"%s,%d,"							//ジョブ内最後の印刷までの時間, キャンセル回数
//				"%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,"	//ドット数(各,計)
				"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,"	//インク量(各,計)
				"%s,%s,%d,"							//機種モード,プラテンサイズ,解像度
				"%d,%d,%d,%d,%d,"					//ハイライト,マスク,黒インク,マルチパス,最低白インク量
				"%s,%d,%d,%d,%d,%d,"				//背景色,彩度,明るさ,コントラスト,インク量,2回印刷
				"%d,%s";							//片方向,作成日時
	if( typeSeparate == 1 )
		format.Replace(_T(","), _T(";") );

	string1.Format( format, 
		m_date.toString(dateFormat), m_name, m_cntPrintEnd, 
		ave.toString(), work.toString(),
		m_cntPurgeStart[0], m_cntPurgeStart[1],
		m_time.toString(timeFormat), m_cntPrintStart-m_cntPrintEnd,
//		m_cntDot[0], m_cntDot[1], m_cntDot[2], m_cntDot[3], m_cntDot[4], m_cntDot[5], m_cntDot[6], m_cntDot[7], 
//		m_cntDot[0]+m_cntDot[1]+m_cntDot[2]+m_cntDot[3], m_cntDot[4]+m_cntDot[5]+m_cntDot[6]+m_cntDot[7], 
		m_cntInkVolume[0], m_cntInkVolume[1], m_cntInkVolume[2], m_cntInkVolume[3], 
		m_cntInkVolume[4], m_cntInkVolume[5], m_cntInkVolume[6], m_cntInkVolume[7], 
		m_cntInkVolume[0]+m_cntInkVolume[1]+m_cntInkVolume[2]+m_cntInkVolume[3], 
		m_cntInkVolume[4]+m_cntInkVolume[5]+m_cntInkVolume[6]+m_cntInkVolume[7], 
		m_csMachine, m_strPlaten, m_iResolution, 
		m_cHighlight, m_cMask, m_cBlack, m_cMultipass, m_cMinWhite, 
		m_csTranscolor, m_cSatu, m_cBrig, m_cCont, m_cInkVolume, m_cEnhance, 
		m_cUniDir, m_csArpTime
		);

	if( m_cFile == -1 ) {
		format	=	",,,,,,";
		if( typeSeparate == 1 )
			format.Replace(_T(","), _T(";") );
		string2 = format;
	}
	else {
		format	=	",%s,%s,%d/%d,%d,%s,%d.%d.%d.%d";
		if( typeSeparate == 1 )
			format.Replace(_T(","), _T(";") );
		string2.Format( format,
			m_os, m_cpu, m_ram[0],m_ram[1], m_cFile, m_app, BYTE(m_ver>>24),BYTE(m_ver>>16),BYTE(m_ver>>8),BYTE(m_ver)
		);
	}


	return string1 + string2;
}

/**
 * タイトルを取得する.
 * @return タイトルの文字列
*/
void CStatisticsJobList::title(CArchive& ar, int separate)
{
		CString strHeader = 
			"clock,name,print,"
			"printtime(ave),worktime,"
			"purgeC,purgeW,"
			"total time,cancel,"
//			"dotK,dotM,dotC,dotY,dotW1,dotW2,dotW3,dotW4,dotCMYK,dotW,"
			"inkK,inkY,inkC,inkM,inkW1,inkW2,inkW3,inkW4,inkCMYK,inkW,"
			"machinemode,platen,resolution,"
			"highlight,mask,blackink,multipass,minwhite,"
			"transcolor,saturation,brightness,contrast,inkvolume,double,"
			"1way,ArpDate,"
			"OS,CPU,memory,file,application,version"
			"\r\n";

	if( separate == 1 )
		strHeader.Replace(_T(","), _T(";") );

	ar.WriteString(strHeader);
}

CLogDate CStatisticsJobList::m_dateActivated(2004, 1, 1);
/**
 * CStatisticsJobList.
 */
CStatisticsJobList::CStatisticsJobList()
{
	m_dateFormat	= CLogDate::DATE_FORMAT_ENGLISH;
	m_separateType	= 0;
	m_machine		= "";
}

/**
 * ~CStatisticsJobList.
 */
CStatisticsJobList::~CStatisticsJobList()
{

}

/**
 * 日付のフォーマットを設定する.
 * @param format フォーマット
 */
void CStatisticsJobList::setDateFormat(int format)
{
	m_dateFormat	= format;
}

/**
 * ジョブ時間のフォーマットを設定する.
 * @param format フォーマット
 */
void CStatisticsJobList::setTimeFormat(int format)
{
	m_timeFormat	= format;
}

/**
 * 区切り文字を設定する.
 * @param type 
 */
void CStatisticsJobList::setSeparateType(int separate)
{
	m_separateType	= separate;
}

/**
 * マシン名を設定する.
 * @param machine 
 */
void CStatisticsJobList::setMachineName(const CString& machine)
{
	m_machine		= machine;
}

/*
 * 統計情報を作成する.
 * @param date1 開始日時（含む）
 * @param date2 終了日時（含まない）
 * @param records ログ
 */
void CStatisticsJobList::create(const CLogList& records,
	const CLogDate& date1, const CLogDate& date2)
{
	CStatisticsJob* pStatJob = NULL;

	POSITION pos = records.GetHeadPosition();

	if(date1 != date2)
	{
		while(NULL != pos)
		{
			CLogRecord* pRecord = records.GetNext(pos);
			if(pRecord->getDate() < date1 || date2 <= pRecord->getDate())
				continue;

			pStatJob = countStatistics(pStatJob, pRecord);
		}
	}
	else
	{
		while(NULL != pos)
		{
			CLogRecord* pRecord = records.GetNext(pos);
			pStatJob = countStatistics(pStatJob, pRecord);
		}
	}
}

/**
 * ログを数える.
 * @param pStatDay 統計情報
 * @param pRecord ログ
 * @return 統計情報
 */

CStatisticsJob* CStatisticsJobList::countStatistics(CStatisticsJob* pStatJob, CLogRecord* pRecord)
{
	//パワーオン
	if( pRecord->isMatched(CODE_POWERON) )
	{
		pStatJob = NULL;
	}
	//受信履歴から印刷データを選択
	else if(pRecord->isMatched(CODE_HISTORY))
	{
		int	nNumber	= ((CLogAnalyze*)pRecord)->GetLogNumber();
		pStatJob = Lookup( nNumber );
	}
	//データ受信、印刷開始 : 受信中印刷
	else if( pRecord->isMatched(CODE_JOBALL) || pRecord->isMatched(CODE_JOBALL_SP) || pRecord->isMatched(CODE_PRINTSTART) )
	{
		int	nNumber	= ((CLogAnalyze*)pRecord)->GetLogNumber();
		if( nNumber != 0 )	//テストデータ以外
		{
			//StatJobの更新
			if( pStatJob == NULL || pStatJob->getNumber() != nNumber )
			{
				pStatJob = new CStatisticsJob;
				pStatJob->setDate( pRecord->getDate() );
				pStatJob->setNumber( nNumber );
				AddTail( pStatJob );
			}

			//個別処理
			if( pRecord->isMatched(CODE_JOBALL) ) {
				pStatJob->countJobAll( pRecord );
			}
			else if( pRecord->isMatched(CODE_JOBALL_SP) ) {
				pStatJob->countJobAllSp( pRecord );
			}
			else if( pRecord->isMatched(CODE_PRINTSTART) ) {
				pStatJob->count( pRecord );
			}
		}
	}
	//印刷終了/停止 : 印刷中受信
	else if( pRecord->isMatched(CODE_PRINTEND) || pRecord->isMatched(CODE_PRINTSTOP)
		|| pRecord->isMatched(CODE_PRINTEND_SP) || pRecord->isMatched(CODE_PRINTSTOP_SP) )
	{
		int nNumber = ((CLogAnalyze*)pRecord)->GetLogNumber();
		if( nNumber != 0 )	//テストデータ以外
		{
			if( pStatJob && pStatJob->getNumber() == nNumber )
				pStatJob->count( pRecord );
			else {
				CStatisticsJob* pStatJob2 = Lookup( nNumber );

				if( pStatJob2 ) {
					pStatJob2->count( pRecord );
				}
			}
		}
	}
	//その他
	else
	{
		if( pStatJob ) {
			pStatJob->count( pRecord );
		}
	}

	return	pStatJob;
}

CStatisticsJob* CStatisticsJobList::Lookup( int nNumber )
{
	if( nNumber == 0 )	//テスト印刷
		return	NULL;

	POSITION pos = GetTailPosition();
	while( NULL != pos )
	{
		CStatisticsJob* pStatJob = GetPrev(pos);

		if( pStatJob->getNumber() == nNumber ) {
			return	pStatJob;
		}
	}

	return	NULL;
}

/**
 * 保存する.
 * @param ar 
 */
void CStatisticsJobList::store(CArchive& ar)
{
	CLogDate AfterMonthDate;

	CTime ct = CTime::GetCurrentTime();
	AfterMonthDate.setDate( ct.GetYear() , ct.GetMonth() , ct.GetDay() );
	AfterMonthDate.afterMonth();//今より一ヶ月後の日付　この日までのログしか読まない

	POSITION pos = GetHeadPosition();
	while(NULL != pos)
	{
		CStatisticsJob* pStatJob = GetNext(pos);
		if( pStatJob == NULL )
		{
			continue;
		}
		if( pStatJob->getCountPrintEnd() == 0 )
		{	//印刷したものだけ
			continue;
		}
		if( pStatJob->getDate() < m_dateActivated || pStatJob->getDate() > AfterMonthDate )
		{//2004.1.1 から　今より一ヵ月後までしか読まない
			continue;
		}

		CString string = pStatJob->toString(m_dateFormat, m_timeFormat, m_separateType);
		ar.WriteString(string);
		ar.WriteString(_T("\r\n"));
	}

#ifdef _DEBUG
	int job = 2;
	pos = GetHeadPosition();
	while(NULL != pos)
	{
		CStatisticsJob* pStatJob = GetNext(pos);

		CFile file;
		CString strPath;
		strPath.Format(_T("WorkTime\\WorkTime%d.csv"), job++);
		if(file.Open(strPath, CFile::modeCreate|CFile::modeWrite))
		{
			CArchive arWorkTime(&file, CArchive::store);
			pStatJob->storeWorkTime(arWorkTime);
			arWorkTime.Close();
			file.Close();
		}
	}
#endif
}

