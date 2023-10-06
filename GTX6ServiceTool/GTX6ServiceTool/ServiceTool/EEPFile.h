// EEPFile.h: CEEPFile クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EEPFILE_H__2E0D38E0_CE97_43BA_A8C4_17BC41EB7D0D__INCLUDED_)
#define AFX_EEPFILE_H__2E0D38E0_CE97_43BA_A8C4_17BC41EB7D0D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "MemEntry.h"
#include "GTLogFile.h"

class CEEPFile : public CObject
{
public:
	bool Open( LPBYTE pData, long nSize );
	bool SaveAsTemplate( CGTLogFile& LogF );
	bool Open( int nResourceID );
	bool IsChanged();
	bool IsNeedRead();
	void SetChanged( bool bChanged = true );
	void SetFlagNeedRead( bool bNeedRead=true );
	CString m_csFileName;
	bool SaveAsTemplate( LPCTSTR pszFileName );
	int GetTopOffset();
	DWORD GetTotalSize();
	bool GetHeaderInfo( DWORD* piType, DWORD *pdwVersion, CString& csVersion, CString& csComment );
	unsigned int GetCount();
	CMemEntry* GetMemEntry( unsigned int nPos );
	void Close();
	bool Open( LPCTSTR pszFileName );
	BOOL Open_Bynari( int nResourceID , BYTE* pJustData, long nJustDataSize );
	CEEPFile();
	virtual ~CEEPFile();

protected:
	DWORD m_nResPos;
	int GetOneChar();
	DWORD m_nResSize;
	LPBYTE m_pResTop;
	bool m_bChanged;
	bool m_bNeedRead;
	bool m_bReaded;
	bool SetReadData( long nReadSize, BYTE* pData );
	DWORD m_dwBlockID;
	bool SaveAsOneLine( CMemFile& MemF, CMemEntry* pEntry );
	int m_nTopOffset;
	DWORD m_nTotalSize;
	UINT m_nValidEntryCount;
	CArray<CMemEntry,CMemEntry&> m_MemArray;
	bool ParseOneLine( CString& csLine, CMemEntry& mEntry );
	bool ReadOneLine( CString& csLine );
	bool LoadData();
	FILE* m_pf;
};

#endif // !defined(AFX_EEPFILE_H__2E0D38E0_CE97_43BA_A8C4_17BC41EB7D0D__INCLUDED_)
