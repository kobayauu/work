#pragma once

#include "ospal.h"


#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
	TYPE_GT3 = 1<<0,
	TYPE_GTX4 = 1<<1,
	TYPE_GTXpro = 1<<2,
    TYPE_GTX6 = 1<<3,
    TYPE_GTX6SP = 1<<4,
    TYPE_GTX6IS = 1<<5,

    TYPE_LAN = 1<<29,
    TYPE_USB = 1<<30,
	TYPE_FILEOUTPUT = 1<<31,
    
    TYPE_MACHINE_ALL = 0x00FFFFFF,
    TYPE_OUTPUT_ALL  = 0xFF000000,
} GTX_PRINTER_TYPE;

//gtx.cpp
#ifdef __APPLE__
void GTX_GetDriverPath( TCHAR* pcPath );
#else   //__APPLE__
void GTX_GetDriverPathA( char* pcPath );
void GTX_GetDriverPathW( WCHAR* pcPath );
#ifdef _UNICODE 
#define GTX_GetDriverPath GTX_GetDriverPathW
#else   //_UNICODE
#define GTX_GetDriverPath GTX_GetDriverPathA
#endif  //_UNICODE
DWORD GTX_GetLanguageMode( GTX_PRINTER_TYPE type );
#endif  //__APPLE__

DWORD GTX_GetCustomMode( GTX_PRINTER_TYPE type );


//printer.cpp/m
typedef BOOL (*EnumPrinterCallBack)( GTX_PRINTER_TYPE type, LPCTSTR szPrinter, void* pUserData );
int GTX_EnumPrinter( GTX_PRINTER_TYPE type, EnumPrinterCallBack callback, void* pUserData );
GTX_PRINTER_TYPE GTX_GetPrinterType( LPCTSTR szPrinter );

BOOL GTX_GetPrinterAddress( LPTSTR szAddress, LPCTSTR szPrinter );
BOOL GTX_IsOnlineAddress( LPCTSTR szAddress );


//send.cpp/mm
int GTX_SendFileWithName( LPCTSTR szPrinter, LPCTSTR szArpFile, LPCTSTR szDocName );
int GTX_SendFileModified( LPCTSTR szPrinter, LPCTSTR szArpFile, BYTE byAutoJobDelete, BOOL bFixPlaten );
int GTX_SendResource( LPCTSTR szPrinter, LPCTSTR szResFile );


#ifdef __cplusplus
}   //extern "C"
#endif
