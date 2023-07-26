#include <vector>
#include <algorithm>

#include "gtx.h"
#include "modpal.h"
#ifndef __APPLE__
#include "gtlib.h"
#endif


////////////////////////////////////////
//    内部関数


namespace {


BYTE* memchk( BYTE* buf, int ch, size_t n )
{
	for( int i = 0; i < n; ++i, ++buf ) {
		if( *buf != ch )	return	buf;
	}
	return	NULL;
}

//ファイルの読み込み
class CFileData
{
	FILE *m_fp;
public:
	CFileData() : m_fp(NULL) {}
	~CFileData() { Close();	}

	int Open( LPCTSTR szFile ) {
		m_fp = _tfopen( szFile, _T("rb") );
		return m_fp ? 0 : -1;
	}
	int Close() {
		if( m_fp ) {
			fclose( m_fp );
			m_fp = NULL;
		}
		return 0;
	}
	int Pos() {
		fpos_t fpos;
		fgetpos( m_fp, &fpos );
		return (int)fpos;
	}
	int Size() {
		fpos_t fpos, fsize = 0;
		fgetpos( m_fp, &fpos );
		fseek( m_fp, 0L, SEEK_END );
		fgetpos( m_fp, &fsize );
		fseek( m_fp, (long)fpos, SEEK_SET );
		return (int)fsize;
	}
	int Read( BYTE* pBuffer, DWORD dwSize ) {
		return (int)fread( pBuffer, 1, dwSize, m_fp );
	}
};

class CFileDataModified : public CFileData
{
	bool m_platen;
	bool m_shifted;
	std::vector<BYTE> m_buff;
public:
	CFileDataModified() : m_shifted(false), m_platen(false) {};

	int FixPlaten( BOOL bFix ) {
		m_platen = bFix;
		return 0;
	}
	int AddFileName( LPCTSTR szArpFile ) {
#ifndef __APPLE__
		gtlib::Utf8String path( szArpFile );
		const char *p = strrchr( path, '\\' );
#else
		const char *path = szArpFile;
		const char *p = strrchr( path, '/' );
#endif
		p = ( p ? p+1 : (const char *)path );
		size_t		s = min( 128, strlen(p) );

		std::vector<BYTE> command = { '#','#',0x00,0x21, 0,0,0,0 };
		command[7] = (BYTE)s;
		command.insert(command.end(), p, p+s);
		command.resize((command.size()+3)/4*4);

		m_buff.insert(m_buff.end(), command.begin(),command.end());
		return 0;
	}
	int AddAutoDelete( BYTE byAutoJobDelete ) {
		if( byAutoJobDelete == 0 ) return 0;
		std::vector<BYTE> command = { '#','#',0x00,0x8D, 0x00,0x00,0x00,0x08, 0,0,0,0,0,0,0,0 };
		command[8] = byAutoJobDelete;

		m_buff.insert(m_buff.end(), command.begin(),command.end());
		return 0;
	}
	int AddPcEnviron2() {
		std::vector<BYTE> command = { '#','#',0x00,0x75, 0x00,0x00,0x00,0x40, 
											0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
											0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
											0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0, 
											0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0 };

		GTX_SUB_GetEnvironData( &command[8] );
#if defined(_WIN64) || defined(__APPLE__)
		command[66] = 1;
#else
		command[66] = 0;
#endif

		m_buff.insert(m_buff.end(), command.begin(),command.end());
		return 0;
	}
	int ReadModified( BYTE* pBuffer, DWORD dwSize ) {
		dwSize = CFileData::Read(pBuffer, dwSize);
		if(dwSize == 0) return dwSize;

		BYTE* p = NULL;
	/*	if( m_platen ) {
			std::vector<BYTE> command = { '#','#',0x00,0x04, 0x00,0x00,0x00,0x20, 0x01,0x00, 0x10,0x68,0x12,0xC0 };
			p = std::search(pBuffer, pBuffer+dwSize, command.begin(), command.end());
			if( p != pBuffer+dwSize ) {
				SET_WORD( p, 16, 0x06EC );
			}
		}	*/
		if( m_shifted ) {
			p = pBuffer;
		} else {
			std::vector<BYTE> command = { '#','#',0x00,0x22 };
			p = std::search(pBuffer, pBuffer+dwSize, command.begin(), command.end());
			if( p != pBuffer+dwSize ) {
				p += 8 + (p[7] + 3) / 4 * 4;
				m_shifted = true;
			}
		}
		if( m_shifted )
		{
			size_t size = m_buff.size();
			std::vector<BYTE> cache(size);
			std::memcpy ( &cache[0] , pBuffer + dwSize - size, size                        );
			std::memmove( p + size  , p                      , pBuffer - p + dwSize - size );
			std::memcpy ( p         , &m_buff[0]             , size                        );
			std::memcpy ( &m_buff[0], &cache[0]              , size                        );
		}

		return	dwSize;
	}
	int ReadRemain( BYTE* pBuffer, DWORD dwSize ) {
		DWORD dwSum = CFileData::Pos();
		DWORD dwLength = 0;
		if( dwSum % 2048 )
			dwLength = 2048 - dwSum % 2048;

		if( m_shifted
		&&	memchk( &m_buff[0], 0, m_buff.size() ) != NULL
		&&	dwLength < m_buff.size() )
			dwLength = 2048;

		if( dwLength == 0 )
			return	0;

		dwLength += 2048;
		std::memset( pBuffer, 0, dwLength );
		std::memcpy( pBuffer, &m_buff[0], m_buff.size() );

		return	dwLength;
	}
};


}	//namespace


////////////////////////////////////////
//    送信関数

const size_t FILE_BUFFER_SIZE = 0x10000;	//multiple of USB_BUFFER_SIZE(0x800)

int GTX_SendFileWithName( LPCTSTR szPrinter, LPCTSTR szArpFile, LPCTSTR szDocName )
{
	CSendPrn send;
	int result = send.Open( szPrinter, szDocName );
	if( result < 0 )  return result;

	CFileData file;
	result = file.Open( szArpFile );
	if( result < 0 )  return result;

	std::vector<BYTE> buffer( FILE_BUFFER_SIZE );
    while( (result = file.Read( &buffer[0], (DWORD)buffer.size() )) ) {
		if( result < 0 )  return result;
		result = send.Write( &buffer[0], result );
		if( result < 0 )  return result;
	}

	return send.Close();
}

int GTX_SendFileModified( LPCTSTR szPrinter, LPCTSTR szArpFile, BYTE byAutoJobDelete, BOOL bFixPlaten )
{
	TCHAR szName[MAX_PATH];
	TCHAR *p = (LPTSTR)_tcsrchr( szArpFile, '/' );
	_tcscpy( szName, p ? p+1 : szArpFile );
    if( (p = _tcsrchr( szName, '.' )) ) *p = 0;

	CSendPrn send;
	int result = send.Open( szPrinter, szName );
	if( result < 0 )  return result;

	CFileDataModified file;
	result = file.Open( szArpFile );
	if( result < 0 )  return result;

	file.AddFileName( szArpFile );
	file.AddPcEnviron2();
	file.AddAutoDelete( byAutoJobDelete );
	file.FixPlaten( bFixPlaten );

	std::vector<BYTE> buffer( FILE_BUFFER_SIZE );
    while( (result = file.ReadModified( &buffer[0], (DWORD)buffer.size() )) ) {
		if( result < 0 )  return result;
		result = send.Write( &buffer[0], result );
		if( result < 0 )  return result;
	}

    if( (result = file.ReadRemain( &buffer[0], (DWORD)buffer.size() )) ) {
		if( result < 0 )  return result;
		result = send.Write( &buffer[0], result );
		if( result < 0 )  return result;
	}

	return send.Close();
}

int GTX_SendResource( LPCTSTR szPrinter, LPCTSTR szResFile )
{
	CSendPrn send;
#ifdef __APPLE__
	int result = send.Open( szPrinter, szResFile );
#else
	int result = send.Open( szPrinter, _T("resource") );
#endif
	if( result < 0 )  return result;

	CResFile file;
	result = file.Open( szResFile );
	if( result < 0 )  return result;

	std::vector<BYTE> buffer( file.Size() );
    while( (result = file.Read( &buffer[0], (DWORD)buffer.size() )) ) {
		if( result < 0 )  return result;
		result = send.Write( &buffer[0], result );
		if( result < 0 )  return result;
	}

	return send.Close();
}
