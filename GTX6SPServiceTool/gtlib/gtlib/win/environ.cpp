#include "gtx.h"
#include "modpal.h"

#include <intrin.h>
#pragma comment(lib, "version.lib")

#ifdef GTAPI
extern HMODULE GetModule();
#endif

///////////////////////////////////////////////////////////
// 関数：内部関数


namespace {


DWORD GetFileVersion( LPCTSTR szFile )
{
	DWORD dwVerHnd;
	DWORD dwVerInfoSize = GetFileVersionInfoSize(szFile, &dwVerHnd);
	if( dwVerInfoSize == 0 ) return 0;

	char* lpstrVffInfo = new char[dwVerInfoSize];
	BOOL bResult = GetFileVersionInfo(szFile, dwVerHnd, dwVerInfoSize, lpstrVffInfo);
	if( ! bResult ) return 0;

	VS_FIXEDFILEINFO* pVsFixedFileInfo;
	UINT nLen = 0;
	bResult = VerQueryValue( lpstrVffInfo, _T("\\"), (LPVOID*)&pVsFixedFileInfo, &nLen );
	if( ! bResult ) return 0;

	BYTE byVer1 = (BYTE) (pVsFixedFileInfo->dwFileVersionMS >>  16);
	BYTE byVer2 = (BYTE) (pVsFixedFileInfo->dwFileVersionMS & 0xFF);
	BYTE byVer3 = (BYTE) (pVsFixedFileInfo->dwFileVersionLS >>  16);
	BYTE byVer4 = (BYTE) (pVsFixedFileInfo->dwFileVersionLS & 0xFF);

	return	byVer1<<24 | byVer2<<16 | byVer3<<8 | byVer4;
}
void GetDriverFileName( GTX_PRINTER_TYPE type, LPTSTR lpFilename, DWORD nSize )
{
								GTX_GetDriverPath( lpFilename ); 
	if( type == TYPE_GT3    )	_tcscat( lpFilename, L"GT3Ui.dll"    );
	if( type == TYPE_GTX4   )   _tcscat( lpFilename, L"GTX4Ui.dll"   );
	if( type == TYPE_GTXpro )	_tcscat( lpFilename, L"GTXproUi.dll" );
	if( type == TYPE_GTX6   )	_tcscat( lpFilename, L"GTX6Ui.dll"   );
	if( type == TYPE_GTX6SP )	_tcscat( lpFilename, L"GTX6SPUi.dll" );
}
void GetAppVersion( DWORD* dwVersion, GTX_PRINTER_TYPE type )	//FIXME:
{
	TCHAR	szPath[MAX_PATH];

	//App
	if( dwVersion[0] == -1 )
	{
		GetModuleFileName( NULL, szPath, MAX_PATH );
		dwVersion[0] = GetFileVersion( szPath );
	}

	//Driver
	if( dwVersion[2] == -1 || dwVersion[1] == -1 )
	{
		GetDriverFileName( type, szPath, MAX_PATH );
		dwVersion[2] = GetFileVersion( szPath );
	}

	//API
	if( dwVersion[1] == -1 )
	{
#ifdef GTAPI
		GetModuleFileName( GetModule(), szPath, MAX_PATH );
		dwVersion[1] = GetFileVersion( szPath );
#endif
	}
}

BOOL GetWindowsVersion(OSVERSIONINFOEXW* pOs)
{
	HMODULE hModule = LoadLibrary(_T("ntdll.dll"));
	if (hModule == NULL) {
		return FALSE;
	}

	typedef DWORD (WINAPI* RtlGetVersionType)(OSVERSIONINFOEXW*);
	auto RtlGetVersion = (RtlGetVersionType)GetProcAddress(hModule, "RtlGetVersion");
	if (RtlGetVersion == 0) {
		FreeLibrary(hModule);
		return FALSE;
	}

	DWORD status = RtlGetVersion(pOs);
	FreeLibrary(hModule);

    return (status == 0x00000000);  //STATUS_SUCCESS
}
void GetOSVersion( BYTE* byOS )
{
	OSVERSIONINFOEXW osw = {0};
    GetWindowsVersion( &osw );

	byOS[0] = (osw.wProductType & 2) ? 2 : 0;
	byOS[1] = (BYTE) osw.dwMajorVersion;
	byOS[2] = (BYTE) osw.dwMinorVersion;
	byOS[3] = 0;
}

void GetCpuID( BYTE* pCpuID )
{
    int		cpui[4];
    __cpuid(cpui, 0x80000000);

    if (cpui[0] >= 0x80000004) {
        __cpuid(cpui, 0x80000002);	memcpy( pCpuID   , cpui, sizeof(cpui) );
        __cpuid(cpui, 0x80000003);	memcpy( pCpuID+16, cpui, sizeof(cpui) );
        __cpuid(cpui, 0x80000004);	memcpy( pCpuID+32, cpui, sizeof(cpui) );
    }
    else {
        __cpuid(cpui, 0);			memcpy( pCpuID  , &cpui[1], sizeof(int) );
                                    memcpy( pCpuID+4, &cpui[3], sizeof(int) );
                                    memcpy( pCpuID+8, &cpui[2], sizeof(int) );
    }
}

void GetMemory( WORD* wMemory )
{
	MEMORYSTATUSEX msex = { sizeof(MEMORYSTATUSEX) };
	GlobalMemoryStatusEx( &msex );

	wMemory[0] = (WORD)( msex.ullTotalPhys    >> 20 );
	wMemory[1] = (WORD)( msex.ullAvailPhys    >> 20 );
	wMemory[2] = (WORD)( msex.ullAvailVirtual >> 20 );
}


}	//namespace


///////////////////////////////////////////////////////////
// 関数：印刷変数

void GTX_SUB_OptionToEnvironData( BYTE *pData, GTX_PRINTER_TYPE type )
{
	GetAppVersion( (DWORD*)(pData + 4), type );
	GetOSVersion( pData + 16 );
    GetCpuID( pData + 20 );
	GetMemory( (WORD*)(pData + 68) );
}

void GTX_SUB_GetEnvironData( BYTE* pData )
{
	GetOSVersion( pData + 0 );
	GetCpuID( pData + 4 );
	GetMemory( (WORD*)(pData + 52) );
}
