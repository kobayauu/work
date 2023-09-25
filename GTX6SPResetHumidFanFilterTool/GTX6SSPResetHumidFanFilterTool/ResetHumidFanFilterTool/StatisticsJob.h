/**
 * StatisticsJob.h
 */

#ifndef _StatisticsJob_H
#define _StatisticsJob_H

#include "LogDate.h"
#include "LogList.h"
#include "WorkTime.h"

/**
 * Jobごとの統計情報
 */
class CStatisticsJob
{
public:
	CStatisticsJob();
	virtual ~CStatisticsJob();

	unsigned long getCountPrintStart() const;
	unsigned long getCountPrintEnd() const;
//	void getCountDot(unsigned long dot[]) const;
	void getCountPurgeStart(unsigned long purge[]) const;
	const CString& getName() const;
	const CString& getComment() const;
	void getTime(unsigned long& hour, unsigned long& min,
		unsigned long& sec, unsigned long& msec) const;
//	int getPlaten() const;

	void count(CLogRecord* pRecord);
	void countJobAll(CLogRecord* pRecord);
	void countJobAllSp(CLogRecord* pRecord);
	void setDate(const CLogDate& date);
	const CLogDate& getDate() const;
	void setNumber(int nNumber);
	int getNumber();


	void SetJobName( CString strJobName );
	void SetJobComment( CString strJobComment );

	CString toString(
		int dateFormat=CLogDate::DATE_FORMAT_ENGLISH_DETAIL,
		int timeFormat=CElapsedTime::TIME_FORMAT_HHMMSS,
		int typeSeparate=0 ) const;

#ifdef _DEBUG
	void storeWorkTime(CArchive& ar) {
		m_workTime.store(ar);
	}
#endif

protected:
	int m_nNumber;
	CLogDate m_date;
	unsigned long m_cntPrintStart;
	unsigned long m_cntPrintEnd;
	unsigned long m_cntPurgeStart[3];//C,W,SP
	double m_cntInkVolume[10];
//	unsigned long m_cntDot[10];
	CString m_name;
	CString m_comment;
	CString m_strPlaten;
	CElapsedTime m_time;
	CElapsedTime m_timePrint;
	CLogDate m_datePrintStart;
	CLogDate m_datePrintEnd;
	CWorkTime m_workTime;
	int m_iResolution;
	char m_cMultipass;
	CString m_csArpTime;
	CString m_csMachine;
	CString m_csTranscolor;
	char m_cSatu;
	char m_cBrig;
	char m_cCont;
	char m_cInkVolume;
	char m_cEnhance;
	char m_cUniDir;
	char m_cBlack;
	char m_cWGrad;
	char m_cMask;
	char m_cHighlight;
	char m_cMinWhite;
	CString m_os;
	CString m_cpu;
	unsigned short m_ram[2];
	char m_cFile;
	CString m_app;
	unsigned long m_ver;
};

/**
 * Jobごとの統計情報のリスト
 */
class CStatisticsJobList : public CTypedPtrList<CPtrList, CStatisticsJob*>
{
public:
	CStatisticsJobList();
	virtual ~CStatisticsJobList();

	void setDateFormat(int format);
	void setTimeFormat(int format);
	void setSeparateType(int separate);
	void setMachineName(const CString& machine);
	void create(const CLogList& records, const CLogDate& date1,const CLogDate& date2);
	void store(CArchive& ar);
	void title(CArchive& ar, int separate);

protected:
	static CLogDate m_dateActivated;
	int m_dateFormat;
	int m_timeFormat;
	int m_separateType;
	CString m_machine;

	CStatisticsJob* countStatistics(CStatisticsJob* pStatJob, CLogRecord* pRecord);
	CStatisticsJob* Lookup( int nNumber );
};

#endif
