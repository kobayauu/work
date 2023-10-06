/**
 * WorkTime.cpp
 */

#include "stdafx.h"
#include "WorkTime.h"

/**
 * CWorkTime.
 */
CWorkTime::CWorkTime()
{
}

/**
 * ~CWorkTime.
 */
CWorkTime::~CWorkTime()
{

}

/**
 * 作業j時間を得る.
 * @param time [out]　作業時間
 */
void CWorkTime::getWorkTime(CElapsedTime& time) const
{
	time.resetToZero();
	//if(!getModeFrequency(time))
		getModeDensity(time);
}

/**
 * 度数分布から最頻値を得る.
 * @param time [out] 最頻値
 * @return true:成功 , false:最大度数が１つでない 
 */
bool CWorkTime::getModeFrequency(CElapsedTime& time) const
{
	time.resetToZero();

	int freq[360];
	createFrequency(freq);

	// find max
	int index = -1;
	int maxFreq = -1;
	int i;
	for(i = 0; i < 360; i++)
	{
		if(maxFreq < freq[i])
		{
			maxFreq = freq[i];
			index = i;
		}
	}
	if(index < 0)
		return false;

	for(i = 0; i < 360; i++)
	{
		if(maxFreq == freq[i] && i != index)
		{
			return false;	// 最大度数が１つでない
		}
	}

	getAverage(time, index*10, (index+1)*10);
	return true;
}

/**
 * 度数分布を求める.
 * @param freq[] [out] 度数
 */
void CWorkTime::createFrequency(int freq[]) const
{
	for(int i = 0; i < 360; i++)//360*10 s =1hour まで対応
		freq[i] = 0;

	POSITION pos = GetHeadPosition();
	while(NULL != pos)
	{
		CElapsedTime& time = (CElapsedTime)GetNext(pos);

		unsigned long hour, min, sec, msec;
		time.getTime(hour, min, sec, msec);
		if(hour > 0)
			continue;

		min += (hour * 60);
		sec += (min * 60);
		freq[sec/10]++;//１０秒間隔
	}
}

/**
 * sec1以上sec2未満の平均時間を得る.
 * @param time [out] 平均時間
 * @param sec1 
 * @param sec2 
 */
void CWorkTime::getAverage(CElapsedTime& time,
							unsigned long sec1, unsigned long sec2) const
{
	int cnt = 0;
	double total = 0;

	if(sec1 == sec2)
	{
		POSITION pos = GetHeadPosition();
		while(NULL != pos)
		{
			CElapsedTime& time = (CElapsedTime)GetNext(pos);

			unsigned long hour, min, sec, msec;
			time.getTime(hour, min, sec, msec);
			if(hour > 0)
				continue;

			min += (hour * 60);
			sec += (min * 60);
			total += sec;
			cnt++;
		}
	}
	else
	{
		POSITION pos = GetHeadPosition();
		while(NULL != pos)
		{
			CElapsedTime& time = (CElapsedTime)GetNext(pos);

			unsigned long hour, min, sec, msec;
			time.getTime(hour, min, sec, msec);
			if(hour > 0)
				continue;

			min += (hour * 60);
			sec += (min * 60);
			if(sec1 <= sec && sec < sec2)
			{
				total += sec;
				cnt++;
			}
		}
	}
	int ave = (int)(total / cnt);
	time.setSecond(ave);
}

/**
 * 度数密度から最頻値を得る.
 * @param time [out] 最頻値
 */
void CWorkTime::getModeDensity(CElapsedTime& time) const
{
	int density[360];
	createDensity(density);

	int maxDens = -1;
	int index[360];
	int cnt = 0;
	for(int i = 0; i < 360; i++)
	{
		if(maxDens < density[i])
		{
			cnt = 0;
			maxDens = density[i];
			index[cnt++] = i;
		}
		else if(maxDens == density[i])
		{
			index[cnt++] = i;
		}
	}

	int widthMax = 0;
	for(int j = 0; j < cnt; j++)
	{
		int imin = index[j];
		while(imin > 0 && density[imin] > 0)
			imin--;

		int imax = index[j];
		while(imax < 360 && density[imax] > 0)
			imax++;

		int width = imax - imin;
		if(width > widthMax)
		{
			widthMax = width;
			getAverage(time, imin*10, imax*10);
		}
	}
}

/**
 * 度数密度(度数/分)を得る.
 * @param density[] 
 */
void CWorkTime::createDensity(int density[]) const
{
	for(int i = 0; i < 360; i++)
		density[i] = 0;

	POSITION pos = GetHeadPosition();
	while(NULL != pos)
	{
		CElapsedTime& time = (CElapsedTime)GetNext(pos);

		unsigned long hour, min, sec, msec;
		time.getTime(hour, min, sec, msec);
		if(hour > 0)
			continue;

		min += (hour * 60);
		sec += (min * 60);
		int index = sec/10;

		int j = index - 3;
		if(j < 0)
			j = 0;
		int k = index + 3;
		if(k > 360)
			k = 360;
		
		while(j < k)
		{
			density[j]++;
			j++;
		}
	}
}

/**
 * 保存する.
 * @param ar 
 */
void CWorkTime::store(CArchive& ar)
{
	POSITION pos = GetHeadPosition();
	while(NULL != pos)
	{
		CElapsedTime& time = GetNext(pos);

		unsigned long hour, min, sec, msec;
		time.getTime(hour, min, sec, msec);
		min += (hour * 60);
		sec += (min * 60);

		CString string;
		string.Format(_T("%d\n"), sec);
		ar.WriteString(string);
	}
}

/**
 * 読み込む.
 * @param ar 
 */
void CWorkTime::load(CArchive& ar)
{
	RemoveAll();
	CString string;
	while(ar.ReadString(string))
	{
		CElapsedTime time;
		time.setSecond(_ttoi(string));
		AddTail(time);
	}
}