////////////////////////////////////////////////////////////
//					ArpCmd.cpp
////////////////////////////////////////////////////////////


#include "StdAfx.h"
#include "ArpCmd.h"


////////////////////////////////////////
//	ファイル

TFile::TFile(void)
{
	m_fp = NULL;
}
TFile::~TFile(void)
{
	Close();
}

BOOL TFile::Open(LPCTSTR szFile, UINT nFlags)
{
	LPCTSTR mode = ( nFlags == 0 ) ? _T("rb") : _T("wb");
	m_fp = _tfopen( szFile, mode );
	return	m_fp != NULL;
}
void TFile::Close()
{
	if( m_fp != NULL ) {
		fclose( m_fp );
		m_fp = NULL;
	}
}

UINT TFile::Read(void* buffer, UINT nCount)
{
	return (UINT) fread( buffer, 1, nCount, m_fp );
}
UINT TFile::Write(const void* buffer, UINT nCount)
{
	return (UINT) fwrite( buffer, 1, nCount, m_fp );
}

UINT TFile::Seek(UINT lOffset, UINT nForm)
{
	fseek( m_fp, lOffset, nForm );
	return ftell( m_fp );
}
UINT TFile::GetPosition() const
{
	return ftell( m_fp );
}
UINT TFile::GetLength() const
{
	long pos = ftell( m_fp );
	fseek( m_fp, 0, SEEK_END );
	long end = ftell( m_fp );
	fseek( m_fp, pos, SEEK_SET );
	return end;
}


////////////////////////////////////////
//	バッファ

TByteArray::TByteArray(void)
{
	m_size = 0;
	m_buffer = new BYTE[ sizeMax ];
}
TByteArray::~TByteArray(void)
{
	delete [] m_buffer;
	m_buffer = 0;
	m_size = 0;
}

void TByteArray::Clear()
{
	memset( m_buffer, 0, m_size );
}
void TByteArray::Copy(const TByteArray& src)
{
	memcpy( m_buffer, src.GetData(), sizeMax );
	m_size = src.GetSize();
}
void TByteArray::Copy(const size_t size, const BYTE *data)
{
	m_size = ( size < sizeMax ) ? size : sizeMax;
	memcpy( m_buffer, data, size );
}

size_t TByteArray::GetSize() const
{
	return	m_size;
}
void TByteArray::SetSize(size_t size)
{
	m_size = ( size < sizeMax ) ? size : sizeMax;
}
void TByteArray::RemoveAll()
{
	m_size = 0;
}

BYTE* TByteArray::GetData() const
{
	return	m_buffer;
}
BYTE& TByteArray::operator[](int n)
{
	if( n < 0 || m_size <= n )	return m_buffer[0];
	return	m_buffer[n];
}

BYTE TByteArray::GetByte(int n) const
{
	if( n < 0 || m_size <= n )  return 0;
	return	m_buffer[n];
}
WORD TByteArray::GetWord(int n) const
{
	if( n < 0 || m_size <= n+1 )  return 0;
	return	m_buffer[n]<<8 | m_buffer[n+1];
}
DWORD TByteArray::GetDWord(int n) const
{
	if( n < 0 || m_size <= n+3 )  return 0;
	return	m_buffer[n]<<24 | m_buffer[n+1]<<16 | m_buffer[n+2]<<8 | m_buffer[n+3];
}
void TByteArray::SetByte(int n, BYTE v)
{
	if( n < 0 || m_size <= n )  return;
	m_buffer[n] = (BYTE)( v );
}
void TByteArray::SetWord(int n, WORD v)
{
	if( n < 0 || m_size <= n+1 )  return;
	m_buffer[n  ] = (BYTE)( v>>8 );
	m_buffer[n+1] = (BYTE)( v    );
}
void TByteArray::SetDWord(int n, DWORD v)
{
	if( n < 0 || m_size <= n+3 )  return;
	m_buffer[n  ] = (BYTE)( v>>24 );
	m_buffer[n+1] = (BYTE)( v>>16 );
	m_buffer[n+2] = (BYTE)( v>> 8 );
	m_buffer[n+3] = (BYTE)( v     );
}




////////////////////////////////////////
//	定義

//コマンド
static const BYTE CMD_COMPRESS_HEAD [] = { 0x23, 0x23, 0x00, 0x0B, 0x00, 0x00, 0x00, 0x08 };
static const BYTE CMD_COMPRESS_PARAM[] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const BYTE CMD_LINENO_HEAD   [] = { 0x23, 0x23, 0x00, 0x56, 0x00, 0x00, 0x00, 0x08 };
static const BYTE CMD_LINENO_PARAM  [] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
static const BYTE CMD_INK_HEAD 		[] = { 0x23, 0x23, 0x00, 0x53, 0x00, 0x00, 0x00, 0x88 };
static const BYTE CMD_INK_SIZE		   = 0x88;


////////////////////////////////////////
//	コンストラクタ

CArpCmd::CArpCmd(void)
{
}

CArpCmd::~CArpCmd(void)
{
	Close();
}


////////////////////////////////////////
//	public関数

//ARPファイルを開く
int CArpCmd::Open(LPCTSTR strFile, BOOL bSave)
{
	UINT mode = ( bSave ? (TFile::modeCreate|TFile::modeWrite) : (TFile::modeRead) );

	if( ! m_File.Open( strFile, mode ) ) {
		return	-101;
	}

	return	0;
}
//ARPファイルを閉じる
int CArpCmd::Close()
{
	m_File   .Close();
	m_baHead .RemoveAll();
	m_baParam.RemoveAll();

	return	0;
}

//ARPコマンドの操作
int CArpCmd::Copy(CArpCmd* pArpCmd)
{
	return	CopyCommand( pArpCmd );
}
int	CArpCmd::Read()
{
	return	ReadCommand();
}
int CArpCmd::Write()
{
	return	WriteCommand();
}
int CArpCmd::Write(TByteArray* pBuff)
{
	return	WriteBuff( pBuff );
}
int CArpCmd::Write(CArpCmd* pArpCmd)
{
	return	WriteCommand( pArpCmd );
}
int CArpCmd::WriteCompMode(int nMode)
{
	return	WriteCommand_Compress( nMode );
}
int CArpCmd::WriteLineNo(int nLine)
{
	return	WriteCommand_LineNo( nLine );
}
int CArpCmd::WriteLast()
{
	return	WriteLastNULL();
}


////////////////////////////////////////
//	コマンド

//コマンドのコピー
int CArpCmd::CopyCommand(CArpCmd* pArpCmd)
{
	m_baHead .Copy( pArpCmd->m_baHead  );
	m_baParam.Copy( pArpCmd->m_baParam );

	return	0;
}

//コマンドの読み込み
int CArpCmd::ReadCommand()
{
	int		nRet = 0;

	if( ReadBuff( &m_baHead, 1 ) )
	{
		//コマンド種類
		switch( m_baHead[0] )
		{
		case 0x00:	nRet = ReadNullCommand();	break;
		case 0x1B:	nRet = ReadEscapeCommand();	break;
		case '#':	nRet = ReadArxCommand();	break;
		default:	nRet = -301;				break;
		}
	}
	else	//コマンドなし
	{
		m_baHead .RemoveAll();
		m_baParam.RemoveAll();
	}

	return	nRet;
}
int CArpCmd::ReadNullCommand()
{
	//パラメータ
	m_baParam.RemoveAll();

	//ヘッダ
	for( UINT nSize = 0; TRUE; nSize += 0x100 )
	{
		//先に読み込み
		UINT nMax = ReReadBuff( &m_baHead, nSize+0x100 );

		//NULLだけ取り出す
		for( UINT nLoop = 0; nLoop < 0x100; ++nLoop )
		{
			if( nSize + nLoop >= nMax ) {
				return	nMax;
			}
			if( m_baHead[ nSize + nLoop ] != 0 ) {
				return	ReReadBuff( &m_baHead, nSize + nLoop );
			}
		}
	}

	return	0;
}
int CArpCmd::ReadEscapeCommand()
{
	//ヘッダ
	int	nHeadLen = ReReadBuff( &m_baHead, 5 );
	if( nHeadLen < 5 ) {
		return	-201;
	}

	//パラメータ
	int	nParamLen;
	if( m_baHead[4] == '@' )
	{
		nParamLen = ReadBuff( &m_baParam, 11 );
		if( nParamLen < 11 ) {
			return	-202;
		}
		if( m_baParam[0] == 0x0B || m_baParam[0] == 0x0C )
		{
			nParamLen = ReReadBuff( &m_baParam, 11 + 16 );
			if( nParamLen < 11+16 ) {
				return	-203;
			}
		}
	}
	else	// m_Buff[4] == '$'
	{
		nParamLen = ReadBuff( &m_baParam, 11 );
		if( nParamLen < 11 ) {
			return	-204;
		}
	}

	return	nHeadLen + nParamLen;
}
int CArpCmd::ReadArxCommand()
{
	//ヘッダ
	int	nHeadLen = ReReadBuff( &m_baHead, 8 );
	if( nHeadLen < 8 ) {
		return	-205;
	}

	//パラメータ
	int	nReadLen  = m_baHead[4]<<24 | m_baHead[5]<<16 | m_baHead[6]<<8 | m_baHead[7];
		nReadLen  = ( nReadLen + 3 ) / 4 * 4;
	int	nParamLen = ReadBuff( &m_baParam, nReadLen );
	if( nParamLen < nReadLen ) {
		return	-206;
	}

	return	nHeadLen + nParamLen;
}

//コマンドの書き込み
int CArpCmd::WriteCommand()
{
	WriteBuff( &m_baHead );
	WriteBuff( &m_baParam );

	return	0;
}
int CArpCmd::WriteCommand(CArpCmd* pArpCmd)
{
	WriteBuff( &pArpCmd->m_baHead );
	WriteBuff( &pArpCmd->m_baParam );

	return	0;
}
int CArpCmd::WriteCommand_Compress(int nMode)
{
	m_baHead .Copy( sizeof(CMD_COMPRESS_HEAD ), CMD_COMPRESS_HEAD  );
	m_baParam.Copy( sizeof(CMD_COMPRESS_PARAM), CMD_COMPRESS_PARAM );

	m_baParam.SetByte( 0, nMode );

	WriteBuff( &m_baHead );
	WriteBuff( &m_baParam );

	return	0;
}
int CArpCmd::WriteCommand_LineNo(int nLine)
{
	m_baHead .Copy( sizeof(CMD_LINENO_HEAD ), CMD_LINENO_HEAD  );
	m_baParam.Copy( sizeof(CMD_LINENO_PARAM), CMD_LINENO_PARAM );

	m_baParam.SetWord( 0, nLine );

	WriteBuff( &m_baHead );
	WriteBuff( &m_baParam );

	return	0;
}
int CArpCmd::WriteLastNULL()
{
	#define	AR_FOOTER_NULL_SIZE	2048

	UINT	nSize = AR_FOOTER_NULL_SIZE;
	UINT	nMod  = m_File.GetLength() % AR_FOOTER_NULL_SIZE;
	if( nMod > 0 ) {
			nSize += AR_FOOTER_NULL_SIZE - nMod;
	}
	m_baParam.RemoveAll();
	m_baHead .SetSize( nSize );
	m_baHead .Clear();

	WriteBuff( &m_baHead );

	return	0;
}


////////////////////////////////////////
//	ファイル

//バイト列の読み込み
int CArpCmd::ReadBuff(TByteArray* pBuff, UINT nCount)
{
	pBuff->SetSize( nCount );
	int	nSize = m_File.Read( pBuff->GetData(), nCount );
	if( nSize != nCount ) {
		pBuff->SetSize( nSize );
	}

	return	nSize;
}
int CArpCmd::ReReadBuff(TByteArray* pBuff, UINT nCount)
{
	UINT	nSize = (UINT)pBuff->GetSize();

	//追加読み込み
	if( nSize < nCount )
	{
		pBuff->SetSize( nCount );
		nSize += m_File.Read( pBuff->GetData() + nSize, nCount-nSize );
		if( nSize != nCount ) {
			pBuff->SetSize( nSize );
		}
	}

	//読み込みを戻す
	else if( nSize > nCount )
	{
		pBuff->SetSize( nCount );
		m_File.Seek( nCount-nSize, TFile::seekCurrent );
		nSize = nCount;
	}

	return	nSize;
}

//バイト列の書き込み
int CArpCmd::WriteBuff(TByteArray* pBuff)
{
	return	m_File.Write( pBuff->GetData(), (UINT)pBuff->GetSize() );
}


////////////////////////////////////////
//	インク量の計算

//コンストラクタ
CCmdInk::CCmdInk(void)
{
	memset( dwDots, 0, sizeof(dwDots) );
	dwInkC = dwInkW = 0;
}
CCmdInk::~CCmdInk(void)
{

}

//public関数

//取得
void CCmdInk::GetParam(CArpCmd* pArpCmd)
{
	size_t size = CMD_SIZE( *pArpCmd );

	if( size == 64 )
	{
		for( int i = 0; i < 8; ++i )
		{
			BYTE	c    = GET_BYTE ( *pArpCmd, i*8     );
			dwDots[c][0] = GET_DWORD( *pArpCmd, i*8 + 4 );
		}
	}
	else	//size == 128,136
	{
		for( int i = 0; i < 8; ++i )
		{
			BYTE	c    = GET_BYTE ( *pArpCmd, i*16      );
			dwDots[c][0] = GET_DWORD( *pArpCmd, i*16 +  4 );
			dwDots[c][1] = GET_DWORD( *pArpCmd, i*16 +  8 );
			dwDots[c][2] = GET_DWORD( *pArpCmd, i*16 + 12 );
		}
	}
	if( size > 128 ) {
		dwInkW = GET_DWORD( *pArpCmd, 128 );
		dwInkC = GET_DWORD( *pArpCmd, 132 );
	}
}
void CCmdInk::AddParam(CArpCmd* pArpCmd)
{
	size_t size = CMD_SIZE( *pArpCmd );

	if( size == 64 )
	{
		for( int i = 0; i < 8; ++i )
		{
			BYTE	c     = GET_BYTE ( *pArpCmd, i*8     );
			dwDots[c][0] += GET_DWORD( *pArpCmd, i*8 + 4 );
		}
	}
	else	//size == 128,136
	{
		for( int i = 0; i < 8; ++i )
		{
			BYTE	c     = GET_BYTE ( *pArpCmd, i*16      );
			dwDots[c][0] += GET_DWORD( *pArpCmd, i*16 +  4 );
			dwDots[c][1] += GET_DWORD( *pArpCmd, i*16 +  8 );
			dwDots[c][2] += GET_DWORD( *pArpCmd, i*16 + 12 );
		}
	}
	if( size > 128 ) {
		dwInkW += GET_DWORD( *pArpCmd, 128 );
		dwInkC += GET_DWORD( *pArpCmd, 132 );
	}
}
void CCmdInk::AddParam_MMB(CArpCmd* pArpCmd, BYTE byHighlight)
{
	size_t size = CMD_SIZE( *pArpCmd );

	int	nRate1 = byHighlight > 7 ? 2 : 1;
	int	nRate2 = byHighlight > 5 ? 4 : 3;
	
	if( size == 64 )
	{
		for( int i = 0; i < 8; ++i )
		{
			BYTE	c = GET_BYTE( *pArpCmd, i*8 );
			if( c < 4 ) {
				dwDots[c][0]  = ( dwDots[c][0] * nRate1 + GET_DWORD( *pArpCmd, i*8 + 4 ) * nRate2 ) / ( nRate1 + nRate2 );
			} else {
				dwDots[c][0] += GET_DWORD( *pArpCmd, i*8 + 4 );
			}
		}
	}
	else	//size == 128,136
	{
		for( int i = 0; i < 8; ++i )
		{
			BYTE	c     = GET_BYTE ( *pArpCmd, i*16      );
			if( c < 4 ) {
				dwDots[c][0]  = ( dwDots[c][0] * nRate1 + GET_DWORD( *pArpCmd, i*16 +  4 ) * nRate2 ) / ( nRate1 + nRate2 );
				dwDots[c][1]  = ( dwDots[c][1] * nRate1 + GET_DWORD( *pArpCmd, i*16 +  8 ) * nRate2 ) / ( nRate1 + nRate2 );
				dwDots[c][2]  = ( dwDots[c][2] * nRate1 + GET_DWORD( *pArpCmd, i*16 + 12 ) * nRate2 ) / ( nRate1 + nRate2 );
			} else {
				dwDots[c][0] += GET_DWORD( *pArpCmd, i*16 +  4 );
				dwDots[c][1] += GET_DWORD( *pArpCmd, i*16 +  8 );
				dwDots[c][2] += GET_DWORD( *pArpCmd, i*16 + 12 );
			}
		}
	}
	if( size > 128 ) {
		dwInkW  = ( dwInkW * nRate1 + GET_DWORD( *pArpCmd, 128 ) * nRate2 ) / ( nRate1 + nRate2 );
		dwInkC += GET_DWORD( *pArpCmd, 132 );
	}
}

//設定
void CCmdInk::SetParam(CArpCmd* pArpCmd)
{
	pArpCmd->m_baHead .Copy( sizeof(CMD_INK_HEAD), CMD_INK_HEAD );
	pArpCmd->m_baParam.SetSize( CMD_INK_SIZE );
	pArpCmd->m_baParam.Clear();

	for( int i = 0; i < 8; ++i )
	{
		SET_BYTE ( *pArpCmd, i*16     , i            );
		SET_DWORD( *pArpCmd, i*16 +  4, dwDots[i][0] );
		SET_DWORD( *pArpCmd, i*16 +  8, dwDots[i][1] );
		SET_DWORD( *pArpCmd, i*16 + 12, dwDots[i][2] );
	}
	SET_DWORD( *pArpCmd, 128, dwInkW );
	SET_DWORD( *pArpCmd, 132, dwInkC );
}
void CCmdInk::SetColor(CArpCmd* pArpCmd)
{
	pArpCmd->m_baHead .Copy( sizeof(CMD_INK_HEAD), CMD_INK_HEAD );
	pArpCmd->m_baParam.SetSize( CMD_INK_SIZE );
	pArpCmd->m_baParam.Clear();

	for( int i = 0; i < 4; ++i )
	{
		SET_BYTE ( *pArpCmd, i*16     , i            );
	}
	for( int i = 4; i < 8; ++i )
	{
		SET_BYTE ( *pArpCmd, i*16     , i            );
		SET_DWORD( *pArpCmd, i*16 +  4, dwDots[i][0] );
		SET_DWORD( *pArpCmd, i*16 +  8, dwDots[i][1] );
		SET_DWORD( *pArpCmd, i*16 + 12, dwDots[i][2] );
	}
	SET_DWORD( *pArpCmd, 132, dwInkC );
}
void CCmdInk::SetWhite(CArpCmd* pArpCmd)
{
	pArpCmd->m_baHead .Copy( sizeof(CMD_INK_HEAD), CMD_INK_HEAD );
	pArpCmd->m_baParam.SetSize( CMD_INK_SIZE );
	pArpCmd->m_baParam.Clear();

	for( int i = 0; i < 4; ++i )
	{
		SET_BYTE ( *pArpCmd, i*16     , i            );
		SET_DWORD( *pArpCmd, i*16 +  4, dwDots[i][0] );
		SET_DWORD( *pArpCmd, i*16 +  8, dwDots[i][1] );
		SET_DWORD( *pArpCmd, i*16 + 12, dwDots[i][2] );
	}
	for( int i = 4; i < 8; ++i )
	{
		SET_BYTE ( *pArpCmd, i*16     , i            );
	}
	SET_DWORD( *pArpCmd, 128, dwInkW );
}

void CCmdInk::SetFinishing(CArpCmd* pArpCmd)
{
	pArpCmd->m_baHead.Copy(sizeof(CMD_INK_HEAD), CMD_INK_HEAD);
	pArpCmd->m_baParam.SetSize(CMD_INK_SIZE);
	pArpCmd->m_baParam.Clear();

	for (int i = 0; i < 4; ++i)
	{
		SET_BYTE(*pArpCmd, i * 16, i);
	}
	for (int i = 4; i < 8; ++i)
	{
		SET_BYTE(*pArpCmd, i * 16, i);
		SET_DWORD(*pArpCmd, i * 16 + 4, dwDots[i][0]);
		SET_DWORD(*pArpCmd, i * 16 + 8, dwDots[i][1]);
		SET_DWORD(*pArpCmd, i * 16 + 12, dwDots[i][2]);
	}
	SET_DWORD(*pArpCmd, 132, dwInkC);
}


