#include "gtlib.h"
#include "module.h"

#include <winspool.h>
#include <ws2tcpip.h>
#include <tcpxcv.h>
#include <iphlpapi.h>
#include <icmpapi.h>

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "winspool.lib")
#pragma comment(lib, "ws2_32.lib")


////////////////////////////////////////////////////////////


namespace gtlib {

namespace spooler {

bool IsOnlinePrinterSpooler( LPCTSTR szPrinter )
{
	BOOL				bRet;
	HANDLE				hPrinter		= NULL;
	PRINTER_DEFAULTS	PrinterDefault	= { NULL, NULL, PRINTER_ALL_ACCESS | PRINTER_ACCESS_ADMINISTER };

	bRet = ::OpenPrinter( (LPTSTR)szPrinter, &hPrinter, &PrinterDefault );
	if( bRet == FALSE || hPrinter == NULL ) {
		return	FALSE;
	}

	BYTE    bData[4+16];
	DWORD   dwType    = REG_BINARY;
	DWORD   dwSize    = 4;
	BOOL    result    = GetPrinterData( hPrinter, (LPTSTR)_T("BrMatCheck"), &dwType, bData, 4, &dwSize );

	::ClosePrinter( hPrinter );

	return( result == ERROR_SUCCESS && dwSize != 0 && bData[0] == 0 );
}

int OpenPrinterSpooler( HANDLE& hPrinter, LPCTSTR szPrinter, LPCTSTR szName, LPCTSTR szOutput )
{
	if( ::OpenPrinter( (LPTSTR)szPrinter, &hPrinter, NULL ) == FALSE )
	{
		return	-2;
	}

	DOC_INFO_1			docinfo = {0};
	docinfo.pDocName	= (LPTSTR) (szName ? szName : _T("GT DATA"));
	docinfo.pDatatype	= (LPTSTR) _T("RAW");
	docinfo.pOutputFile	= (LPTSTR) szOutput;
	if( ::StartDocPrinter( hPrinter, 1, (LPBYTE) &docinfo ) == 0 )
	{
		return	-3;
	}

	if( ::StartPagePrinter( hPrinter ) == 0 )
	{
		return	-4;
	}

	return	0;
}

int WritePrinterSpooler( HANDLE hPrinter, BYTE* pBuffer, DWORD dwLength )
{
	DWORD	dwWrite;

	if( ::WritePrinter( hPrinter, pBuffer, dwLength, &dwWrite ) == FALSE )
	{
		return	-6;
	}
	if( dwWrite < dwLength )
	{
		return	-7;
	}

	return	0;
}

int ClosePrinterSpooler( HANDLE& hPrinter )
{
	if( hPrinter == NULL )	return	0;

	int result = 0;
	if( ::EndPagePrinter( hPrinter ) == FALSE )
	{
		result = -8;
	}
	if( ::EndDocPrinter( hPrinter ) == FALSE )
	{
		result = -9;
	}

	::ClosePrinter( hPrinter );
	hPrinter = NULL;

	return	result;
}


} //namespace spooler


////////////////////////////////////////////////////////////


namespace network {

long GetIpAddressByString( LPCTSTR szAddress )
{
	gtlib::Utf16String address(szAddress);
	ADDRINFOW* addr_info;
	int result = GetAddrInfoW( address, L"", nullptr, &addr_info );
	if (result != 0) {
		return  0;
	}

	for (auto ai = addr_info; ai != nullptr; ai = ai->ai_next)
	{
		if (ai->ai_family == AF_INET) {
			sockaddr_in* sa = (sockaddr_in*) ai->ai_addr;
			return sa->sin_addr.S_un.S_addr;
		}
	}
	return  0;
}

BOOL GetIpAddressByPort( LPTSTR szAddress, LPCTSTR szPort )
{
	BOOL				bRet;
	HANDLE				hPrinter		= NULL;

	TCHAR				szPortName[MAX_PATH];
	wsprintf( szPortName, _T(",XcvPort %s"), szPort );
	bRet = ::OpenPrinter( szPortName, &hPrinter, NULL );
	if( bRet == FALSE || hPrinter == NULL ) {
		return	FALSE;
	}

	DWORD				dwStatus;
	DWORD				cbNeeded		= 0;
	CONFIG_INFO_DATA_1	ConfigInfoData	= {0};
	PORT_DATA_1			PortData		= {0};
	ConfigInfoData.dwVersion	= 1;
	PortData.dwVersion			= 1;

	bRet = ::XcvData( hPrinter, L"GetConfigInfo", (PBYTE)&ConfigInfoData, sizeof(ConfigInfoData), (PBYTE)&PortData, sizeof(PortData), &cbNeeded, &dwStatus );
	::ClosePrinter( hPrinter );

	if( bRet == FALSE || wcslen(PortData.sztHostAddress) == 0 ) {
		return	FALSE;
	}

	if( szAddress != NULL ) {
		_tcscpy( szAddress, PortData.sztHostAddress );
	}
	return	TRUE;
}
long GetIpAddressByPort( LPCTSTR szPort )
{
	TCHAR	szAddress[MAX_NETWORKNAME_LEN];

	if( ! GetIpAddressByPort( szAddress, szPort ) ) {
		return	0;
	}

	return	GetIpAddressByString( szAddress );
}

long GetIpAddressByPrinter( LPCTSTR szPrinter )
{
	BOOL				bRet;
	HANDLE				hPrinter		= NULL;

	bRet = ::OpenPrinter( (LPTSTR)szPrinter, &hPrinter, NULL );
	if( bRet == FALSE || hPrinter == NULL ) {
		return	0;
	}

	DWORD	dwSize, dwNeed;

	::GetPrinter( hPrinter, 2, 0, 0, &dwSize );
	LPBYTE pBuffer = new BYTE[ dwSize ];
	::GetPrinter( hPrinter, 2, pBuffer, dwSize, &dwNeed );

	::ClosePrinter( hPrinter );

	LPCTSTR szPort = ((PRINTER_INFO_2 *)pBuffer)->pPortName;
	long nAddress = GetIpAddressByPort( szPort );
	delete [] pBuffer;

	return	nAddress;
}

long GetIpAddressByName( LPCTSTR szName )
{
	long nAddress = GetIpAddressByString( szName );
	if( nAddress == 0 ) {
		nAddress = GetIpAddressByPrinter( szName );
	}
	return	nAddress;	
}


bool IsIpAddress( LPCTSTR szAddress )
{
	return	GetIpAddressByString( szAddress );
}
bool IsPrinterNetwork( LPCTSTR szPrinter )
{
	return	GetIpAddressByName( szPrinter );
}

bool IsOnlinePrinterNetwork( long nAddress )
{
	HANDLE hIcmpFile = IcmpCreateFile();
	if( hIcmpFile == INVALID_HANDLE_VALUE ) {
		return FALSE;
	}

	ICMP_ECHO_REPLY Reply = {0};
	DWORD dwRetVal = IcmpSendEcho( hIcmpFile, nAddress, NULL, 0, NULL, &Reply, sizeof(Reply), 1000 );

	IcmpCloseHandle( hIcmpFile );
	return( dwRetVal != 0 && Reply.Status == IP_SUCCESS );
}
bool IsOnlinePrinterNetwork( LPCTSTR szPrinter )
{
	long nAddress = GetIpAddressByName( szPrinter );

	return	IsOnlinePrinterNetwork( nAddress );
}

int OpenPrinterNetwork( SOCKET& nSocket, long nAddress, long nPort = 48000 )
{
    if( ! IsOnlinePrinterNetwork(nAddress) ) {
        return	-2;
    }

	struct sockaddr_in	dstAddr		= {0};
	dstAddr.sin_port		= htons( (u_short)nPort );
	dstAddr.sin_family		= AF_INET;
	dstAddr.sin_addr.s_addr	= nAddress;

	nSocket =  ::socket( AF_INET, SOCK_STREAM, 0 );
//	if( nSocket < 0 ) {
//		return	-3;
//	}

	int nRet = ::connect( nSocket, (struct sockaddr *) &dstAddr, sizeof(dstAddr) );
	if( nRet < 0 ) {
		return	-4;
	}

	return	0;
}
int OpenPrinterNetwork( SOCKET& nSocket, LPCTSTR szPrinter, long nPort )
{
	long nAddress = GetIpAddressByName( szPrinter );

	return	OpenPrinterNetwork( nSocket , nAddress, nPort );
}

int WritePrinterNetwork( SOCKET nSocket, BYTE* pBuffer, DWORD dwSize )
{
	int writed = ::send( nSocket, (const char *) pBuffer, dwSize, 0 );
	if( writed < 0 )
	{
		return	-6;
	}
	if( writed < dwSize )
	{
		return	-7;
	}

	return	0;
}

int WriteHeaderPrinterNetwork( SOCKET nSocket, DWORD dwTotalSize )
{
	BYTE    header[] = { '@','@', 0,0, 0,0,0,0 };
	SET_DWORD( header, 4, dwTotalSize );

	return	WritePrinterNetwork( nSocket, header, sizeof(header) );
}

int ReadPrinterNetwork( SOCKET nSocket, BYTE* pBuffer, DWORD* lpSize )
{
	fd_set			fds;
	struct timeval 	tv			= { 0, 500000000L };	//0.5s
	DWORD			dwRead		= *lpSize;
	DWORD			dwNeeded	= 0;
	BOOL			selected	= false;

	for( int loop = 0; loop < 6 && dwNeeded == 0; ++loop )
	{
		if( selected == false )
		{
			FD_ZERO( &fds );
			FD_SET( nSocket, &fds );
			select( (int)nSocket + 1, &fds, NULL, NULL, &tv );
			if( FD_ISSET( nSocket, &fds ) == false ) {
				continue;
			}
			Sleep( 10 );
			selected	= true;
		}
		else
			Sleep( 500 );	//0.5s

		dwNeeded = (DWORD) recv( nSocket, (char *) pBuffer, dwRead, 0 );
	}

	if( dwNeeded == 0 ) {
		return	-10;
	}
	*lpSize = dwNeeded;

	if( dwNeeded != dwRead ) {
		return	-11;
	}

	return	0;
}

int ClosePrinterNetwork( SOCKET& nSocket )
{
	if( nSocket == NULL )	return	0;

	::closesocket( nSocket );
	nSocket = NULL;

	return	0;
}

} //namespace network


////////////////////////////////////////////////////////////


namespace tofile {

int OpenPrinterToFile( FILE* &fp, LPCTSTR szOutput )
{
	fp = ::_tfopen( szOutput, _T("wb") );
	if( fp == NULL ) {
		return 	-2;
	}

	return	0;
}

int WritePrinterToFile( FILE* fp, BYTE* pBuffer, DWORD dwSize )
{
	size_t size = ::fwrite( pBuffer, 1, dwSize, fp );
	if( size < dwSize ) {
		return	-7;
	}

	return	0;
}

int ClosePrinterToFile( FILE* &fp )
{
	if( fp == NULL )	return	0;

	::fclose( fp );
	fp = NULL;

	return	0;
}

} //namespace tofile


////////////////////////////////////////////////////////////


namespace {

//Spooler, Network 切り替え
const DWORD USB_BUFFER_SIZE = 0x800;
const DWORD LAN_BUFFER_SIZE = 0x1000000;

typedef struct _COMMUNICATE_PRINTER {
	FILE*	fp;
	HANDLE	hPrinter;
	long	nAddress;
    DWORD   dwSize;
    DWORD   dwFullSize;
    BYTE*   pBuff;
} COMMPRN;

} //namespace


namespace printer {

bool IsOnlineCommPrinter( LPCTSTR szPrinter )
{
	if( network::IsPrinterNetwork( szPrinter ) ) {
		return	network::IsOnlinePrinterNetwork( szPrinter );
	} else {
		return	spooler::IsOnlinePrinterSpooler( szPrinter );
	}
}

int CommPrinterOpen( HANDLE& hPrinter, LPCTSTR szPrinter, LPCTSTR szName, LPCTSTR szOutput )
{
	int			nResult	= 0;
	COMMPRN*	pComm	= new COMMPRN();

	if( szOutput != NULL )
	{
		nResult = tofile::OpenPrinterToFile( pComm->fp, szOutput );
	}
	else
	{
		WSADATA				data;
		WSAStartup( MAKEWORD(2,0), &data );

		pComm->nAddress = network::GetIpAddressByString( szPrinter );
		if( pComm->nAddress == 0 ) {
			nResult = spooler::OpenPrinterSpooler( pComm->hPrinter, szPrinter, szName, szOutput );
			pComm->dwFullSize = USB_BUFFER_SIZE;
		}
		else {
			pComm->dwFullSize = LAN_BUFFER_SIZE;
		}
			pComm->dwSize = 0;
			pComm->pBuff = (BYTE *) malloc( pComm->dwFullSize );
	}

	hPrinter = (HANDLE*) pComm;
	return	nResult;
}

int CommPrinterWrite( HANDLE hPrinter, BYTE* pBuffer, DWORD dwLength )
{
	if( hPrinter == NULL )	return	0;

	COMMPRN*	pComm   = (COMMPRN*) hPrinter;
    int         nResult = 0;

	if( pComm->fp != NULL )
	{
		nResult = tofile::WritePrinterToFile( pComm->fp, pBuffer, dwLength );
	}
	else if( pComm->nAddress == 0 )
    {
        DWORD	dwAddSize	= 0;
        DWORD	dwIndex		= 0;

        while( dwIndex < dwLength && nResult >= 0 )
        {
            dwAddSize = min( USB_BUFFER_SIZE - pComm->dwSize, dwLength - dwIndex );

            memcpy( pComm->pBuff + pComm->dwSize, pBuffer + dwIndex, dwAddSize );
            pComm->dwSize	+= dwAddSize;
            dwIndex		  	+= dwAddSize;

            if( pComm->dwSize == USB_BUFFER_SIZE ) {
                nResult		    = spooler::WritePrinterSpooler( pComm->hPrinter, pComm->pBuff, USB_BUFFER_SIZE );
                pComm->dwSize = 0;
            }
        }
	}
	else
    {
        if( pComm->dwSize + dwLength > pComm->dwFullSize ) {
            pComm->dwFullSize += LAN_BUFFER_SIZE;
            pComm->pBuff = (BYTE*) realloc( pComm->pBuff, pComm->dwFullSize );
        }

        memcpy( pComm->pBuff + pComm->dwSize, pBuffer, dwLength );
        pComm->dwSize += dwLength;
    }

    return	nResult;
}

int CommPrinterClose( HANDLE& hPrinter )
{
	if( hPrinter == NULL )	return	0;

    int         nResult = 0;
	COMMPRN*	pComm   = (COMMPRN*) hPrinter;

	if( pComm->fp != NULL )
	{
		nResult = tofile::ClosePrinterToFile( pComm->fp );
	}
	else
	{
		if( pComm->nAddress == 0 )
		{
			if( pComm->dwSize )	nResult = spooler::WritePrinterSpooler( pComm->hPrinter, pComm->pBuff, pComm->dwSize );
			if( nResult >= 0 )	nResult = spooler::ClosePrinterSpooler( pComm->hPrinter );
		}
		else
		{
			SOCKET nSocket = NULL;
								nResult = network::OpenPrinterNetwork( nSocket, pComm->nAddress );
			if( nResult >= 0 )	nResult = network::WriteHeaderPrinterNetwork( nSocket, pComm->dwSize );
			if( nResult >= 0 )	nResult = network::WritePrinterNetwork( nSocket, pComm->pBuff, pComm->dwSize );
			if( nResult >= 0 )	nResult = network::ClosePrinterNetwork( nSocket );
		}
	    free( pComm->pBuff );

		WSACleanup();
	}

	delete	pComm;
	hPrinter = NULL;

	return	nResult;
}

} //namespace printer

} //namespace gtlib
