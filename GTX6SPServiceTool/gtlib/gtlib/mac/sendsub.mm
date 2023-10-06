#define _IPP_PRIVATE_STRUCTURES 1
#import <Cocoa/Cocoa.h>
#import <cups/cups.h>
#import <sys/stat.h>
#import <sys/sysctl.h>

#include "gtx.h"
#include "modpal.h"


////////////////////////////////////////
//    内部関数


namespace {


int GetProcessID( const char *name )
{
    //get process list
#define MIB_NAMELEN 4
    int mibname[MIB_NAMELEN] = { CTL_KERN, KERN_PROC, KERN_PROC_ALL, 0}; // all processes
    size_t buffersize = 0;
    
    if( sysctl(mibname, MIB_NAMELEN, NULL, &buffersize, NULL, 0) < 0 ) {
        return -1;
    }
    struct kinfo_proc *procs = (struct kinfo_proc *) malloc(buffersize);
    if( sysctl(mibname, MIB_NAMELEN, procs, &buffersize, NULL, 0) < 0 ) {
        free( procs );
        return -1;
    }
    size_t count = buffersize / sizeof(struct kinfo_proc);
    
    //check exist process
    for( int index = 0; index < count; ++index ) {
        if( strcmp(name, procs[index].kp_proc.p_comm) == 0 ) {
            free( procs );
            return procs[index].kp_proc.p_pid;
        }
    }
    free( procs );
    return -1;
}


}    //namespace


////////////////////////////////////////
//	構造体

struct CSendPrn::Impl
{
	FILE*	m_fp;
	TCHAR	m_szPrinter[MAX_PATH];

    Impl();

    bool IsFileOutput( LPCTSTR szPrinter );
    bool IsFileOutput( void );

    int OpenFileOutput( LPCTSTR szPrinter, GTX_PRINTER_TYPE type );
    int CloseFileOutput( void );
    int WriteFileOutput( BYTE* pBuffer, DWORD dwLength );

    int OpenCups( LPCTSTR szPrinter, LPCTSTR szName );
    int CloseCups( void );
    int WriteCups( BYTE* pBuffer, DWORD dwLength );
};

CSendPrn::Impl::Impl() : m_fp(NULL), m_szPrinter() {};

bool CSendPrn::Impl::IsFileOutput( LPCTSTR szPrinter )
{
    return strstr( szPrinter, "FileOutput" );
}
bool CSendPrn::Impl::IsFileOutput( void )
{
    return m_fp;
}

// FileOutput

int CSendPrn::Impl::OpenFileOutput( LPCTSTR szPrinter, GTX_PRINTER_TYPE type )
{
	const char *viewer = NULL, *path, *ext;
	if( type & TYPE_GT3 ) {
		viewer	= "GT3FileViewer";
		path	= "/library/caches/com.brother.gt3/";
		ext		= "ar3";
	}
	if( type & TYPE_GTX4 ) {
		viewer	= "GTX4FileViewer";
		path	= "/library/caches/com.brother.gtx4/";
		ext		= "arx4";
	}
	if( type & TYPE_GTXpro ) {
		viewer	= "GTXproFileViewer";
		path	= "/library/caches/com.brother.gtxpro/";
		ext		= "arxp";
	}
	if( type & TYPE_GTX6 ) {
		viewer	= "GTX6FileViewer";
		path	= "/library/caches/com.brother.gtx6/";
		ext		= "arx6";
	}
	if( type & TYPE_GTX6SP ) {
		viewer	= "GTX6SPFileViewer";
		path	= "/library/caches/com.brother.gtx6sp/";
		ext		= "arx6e";
	}

	if( viewer == NULL || GetProcessID( viewer ) == -1 ) {
		return -99;
	}

	if( mkdir(path, S_IRWXU|S_IRWXG|S_IRWXO) == 0 ) {
		chmod( path, S_IRWXU|S_IRWXG|S_IRWXO );
	}

	int iJobID = (int) time(NULL);
	char szARP[MAX_PATH] = {0};
	sprintf( szARP, "%s%d.%s", path, iJobID, ext );

	m_fp = fopen(szARP, "wb");
	if( m_fp == NULL ) {
		return -2;
	}

    strcpy( m_szPrinter, szARP );
	return 0;
}

int CSendPrn::Impl::CloseFileOutput( void )
{
	fclose( m_fp );
    chmod( m_szPrinter, S_IRWXU|S_IRWXG|S_IRWXO );
	return 0;
}

int CSendPrn::Impl::WriteFileOutput( BYTE* pBuffer, DWORD dwLength )
{
	size_t result = fwrite( pBuffer, 1, dwLength, m_fp );
	if( result != dwLength ) {
		return -7;
	}
    return 0;
}

// cups

int CSendPrn::Impl::OpenCups( LPCTSTR szPrinter, LPCTSTR szName )
{
    char szPID[1024];
    GTX_SUB_GetPID(szPID, szPrinter);

    //szPiD
	int jobID = cupsCreateJob( CUPS_HTTP_DEFAULT, szPID, szName, 0, nil );
	if( jobID < 0 ) {
		return -1;
	}
	http_status_t status = cupsStartDocument( CUPS_HTTP_DEFAULT, szPID, jobID, NULL, CUPS_FORMAT_AUTO, 1 );
	if( status != HTTP_CONTINUE ) {
		cupsCancelJob2( CUPS_HTTP_DEFAULT, szPID, jobID, 0 );
		return -2;
	}
	strcpy( m_szPrinter, szPrinter );
	return 0;
}

int CSendPrn::Impl::CloseCups( void )
{
	cupsFinishDocument( CUPS_HTTP_DEFAULT, m_szPrinter );
    return 0;
}

int CSendPrn::Impl::WriteCups( BYTE* pBuffer, DWORD dwLength )
{
	int result = cupsWriteRequestData( CUPS_HTTP_DEFAULT, (const char *)pBuffer, (size_t)dwLength );
	if (result != HTTP_STATUS_CONTINUE) {
		return -6;
	}
    return 0;
}


////////////////////////////////////////
//    送信関数

CSendPrn::CSendPrn() : pimpl_(new CSendPrn::Impl())
{}
CSendPrn::~CSendPrn()
{
	Close();
	delete pimpl_;
}

int CSendPrn::Open( LPCTSTR szPrinter, LPCTSTR szName )
{
    GTX_PRINTER_TYPE type = GTX_GetPrinterType( szPrinter );
	if( type & TYPE_FILEOUTPUT ) {
		return pimpl_->OpenFileOutput( szPrinter, type );
	} else {
		return pimpl_->OpenCups( szPrinter, szName );
	}
}

int CSendPrn::Write( BYTE* pBuffer, DWORD dwLength )
{
	if( pimpl_->IsFileOutput() ) {
		return pimpl_->WriteFileOutput( pBuffer, dwLength );
	} else {
		return pimpl_->WriteCups( pBuffer, dwLength );
	}
}

int CSendPrn::Close()
{
	if( pimpl_->IsFileOutput() ) {
		return pimpl_->CloseFileOutput();
	} else {
		return pimpl_->CloseCups();
	}
}


////////////////////////////////////////
//	リソース関数

struct CResFile::Impl
{
	NSData *m_data;
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
    NSString *path = [NSString stringWithUTF8String:szFile];
	NSURL *url = [NSBundle.mainBundle URLForResource:path withExtension:@"arx6"];
    pimpl_->m_data = [NSData dataWithContentsOfURL:url];
	if( pimpl_->m_data == nil)	return -1;

	return 0;
}

int CResFile::Close()
{
    return 0;
}

int CResFile::Size()
{
    return (int)[pimpl_->m_data length];
}

int CResFile::Read( BYTE* pBuffer, DWORD dwSize )
{
	size_t rest = [pimpl_->m_data length] - pimpl_->m_pos;
	if( dwSize > rest ) {
		dwSize = (int)rest;
	}
	BYTE* resume = (BYTE *)[pimpl_->m_data bytes] + pimpl_->m_pos;
	memcpy( pBuffer, resume, dwSize );
	pimpl_->m_pos += dwSize;

	return dwSize;
}
