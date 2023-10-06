#include "ospal.h"
#include <winspool.h>
#include <ws2tcpip.h>
#include <tcpxcv.h>
#include <iphlpapi.h>
#include <icmpapi.h>

#pragma comment(lib, "winspool.lib")
#pragma comment(lib, "iphlpapi.lib")

#include "gtx.h"
#include "gtlib.h"
#include "gtlib/module.h"


namespace {


//一覧の取得

PRINTER_INFO_2* GetPrinterInfo2( LPCTSTR szPrinter )
{
	HANDLE	hPrinter = NULL;
	BOOL	bRet = ::OpenPrinter( (LPTSTR)szPrinter, &hPrinter, NULL );
	if( bRet == FALSE || hPrinter == NULL ) {
		return	NULL;
	}

	DWORD	dwSize, dwNeed;
	::GetPrinter( hPrinter, 2, 0, 0, &dwSize );
	LPBYTE pBuffer = new BYTE[ dwSize ];
	::GetPrinter( hPrinter, 2, pBuffer, dwSize, &dwNeed );
	
	::ClosePrinter( hPrinter );

	return	(PRINTER_INFO_2*) pBuffer;
}
BOOL ListPrinterInfo2( PRINTER_INFO_2** ppPrinterInfo2, DWORD* pNumber )
{
	DWORD dwNeeded;
	DWORD dwReturned;
	::EnumPrinters(PRINTER_ENUM_LOCAL,NULL,2,NULL,0,&dwNeeded,&dwReturned);

	LPBYTE pBuffer = new BYTE[dwNeeded];
	if( ::EnumPrinters(PRINTER_ENUM_LOCAL,NULL,2,pBuffer,dwNeeded,&dwNeeded,&dwReturned) == 0 ) {
		delete [] pBuffer;
		return  FALSE;
	}

	*pNumber = dwReturned;
	*ppPrinterInfo2 = (PRINTER_INFO_2*) pBuffer;

	return  TRUE;
}

BOOL ListPortInfo2( PORT_INFO_2** ppPortInfo2, DWORD* pNumber )
{
	DWORD dwNeeded;
	DWORD dwReturned;
	::EnumPorts( NULL, 2, NULL, 0, &dwNeeded, &dwReturned );

	LPBYTE pBuffer = new BYTE[dwNeeded];
	if( ::EnumPorts( NULL, 2, pBuffer,dwNeeded,&dwNeeded,&dwReturned) == 0 ) {
		delete [] pBuffer;
		return  FALSE;
	}

	*pNumber = dwReturned;
	*ppPortInfo2 = (PORT_INFO_2*) pBuffer;

	return  TRUE;
}

//ドライバーの種類の確認

GTX_PRINTER_TYPE GetPrinterType( PRINTER_INFO_2* pPrinterInfo2 )
{
	GTX_PRINTER_TYPE type = (GTX_PRINTER_TYPE) 0;
	if( pPrinterInfo2->pPrinterName == NULL ) {
		return	type;
	}

	if( _tcscmp( pPrinterInfo2->pDriverName, _T("Brother GT-3") ) == 0 ) {
		type = TYPE_GT3;
	}
	else if( _tcscmp( pPrinterInfo2->pDriverName, _T("Brother GTX-4") ) == 0 ) {
		type = TYPE_GTX4;
	}
	else if( _tcscmp( pPrinterInfo2->pDriverName, _T("Brother GTX pro") ) == 0 ) {
		type = TYPE_GTXpro;
	}
	else if( _tcscmp( pPrinterInfo2->pDriverName, _T("Brother GTX-6") ) == 0 ) {
		type = TYPE_GTX6;
	}
	else if( _tcscmp( pPrinterInfo2->pDriverName, _T("Brother GTX-6 Extra Colors ORGR") ) == 0 ) {
		type = TYPE_GTX6SP;
	}
	else if( _tcscmp( pPrinterInfo2->pDriverName, _T("Brother GTX-6 Ink Server") ) == 0 ) {
		type = TYPE_GTX6IS;
	}

	if( _tcsstr( pPrinterInfo2->pPrinterName, _T("FileOutput") ) != NULL
	||	_tcscmp( pPrinterInfo2->pPortName, _T("GT3FPort:")    ) == 0
	||	_tcscmp( pPrinterInfo2->pPortName, _T("GTX4FPort:")   ) == 0
	||	_tcscmp( pPrinterInfo2->pPortName, _T("GTXproFPort:") ) == 0
	||	_tcscmp( pPrinterInfo2->pPortName, _T("GTX6FPort:")   ) == 0
	||	_tcscmp( pPrinterInfo2->pPortName, _T("GTX6SPFPort:") ) == 0
	||	_tcscmp( pPrinterInfo2->pPortName, _T("FILE:")        ) == 0 ) {
		type = static_cast<GTX_PRINTER_TYPE>(type | TYPE_FILEOUTPUT);
	}
    else if(gtlib::network::GetIpAddressByPort(NULL, pPrinterInfo2->pPortName) ) {
		type = static_cast<GTX_PRINTER_TYPE>(type | TYPE_LAN);
    }
    else {
		type = static_cast<GTX_PRINTER_TYPE>(type | TYPE_USB);
    }

	return	type;
}


} //namespace


GTX_PRINTER_TYPE GTX_GetPrinterType( LPCTSTR szPrinter )
{
	PRINTER_INFO_2* pPrtInfo2 = GetPrinterInfo2( szPrinter );
	if( pPrtInfo2 == NULL ) {
        return  (GTX_PRINTER_TYPE) 0;
	}

	return	GetPrinterType( pPrtInfo2 );
}


////////////////////////////////////////
//    外部関数


int GTX_EnumPrinter( GTX_PRINTER_TYPE type, EnumPrinterCallBack callback, void* pUserData )
{
	PRINTER_INFO_2* pPrtInfo2;
	DWORD dwPrnNum;
	if( ! ListPrinterInfo2(&pPrtInfo2, &dwPrnNum) ) {
		return  -1;
	}

	PORT_INFO_2* pPortInfo2;
	DWORD dwPortNum;
	if( ! ListPortInfo2(&pPortInfo2, &dwPortNum) ) {
		delete [] pPrtInfo2;
		return  -2;
	}

	WSADATA data;
	WSAStartup( MAKEWORD(2,0), &data );

	//一覧でループ
	int result = 0;
	for( DWORD i = 0 ; i < dwPrnNum; ++i )
	{
		GTX_PRINTER_TYPE driverType = GetPrinterType( &pPrtInfo2[i] );
		if( ! (type & driverType & TYPE_MACHINE_ALL) ) {
			continue;
		}
		if( ! (type & driverType & TYPE_OUTPUT_ALL) ) {
			continue;
		}

        if (! (type & driverType & TYPE_FILEOUTPUT)
		&&	! gtlib::printer::IsOnlineCommPrinter( pPrtInfo2[i].pPrinterName ) ) {
			continue;
		}

        try
		{
			if( ! callback( driverType, pPrtInfo2[i].pPrinterName, pUserData ) ) {
				result = -4;
				break;
			}
		}
        catch(...)
		{
			result = -3;
			break;
		}
	}

	WSACleanup();

	delete [] pPortInfo2;
	delete [] pPrtInfo2;

	return  result;
}

BOOL GTX_GetPrinterAddress( LPTSTR szAddress, LPCTSTR szName )
{
	PRINTER_INFO_2* pPrtInfo2 = GetPrinterInfo2( szName );
	if( pPrtInfo2 == NULL ) {
		return	FALSE;
	}

	BOOL bRet = gtlib::network::GetIpAddressByPort( szAddress, pPrtInfo2->pPortName );
	delete [] pPrtInfo2;
	return	bRet;
}

BOOL GTX_IsOnlineAddress( LPCTSTR szAddress )
{
	WSADATA				data;
	WSAStartup( MAKEWORD(2,0), &data );
	bool result = gtlib::network::IsOnlinePrinterNetwork( szAddress );
	WSACleanup();
	return	result;
}
