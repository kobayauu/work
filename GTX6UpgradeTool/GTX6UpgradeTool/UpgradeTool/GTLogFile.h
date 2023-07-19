// GTLogFile.h: CGTLogFile クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GTLOGFILE_H__9982F737_5CB4_4508_9E4A_C37D62A6E834__INCLUDED_)
#define AFX_GTLOGFILE_H__9982F737_5CB4_4508_9E4A_C37D62A6E834__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "GTLogEntry.h"
#include "GTLogFile.h"
#include "FirmLogCode.h"	// ClassView によって追加されました。

class CGTLogFile  
{
public:
	long GetLogEntryCount();
	bool ReadTagString( LPCTSTR pszTag, CString& cStr );
	bool WriteTagData( long lSize, void* pData );
	bool WriteFlush();
	bool WriteOneByte( BYTE b );
	bool UpdateTagSize( LPCTSTR pszTagName, long lSize );
	bool OpenLogDirectDebug( LPCTSTR pszFileName );
	int ReadLogEntry( CGTLogEntry& cEntry );
	bool LogSeekTop();
	bool OpenLog( long *plEntryCount=NULL );
	bool Create( LPCTSTR pszFileName );
	bool ReadTagData( LPCTSTR pszTagName, long nAreaSize, void* pData, long* pnReaded );
	bool ReadData( long nSize, void* pData);
	int Open( LPCTSTR pszFileName, CString& csPCDate );
	bool WriteEndTag();
	bool ReadTagHeaderAndSeek( LPCTSTR pszTagName, long* plSize );
	int Open( LPCTSTR pszFileName );
	bool WriteTagData( LPCTSTR pszTagName, long lSize, void* pData );
	bool Close();
	bool WriteTagHeader( LPCTSTR pszTagName, long lSize );
	bool MakeHeader( long lPrinterTime );
	bool CreateFile( LPCTSTR pszFileName );
	CGTLogFile();
	virtual ~CGTLogFile();

protected:
	DWORD GetNormalDateValMax();
	long m_lLogEntryCount;
	bool WriteData( long lSize, void* pData );
	long m_lLogReadBuffTopOffset;
	long m_lBuffCount;
	long m_lBuffSize;
	BOOL m_bZlg;
	BYTE* m_pBuff;
	DWORD m_lLogReadedDWSize;
	DWORD m_lLogLastPos;
	bool ReadLogExtData( int nDataSize, BYTE** ppData );
	bool m_bLogOpened;
	DWORD m_lLogStartPos;
	DWORD m_lLogDWSize;
	DWORD m_lLogCurPos;
	bool FillLogBuff();
	DWORD m_lLogSize;
	DWORD m_lLogReadDWOffset;
	DWORD m_lLogReadDWSize;
	int ReadLogDWORD( DWORD* pdwData );
	bool SearchNewestLogPos( long *plEntryCount );
	BYTE* m_pLogBuff;
	DWORD m_lLogTopPos;
	bool m_bReadMode;
	long m_nTagDataSize;
	FILE* m_pFile;
	CString m_csFileName;

	int UnCompZlgFile();
	int UnCompZlib( CString strMoto , CString strUnZlib );
};

#endif // !defined(AFX_GTLOGFILE_H__9982F737_5CB4_4508_9E4A_C37D62A6E834__INCLUDED_)
