#include "gtx.h"


//Driver Path
void GTX_GetDriverPathA( char* pcPath )
{
	GetSystemDirectoryA( pcPath, MAX_PATH );

#ifdef _WIN64
	strcat( pcPath, "/spool/drivers/x64/3/" );
#else	//_WIN64
	strcat( pcPath, "/spool/drivers/w32x86/3/" );
#endif	//_WIN64
}
void GTX_GetDriverPathW( WCHAR* pcPath )
{
	GetSystemDirectoryW( pcPath, MAX_PATH );

#ifdef _WIN64
	wcscat( pcPath, L"/spool/drivers/x64/3/" );
#else	//_WIN64
	wcscat( pcPath, L"/spool/drivers/w32x86/3/" );
#endif	//_WIN64
}


//カスタム設定
static LPCTSTR GetTypeRegKey( GTX_PRINTER_TYPE type )
{
	switch( type ) {
	case TYPE_GT3:		return	_T("SOFTWARE\\Brother\\GT-3 Tools");
	case TYPE_GTX4:		return	_T("SOFTWARE\\Brother\\GTX-4 Tools");
	case TYPE_GTXpro:	return	_T("SOFTWARE\\Brother\\GTX pro Tools");
	case TYPE_GTX6:		return	_T("SOFTWARE\\Brother\\GTX-6 Tools");
	case TYPE_GTX6SP:	return	_T("SOFTWARE\\Brother\\GTX-6 SP Tools");
	case TYPE_GTX6IS:	return	_T("SOFTWARE\\Brother\\GTX-6 IS Tools");
	default:			return	NULL;
	}
}
static DWORD GetRegistryValue( LPCTSTR szKey, LPCTSTR szValue )
{
	HKEY		hKey;
	LONG		nRet;
	DWORD		dwData;
	DWORD		dwSize = sizeof(DWORD);

#ifndef _WIN64
	nRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, szKey, 0, KEY_EXECUTE, &hKey);
#else
	nRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, szKey, 0, KEY_EXECUTE | KEY_WOW64_32KEY, &hKey);
#endif
	if (nRet != ERROR_SUCCESS || hKey == NULL)
		return	0;

	nRet = RegQueryValueEx(hKey, szValue, NULL, NULL, (LPBYTE)&dwData, &dwSize);

	RegCloseKey(hKey);

	if (nRet != ERROR_SUCCESS || dwSize != sizeof(DWORD))
		return	0;

	return	dwData;	
}
DWORD GTX_GetCustomMode( GTX_PRINTER_TYPE type )
{
	LPCTSTR szKey   = GetTypeRegKey(type);
	LPCTSTR szValue = _T("SetupMode");

	return	GetRegistryValue( szKey, szValue );
}

//言語モード
DWORD GTX_GetLanguageMode( GTX_PRINTER_TYPE type )
{
	LPCTSTR szKey   = GetTypeRegKey(type);
	LPCTSTR szValue = _T("SetupLangID");

	DWORD dwLangID = GetRegistryValue( szKey, szValue );
	switch( dwLangID )
	{
	case 4:		case 2052:
		return	MAKELANGID( LANG_CHINESE , SUBLANG_CHINESE_SIMPLIFIED );
	case 7:		case 1031:
		return	MAKELANGID( LANG_GERMAN  , SUBLANG_GERMAN );
	case 12:	case 1036:
		return	MAKELANGID( LANG_FRENCH  , SUBLANG_FRENCH );
	case 10:	case 1034:
		return	MAKELANGID( LANG_SPANISH , SUBLANG_SPANISH_MODERN );
	case 16:	case 1040:
		return	MAKELANGID( LANG_ITALIAN , SUBLANG_ITALIAN );
	case 17:	case 1041:
		return	MAKELANGID( LANG_JAPANESE , SUBLANG_DEFAULT );
	case 18:	case 1042:
		return	MAKELANGID( LANG_KOREAN , SUBLANG_DEFAULT );
	case 25:	case 1049:
		return	MAKELANGID( LANG_RUSSIAN , SUBLANG_DEFAULT );
	case 31:	case 1055:
		return	MAKELANGID( LANG_TURKISH , SUBLANG_DEFAULT );
	default:
		return	MAKELANGID( LANG_ENGLISH , SUBLANG_ENGLISH_US );
	}
}
