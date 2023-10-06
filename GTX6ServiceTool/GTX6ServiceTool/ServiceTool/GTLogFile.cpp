// GTLogFile.cpp: CGTLogFile クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "BGJPrinter.h"
#include "BGJServTool.h"
#include "MemEntry.h"
#include "EEPFile.h"
#include "GTLogFile.h"
#include "zlib/zlib.h"
#include "Language.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define LOG_BUFFER_DWORD_SIZE (1024*64) // 1024*256 byte
#define EDGE_VAL 0x45644765 // EdGe big endian value
#define LOG_BODY_SIZE 4
#define DATA_SIZE_MASK 0x001FFF00
#define TYPE_MASK 0x000000F8
#define LEVEL_MASK 0x00000007

#define WRITE_BUFFER_SIZE (1024*8)

#define SIZE_TAG_NAME	4
#define SIZE_TAG_SIZE	4
#define SIZE_FILE_ID	8
#define SIZE_PRINTER_DATE 4
#define SIZE_PC_DATE 12
#define SIZE_HEADER_RESERVED	12
#define SIZE_FILE_HEADER (SIZE_FILE_ID+SIZE_PRINTER_DATE+SIZE_PC_DATE+12)

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CGTLogFile::CGTLogFile()
{
	m_pFile = NULL;
	m_pLogBuff = NULL;
	m_pBuff = NULL;
	m_lBuffSize = 0;
	m_lBuffCount = 0;
	m_bZlg = FALSE;
}

CGTLogFile::~CGTLogFile()
{
	Close();
}

bool CGTLogFile::CreateFile(LPCTSTR pszFileName)
{
	bool bRet = false;
	m_pFile = _tfopen( pszFileName, _T("w+b") );
	if( m_pFile != NULL ){
		m_csFileName = pszFileName;
		m_bReadMode = false;
		bRet = true;
	}else{
//		CQErr::MsgBoxLastError();
	}
	return bRet;
}

bool CGTLogFile::MakeHeader(long lPrinterTime)
{
	bool bRet = true;
	if( (m_pFile != NULL) && (m_bReadMode == false) ){
		CTime t = CTime::GetCurrentTime();
		CString cs = t.Format( _T("%d%m%Y%H%M") );
		BYTE buff[SIZE_FILE_HEADER];
		BYTE* pB = buff; 
		::ZeroMemory( buff, sizeof(buff) );
		*pB++ = 'G';
		*pB++ = 'T';
		*pB++ = '5';
		*pB++ = '4';
		*pB++ = '1';
		*pB++ = 'L';
		*pB++ = 'O';
		*pB++ = '1';
		*pB++ = (BYTE)(lPrinterTime >> 24);
		*pB++ = (BYTE)(lPrinterTime >> 16);
		*pB++ = (BYTE)(lPrinterTime >> 8);
		*pB++ = (BYTE)(lPrinterTime);
		for( int i=0; i<SIZE_HEADER_RESERVED; ++i ){
			*pB++ = cs[i];
		}
		size_t lSize = fwrite( buff, 1, sizeof(buff), m_pFile );
		if( lSize != sizeof(buff) ){
			bRet = false;
//			CQErr::MsgBoxLastError();
		}
	}else{
		bRet = false;
	}
	return bRet;
}

bool CGTLogFile::WriteTagHeader(LPCTSTR pszTagName, long lSize)
{
	bool bRet = true;
	if( (m_pFile != NULL) && (m_bReadMode == false) ){
		m_nTagDataSize = lSize;
		BYTE b[SIZE_TAG_NAME + SIZE_TAG_SIZE];
		BYTE* pb = b;
		*pb++ = pszTagName[0];
		*pb++ = pszTagName[1];
		*pb++ = pszTagName[2];
		*pb++ = pszTagName[3];
		*pb++ = (BYTE)(lSize>>24);
		*pb++ = (BYTE)(lSize>>16);
		*pb++ = (BYTE)(lSize>>8);
		*pb++ = (BYTE)(lSize);
		size_t lSize = fwrite( b, 1, sizeof(b), m_pFile );
		if( lSize != sizeof(b) ){
			bRet = false;
//			CQErr::MsgBoxLastError();
		}
	}else{
		bRet = false;
	}
	return bRet;
}

bool CGTLogFile::WriteData(long lSize, void *pData)
{
	bool bRet = true;
	if( (m_pFile != NULL) && (m_bReadMode == false) ){
		size_t lWriteSize = fwrite( pData, 1, lSize, m_pFile );
		if( lWriteSize != (size_t)lSize ){
			bRet = false;
//			CQErr::MsgBoxLastError();
		}
	}else{
		bRet = false;
	}
	return bRet;
}

bool CGTLogFile::Close()
{
	bool bRet = true;
	if( m_pBuff ){
		if( m_lBuffCount > 0 ){
			WriteData( m_lBuffCount, m_pBuff );
			fflush( m_pFile );
		}
		delete [] m_pBuff;
		m_pBuff = NULL;
	}
	if( m_pFile != NULL ){
		fclose( m_pFile );
		m_pFile = NULL;
	}else{
		bRet = false;
	}
	if( m_pLogBuff ){
		delete [] m_pLogBuff;
		m_pLogBuff = NULL;
	}
	if( m_bZlg )
	{
		DeleteFile( m_csFileName );
		m_bZlg = FALSE;
	}
	m_csFileName.Empty();
	return bRet;
}

bool CGTLogFile::WriteTagData(LPCTSTR pszTagName, long lSize, void *pData)
{
	bool bRet = true;
	long lAlignmentSize = (((lSize+3)/4))*4;
	long lAddSize = lAlignmentSize - lSize;
	if( (bRet = WriteTagHeader( pszTagName, lAlignmentSize )) ){
		if( (bRet = WriteTagData( lSize, pData ) ) ){
			if( lAddSize > 0 ){
				BYTE b[4] = {0,0,0,0};
				bRet = WriteTagData( lAddSize, b );
			}
		}
	}
	return bRet;
}

//ログファイルのオープン
int CGTLogFile::Open(LPCTSTR pszFileName)
{
	int iRet = -1; // 1:OK, 0:Not Log File, -1:Error
	Close();
	m_pFile = _tfopen( pszFileName, _T("rb") );
	if( m_pFile != NULL ){
		iRet = 0;
		m_csFileName = pszFileName;
		m_bReadMode = true;
		char cID[SIZE_FILE_ID+1];
		for( int i=0; i<sizeof(cID); ++i ){
			cID[i] = 0;
		}
		size_t nSize = fread( cID, 1, SIZE_FILE_ID, m_pFile );
		if( nSize == SIZE_FILE_ID )
		{
			CString cs = cID;
			if( cs == _T("GTXLG1XX")) //本当は0 が正しいけど　Oでも開くようにした
			{//ノーマル
				iRet = 1;
			}else if( cs == _T("GTXLG1ZL") )
			{//圧縮形式
				iRet = UnCompZlgFile(); //解凍してオープン
			}
		}
	}else{
//		CQErr::MsgBoxLastError();
	}
	return iRet;
}

//Zlgファイルを解凍する
int CGTLogFile::UnCompZlgFile()
{
	int iRet = 1;// 1:OK, 0:Not Log File, -1:Error
	FILE* fpTmp = _tfopen( m_csFileName + _T(".tjg") , _T("wb") );//tjgは被らないだろう拡張子
	if( fpTmp == NULL )
	{
		iRet = -2;
	}else
	{
		//ファイル識別ID"GT782LZ1"後のデータを取り出して　m_csFileName + ".tjg"のファイルを作成する
		//m_pFileの位置はファイル識別IDの後を指している
		BYTE byBuff[1000];
		size_t nLen;
		for( ;iRet >= 0 ; )
		{
			nLen = fread( byBuff, 1, sizeof(byBuff), m_pFile );
			if( ferror(m_pFile) )
			{
				iRet = -3;
			}else if( nLen == 0 )
			{
				break;
			}else
			{
				if( fwrite( byBuff , 1 , (unsigned)nLen , fpTmp ) != (int)nLen )
				{
					iRet = -4;
				}
			}
		}
		fclose( fpTmp );
		fclose( m_pFile );
		if( iRet >= 0 )
		{//ファイル識別IDなしの純粋なZlibファイルを解凍する　解凍後のファイル名はm_csFileName + ".bgl"
			iRet = UnCompZlib( m_csFileName + _T(".tjg") , m_csFileName + _T(".bgl") );//bglも被らないだろう拡張子
		}
		DeleteFile( m_csFileName + _T(".tjg") );//Zlibファイルの削除
		if( iRet >= 0 )
		{
			iRet = Open( m_csFileName + _T(".bgl") );//解凍ファイルで再びOpenへ
			m_bZlg = TRUE;//Open()の中にClose()があるので、m_bZlgはOpenの後で操作する
		}
	}
	return iRet;
}

#define COMP_BUFF_SIZE 16384
//Zlibファイルを解凍し、名前strUnZlibのファイルを作る
int CGTLogFile::UnCompZlib( CString strMoto , CString strUnZlib )
{
	ATL::CW2A szMoto(strMoto);
	ATL::CW2A szUnZlib(strUnZlib);
	int iRet = 0;
    FILE  *fpDst;
    gzFile pgzSrc;
    pgzSrc = gzopen( szMoto, "rb" );
    if( pgzSrc != NULL ){
		fpDst = fopen( szUnZlib, "wb" );
		if( fpDst != NULL ){
			char bBuff[ COMP_BUFF_SIZE ];
			int nLen;
			for(;iRet >= 0 ; ){
				nLen = gzread( pgzSrc, bBuff, sizeof(bBuff) );//解凍して読み込み
				if( nLen < 0 ){
					iRet = -5;
				}else if( nLen == 0 ){
					break;
				}else{
					if( (int)fwrite( bBuff, 1, (unsigned)nLen, fpDst ) != nLen ){
						iRet = -6;
					}
				}
			}
			fclose( fpDst );
			if( gzclose( pgzSrc ) != Z_OK){
				iRet = -7;
			}
		}else iRet = -8;
	}else iRet = -9;

	return iRet;
}

bool CGTLogFile::ReadTagHeaderAndSeek(LPCTSTR pszTagName, long *plSize)
{
	bool bRet = true;
	if( m_pFile != NULL ){
		long lPos = SIZE_FILE_HEADER;
		if( fseek( m_pFile, lPos, SEEK_SET ) == 0 ){
			bool bContinue = true;
			while( bContinue && bRet ){
				BYTE b[SIZE_TAG_NAME + SIZE_TAG_SIZE];
				size_t nSize = fread( b, 1, sizeof(b), m_pFile );
				if( nSize == sizeof(b) ){
					lPos += sizeof(b);
					CString cs;
					DWORD dw;
					cs += b[0];
					cs += b[1];
					cs += b[2];
					cs += b[3];
					dw = ((DWORD)b[4]<<24)|((DWORD)b[5]<<16)|((DWORD)b[6]<<8)|b[7];
					if( cs == pszTagName ){
						*plSize = (long)dw;
						bContinue = false;
					}else if( cs == _T("ENDF") ){
						bContinue = false;
						bRet = false;
					}else{
						lPos += dw;
						if( fseek( m_pFile, lPos, SEEK_SET ) == 0 ){
							;
						}else{
							bRet = false;
//							CQErr::MsgBoxLastError();
						}
					}
				}else{
					bRet = false;
//					CQErr::MsgBoxLastError();
				}
			}
		}else{
			bRet = false;
//			CQErr::MsgBoxLastError();
		}
	}else{
		bRet = false;
	}
	return bRet;
}

bool CGTLogFile::WriteEndTag()
{
	bool bRet = true;
	bRet = WriteTagHeader(_T("ENDF"), 0 );
	return bRet;
}

int CGTLogFile::Open(LPCTSTR pszFileName, CString &csPCDate)
{
	int iRet = 0; // 1:OK, 0:Not Log File, -1:Error
	if( (iRet = Open( pszFileName ) ) == 1 ){
		const size_t cnReadSize = SIZE_PRINTER_DATE+SIZE_PC_DATE+SIZE_HEADER_RESERVED;
		BYTE b[cnReadSize];
		if( fread( b, 1, cnReadSize, m_pFile ) == cnReadSize ){
			DWORD lPrinterTime = ((DWORD)b[0]<<24)|((DWORD)b[1]<<16)|((DWORD)b[2]<<8)|b[3];
			
			csPCDate.Empty();
			for( int i=0; i<SIZE_PC_DATE; ++i ){
				csPCDate += b[i+SIZE_PRINTER_DATE];
			}
		}else{
			iRet = -1;
//			CQErr::MsgBoxLastError();
		}
	}
	return iRet;
}

bool CGTLogFile::ReadData(long nSize, void *pData)
{
	bool bRet = true;
	if( (m_pFile != NULL)&&(m_bReadMode) ){
		size_t nReaded = fread( pData, 1, nSize, m_pFile );
		if( (size_t)nSize == nReaded ){
			;
		}else{
			bRet = false;
		}
	}else{
		bRet = false;
	}
	return bRet;
}

bool CGTLogFile::ReadTagData(LPCTSTR pszTagName, long nAreaSize, void *pData, long *pnReaded)
{
	bool bRet = true;
	long nSize = 0;
	if( (bRet = ReadTagHeaderAndSeek( pszTagName, &nSize ) ) ){
		if( nSize <= nAreaSize ){
			if( (nAreaSize > 0)&&(pData != NULL) ){
				if( (bRet = ReadData( nSize, pData ) ) ){
					*pnReaded = nSize;
				}
			}
		}else if( pnReaded != NULL ){
			*pnReaded = nSize;
		}
	}
	return bRet;
}

bool CGTLogFile::Create(LPCTSTR pszFileName)
{
	bool bRet = false;
	if( (bRet = CreateFile( pszFileName ) )){
		bRet = MakeHeader( 0 );
	}
	return bRet;
}

bool CGTLogFile::OpenLog( long *plEntryCount  )
{
	bool bRet = false;
	if( (m_pFile != NULL)&&(m_bReadMode) )
	{
		long nSize = 0;

		TCHAR* pTag = _T("LGDT");//ログのタグ

		if( ReadTagHeaderAndSeek( pTag , &nSize ) )
		{
			if( (nSize > 0)&&((nSize%4) == 0) ){
				m_lLogEntryCount = 0;//LOGDデータの項目数
				m_lLogTopPos = ftell( m_pFile );//ログ全体の中のLOGDの位置
				m_lLogCurPos = m_lLogTopPos;//現在の位置
				m_lLogLastPos = m_lLogTopPos + nSize;//LOGDデータの最後の位置
				m_pLogBuff = new BYTE[LOG_BUFFER_DWORD_SIZE*4];
				m_lLogReadDWSize = 0;
				m_lLogReadDWOffset = 0;
				m_lLogDWSize = nSize/4;//LOGDデータのサイズ/4
				m_lLogSize = nSize;//LOGDデータのサイズ
				m_lLogStartPos = m_lLogTopPos;
				m_lLogReadedDWSize = 0;
				if( SearchNewestLogPos( &m_lLogEntryCount ) )
				{
					m_bLogOpened = true;
					if( LogSeekTop() )
					{
						bRet = true;
						if( plEntryCount )
						{
							*plEntryCount = m_lLogEntryCount;
						}
					}
				}
			}else
			{
				LangAfxMsgBox( IDS_ERR_BUG , -150 );
				//"Error: Log data is 0 or not 4 byte alignment"
			}
		}
	}
	return bRet;
}

bool CGTLogFile::SearchNewestLogPos( long *plEntryCount )
{
	bool bRet = true;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	*plEntryCount = 0;
	DWORD dwTime = 0;
	DWORD dwMilliSec = 0;
	long lStartDWOffset = 0;
	long lDWOffset = 0;
	long lTempTopDWOffset = 0;
	DWORD lMilliSec = 0;
	long lDataSize = 0;
	enum { eElse=0, eDate=1, eAttr=2, eCode=3, eData=4, eAttrSameTime=5 } eMode;
	eMode = eElse;
	bool bNeedInitMillisec = false;
//	DWORD dwNormalTimeMax = GetNormalDateValMax();
	DWORD dw = 0;

	while( lDWOffset < (long)m_lLogDWSize )
	{
		if( ReadLogDWORD( &dw ) == 1 )
		{
			switch( eMode )
			{
			case eElse:
				if( dw == EDGE_VAL )
				{//EDGEを探す
					eMode = eDate;
					lTempTopDWOffset = lDWOffset;
					*plEntryCount += 1;
				}
				break;
			case eDate:
			//	if( dw <= dwNormalTimeMax )
				{ // check illegal date value 0x37000000==10/09/2029
					if( dw == dwTime )
					{
						eMode = eAttrSameTime;
					}else
					{
						if( dw > dwTime )
						{
							dwTime = dw;
							lStartDWOffset = lTempTopDWOffset;
							bNeedInitMillisec = true;
//	{	CString cs; cs.Format( "Time:%08X, dwOff:%08X, Off:%08X\n", dw, lStartDWOffset, m_lLogReadBuffTopOffset+ m_lLogReadDWOffset*4 );
//	::OutputDebugString( (LPCTSTR)cs ); }
						}
						eMode = eAttr;
					}
			/*	}else
				{
					eMode = eElse;	*/
				}
				break;
			case eAttrSameTime:
				if( lMilliSec < (dw & 0xFFE00000) )
				{
					lMilliSec = dw & 0xFFE00000;
					lStartDWOffset = lTempTopDWOffset;
				}
				// NO break;
			case eAttr:
				if( bNeedInitMillisec )
				{
					lMilliSec = dw & 0xFFE00000;
					bNeedInitMillisec = false;
				}
				lDataSize = dw & DATA_SIZE_MASK;
				lDataSize >>= 8;
				if( (lDataSize % 4)!= 0){
					//CString cs;
					//cs.Format( "Error:DataSize is not 4byte-aligned, offset=0x%0X", m_lLogReadBuffTopOffset+ m_lLogReadDWOffset*4 );
					//CQErr::Error( cs );
					lDataSize = 0;
					//bRet = false;
				}
				eMode = eCode;
				break;
			case eCode:
				if( lDataSize == 0 )
				{
					eMode = eElse;
				}else
				{
					eMode = eData;
				}
				break;
			case eData:
				lDataSize -= 4;
				if( lDataSize > 0 )
				{
					;
				}else if( lDataSize < 0 )
				{
					LangAfxMsgBox( IDS_ERR_BUG , -151 , 
						(DWORD)m_lLogReadBuffTopOffset , (DWORD)m_lLogReadDWOffset );
					//Error:DataSize is not 4byte-aligned, offset=%d", 
					//			m_lLogReadBuffTopOffset+ m_lLogReadDWOffset*4 );
					bRet = false;
				}else
				{
					eMode = eElse;
				}
				break;
			}
		}else
		{
			LangAfxMsgBox( IDS_ERR_BUG , -152 );
			//Error: Read Log count mismatch" );

			lDWOffset = m_lLogDWSize;
			bRet = false;
		}
		lDWOffset += 1;
	}
	if( bRet )
	{
		// Now, lStartDWOffset points newest log position

		m_lLogStartPos = lStartDWOffset*4 + m_lLogTopPos;
	}
	return bRet;
}

int CGTLogFile::ReadLogDWORD( DWORD* pdwData )
{
	// return 1:Normal read, 0:data end, -1:Error
	int iRet = -1;
	BYTE* pd;
	if( m_lLogReadedDWSize < m_lLogDWSize )
	{
		bool bRet = true;
		if( m_lLogReadDWSize <= m_lLogReadDWOffset )
		{
			bRet = FillLogBuff();
		}

		if( bRet )
		{
			pd = &m_pLogBuff[m_lLogReadDWOffset*4];
			*pdwData = (DWORD(pd[0])<<24) | (DWORD(pd[1])<<16) | 
							(DWORD(pd[2])<<8) | pd[3];
			m_lLogReadDWOffset += 1;
			m_lLogReadedDWSize += 1;
			iRet = 1;
		}
	}else
	{
		iRet = 0;
		
	}

	return iRet;
}

bool CGTLogFile::FillLogBuff()
{
	bool bRet = true;
	long nReadSize = LOG_BUFFER_DWORD_SIZE*4;
	long lLeftLogDWSize = m_lLogDWSize - m_lLogReadedDWSize;
	if( nReadSize >= (lLeftLogDWSize*4) ){
		nReadSize = (lLeftLogDWSize*4);
	}
	if( m_lLogLastPos <= m_lLogCurPos ){
		m_lLogCurPos = m_lLogTopPos;
		fseek( m_pFile, m_lLogCurPos, SEEK_SET );
	}
	if( (m_lLogCurPos + nReadSize) > m_lLogLastPos ){
		nReadSize = m_lLogLastPos - m_lLogCurPos;
	}
	long lRead = fread( m_pLogBuff, 1, nReadSize, m_pFile );
	if( lRead == nReadSize ){
		m_lLogReadBuffTopOffset = m_lLogCurPos;
		m_lLogCurPos += nReadSize;
		m_lLogReadDWSize = nReadSize/4;
		m_lLogReadDWOffset = 0;
	}else{
//		CQErr::MsgBoxLastError();
		bRet = false;
	}
	return bRet;
}

bool CGTLogFile::LogSeekTop()
{
	bool bRet = false;
	if( (m_pFile != NULL)&&(m_bReadMode)&&(m_bLogOpened) ){
		m_lLogReadDWSize = m_lLogReadDWOffset = 0;
		if( fseek( m_pFile, m_lLogStartPos, SEEK_SET ) == 0 ){
			m_lLogCurPos = m_lLogStartPos;
			m_lLogReadedDWSize = 0;
			CGTLogEntry cLog;
			if( ReadLogEntry( cLog ) ){
				// Now Nest entry is oldest log, reset parameter
				m_lLogStartPos += m_lLogReadedDWSize*4;
				if( m_lLogStartPos >= m_lLogLastPos ){
					m_lLogStartPos = (m_lLogLastPos - m_lLogStartPos) + m_lLogTopPos;
				}
				m_lLogReadDWSize = m_lLogReadDWOffset = 0;
				m_lLogCurPos = m_lLogStartPos;
				m_lLogReadedDWSize = 0;
				if( fseek( m_pFile, m_lLogStartPos, SEEK_SET ) == 0 ){
					bRet = true;
				}
			}
		}
	}
	return bRet;
}

int CGTLogFile::ReadLogEntry(CGTLogEntry &cEntry)
{
	int iRet = -1; // Return value -1:Error, 0:End of data, 1:Read success
	bool bCont = true;
	int iStat = 1;
	DWORD dw;
	while( bCont ){
		iStat = ReadLogDWORD( &dw );
		if( iStat == 1 ){
			if( dw == EDGE_VAL ){
				bCont = false;
				iRet = 1;
			}
		}else{
			iRet = iStat;
			bCont = false;
		}
	}
	if( iRet == 1 ){
		if( (iRet = ReadLogDWORD( &dw ))==1 ){
			cEntry.m_dwTime = dw;
			if( (iRet = ReadLogDWORD( &dw ))==1 ){
				cEntry.m_nMillisec = dw >> 21;
				cEntry.m_nDataSize = (dw & DATA_SIZE_MASK) >> 8;
				cEntry.m_nType = (dw & TYPE_MASK)>>3;
				cEntry.m_nLevel = dw & LEVEL_MASK;
				if( (iRet = ReadLogDWORD( &dw ))==1 ){
					cEntry.m_nCode = dw;
					BYTE* pData = NULL;
					if( ReadLogExtData( cEntry.m_nDataSize, &pData ) ){
						cEntry.SetExtData( pData );
					}
				}
			}
		}
	}
	return iRet;
}


bool CGTLogFile::ReadLogExtData(int nDataSize, BYTE **ppData)
{
	bool bRet = true;
	if( nDataSize > 0 ){
		BYTE* pData = new BYTE[ nDataSize + 4 ];
		BYTE* p = pData;
		int nReadCount = nDataSize / 4;
		for( int i=0; (i<nReadCount)&&(bRet); ++i ){
			DWORD dw;
			if( ReadLogDWORD( &dw ) == 1 ){
				*p++ = (BYTE)(dw>>24);
				*p++ = (BYTE)(dw>>16);
				*p++ = (BYTE)(dw>>8);
				*p++ = (BYTE)(dw);
			}else{
				bRet = false;
			}
		}
		if( bRet ){
			*ppData = pData;
		}else{
			delete [] pData;
		}
	}else{
		bRet = false;
	}
	return bRet;
}

bool CGTLogFile::OpenLogDirectDebug(LPCTSTR pszFileName)
{
	bool bRet = false;
	Close();
	m_pFile = _tfopen( pszFileName, _T("rb") );
	if( m_pFile != NULL ){
		m_lLogEntryCount = 0;
		m_csFileName = pszFileName;
		m_bReadMode = true;
		m_lLogTopPos = 0;
		m_lLogCurPos = m_lLogTopPos;
		fseek( m_pFile, 0, SEEK_END );
		m_lLogLastPos = ftell( m_pFile );
		fseek( m_pFile, 0, SEEK_SET );
		long nSize = m_lLogLastPos - m_lLogTopPos;
		m_pLogBuff = new BYTE[LOG_BUFFER_DWORD_SIZE*4];
		m_lLogReadDWSize = 0;
		m_lLogReadDWOffset = 0;
		m_lLogDWSize = nSize/4;
		m_lLogSize = nSize;
		m_lLogStartPos = m_lLogTopPos;
		m_lLogReadedDWSize = 0;
		if( SearchNewestLogPos( &m_lLogEntryCount ) ){
			m_bLogOpened = true;
			if( LogSeekTop() ){
				bRet = true;
			}
		}
	}else{
//		CQErr::MsgBoxLastError();
	}
	return bRet;

}

bool CGTLogFile::UpdateTagSize(LPCTSTR pszTagName, long lSize)
{
	bool bRet = true;
	if( (m_pFile != NULL) && (m_bReadMode == false) ){
		WriteFlush();
		fflush( m_pFile );
		long lCurPos = ftell( m_pFile );
		long lWork = 0;
		if( (bRet = ReadTagHeaderAndSeek( pszTagName, &lWork ) )){
			if( fseek( m_pFile, - (SIZE_TAG_NAME + SIZE_TAG_SIZE), SEEK_CUR ) ==0 ){
				if( (bRet = WriteTagHeader( pszTagName, lSize ) )){
					fseek( m_pFile, lCurPos, SEEK_SET );
				}
			}else{
				bRet = false;
			}
		}
	}
	return bRet;
}

bool CGTLogFile::WriteOneByte(BYTE b)
{
	bool bRet = false;
	if( (m_pFile != NULL) && (m_bReadMode == false) ){
		if( m_pBuff == NULL ){
			m_pBuff = new BYTE[WRITE_BUFFER_SIZE];
			m_lBuffSize = WRITE_BUFFER_SIZE;
			m_lBuffCount = 0;
		}
		if( m_pBuff ){
			m_pBuff[m_lBuffCount] = b;
			m_lBuffCount += 1;
			bRet = true;
			if( m_lBuffCount >= m_lBuffSize ){
				if( WriteData( m_lBuffCount, m_pBuff ) ){
					m_lBuffCount = 0;
				}else{
					bRet = false;
				}
			}
		}
	}
	return bRet;
}

bool CGTLogFile::WriteFlush()
{
	bool bRet = true;
	if( (m_pFile != NULL) && (m_bReadMode == false) ){
		if( m_pBuff ){
			if( m_lBuffCount > 0 ){
				bRet = WriteData( m_lBuffCount, m_pBuff );
				m_lBuffCount = 0;
			}
		}
	}else{
		bRet = false;
	}
	return bRet;
}

bool CGTLogFile::WriteTagData(long lSize, void *pData)
{
	bool bRet = true;
	if( (m_pFile != NULL) && (m_bReadMode == false) ){
		if( m_nTagDataSize >= lSize ){
			m_nTagDataSize -= lSize;
			bRet = WriteData( lSize, pData );
		}else{
			bRet = false;
		}
	}else{
		bRet = false;
	}
	return bRet;
}

bool CGTLogFile::ReadTagString(LPCTSTR pszTagName, CString &cStr)
{
	bool bRet = true;
	long nSize = 0;
	CByteArray buf;

	//メモリ確保
	if (!ReadTagData(pszTagName, 0, NULL, &nSize))
		return	FALSE;

	if (nSize <= 0)
		return	FALSE;

	buf.SetSize(nSize);

	//データ
	if (!ReadTagData(pszTagName, nSize, buf.GetData(), &nSize))
		return	FALSE;

	cStr = buf.GetData();
	return bRet;
}

long CGTLogFile::GetLogEntryCount()
{
	return m_lLogEntryCount;
}

DWORD CGTLogFile::GetNormalDateValMax()
{
	DWORD dwRet = 0;
	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	DWORD dwInternal = (DWORD)pApp->GetCurrentGMTSecond();
	dwRet = dwInternal + (60*60*24*365); // + 1 year
	return dwRet;
}
