#pragma once

#undef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <winsock2.h>
#include <tchar.h>

#include "gtlib/defines.hpp"
#include "gtlib/string.hpp"


namespace gtlib {

namespace network {
bool IsIpAddress( LPCTSTR szAddress );
bool IsPrinterNetwork( LPCTSTR szPrinter );
int OpenPrinterNetwork( SOCKET& nSocket, LPCTSTR szPrinter, long nPort = 48000 );
int WritePrinterNetwork( SOCKET nSocket, BYTE* pBuffer, DWORD dwSize );
int ReadPrinterNetwork( SOCKET nSocket, BYTE* pBuffer, DWORD* lpSize );
int ClosePrinterNetwork( SOCKET& nSocket );
} //namespace network

namespace printer {
int CommPrinterOpen( HANDLE& hPrinter, LPCTSTR szPrinter, LPCTSTR szName, LPCTSTR szOutput = NULL );
int CommPrinterWrite( HANDLE hPrinter, BYTE* pBuffer, DWORD dwLength );
int CommPrinterClose( HANDLE& hPrinter );
} //namespace printer

} //namespace gtlib
