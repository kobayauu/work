/**
 * LogString.h
 */

#ifndef _LogString_H
#define _LogString_H

class CLogString
{
public:
	CLogString();
	virtual ~CLogString();

	static CString tokenize(const CString& string, const CString& separator, int& pos);
	static CString tokenizeString(const CString& string, const CString& separator, int& start, int loop);
	static bool ConvUtf8toSJis( BYTE* pSource, BYTE* pDist, int* pSize );
	static bool stringToMonth(const CString& string, unsigned long& month);
	static bool stringToLogclass(const CString& string, unsigned long& logclass);
	static bool stringToDigit(const CString& string, unsigned long& digit);
	static CString logclassToString(unsigned long logclass);
};

#endif
