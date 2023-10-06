/**
 * LogDate.h
 */

#ifndef _LogDate_H
#define _LogDate_H

/**
 * “ú•t
 */
class CLogDate
{
public:
	CLogDate();
	CLogDate(unsigned long year, unsigned long month,
			unsigned long day, unsigned long hour=0, unsigned long min=0,
			unsigned long sec=0, unsigned long msec=0);
	virtual ~CLogDate();

	void operator=(const CLogDate& date);
	int setDate(unsigned long year, unsigned long month,
			unsigned long day, unsigned long hour=0, unsigned long min=0,
			unsigned long sec=0, unsigned long msec=0);
	void getDate(unsigned long& year, unsigned long& month,
			unsigned long& day, unsigned long& hour, unsigned long& min,
			unsigned long& sec, unsigned long& msec) const;

	enum {
		DATE_FORMAT_DISPLAY,
		DATE_FORMAT_ENGLISH_DETAIL,
		DATE_FORMAT_ENGLISH,
		DATE_FORMAT_JAPANESE_DETAIL,
		DATE_FORMAT_JAPANESE
	};
	CString toString(int format=DATE_FORMAT_DISPLAY) const;
	unsigned long dayOfYear() const;

	void afterMinute();
	void afterHour();
	void afterDay();
	void afterMonth();
	void afterYear();

	bool isSameDay(const CLogDate& date) const;

	friend int operator==(const CLogDate& date1, const CLogDate& date2);
	friend int operator!=(const CLogDate& date1, const CLogDate& date2);
	friend int operator<(const CLogDate& date1, const CLogDate& date2);
	friend int operator<=(const CLogDate& date1, const CLogDate& date2);
	friend int operator>(const CLogDate& date1, const CLogDate& date2);
	friend int operator>=(const CLogDate& date1, const CLogDate& date2);

protected:
   unsigned long m_year;
   unsigned long  m_month;
   unsigned long  m_day;
   unsigned long  m_hour;
   unsigned long  m_min;
   unsigned long  m_sec;
   unsigned long  m_msec;

};

/**
 * Œo‰ßŽžŠÔ
 */
class CElapsedTime
{
public:
	CElapsedTime();
	CElapsedTime(unsigned long hour, unsigned long min,
						   unsigned long sec, unsigned long msec);
	virtual ~CElapsedTime();

	void resetToZero();
	void setSecond(unsigned long sec);
	void compute(const CLogDate& begin, const CLogDate& end);
	void operator +=(const CElapsedTime& time);
	void operator/=(int div);

	void getTime(unsigned long& hour, unsigned long& min,
			unsigned long& sec, unsigned long& msec) const;
	CString toString(int format=TIME_FORMAT_HHMMSS) const;

	enum {
		TIME_FORMAT_HHMMSSMS,
		TIME_FORMAT_HHMMSS,
		TIME_FORMAT_MINUTE
	};

protected:
	unsigned long  m_hour;
	unsigned long  m_min;
	unsigned long  m_sec;
	unsigned long  m_msec;
};

#endif
