/**
 * LogString.cpp
 */

#include "stdafx.h"
#include "LogString.h"
#include "LogCode_LogReader.h"

/**
 * CLogString.
 */
CLogString::CLogString()
{
}

/**
 * ~CLogString.
 */
CLogString::~CLogString()
{

}

/**
 * 文字列を月に変換する.
 * @param string 文字列
 * @param digit 数値
 * @return true:成功 , false:失敗 
 */
bool CLogString::stringToMonth(const CString& string, unsigned long& month)
{
	//"January", "February", "March", "April", "May", "June",
	//"July", "August", "September", "October", "November", "December"

	month = 0;
	switch(string[0])
	{
	case 'J':
		switch(string[1])
		{
		case 'a':
			month = 1;
			break;
		case 'u':
			switch(string[2])
			{
			case 'n':
				month = 6;
				break;
			case 'l':
				month = 7;
				break;
			}
			break;
		}
		break;
	case 'F':
		month = 2;
		break;
	case 'M':
		switch(string[1])
		{
		case 'a':
			switch(string[2])
			{
			case 'r':
				month = 3;
				break;
			case 'y':
				month = 5;
				break;
			}
			break;
		}
		break;
	case 'A':
		switch(string[1])
		{
		case 'p':
			month = 4;
			break;
		case 'u':
			month = 8;
			break;
		}
		break;
	case 'S':
		month = 9;
		break;
	case 'O':
		month = 10;
		break;
	case 'N':
		month = 11;
		break;
	case 'D':
		month = 12;
		break;
	}
	return (0 == month) ? false : true;
}

/**
 * 文字列をログ種別に変換する
 * @param string 文字列
 * @param class ログ種別
 * @return true:成功 , false:失敗 
 */
bool CLogString::stringToLogclass(const CString& string, unsigned long& logclass)
{
	// "OPE ", "STS ", "MNT ", "ERR ", "INF "
	logclass = 0;
	switch(string[0])
	{
	case 'O':
		logclass = LOGCLASS_OPERATION;
		break;
	case 'S':
		logclass = LOGCLASS_STATUS;
		break;
	case 'M':
		logclass = LOGCLASS_MAINTENANCE;
		break;
	case 'E':
		logclass = LOGCLASS_ERROR;
		break;
	case 'I':
		logclass = LOGCLASS_DEBUG;
		break;
	}
	return (0 == logclass) ? false : true;
}

/**
 * logclassToString.
 * @param logclass 
 * @return 
 */
CString CLogString::logclassToString(unsigned long logclass)
{
	switch(logclass)
	{
	case LOGCLASS_OPERATION:
		return "OPE ";
	case LOGCLASS_STATUS:
		return "STS ";
	case LOGCLASS_MAINTENANCE:
		return "MNT ";
	case LOGCLASS_ERROR:
		return "ERR ";
	case LOGCLASS_DEBUG:
		return "DBG ";
	default:
		return "";
	}
}

/**
 * 文字列を数値に変換する.
 * @param string 文字列
 * @param digit 数値
 * @return true:成功 , false:失敗 
 */
bool CLogString::stringToDigit(const CString& string, unsigned long& digit)
{
	int len = string.GetLength();

	digit = 0;
	if(len > 2 && '0' == string[0] && ('x' == string[1] || 'X' == string[1]))
	{
		for(int i = 2; i < len; i++)
		{
			if('0' <= string[i] && string[i] <= '9')
				digit = digit*0x10 + string[i]-'0';
			else if('a' <= string[i] && string[i] <= 'f')
				digit = digit*0x10 + 0x0a+string[i]-'a';
			else if('A' <= string[i] && string[i] <= 'F')
				digit = digit*0x10 + 0x0a+string[i]-'A';
			else
				return false;
		}
	}
	else
	{
		for(int i = 0; i < len; i++)
		{
			if('0' <= string[i] && string[i] <= '9')
				digit = digit*10 + string[i]-'0';
			else
				return false;
		}
	}
	return true;
}

/**
 * 文字列から区切り文字で区切られる部分文字列を取り出す.
 * @param string 文字列
 * @param pos 開始位置
 * @return 部分文字列
 */
CString CLogString::tokenize(const CString& string, const CString& separator, int& pos)
{
	int i = 0;
	char buf[256];
	int len = string.GetLength();
	while(pos < len)
	{
		char c = string[pos++];
		if(-1 != separator.Find(c))
		{
			if(0 != i)
			{
				buf[i] = '\0';
				return buf;
			}
		}
		else
			buf[i++] = c;
	}
	buf[i] = '\0';
	return buf;
}
CString CLogString::tokenizeString(const CString& string, const CString& separator, int& start, int loop)
{
	unsigned char buf[256] ={0};
	int cnt = 0;
	bool flg = true;

	for(int i = 0; i < loop; i++)
	{
		CString strToken = tokenize(string, " ", start);
		if (flg)
		{
			for(int j = 0; j < 4; j++)
			{
				CString strChar = "0x"+strToken.Mid(2*j, 2);
				unsigned long digit;
				stringToDigit(strChar, digit);
				if(0 <= digit && digit < 255)
				{
					buf[cnt] = (unsigned char) digit;
					if('\0' == buf[cnt]) {
						flg = false;
						break;
					}
					else
						cnt++;
				}
			}
		}
	}
	buf[cnt] = '\0';

	unsigned char buf2[256] = {0};
	int size;
	ConvUtf8toSJis( buf, buf2, &size );
	return buf2;
}

//文字コード変換	UTF-8 → S-JIS
bool CLogString::ConvUtf8toSJis( BYTE* pSource, BYTE* pDist, int* pSize )
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
