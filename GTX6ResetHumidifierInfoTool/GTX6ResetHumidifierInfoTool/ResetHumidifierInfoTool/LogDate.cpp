/**
 * LogDate.cpp
 */

#include "stdafx.h"
#include "LogDate.h"

static unsigned long daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

/**
 * CLogDate.
 */
CLogDate::CLogDate()
{
   m_year = 0;
   m_month = 0;
   m_day = 0;
   m_hour = 0;
   m_min = 0;
   m_sec = 0;
   m_msec = 0;
}

/**
 * CLogDate.
 * @param year
 * @param month
 * @param day
 * @param hour
 * @param min
 * @param sec
 * @param msec
 */
CLogDate::CLogDate(unsigned long year, unsigned long month,
		unsigned long day, unsigned long hour, unsigned long min,
		unsigned long sec, unsigned long msec)
{
   m_year = year;
   m_month = month;
   m_day = day;
   m_hour = hour;
   m_min = min;
   m_sec = sec;
   m_msec = msec;
}

/**
 * ~CLogDate.
 */
CLogDate::~CLogDate()
{

}

/**
 * 代入.
 * @param date 
 */
void CLogDate::operator=(const CLogDate& date)
{
	setDate(date.m_year, date.m_month, date.m_day,
		date.m_hour, date.m_min, date.m_sec, date.m_msec);
}

/**
 * 日付を設定する.
 * @param year
 * @param month
 * @param day
 * @param hour
 * @param min
 * @param sec
 * @param msec
 */
int CLogDate::setDate(unsigned long year, unsigned long month,
		unsigned long day, unsigned long hour, unsigned long min,
		unsigned long sec, unsigned long msec)
{
   m_year = year;
   m_month = month;
   m_day = day;
   m_hour = hour;
   m_min = min;
   m_sec = sec;
   m_msec = msec;
   return 0;
}

/**
 * 日付を取得する.
 * @param year
 * @param month
 * @param day
 * @param hour
 * @param min
 * @param sec
 * @param msec
 */
void CLogDate::getDate(unsigned long& year, unsigned long& month,
		unsigned long& day, unsigned long& hour, unsigned long& min,
		unsigned long& sec, unsigned long& msec) const
{
   year = m_year;
   month = m_month;
   day = m_day;
   hour = m_hour;
   min = m_min;
   sec = m_sec;
   msec = m_msec;
}

/**
 * 文字列に変換する.
 * @param version 0:January 27, 2004  09:24:51.097
 *                      1:MM/DD/YYYY  hh:mm:00
 *                      2:MM/DD/YYYY
 * @return 文字列
 */
CString CLogDate::toString(int format) const
{
	const CString strMonth[] = {
		"January", "February", "March", "April", "May", "June",
		"July", "August", "September", "October", "November", "December"
	};

	CString string;
	switch(format)
	{
	case DATE_FORMAT_DISPLAY:
		string.Format(_T("%02d %s, %04d  %02d:%02d:%02d.%03d"),
			m_day, strMonth[m_month-1], m_year, m_hour, m_min, m_sec, m_msec);
		break;

	case DATE_FORMAT_ENGLISH_DETAIL:
		string.Format(_T("%d/%d/%d %d:%02d"), m_day, m_month, m_year, m_hour, m_min);
		break;

	case DATE_FORMAT_ENGLISH:
		string.Format(_T("%d/%d/%d"), m_day, m_month, m_year);
		break;

	case DATE_FORMAT_JAPANESE_DETAIL:
		string.Format(_T("%d/%d/%d %d:%02d"), m_year, m_month, m_day, m_hour, m_min);
		break;

	case DATE_FORMAT_JAPANESE:
		string.Format(_T("%d/%d/%d"), m_year, m_month, m_day);
		break;
	}
	return string;
}

/**
 * 1/1からの日数を求める(1/1は1).
 * @return 1/1からの日数
 */
unsigned long CLogDate::dayOfYear() const
{
	unsigned long day = m_day;
	int leep = ((0 == m_year%4 && 0 != m_year%100) || 0 == m_year%400);
	for(unsigned long month = 1; month < m_month; month++)
		day += daytab[leep][month];
	return day;
}

/**
 * 1分進める.
 */
void CLogDate::afterMinute()
{
	m_min += 1;
	if(60 == m_min)
	{
		m_min = 0;
		afterHour();
	}
}

/**
 * 1時間進める.
 */
void CLogDate::afterHour()
{
	m_hour += 1;
	if(24 == m_hour)
	{
		m_hour = 0;
		afterDay();
	}
}

/**
 * 1日進める.
 */
void CLogDate::afterDay()
{
	m_day += 1;
	int leep = ((0 == m_year%4 && 0 != m_year%100) || 0 == m_year%400);
	if(daytab[leep][m_month] < m_day)
	{
		m_day = 1;
		afterMonth();
	}
}

/**
 * 1月進める.
 */
void CLogDate::afterMonth()
{
	m_month += 1;
	if(13 == m_month)
	{
		m_month = 1;
		afterYear();
	}
}

/**
 * 1年進める.
 */
void CLogDate::afterYear()
{
	m_year += 1;
	if(2 == m_month)
	{
		int leep = ((0 == m_year%4 && 0 != m_year%100) || 0 == m_year%400);
		if(daytab[leep][m_month] < m_day)
		{
			m_month = 3;
			m_day = 1;
		}
	}
}

/**
 * 同じ日？.
 * @param date 比べる日付
 * @return true:Yes , false:No 
 */
bool CLogDate::isSameDay(const CLogDate& date) const
{
	if(m_year == date.m_year &&
	   m_month == date.m_month &&
	   m_day == date.m_day)
		return true;
	else
		return false;
}

/**
 * 等号.
 * @param date1 
 * @param date2 
 * @return 
 */
int operator==(const CLogDate& date1, const CLogDate& date2)
{
	if(date1.m_year == date2.m_year &&
	   date1.m_month == date2.m_month &&
	   date1.m_day == date2.m_day &&
	   date1.m_hour == date2.m_hour &&
	   date1.m_min == date2.m_min &&
	   date1.m_sec == date2.m_sec &&
	   date1.m_msec == date2.m_msec)
		return 1;
	else
		return 0;
}

/**
 * 非等号.
 * @param date1 
 * @param date2 
 * @return 
 */
int operator!=(const CLogDate& date1, const CLogDate& date2)
{
	return !(date1 == date2);
}

/**
 * 不等号.
 * @param date1 
 * @param date2 
 * @return 
 */
int operator<(const CLogDate& date1, const CLogDate& date2)
{
	if(date1.m_year < date2.m_year)
		return 1;
	else if(date1.m_year == date2.m_year)
	{
		if(date1.m_month < date2.m_month)
			return 1;
		else if(date1.m_month == date2.m_month)
		{
			if(date1.m_day < date2.m_day)
				return 1;
			else if(date1.m_day == date2.m_day)
			{
				if(date1.m_hour < date2.m_hour)
					return 1;
				else if(date1.m_hour == date2.m_hour)
				{
					if(date1.m_min < date2.m_min)
						return 1;
					else if(date1.m_min == date2.m_min)
					{
						if(date1.m_sec < date2.m_sec)
							return 1;
						else if(date1.m_sec == date2.m_sec)
						{
							if(date1.m_msec < date2.m_msec)
								return 1;
						}
					}
				}
			}
		}
	}
	return 0;
}

/**
 * 不等号.
 * @param date1 
 * @param date2 
 * @return 
 */
int operator>(const CLogDate& date1, const CLogDate& date2)
{
	return !(date1 <= date2);
}

/**
 * 不等号.
 * @param date1 
 * @param date2 
 * @return 
 */
int operator<=(const CLogDate& date1, const CLogDate& date2)
{
	return (date1 < date2) || (date1 == date2);
}

/**
 * 不等号.
 * @param date1 
 * @param date2 
 * @return 
 */
int operator>=(const CLogDate& date1, const CLogDate& date2)
{
	return (date1 > date2) || (date1 == date2);
}

/**
 * CElapsedTime Constructor.
 */
CElapsedTime::CElapsedTime()
{
   m_hour = 0;
   m_min = 0;
   m_sec = 0;
   m_msec = 0;
}

/**
 * CElapsedTime Constructor.
 */
CElapsedTime::CElapsedTime(unsigned long hour, unsigned long min,
						   unsigned long sec, unsigned long msec)
{
   m_hour = hour;
   m_min = min;
   m_sec = sec;
   m_msec = msec;
}

/**
 * CElapsedTime Destructor.
 */
CElapsedTime::~CElapsedTime()
{
}

/**
 * 経過時間を0にする.
 */
void CElapsedTime::resetToZero()
{
   m_hour = 0;
   m_min = 0;
   m_sec = 0;
   m_msec = 0;
}

/**
 * 経過秒数を設定する.
 * @param sec 秒数
 */
void CElapsedTime::setSecond(unsigned long sec)
{
	m_hour = 0;
	m_min = 0;
	m_sec = sec;
	m_msec = 0;

	while(m_sec >= 60)
	{
		m_min++;
		m_sec -= 60;
	}
	while(m_min >= 60)
	{
		m_hour++;
		m_min -= 60;
	}
}

/**
 * 経過時間を計算する.
 * @param begin 開始時間
 * @param end 終了時間
 */
void CElapsedTime::compute(const CLogDate& begin, const CLogDate& end)
{
	if(begin >= end)
	{
	   m_hour = 0;
	   m_min = 0;
	   m_sec = 0;
	   m_msec = 0;
	}
	else
	{
		unsigned long year1, year2;
		unsigned long month1, month2;
		unsigned long day1, day2;
		unsigned long hour1, hour2;
		unsigned long min1, min2;
		unsigned long sec1, sec2;
		unsigned long msec1, msec2;
		
		begin.getDate(year1, month1, day1, hour1, min1, sec1, msec1);
		end.getDate(year2, month2, day2, hour2, min2, sec2, msec2);

		// hour
		unsigned long day = 0;
		for(unsigned long year = year1; year < year2; year++)
		{
			CLogDate date(year, 12, 31);
			day += date.dayOfYear();
		}
		day += end.dayOfYear();
		day -= begin.dayOfYear();
		m_hour = day*24 + hour2 - hour1;

		// min
		if(min1 > min2)
		{
			m_hour -= 1;
			min2 += 60;
		}
		m_min = min2 - min1;

		// sec
		if(sec1 > sec2)
		{
			if(0 == m_min)
			{
				m_hour -= 1;
				m_min = 60;
			}
			m_min -= 1;
			sec2 += 60;
		}
		m_sec = sec2 - sec1;

		// msec
		if(msec1 > msec2)
		{
			if(0 == m_sec)
			{
				if(0 == m_min)
				{
					m_hour -= 1;
					m_min = 60;
				}
				m_min -= 1;
				m_sec = 60;
			}
			m_sec -= 1;
			msec2 += 1000;
		}
		m_msec = msec2 - msec1;
	}
}

/**
 * 加える
 * @param time 加える時間
 */
void CElapsedTime::operator +=(const CElapsedTime& time)
{
	m_msec += time.m_msec;
	m_sec += (m_msec / 1000);
	m_msec %= 1000;

	m_sec += time.m_sec;
	m_min += (m_sec / 60);
	m_sec %= 60;

	m_min += time.m_min;
	m_hour += (m_min / 60);
	m_min %= 60;

	m_hour += time.m_hour;
}

/**
 * 割る
 * @param div 割る数
 */
void CElapsedTime::operator/=(int div)
{
	m_min += (m_hour % div) * 60;
	m_hour /= div;

	m_sec += (m_min % div) * 60;
	m_min /= div;

	m_msec += (m_sec % div) * 1000;
	m_sec /= div;

	m_msec /= div;
}

/**
 * 時間を取得する.
 * @param hour 
 * @param min 
 * @param sec 
 * @param msec 
 */
void CElapsedTime::getTime(unsigned long& hour, unsigned long& min,
		unsigned long& sec, unsigned long& msec) const
{
   hour = m_hour;
   min = m_min;
   sec = m_sec;
   msec = m_msec;
}

/**
 * 文字列に変換する.
 * @param version 0:hhhh:mm:ss:ddd, 1:hhhh:mm:ss, 2:min
 * @return 変換した文字列
 */
CString CElapsedTime::toString(int format) const
{
	CString string;
	switch(format)
	{
	case TIME_FORMAT_HHMMSSMS:
		string.Format(_T("%4d:%02d:%02d:%03d"), m_hour, m_min, m_sec, m_msec);
		break;
	case TIME_FORMAT_HHMMSS:
		string.Format(_T("%d:%02d:%02d"), m_hour, m_min, m_sec);
		break;
	case TIME_FORMAT_MINUTE:
		string.Format(_T("%d"), m_hour*60+m_min+((m_sec > 0)?1:0));
		break;
	}
	return string;
}

