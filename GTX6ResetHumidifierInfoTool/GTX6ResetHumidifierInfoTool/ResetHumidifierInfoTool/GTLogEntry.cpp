// GTLogEntry.cpp: CGTLogEntry クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "BGJPrinter.h"
#include "BGJServTool.h"
#include "GTLogEntry.h"
#include "LOGcode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CGTLogEntry::CGTLogEntry()
{
	m_pData = NULL;
	m_dwTime = 0;
	m_nCode = 0;
	m_nDataSize = 0;
	m_nLevel = 0;
	m_nMillisec = 0;
	m_nType = 0;
}

CGTLogEntry::~CGTLogEntry()
{
	if( m_pData ){
		delete [] m_pData;
		m_pData = NULL;
	}
}

bool CGTLogEntry::SetExtData(BYTE* pData)
{
	bool bRet = true;
	if( m_pData != NULL ){
		delete [] m_pData;
		m_pData = NULL;
	}
	m_pData = pData;
	return bRet;
}

//#pragma optimize ("",off)

bool CGTLogEntry::ChangeTimeToStr(CString &csTime, LPCTSTR pszFormat)
{
	bool bRet = true;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	DWORD dwTime = m_dwTime - pApp->GetTimeZoneDiff();
//	if( dwTime <= 0x37000000 ){
		CTime ct( 2000, 1, 1, 0, 0, 0, 0 );
		ct += CTimeSpan( dwTime );
		//long nSec = _timezone;
		//long nMinute = nSec / 60;
		//long nHour = nMinute / 60;
		//long nDays = nHour / 24;
		//nSec %= 60;
		//nMinute %= 60;
		//nHour %= 24;
		//CTimeSpan cTZ( nDays, nHour, nMinute, nSec );
		//ct += cTZ;
		if( pszFormat == NULL ){
			pszFormat = _T("%d/%m/%Y %H:%M:%S");
		}
		csTime = ct.Format( pszFormat );
/*	}else{
		csTime = _T("\?\?/\?\?/\?\?\?\? \?\?:\?\?:\?\?");
	}	*/
	return bRet;
}

bool CGTLogEntry::ChangeTypeToStr(CString &csType)
{
	if     ( m_nLevel == LVL_FATAL || m_nLevel == LVL_MIDDLE ) {
		csType += _T("ERR");
	}
	else if( m_nLevel == LVL_WARNING ) {
		csType += _T("WRN");
	}
	else if( m_nLevel == LVL_EVENT1 || m_nLevel == LVL_EVENT2 ) {
		csType += _T("INF");
	}
	else {
		csType.Format( _T("%03X"), m_nLevel );
	}
	return true;
}

/*
bool CGTLogEntry::GetLogMsg(CString& csMsg,int eType)
{
	bool bRet = true;
	Cstring csBody;
	if( m_cLogCode.GetLogCodeExplanation( csBody, m_nCode, m_nLevel, m_nType ) ){
		
	}
	return bRet;
}
*/

bool CGTLogEntry::ChangeCodeToStr(CString &cs)
{
	bool bRet = false;
	if( m_cLogCode.GetLogCodeExplanation( cs, m_nCode, m_nLevel, m_nType ) ){
		bRet = true;
	}
	return bRet;
}

bool CGTLogEntry::MakeLogLine1(CString &csLine, int iNumber)
{
	bool bRet = true;
	CString csDate;
	ChangeTimeToStr( csDate );
	CString csType;
	ChangeTypeToStr( csType );
	CString csMsg;
	bRet = m_cLogCode.GetLogCodeExplanation( csMsg, m_nCode, m_nLevel, m_nType );
	csLine.Format(_T("%06d: %s [%08X] (%s) \"%s\""), iNumber, (LPCTSTR)csDate, m_nCode, (LPCTSTR)csType, (LPCTSTR)csMsg );
	return bRet;
}

bool CGTLogEntry::MakeLogLine2(CString &csLine)
{
	bool bRet = true;
	CString csMsg;
	bRet = m_cLogCode.GetLogCodeExplanation( csMsg, m_nCode, m_nLevel, m_nType );
	csLine = _T("       "); // 8 blanks
	csLine += csMsg;
	return bRet;
}

bool CGTLogEntry::MakeLogLine1Csv(CString &csLine, int iNumber)		// mizutani
{
	bool bRet = true;
	CString csDate, csTime;
	ChangeTimeToStrCsv( csDate, csTime );
	CString csType;
	ChangeTypeToStr( csType );
	CString csMsg;
	bRet = m_cLogCode.GetLogCodeExplanation( csMsg, m_nCode, m_nLevel, m_nType );
	int nLogCode = m_nCode & 0x0000FFFF;
	csLine.Format(_T("%06d,%s,%s,%04X,%02d,%s"), iNumber, (LPCTSTR)csDate, (LPCTSTR)csTime, nLogCode, m_nType, (LPCTSTR)csMsg );

	int nOffset = 0;
	int nSize = m_nDataSize;
	BYTE* pData = &m_pData[0];
	CString csExtData;
	for( int iCount = 0; iCount < 12; ++iCount )
	{
		csLine += _T(",");
		if( nSize > 0 )
		{
			DWORD dwOneData = (pData[nOffset]     << 24) +
							  (pData[nOffset + 1] << 16) +
							  (pData[nOffset + 2] <<  8) +
							   pData[nOffset + 3];
			csExtData.Format(_T("%d"), dwOneData );
			csLine += csExtData;
			nSize -= 4;
			nOffset += 4;
		}
	}
		
	return bRet;
}

bool CGTLogEntry::ChangeTimeToStrCsv( CString &csDate, CString &csTime )	// mizutani
{
	bool bRet = true;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	DWORD dwTime = m_dwTime - pApp->GetTimeZoneDiff();
//	if( dwTime <= 0x37000000 ){
		CTime ct( 2000, 1, 1, 0, 0, 0, 0 );
		ct += CTimeSpan( dwTime );
		csDate = ct.Format( _T("%d/%m/%Y") );
		csTime = ct.Format( _T("%H:%M:%S") );
/*	}else{
		csDate = "\?\?/\?\?/\?\?\?\?";
		csTime = "\?\?:\?\?:\?\?";
	}	*/
	return bRet;
}

//#pragma optimize ("",off)

bool CGTLogEntry::MakeLogLineExtDat( CString& csLine )
{
	bool bRet = true;

	for (int i = 0; i < m_nDataSize; i+=4)
	{
		CString cs;
		cs.Format(_T(" %08X"), m_pData[i]<<24|m_pData[i+1]<<16|m_pData[i+2]<<8|m_pData[i+3] );
		csLine += cs;
	}

	return bRet;
}

bool CGTLogEntry::MakeLogLineExtParam( CString& csLine )
{
	CString cs;
	BYTE buf[MAX_PATH] = {0};
	int size;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();

	if( m_nDataSize )
	{
		switch( m_nCode )
		{
		case 0x90080000:	//ARP_LOADED_JOB_NAME
		case 0x90090000:	//ARP_LOADED_JOB_COMMENT
			ConvUtf8toSJis( m_pData+4, buf, &size );
			cs.Format(_T("\"%s\""), (CString)buf );
			break;

		case 0x12600000:	//MN_AR3_FILE_LOAD
		case 0x12620000:	//MN_FIRM_UPDATE_USB
		case 0x12610000:	//MN_LOG_SAVE_USB
		case 0x00004100:	//EFFS_FILE_OPEN
		case 0x00004103:	//EFFS_FILE_SEEK
		case 0x00004104:	//EFFS_FILE_READ
		case 0x00004105:	//EFFS_FILE_WRITE
		case 0x00004101:	//EFFS_FILE_CREATE
		case 0x00003408:	//EDT_JOB_BIG
		case 0x00003412:	//EDT_NO_JOB_START
			ConvUtf8toSJis( m_pData, buf, &size );
			cs.Format(_T("\"%s\""), (CString)buf );
			break;

		case 0x00001061:	//WRN_SUR_TEMP_HIGH
		case 0x00001060:	//WRN_SUR_TEMP_LOW
		case 0x00002051:	//ERR_SUR_TEMP_HIGH
		case 0x00002050:	//ERR_SUR_TEMP_LOW
			if( pApp->GetLCID() == MAKELCID( 0x0411 , SORT_DEFAULT ) )
				cs.Format(_T("[%.1f ℃]"), (m_pData[2]<<8|m_pData[3])/10.0 );
			else
				cs.Format(_T("[%d deg F]"), ((m_pData[2]<<8|m_pData[3])*18 + 50) / 100 + 32 );
			break;

		case 0x13400000:	//MN_SET_AUTO_CLN
		case 0x13410000:	//MN_SET_FLUSH_CYCLE
		case 0x13420000:	//MN_SET_FLUSH_DROPS
		case 0x13430000:	//MN_SET_REFRESH_W
			cs.Format(_T("[%d]"), m_pData[0]<<24|m_pData[1]<<16|m_pData[2]<<8|m_pData[3] );
			break;

        case 0x15300000:    //MNT_CLEAN_CAPWIPE
            cs = CTimeSpan( *((DWORD *)m_pData) ).Format(_T("[%D %H:%M:%S]") );
            break;
		}
	}
	csLine += cs;

	return true;
}

//文字コード変換	UTF-8 → S-JIS
bool CGTLogEntry::ConvUtf8toSJis( BYTE* pSource, BYTE* pDist, int* pSize )
{
	*pSize = 0;

	//UTF-8からUTF-16へ変換
	const int nSize = ::MultiByteToWideChar( CP_UTF8, 0, (LPCSTR)pSource, -1, NULL, 0 );

	BYTE* buffUtf16 = new BYTE[ nSize * 2 + 2 ];
	if( !buffUtf16 ) {
		return FALSE;
	}
	::MultiByteToWideChar( CP_UTF8, 0, (LPCSTR)pSource, -1, (LPWSTR)buffUtf16, nSize );

	//UTF-16からShift-JISへ変換
	const int nSizeSJis = ::WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)buffUtf16, -1, NULL, 0, NULL, NULL );
	if( !pDist ){
		*pSize = nSizeSJis;
		delete [] buffUtf16;
		return TRUE;
	}

	BYTE* buffSJis = new BYTE[ nSizeSJis * 2 ];
	if( !buffSJis ) {
		delete [] buffUtf16;
		return FALSE;
	}

	ZeroMemory( buffSJis, nSizeSJis * 2 );
	::WideCharToMultiByte( CP_ACP, 0, (LPCWSTR)buffUtf16, -1, (LPSTR)buffSJis, nSizeSJis, NULL, NULL );

	*pSize = lstrlenA( (char*)buffSJis );
	memcpy( pDist, buffSJis, *pSize );

	delete [] buffUtf16;
	delete [] buffSJis;

	return TRUE;
}
