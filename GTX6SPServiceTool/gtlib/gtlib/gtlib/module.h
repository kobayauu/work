#pragma once


////////////////////////////////////////////////////////////


namespace gtlib {


namespace network {
BOOL GetIpAddressByPort( LPTSTR szAddress, LPCTSTR szPort );
bool IsOnlinePrinterNetwork( LPCTSTR szPrinter );
} //namespace network


namespace printer {
bool IsOnlineCommPrinter( LPCTSTR szPrinter );
} //namespace printer


} //namespcae gtlib