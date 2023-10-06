#pragma once

#include <stdio.h>


#ifdef __cplusplus
extern "C" {
#endif


//environ.cpp/m
void GTX_SUB_OptionToEnvironData( BYTE *pData, GTX_PRINTER_TYPE type );
void GTX_SUB_GetEnvironData( BYTE* pData );

//printers.cpp/m
void GTX_SUB_GetPID( LPTSTR szPID, LPCTSTR szName );	//macOS

#ifdef __cplusplus

//sendprn.cpp/m
class CSendPrn
{
	struct Impl;
	Impl* pimpl_;

public:
	CSendPrn();
	~CSendPrn();

	int Open( LPCTSTR szPrinter, LPCTSTR szName );
	int Write( BYTE* pBuffer, DWORD dwLength );
	int Close();
};

class CResFile
{
	struct Impl;
	Impl* pimpl_;

public:
	CResFile();
	~CResFile();

	int Open( LPCTSTR szFile );
	int Close();
	int Size();
	int Read( BYTE* pBuffer, DWORD dwSize );
};

#endif


#ifdef __cplusplus
}   //extern "C"
#endif
