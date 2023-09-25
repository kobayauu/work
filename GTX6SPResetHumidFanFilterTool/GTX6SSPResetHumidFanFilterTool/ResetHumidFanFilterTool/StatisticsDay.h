/**
 * StatisticsDay.h
 */

#ifndef _StatisticsDay_H
#define _StatisticsDay_H

#include "LogDate.h"
#include "LogList.h"

/**
 * 日ごとの統計情報
 */
class CStatisticsDay
{
public:
	CStatisticsDay();
	virtual ~CStatisticsDay();

	unsigned long getCountPrintStart() const;
	unsigned long getCountPrintEnd() const;
	unsigned long getCountJobStart() const;
	unsigned long getCountPowerOn() const;
	// unsigned long getCountMainteWiperC() const;
	// unsigned long getCountMainteWiperW() const;
	// unsigned long getCountMainteFlushC() const;
	// unsigned long getCountMaintePlushW() const;
	unsigned long getMenuTestPrint() const;
//	void getCountDot(unsigned long dot[]) const;
	unsigned long getCountAutoPurgeStart() const;
	void getCountPurgeStart(unsigned long purge[]) const;

	bool isSameDay(CLogRecord* pRecord);
	void count(CLogRecord* pRecord, BOOL* pbOverNight);
	const CLogDate& getDate() const;
	void setDate(const CLogDate& date);

	CString toString( int dateFormat=CLogDate::DATE_FORMAT_ENGLISH , int typeSeparate=0 ) const;

protected:
	CLogDate m_date;
	unsigned long m_cntPrintStart;
	unsigned long m_cntPrintEnd;
	double m_cntInkVolume[10];
//	unsigned long m_cntDot[8];
	unsigned long m_cntJobStart;
	unsigned long m_cntAutoPurgeStart;
	unsigned long m_cntPurgeStart[3];
	unsigned long m_cntPowerOn;
	// unsigned long m_cntWiperC;
	// unsigned long m_cntWiperW;
	// unsigned long m_cntFlushC;
	// unsigned long m_cntFlushW;
	unsigned long m_cntMenuTestPrint;
//	unsigned long m_cntInkEmpty[8];
	int m_iMenuTestPrintFlag;
	int m_iResolution;
};


/**
 * 日ごとの統計情報のリスト
 */
class CStatisticsDayList : public CTypedPtrList<CPtrList, CStatisticsDay*>
{
public:
	CStatisticsDayList();
	virtual ~CStatisticsDayList();

	void setDateFormat(int format);
	void setSeparateType(int separate);
	void setMachineName(const CString& machine);
	void create(const CLogList& records, const CLogDate& date1,const CLogDate& date2);
	void store(CArchive& ar);
	void title(CArchive& ar, int separate);

protected:
	static CLogDate m_dateActivated;

	int m_dateFormat;
	int m_separateType;
	CString m_machine;

	CStatisticsDay* countStatistics(CStatisticsDay* pStatDay, CLogRecord* pRecord);
};

#endif
