// GTLogEntry.h: CGTLogEntry クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GTLOGENTRY_H__4C24DF90_BBF3_43F7_BFD8_2984982DE33B__INCLUDED_)
#define AFX_GTLOGENTRY_H__4C24DF90_BBF3_43F7_BFD8_2984982DE33B__INCLUDED_

#include "FirmLogCode.h"	// ClassView によって追加されました。
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGTLogEntry  
{
private:
	bool ConvUtf8toSJis( BYTE* pSource, BYTE* pDist, int* pSize );
public:
	bool MakeLogLineExtParam( CString& csLine );
	bool MakeLogLineExtDat( CString& csLine );
	bool MakeLogLine2( CString& csLine);
	bool MakeLogLine1( CString &csLine, int iNumber );
	bool MakeLogLine1Csv( CString &csLine, int iNumber );
	bool ChangeTimeToStrCsv(CString& csDate, CString& csTime);
	bool ChangeCodeToStr( CString & cs );
	bool ChangeTypeToStr( CString& csType );
	bool ChangeTimeToStr(CString& csTime, LPCTSTR pszFormat=NULL);
	bool SetExtData( BYTE* pData );
	BYTE* m_pData;
	int m_nCode;
	int m_nLevel;
	int m_nType;
	int m_nDataSize;
	int m_nMillisec;
	DWORD m_dwTime;
	CGTLogEntry();
	virtual ~CGTLogEntry();
protected:
	CFirmLogCode m_cLogCode;
};

#endif // !defined(AFX_GTLOGENTRY_H__4C24DF90_BBF3_43F7_BFD8_2984982DE33B__INCLUDED_)
