#include "gtlib.h"
#include "gtx.h"
#include "modpal.h"


////////////////////////////////////////
//    送信関数

struct CSendPrn::Impl
{
	HANDLE	m_hPrinter;
};

CSendPrn::CSendPrn() : pimpl_(new CSendPrn::Impl())
{}
CSendPrn::~CSendPrn()
{
	Close();
	delete pimpl_;
}

int CSendPrn::Open( LPCTSTR szPrinter, LPCTSTR szName )
{
	return	gtlib::printer::CommPrinterOpen( pimpl_->m_hPrinter, szPrinter, szName, NULL );
}

int CSendPrn::Write( BYTE* pBuffer, DWORD dwLength )
{
	return	gtlib::printer::CommPrinterWrite( pimpl_->m_hPrinter, pBuffer, dwLength );
}

int CSendPrn::Close()
{
	return	gtlib::printer::CommPrinterClose( pimpl_->m_hPrinter );
}


////////////////////////////////////////
//	リソース関数

struct CResFile::Impl
{
	size_t	m_size;
	BYTE*	m_data;
	size_t	m_pos;
};

CResFile::CResFile() : pimpl_(new CResFile::Impl())
{}
CResFile::~CResFile()
{
	Close();
	delete pimpl_;
}

int CResFile::Open( LPCTSTR szFile )
{
	HRSRC hRes = ::FindResource( NULL, szFile, _T("ARP") );
	if( hRes == NULL )	return -1;

	HGLOBAL hArp = ::LoadResource( NULL, hRes );
	if( hArp == NULL )	return -2;

	pimpl_->m_size = ::SizeofResource( NULL, hRes );
	pimpl_->m_data = (BYTE*) ::LockResource( hArp );
	if( pimpl_->m_size == 0 || pimpl_->m_data == NULL ) {
		return -3;
	}

	return 0;
}

int CResFile::Close()
{
	return 0;
}

int CResFile::Size()
{
	return pimpl_->m_size;
}

int CResFile::Read( BYTE* pBuffer, DWORD dwSize )
{
	size_t rest = pimpl_->m_size - pimpl_->m_pos;
	if( dwSize > rest ) {
		dwSize = rest;
	}
	BYTE* resume = pimpl_->m_data + pimpl_->m_pos;
	memcpy( pBuffer, resume, dwSize );
	pimpl_->m_pos += dwSize;

	return dwSize;
}
