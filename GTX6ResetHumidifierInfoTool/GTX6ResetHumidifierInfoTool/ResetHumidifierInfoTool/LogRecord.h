/**
 * LogRecord.h
 */

#ifndef _LogRecord_H
#define _LogRecord_H

#include <afxtempl.h>
#include "LogDate.h"
#include "LogArchive.h"

/**
 * ÉçÉO
 */
class CLogRecord  
{
public:
	CLogRecord();
	virtual ~CLogRecord();

	bool isSelected() const;
	bool isMatched(unsigned long code) const;
	bool isMatched(unsigned long code, unsigned long logclass) const;
	void select();
	void deselect();

	int getCountAddition() const;
	CString getAddition(int index) const;
	void setAddition(const CString& sddition);

	unsigned long getID() const;
	void setID(unsigned long id);
	unsigned long getCode() const;
	unsigned long getLogclass() const;
	unsigned long getLevel() const;
	const CLogDate& getDate() const;

	CString GetFileName() const; 

	const CString& getCaption() const;
	void setCaption(const CString& caption);

	CString toString() const;
	void getRecord(unsigned long& id, unsigned long& code, CLogDate& date,
		unsigned long& logclass, unsigned long& level) const;
	bool setRecord(const CString& string);

	unsigned long load(CArchive& ar);
	bool setData(char *data, unsigned long dataSize);

	bool isSameRecord(const CLogRecord& record) const;

protected:
	bool loadEdge(CArchive& ar);
	bool loadRecord(CArchive& ar, unsigned long& addSize);
	bool loadAddition(CArchive& ar, unsigned long addSize);

	bool m_selected;
	unsigned long m_id;
	unsigned long m_code;
	CLogDate m_date;
	unsigned long m_logclass;
	unsigned long m_level;
	CString m_caption;
	CString m_addition;
	CString m_strFileName;
};

/**
 * ÉçÉOâêÕ
 */
class CLogAnalyze : public CLogRecord
{
public:
	CLogAnalyze();
	virtual ~CLogAnalyze();

	unsigned long GetLogNumber();
	CString getFilename();
	CString getString();

	void getCountDot(unsigned long dot[]);
	static double dotToCC(unsigned long dotL, unsigned long dotM, unsigned long dotS, unsigned long dpi, bool pale);

	BOOL GetGraphics( char* pColor, char* pWhite, int* pResolution, char* pMultipass, char *pEnhance );

	BOOL GetPrintMode( char* pUniDir, char* pEndless, char* pMulti );

	BOOL GetJobAll( CString* pPlaten, CString* pArpTime, CString* pMachine, CString* pTranscolor,
					char* pSatu, char* pBrig, char* pCont, char* pInkVolume,
					char* pUniDir, char* pBlack, char* pMask, char* pHighlight, char* cMinWhite );

	BOOL GetPurge( unsigned long* pType, unsigned long* pColor );

	BOOL GetPcInfo( CString* pOS, CString* pCpu, unsigned short* pRam,
					char* pFile, CString* pApp, unsigned long* pVer );
};

#endif
