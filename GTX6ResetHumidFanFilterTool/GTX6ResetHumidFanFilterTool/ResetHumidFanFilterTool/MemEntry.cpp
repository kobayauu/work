// MemEntry.cpp: CMemEntry クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BGJServTool.h"
#include "MemEntry.h"
#include "Language.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CMemEntry::CMemEntry()
{
	Clear();
}

CMemEntry::~CMemEntry()
{

}

bool CMemEntry::SetMemEntry(LPCSTR pszNum, LPCSTR pszSize, LPCSTR pszData, LPCSTR pszType,
							LPCSTR pszName, LPCSTR pszComment)
{
	bool bRet = true;
	Clear();
	if( pszNum && pszSize && pszData && pszType && pszName ){
		if( pszComment ){
			m_csComment = pszComment;
		}
		if( (pszNum[0]=='\0')&&(pszSize[0]=='\0')&&(pszData[0]=='\0')&&(pszType[0]=='\0')
			&&(pszName[0]=='\0') ){
			// NULL line or commnet only line
		}else if( (pszNum[0]=='\0')||(pszSize[0]=='\0')||(pszName[0]=='\0') ){
			// if this is not commnet line, number, size, name are requred.
			bRet = false;
		}else{
			if( (bRet = qAtoDWORD( pszNum, (DWORD*)&m_iNumber )) ){
				if( (bRet = qAtoDWORD( pszSize, (DWORD*)&m_nSize )) ){
					if( (bRet = qAtoDWORD( pszType, (DWORD*)&m_iType )) ){
						m_csName = pszName;
						if( (m_iNumber < 0)||(m_nSize > 8)||(m_nSize <= 0)
							||(m_iType<0)||(m_iType>3) ){
							if( m_iNumber == -3333 ){
								m_csComment = pszData;
							}else if( m_nSize == -1 ){ // for Index file
								LPCSTR pStr = SkipBlank( pszData );
								if( (pStr[0] == '0')&&((pStr[1]=='x')||(pStr[1]=='X')) ){
									pStr += 2;
									bRet = SetHexStr( pStr, m_nSize );
								}else{
									bRet = qAtoDWORD( pStr, &m_dwData1 );
								}
							}else{
								bRet = false;
							}
						}else if(m_iType==3){
							m_csDate = SkipBlank( pszData );
							bRet = true;
						}else{
							LPCSTR pStr = SkipBlank( pszData );
							if( (pStr[0] == '0')&&((pStr[1]=='x')||(pStr[1]=='X')) ){
								pStr += 2;
								bRet = SetHexStr( pStr, m_nSize );
							}else{
								bRet = qAtoDWORD( pStr, &m_dwData1 );
							}
						}
					}
				}	
			}
		}
	}else bRet = false;
	if( ! bRet )
	{
		LangAfxMsgBox( IDS_ERR_MEM_ENTRY , -20 );
	}
	return bRet;
}

long CMemEntry::q_atol(LPCSTR lp_str)
{
	long			rtc;
	BOOL			is_minus;
	BOOL			is_hex;
	BOOL			is_continue;
	BOOL			is_found;
	UINT			c;
	int				count;
    /*====================================  function  body  =========*/
	rtc		= 0;
	is_minus = is_hex = FALSE;
	is_continue = TRUE;
	is_found = FALSE;
	count = 0;
	while( is_continue && ( *lp_str != '\0' ) && ( count < 11 ) ){
		if( is_hex ){
			c = (BYTE)*lp_str;
			if( ( '0' <= c ) && ( c <= '9' ) ){
				rtc <<= 4;
				rtc |= ( c - '0' ) & 0x000F;
				is_found = TRUE;
			}else if( ( 'A' <= c ) && ( c <= 'F' ) ){
				rtc <<= 4;
				rtc |= ( c - 'A' + 0x0A ) & 0x000F;
			}else if( ( 'a' <= c ) && ( c <= 'f' ) ){
				rtc <<= 4;
				rtc |= ( c - 'a' + 0x0A ) & 0x000F;
			}else{
				is_continue = FALSE;
			}
		}else{
			c = *lp_str;
			if( ( '0' <= c ) && ( c <= '9' ) ){
				rtc *= 10;
				rtc += ( c - '0' );
				is_found = TRUE;
			}else if( ( c == ' ' ) || ( c == '\t' ) ){
				if( is_found )	is_continue = FALSE;
			}else if( ( c == 'x' ) || ( c == 'X' ) ){
				if(   is_found
					&&( ! is_minus )
					&&( rtc == 0 ) )
				{
					is_hex = TRUE;
				}
				else		is_continue = FALSE;
			}else if( c == '-' ){
				if( !is_found )	is_minus = TRUE;
				else			is_continue = FALSE;
			}else if( c == '+' ){
				if( is_found )	is_continue = FALSE;
			}else{
				is_continue = FALSE;
			}
		}
		++count;
		++lp_str;
	}
	if( is_minus ){
		rtc = -rtc;
	}
	return( rtc );
}

LPCSTR CMemEntry::SkipBlank(LPCSTR psz)
{
	while( (*psz==' ')||(*psz=='\t') ){
		psz += 1;
	}
	return psz;
}

bool CMemEntry::qAtoDWORD(LPCSTR pszInStr, DWORD *pData)
{
	bool bRet = TRUE;
	BOOL			is_minus;
	BOOL			is_hex;
	BOOL			is_continue;
	BOOL			is_found;
	UINT			c;
	int				count;
	DWORD rtc = 0;
	char szStr[256];
	int j=0;
	for( int i=0; (i<255)&&(pszInStr[i] != _T('\0')) ; ++i ){
		if( (pszInStr[i] != 0x0A)&&(pszInStr[i] != 0x0D) ){
			if( pszInStr[i] != _T(' ') ){
				szStr[j++] = pszInStr[i];
			}
		}
	}
	szStr[j++] = _T('\0');
	LPCSTR pszStr = szStr;
	is_minus = is_hex = FALSE;
	is_continue = TRUE;
	is_found = FALSE;
	count = 0;
	while( bRet && is_continue && ( *pszStr != '\0' ) && ( count < 11 ) ){
		if( is_hex ){
			c = (BYTE)*pszStr;
			if( ( '0' <= c ) && ( c <= '9' ) ){
				rtc <<= 4;
				rtc |= ( c - '0' ) & 0x000F;
				is_found = TRUE;
			}else if( ( 'A' <= c ) && ( c <= 'F' ) ){
				rtc <<= 4;
				rtc |= ( c - 'A' + 0x0A ) & 0x000F;
			}else if( ( 'a' <= c ) && ( c <= 'f' ) ){
				rtc <<= 4;
				rtc |= ( c - 'a' + 0x0A ) & 0x000F;
			}else if( ( c == ' ' ) || ( c == '\t' ) ){
				is_continue = FALSE;
			}else{
				bRet = false;
			}
		}else{
			c = *pszStr;
			if( ( '0' <= c ) && ( c <= '9' ) ){
				rtc *= 10;
				rtc += ( c - '0' );
				is_found = TRUE;
			}else if( ( c == ' ' ) || ( c == '\t' ) ){
				if( is_found )	is_continue = FALSE;
			}else if( ( c == 'x' ) || ( c == 'X' ) ){
				if(   is_found
					&&( ! is_minus )
					&&( rtc == 0 ) )
				{
					is_hex = TRUE;
				}
				else		bRet = false;
			}else if( c == '-' ){
				if( !is_found )	is_minus = TRUE;
				else			bRet = false;
			}else if( c == '+' ){
				if( is_found )	is_continue = FALSE;
				else			bRet = false;
			}else{
				bRet = false;
			}
		}
		++count;
		++pszStr;
	}
	if( is_minus ){
		long l = -(long)rtc;
		rtc = (DWORD)l;
	}
	*pData = rtc;
	return bRet;

}

void CMemEntry::Clear()
{
	m_csComment.Empty();
	m_csName.Empty();
	m_dwData1 = m_dwData2 = 0;
	m_dwAddr = 0;
	m_nSize = 0;
	m_iType = 0;
	m_iNumber = -1;
}

bool CMemEntry::SetHexStr(LPCSTR pszInStr, int nByte)
{
	bool bRet = true;
	char szStr[256];
	int j=0;
	int i;
	for( i=0; (i<255)&&(pszInStr[i] != _T('\0')) ; ++i ){
		if( pszInStr[i] != _T(' ') ){
			szStr[j++] = pszInStr[i];
		}
	}
	szStr[j++] = _T('\0');
	LPCSTR pStr = szStr;
	int nHexLen = 0;
	while( pStr[nHexLen] != '\0' ){
		nHexLen += 1;
	}
	while( (nHexLen > 0)&&((pStr[nHexLen-1]==' ')||(pStr[nHexLen-1]=='\t'))){
		nHexLen -= 1;
	}
	bool bFirstSkip = false;
	if( nHexLen & 1 )	bFirstSkip = true;
	if( (0<nHexLen)&&(nHexLen<=16) ){ 
		i = 0;
		while( (i<nHexLen)&&(bRet) ){
			BYTE b = 0;
			if( ! bFirstSkip ){ // if skip nHexLen is ODD
				if( ('0'<=*pStr)&&(*pStr<='9') )	b = (*pStr - '0');
				else if( ('A'<=*pStr)&&(*pStr<='F') )	b = (*pStr - 'A' + 0x0A);
				else if( ('a'<=*pStr)&&(*pStr<='f') )	b = (*pStr - 'a' + 0x0A);
				else bRet = false;
				b <<= 4;
				i += 1;
				pStr += 1;
			}else{
				bFirstSkip = false;
			}
			if( i <= nHexLen ){
				if( ('0'<=*pStr)&&(*pStr<='9') )	b |= (*pStr - '0');
				else if( ('A'<=*pStr)&&(*pStr<='F') )	b |= (*pStr - 'A' + 0x0A);
				else if( ('a'<=*pStr)&&(*pStr<='f') )	b |= (*pStr - 'a' + 0x0A);
				else bRet = false;
				pStr += 1;
				i += 1;
			}
			m_dwData2 = (m_dwData2 << 8) | ((m_dwData1 >> 24) & 0xFF);
			m_dwData1 = (m_dwData1 << 8) | b;
		}
	}else{
		bRet = false;
	}
	return bRet;
}

BYTE CMemEntry::GetDataByte(unsigned int iByteIndex)
{
	BYTE b = 0;
	DWORD dw;
	if( m_nSize > 0 ){
		int nPos = m_nSize - iByteIndex - 1;
		if( nPos >= 0 ){
			if( nPos < 4 ){
				dw = m_dwData1;
			}else{
				dw = m_dwData2;
				nPos -= 4;
			}
			for( int i=0; i < nPos; ++i ){
				dw >>= 8;
			}
			b = (BYTE)dw;
		}
	}
	return b;
}

bool CMemEntry::ChangeData(int nSize, const BYTE *pData)
{
	bool bRet = true;
	if( nSize == m_nSize )
	{
		m_dwData2 = m_dwData1 = 0;
		for( int i=0; i<nSize; ++i )
		{
			m_dwData2 = (m_dwData2 << 8) | ((m_dwData1 >> 24) & 0xFF);
			m_dwData1 = (m_dwData1 << 8) | pData[i];
		}
	}else
	{
		bRet = false;
	}
	return bRet;
}

bool CMemEntry::ChangeDataByStr(LPCSTR pInStr)
{
	bool bRet = true;
	if( pInStr ){
		m_dwData1 = m_dwData2 = 0;
		LPCSTR pStr = SkipBlank( pInStr );
		if( (pStr[0] == '0')&&((pStr[1]=='x')||(pStr[1]=='X')) ){
			pStr += 2;
			bRet = SetHexStr( pStr, m_nSize );
		}else{
			bRet = qAtoDWORD( pStr, &m_dwData1 );
		}
	}else bRet = false;
	return bRet;
}
