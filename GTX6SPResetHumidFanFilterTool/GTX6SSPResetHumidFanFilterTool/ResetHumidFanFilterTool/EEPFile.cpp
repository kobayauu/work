// EEPFile.cpp: CEEPFile クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BGJServTool.h"
#include "MemEntry.h"
#include "EEPFile.h"
#include "Language.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

static const char cCommentChar = '#';
static const char cDelimiter = ',';
static const char cDoubleQuate = '"';
static const int ciHeaderItemNumber = -3333;

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CEEPFile::CEEPFile()
{
	m_pf = NULL;
	m_nValidEntryCount = 0;
	m_nTotalSize = 0;
	m_nTopOffset = 0;
	m_bReaded = false;
	m_bNeedRead = false;
	m_bChanged = false;
}

CEEPFile::~CEEPFile()
{
	Close();
}

bool CEEPFile::Open(LPCTSTR pszFileName)
{
	bool bRet = true;
	Close();
	m_bReaded = false;
	if( pszFileName ){
		m_csFileName = pszFileName;
		m_pf = _tfopen( pszFileName, _T("rb") );
		if( m_pf ){
			bRet = LoadData();
			fclose( m_pf );
			m_pf = NULL;
		}else{
//			CQErr::MsgBoxLastError();
			bRet = false;
		}
	}
	return bRet;
}

void CEEPFile::Close()
{
	if( m_pf ){
		fclose( m_pf );
		m_pf = NULL;
	}
}

bool CEEPFile::LoadData()
{
	bool bRet = true;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	DWORD dwAddr = 0;
	m_nValidEntryCount = 0;
	m_nTotalSize = 0;
	m_MemArray.SetSize( 0, 128 );
	m_nTopOffset = -1;
	CString csLine;
	while( bRet && ReadOneLine( csLine ) ){
		CMemEntry mEntry;
		if( ParseOneLine( csLine, mEntry ) ){
			if( (UINT)mEntry.m_iNumber == m_nValidEntryCount )
			{
				mEntry.m_dwAddr = dwAddr;
				dwAddr += mEntry.m_nSize;
				m_nTotalSize += mEntry.m_nSize;
				m_nValidEntryCount += 1;
				if( mEntry.m_nSize > 4 ){
					mEntry.m_iType = 0;
				}
			}else if( mEntry.m_iNumber == -1 )
			{
				;
			}else if( mEntry.m_iNumber == ciHeaderItemNumber )
			{
				// Header line
				if( m_nTopOffset == -1 ){
					m_nTopOffset = 0; // mEntry.m_iType;
					m_dwBlockID = mEntry.m_nSize;
					dwAddr = m_nTopOffset;
					if( m_nValidEntryCount > 0 )
					{
						bRet = false;
						LangAfxMsgBox( IDS_ERR_BUG , -120 );
						//"Error: EEPROM: Header line must be first line"
						
					}
				}else
				{
					// Too many header lines.
					bRet = false;
					LangAfxMsgBox( IDS_ERR_BUG , -121 );
					//"Error: EEPROM template file containes too many header lines"
				}
			}else
			{
				bRet = false;
				LangAfxMsgBox( IDS_ERR_BUG , -122 );
				//"Error: EEPROM template file is corrupted"
			}
			if( bRet )
			{
				m_MemArray.Add( mEntry );
			}
		}else
		{
			bRet = false;

			LangAfxMsgBox( IDS_ERR_BUG , -123 );
			//"Error: EEPROM Template file: illegal line found \"%s\"", (LPCTSTR)csLine )
			
		}
	}
	if( m_nTopOffset < 0 )
	{
		bRet = false;
		LangAfxMsgBox( IDS_ERR_BUG , -124 );
		//"Error: EEPROM template file is corrupted or containes No header line"
	}
	return bRet;
}

bool CEEPFile::ReadOneLine(CString &csLine)
{
	bool bRet = true;
	int c = 0;
	bool bCont = true;
	int n = 0;
	csLine.Empty();
	while( bCont ){
		c = GetOneChar();
		switch( c ){
		case EOF:
			if( 0 == n ){ // end of file and nothing readed
				bRet = false;
			}
			bCont = false;
			break;
		case 0x0D: // CR
		case 0x0A: // LF
			if( n ){ // skip if n==0 i.e. garbage of previous line
				bCont = false;
			}
			break;
		default:
			csLine += (TCHAR)c;
			n += 1;
		}
	}
	return bRet;
}

bool CEEPFile::ParseOneLine(CString &csLine, CMemEntry& mEntry)
{
	bool bRet = true;
	int nLen = csLine.GetLength();
	int j=0;
	char szNum[512];
	char szSize[512];
	char szData[512];
	char szType[512];
	char szName[512];
	char szNone[512];
	char* pCurrentBuf;
	enum { eNumber, eSize, eData, eType, eName, eComment, eNone } eMode;
	eMode = eNumber;
	pCurrentBuf = szNum;
	szNum[0] = szSize[0] = szData[0] = szType[0] = szName[0] = '\0';
	bool bInQuate = false;
	for( int i=0; (i<=nLen)&&(bRet); ++i ){
		int c = '\0';
		if( i < nLen ) c = csLine[i];
		if( ! bInQuate ){
			switch( c ){
			case cDoubleQuate:
				bInQuate = true;
				break;
			case cCommentChar:
				pCurrentBuf[j] = '\0'; j = 0;
				if( (eMode == eNumber)||(eMode==eName)){
					bRet = mEntry.SetMemEntry( szNum, szSize, szData, szType, szName, NULL ); 
					eMode = eComment;
					if( mEntry.m_iNumber != ciHeaderItemNumber ){
						mEntry.m_csComment = csLine.Right( nLen - i );
					}
					i = nLen + 1; // one line end
				}else{
					bRet = false;
				}
				break;
			case cDelimiter:
				pCurrentBuf[j] = '\0'; j = 0;
				switch( eMode ){
				case eNumber:	eMode = eSize; pCurrentBuf = szSize; break;
				case eSize:		eMode = eData; pCurrentBuf = szData; break;
				case eData:		eMode = eType; pCurrentBuf = szType; break;
				case eType:		eMode = eName; pCurrentBuf = szName; break;
				case eName:		eMode = eNone; pCurrentBuf = szNone; break;
				default:
					bRet = false;
					break;
				}
				break;
			case 0x0D:
			case 0x0A:
			case '\0':
				pCurrentBuf[j] = '\0'; j = 0;
				if( (eMode == eNumber)||(eMode==eName)){
					bRet = mEntry.SetMemEntry( szNum, szSize, szData, szType, szName, NULL );
					i = nLen + 1; // end
				}else{
					bRet = false;
				}
				break;
			default:
				if( j < 512-1 ){
					pCurrentBuf[j] = csLine[i];
					j += 1;
					if( i == (nLen - 1) ){
						pCurrentBuf[j] = '\0'; j = 0;
						if( (eMode == eNumber)||(eMode==eName)){
							bRet = mEntry.SetMemEntry( szNum, szSize, szData, szType, szName, NULL );
							i = nLen + 1; // end
						}else bRet = false;
					}
				}else{
					bRet = false;
				}
				break;
			}
		}else{
			// if in quate 
			switch( c ){
			case cDoubleQuate:
				bInQuate = false;
				break;
			case 0x0D:
			case 0x0A:
			case '\0':
				pCurrentBuf[j] = '\0'; j = 0;
				if( (eMode == eNumber)||(eMode==eName)){
					bRet = mEntry.SetMemEntry( szNum, szSize, szData, szType, szName, NULL );
					i = nLen + 1; // end
				}else{
					bRet = false;
				}
				break;
			default:
				if( j < 512-1 ){
					pCurrentBuf[j] = csLine[i];
					j += 1;
					if( i == (nLen - 1) ){
						pCurrentBuf[j] = '\0'; j = 0;
						if( (eMode == eNumber)||(eMode==eName)){
							bRet = mEntry.SetMemEntry( szNum, szSize, szData, szType, szName, NULL );
							i = nLen + 1; // end
						}else bRet = false;
					}
				}else{
					bRet = false;
				}
				break;
			}
		}
	}
	return bRet;
}

CMemEntry* CEEPFile::GetMemEntry(unsigned int nPos)
{
	CMemEntry* pEntry = NULL;
	int nLen = m_MemArray.GetSize();
	for( int i=0; (i<nLen)&&(pEntry==NULL); ++i ){
		if( m_MemArray.ElementAt(i).m_iNumber == (int)nPos ){
			pEntry = &(m_MemArray.ElementAt(i));
		}
	}
	return pEntry;
}

unsigned int CEEPFile::GetCount()
{
	return m_nValidEntryCount;
}

bool CEEPFile::GetHeaderInfo(DWORD *piType, DWORD *pdwVersion, CString &csVersion, CString &csComment)
{
	bool bRet = false;
	CMemEntry* pEntry = NULL;
	int nLen = m_MemArray.GetSize();
	for( int i=0; (i<nLen)&&(pEntry==NULL); ++i )
	{
		if( m_MemArray.ElementAt(i).m_iNumber == ciHeaderItemNumber )
		{
			pEntry = &(m_MemArray.ElementAt(i));
			*piType = pEntry->m_nSize;
			*pdwVersion = pEntry->m_iType;
			csVersion = pEntry->m_csComment;
			csComment = pEntry->m_csName;
			bRet = true;
		}
	}
	return bRet;
}


DWORD CEEPFile::GetTotalSize()
{
	return m_nTotalSize;
}

int CEEPFile::GetTopOffset()
{
	return m_nTopOffset;
}

bool CEEPFile::SaveAsTemplate(LPCTSTR pszFileName)
{
	bool bRet = true;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	FILE* pf = _tfopen( pszFileName, _T("wb") );
	if( pf ){
		CMemEntry* pEntry = NULL;
		CMemFile MemF;
		MemF.Write( "\xff\xfe", 2 );
		int nLen = m_MemArray.GetSize();
		for( int i=0; (i<nLen)&&(bRet); ++i )
		{
			pEntry = &(m_MemArray.ElementAt(i));
			if( pEntry )
			{
				bRet = SaveAsOneLine( MemF, pEntry );
			}
		}
		if( bRet )
		{
			DWORD dwSize = (DWORD)MemF.GetLength();
			BYTE* pData = MemF.Detach();
			fwrite( pData, 1, dwSize, pf );
			free( pData );
		}
		fclose( pf );
	}else
	{
		LangAfxMsgBox( IDS_EER_FILE_IO , -125 , pszFileName );
		bRet = false;
	}
	return bRet;
}

bool CEEPFile::SaveAsOneLine(CMemFile& MemF, CMemEntry *pEntry)
{
	bool bRet = true;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	CString cs;
	if( pEntry->m_iNumber == ciHeaderItemNumber){
		if( pEntry->m_csName.IsEmpty() ){
			pEntry->m_csName = _T("");
		}
		if( pEntry->m_csComment.IsEmpty() ){
			pEntry->m_csComment = _T("");
		}
		cs.Format( _T("%d,0x%04X,\"%s\",0x%04X,\"%s\"\r\n"), pEntry->m_iNumber, pEntry->m_nSize,
			(LPCTSTR)pEntry->m_csComment, pEntry->m_iType, (LPCTSTR)pEntry->m_csName );
	}else if( pEntry->m_iNumber < 0 ){ // comment line
		if( pEntry->m_csComment.IsEmpty() ){ // null line
			cs.Format( _T("\r\n") );
		}else{
			cs.Format( _T("%s\r\n"), (LPCTSTR)pEntry->m_csComment );
		}
	}else{
		// normal entry
		CString csData;
		switch( pEntry->m_iType ){
		case 1: // unsigned
			csData.Format( _T("%u"), pEntry->m_dwData1 );
			break;
		case 2: // signed
			csData.Format( _T("%d"), pEntry->m_dwData1 );
			break;
		case 3: // date
			csData = pEntry->m_csDate;
			break;
		case 0: // Hex
		default:
			{
				BYTE b;
				DWORD dw1, dw2;
				csData += _T("0x");
				dw1 = pEntry->m_dwData1;
				dw2 = pEntry->m_dwData2;
				int i;
				for( i=0; i<(8 - pEntry->m_nSize); ++i ){ // skip
					dw2 = (dw2 << 8) | ((dw1 >> 24) & 0xFF);
					dw1 <<= 8;
				}
				for( i=0; i<pEntry->m_nSize; ++i ){
					CString cs2;
					b = (BYTE)(dw2 >> 24);
					dw2 = (dw2 << 8) | ((dw1 >> 24) & 0xFF);
					dw1 <<= 8;
					cs2.Format(_T("%02X"), b );
					csData += cs2;
				}
			}
			break;
		}
		cs.Format(_T("%d,%d,%s,%d,\"%s\" "), pEntry->m_iNumber, pEntry->m_nSize, (LPCTSTR)csData,
			pEntry->m_iType, (LPCTSTR)pEntry->m_csName );
		if( pEntry->m_csComment.IsEmpty() ){
			cs += _T("\r\n");
		}else{
			CString cs1;
			cs1.Format(_T(" %s\r\n"), (LPCTSTR)pEntry->m_csComment );
			cs += cs1;
		}
	}
	if( ! cs.IsEmpty() ){
		long lSize = cs.GetLength() * sizeof(TCHAR);
		MemF.Write( (LPCTSTR)cs, lSize );
	}
	return bRet;
}

bool CEEPFile::SetReadData(long nReadSize, BYTE *pData)
{
	bool bRet = true;
	BYTE* pTopAddr = pData;
	UINT nCount = GetCount();
	UINT i;
	BYTE nulld[32];
	memset( (void*)nulld, 0, sizeof(nulld) );
	long nLeft = nReadSize;
	for( i=0; i<nCount; ++i ){
		CMemEntry* pME = GetMemEntry( i );
		if( nLeft >= pME->m_nSize ){
			pME->ChangeData( pME->m_nSize, pData );
			pData += pME->m_nSize;
			nLeft -= pME->m_nSize;
		}else{
			pME->ChangeData( pME->m_nSize, nulld );
		}
	}
	return bRet;
}


void CEEPFile::SetFlagNeedRead(bool bNeedRead)
{
	m_bNeedRead = bNeedRead;
}

void CEEPFile::SetChanged( bool bChanged )
{
	m_bChanged = true;
}

bool CEEPFile::IsNeedRead()
{
	return m_bNeedRead;
}

bool CEEPFile::IsChanged()
{
	return m_bChanged;
}

bool CEEPFile::Open(int nResourceID)
{
	bool bRet = false;
	Close();
	m_bReaded = false;
	m_pf = NULL;
	m_pResTop = NULL;
	m_nResSize = 0;
	m_nResPos = 0;
	HGLOBAL hArp = NULL;
	if( nResourceID != 0 ){
		LPCTSTR lp = MAKEINTRESOURCE( nResourceID );
		HRSRC hRes = ::FindResource( NULL, (LPCTSTR)lp, _T("Template") );
		if( hRes ){
			m_nResSize = ::SizeofResource( NULL, hRes );
			hArp = ::LoadResource( NULL, hRes );
			if( hArp && (m_nResSize > 0) ){
				m_pResTop = (LPBYTE)::LockResource( hArp );
				bRet = LoadData();
			}else{
				m_nResSize = 0;
			}
		}
	}
	return bRet;
}

int CEEPFile::GetOneChar()
{
	int c;
	if( m_pf != NULL ){
		c = getc( m_pf );
	}else if( m_nResPos < m_nResSize ){
		c = m_pResTop[ m_nResPos ];
		m_nResPos += 1;
	}else{
		c = EOF;
	}
	return c;
}

bool CEEPFile::SaveAsTemplate(CGTLogFile &LogF)
{
	bool bRet = true;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	CMemEntry* pEntry = NULL;
	DWORD dwType, dwVersion;
	CString csVersion;
	CString csComment;
	if( GetHeaderInfo( &dwType, &dwVersion, csVersion, csComment ) ){
		CMemFile MemF;
		MemF.Write( "\xff\xfe", 2 );
		int nLen = m_MemArray.GetSize();
		for( int i=0; (i<nLen)&&(bRet); ++i ){
			pEntry = &(m_MemArray.ElementAt(i));
			if( pEntry ){
				bRet = SaveAsOneLine( MemF, pEntry );
			}
		}
		if( bRet )
		{
			DWORD dwSize = (DWORD)MemF.GetLength();
			BYTE* pData = MemF.Detach();
			CString cs;
			cs.Format(_T("%04X"), dwType );
			bRet = LogF.WriteTagData( (LPCTSTR)cs, dwSize, pData );
			free( pData );
		}else
		{
			LangAfxMsgBox( IDS_ERR_BUG , -144 );
			//"Error: SaveAsTemplate: EEPROM data convert failed"
		}
	}
	return bRet;
}

bool CEEPFile::Open(LPBYTE pData, long nSize)
{
	bool bRet = false;
	Close();
	m_bReaded = false;
	m_pf = NULL;
	m_pResTop = NULL;
	m_nResSize = 0;
	m_nResPos = 0;
	if( (pData != NULL)&&(nSize > 0) ){
		m_nResSize = nSize;
		m_pResTop = pData;
		bRet = LoadData();
	}
	return bRet;
}

//バイナリ形式からセットする　　　　　　　　　論理炉ブロックのデータとデータサイズ
BOOL CEEPFile::Open_Bynari( int nResourceID , BYTE* pJustData, long nJustDataSize )
{
	BOOL bRet = FALSE;
	if( Open( nResourceID ) )
	{
		bRet = SetReadData( nJustDataSize , pJustData );
	}
	return bRet;
}
