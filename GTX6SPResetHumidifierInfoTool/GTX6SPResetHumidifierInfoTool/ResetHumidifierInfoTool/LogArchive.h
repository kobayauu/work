/**
 * LogArchive.h
 */

#ifndef _LogArchive_H
#define _LogArchive_H

#include <Afxtempl.h>

class CLogArchive
{
public:
	CLogArchive(CArchive& ar);
	virtual ~CLogArchive();

	void Close();
	CFile* GetFile( ) const;
	BOOL ReadString(CString& rString);
	LPTSTR ReadString(LPTSTR lpsz, UINT nMax);

	void readFile();
	void readBackup();
	void clearBackup();
	UINT Read(void* lpBuf, UINT nMax);

protected:
	bool m_readFile;
	CArchive& m_ar;
	CList<BYTE, BYTE&> m_backup;
	POSITION m_pos;
};

#endif
