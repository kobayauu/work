/**
 * WorkTime.h
 */

#ifndef _WorkTime_H
#define _WorkTime_H

#include <Afxtempl.h>
#include "LogDate.h"

/**
 * ��Ǝ��� 10�Ԋu�ŋ�؂������̍ŕp�͈͂𓾂�
 */
class CWorkTime : public CList<CElapsedTime, CElapsedTime&>
{
public:
	CWorkTime();
	virtual ~CWorkTime();

	void getWorkTime(CElapsedTime& time) const;
	void store(CArchive& ar);
	void load(CArchive& ar);

protected:
	bool getModeFrequency(CElapsedTime& time) const;
	void createFrequency(int freq[]) const;
	void getAverage(CElapsedTime& time,
			unsigned long sec1=0, unsigned long sec2=0) const;
	void getModeDensity(CElapsedTime& time) const;
	void createDensity(int density[]) const;
};

#endif
