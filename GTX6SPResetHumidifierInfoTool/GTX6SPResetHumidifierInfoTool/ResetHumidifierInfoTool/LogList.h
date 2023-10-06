/**
 * LogList.h
 */

#ifndef _LogList_H
#define _LogList_H

#include <afxtempl.h>
#include "LogRecord.h"

/**
 * ログレコードのリスト
 */
class CLogList : public CTypedPtrList<CPtrList, CLogRecord*>
{
public:
	CLogList();
	virtual ~CLogList();

	void load(CArchive& ar);
	int load( CString strFilePath );
	void store(CArchive& ar);

	CLogRecord* getNextSelected(CLogRecord* pRecord);
	CLogRecord* getPrevSelected(CLogRecord* pRecord);

protected:
	unsigned long seekEdge(CArchive& ar);
	unsigned long seekEdge(CArchive& ar, char buf[], unsigned long bufsize);
	bool isRecord(const CString& string);

	unsigned long seekEdge(FILE* fp , char buf[], unsigned long bufsize);
	unsigned long seekEdge( FILE* fp );
};

#endif
