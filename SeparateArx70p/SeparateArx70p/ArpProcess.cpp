////////////////////////////////////////////////////////////
//					ArpProcess.cpp
////////////////////////////////////////////////////////////


#include "StdAfx.h"
#include <climits>
#include "ArpProcess.h"


////////////////////////////////////////
//	定義

#define	NO_LINE	INT_MAX


////////////////////////////////////////
//	２つのARPを、１つに重ねる

CStackArp::CStackArp(void)
{

}
CStackArp::~CStackArp(void)
{
	Close();
}

int CStackArp::Open(LPCTSTR szIn1, LPCTSTR szIn2, LPCTSTR szOut)
{
	int	nRet = m_Inpt1.Open( szIn1, FALSE );
	if( nRet < 0 )	return -101;

	nRet = m_Inpt2.Open( szIn2, FALSE );
	if( nRet < 0 )	return -102;

	nRet = m_Stack.Open( szOut, TRUE  );
	if( nRet < 0 )	return -103;

	return	0;
}
int CStackArp::Close()
{
	m_Inpt1.Close();
	m_Inpt2.Close();
	m_Stack.Close();

	return	0;
}
int CStackArp::Process(UINT nWait)
{
	int		nGraphic1, nGraphic2;
	int		nGraphic = 0;
	int		nMultipass = 0;
	int		nRasterBit = 0;
	int		nDataSize = 0;
	int		nStartPos = 0;

	int				nRet = ProcessHeader( &nGraphic1, &nGraphic2 );
	if( nRet >= 0 )	nRet = ProcessGraphic( nGraphic1, nGraphic2, nWait );
	if( nRet >= 0 )	nRet = ProcessFooter( nGraphic, nMultipass, nRasterBit, nDataSize, nStartPos, nWait );

	return	nRet;
}

int CStackArp::ProcessHeader(int* pGraphic1, int* pGraphic2)
{
	int		nRet = 0;

	BYTE	byHead, byTime;
	WORD	wWidth, wHeight, wWMax;

	//コマンド読み込み
	while( ( nRet = m_Inpt1.Read() ) > 0 )
	{
		//Job Start
		if( CMD_KIND(m_Inpt1) == 0x1B && JOB_TYPE(m_Inpt1) == '@' )
		{
			if( GET_BYTE( m_Inpt1, 0 ) != 0x0C ) {	//コマンドバージョン
				nRet = -302;
				break;
			}
			if( GET_BYTE( m_Inpt1, 1 ) != 0x50 ) {	//ジョブ種別
				nRet = -303;
				break;
			}
			byHead = GET_BYTE( m_Inpt1, 7 );
			*pGraphic1 = GET_BYTE( m_Inpt1, 8 );
		}
		//Platen
		else if( CMD_KIND(m_Inpt1) == '#' && CMD_TYPE(m_Inpt1) == 0x0004 )
		{
			wWidth  = GET_WORD( m_Inpt1, 2 );
			wHeight = GET_WORD( m_Inpt1, 4 );
		}
		//ドライバー設定状況
		else if( CMD_KIND(m_Inpt1) == '#' && CMD_TYPE(m_Inpt1) == 0x002D )
		{
			byTime = GET_BYTE( m_Inpt1, 14 );
			wWMax  = GET_WORD( m_Inpt1, 23 );
		}

		//ヘッド移動最適化モード指定		ヘッダの最終コマンド
		if( CMD_KIND(m_Inpt1) == '#' && CMD_TYPE(m_Inpt1) == 0x0008 )
			break;
	}
	if( nRet < 0 )	return	nRet;

	//コマンド読み込み
	while( ( nRet = m_Inpt2.Read() ) > 0 )
	{
		//Job Start
		if( CMD_KIND(m_Inpt2) == 0x1B && JOB_TYPE(m_Inpt2) == '@' )
		{
			if( GET_BYTE( m_Inpt2, 0 ) != 0x0C ) {	//コマンドバージョン
				nRet = -302;
				break;
			}
			if( GET_BYTE( m_Inpt2, 1 ) != 0x50 ) {	//ジョブ種別
				nRet = -303;
				break;
			}
			*pGraphic2 = GET_BYTE( m_Inpt2, 8 );
			if( *pGraphic1 + *pGraphic2 > 10 ) {
				nRet = -401;
				break;
			}
			OR_BYTE(  m_Inpt2,  7, byHead );
			SET_BYTE( m_Inpt2,  8, *pGraphic1 + *pGraphic2 );
			SET_BYTE( m_Inpt2,  9, *pGraphic1 + *pGraphic2 );
			SET_BYTE( m_Inpt2, 10, 0 );
		}
		//Platen
		else if( CMD_KIND(m_Inpt2) == '#' && CMD_TYPE(m_Inpt2) == 0x0004 )
		{
			if( wWidth  != GET_WORD( m_Inpt2, 2 )
			||	wHeight != GET_WORD( m_Inpt2, 4 ) ) {
				nRet = -402;
				break;
			}
		}
		//ドライバー設定状況
		else if( CMD_KIND(m_Inpt2) == '#' && CMD_TYPE(m_Inpt2) == 0x002D )
		{
			ADD_BYTE( m_Inpt2, 14, byTime );
			ADD_WORD( m_Inpt2, 23, wWMax  );
		}

		//コマンド書き込み
		m_Stack.Write( &m_Inpt2 );

		//ヘッド移動最適化モード指定		ヘッダの最終コマンド
		if( CMD_KIND(m_Inpt2) == '#' && CMD_TYPE(m_Inpt2) == 0x0008 )
			break;
	}
	if( nRet < -400 )	return	nRet;
	if( nRet <    0 )	return	nRet-50;

	return	nRet;
}
int CStackArp::ProcessGraphic(int nGraphic1, int nGraphic2, UINT nWait)
{
	int		nRet = 0;

	while( nGraphic1 > 0 && nRet >= 0 )
	{
		//コマンド読み込み
		while( ( nRet = m_Inpt1.Read() ) > 0 )
		{
			//Preview
			if( CMD_KIND(m_Inpt1) == '#' && CMD_TYPE(m_Inpt1) == 0x0065 )
			{
				continue;
			}

			//コマンド書き込み
			m_Stack.Write( &m_Inpt1 );

			//Graphic End
			if( CMD_KIND(m_Inpt1) == '#' && CMD_TYPE(m_Inpt1) == 0x0051 )
				break;
		}
		--nGraphic1;
	}
	if( nRet < 0 )	return	nRet;

	while( nGraphic2 > 0 && nRet >= 0 )
	{
		//コマンド読み込み
		while( ( nRet = m_Inpt2.Read() ) > 0 )
		{
			//Preview
			if( CMD_KIND(m_Inpt2) == '#' && CMD_TYPE(m_Inpt2) == 0x0065 )
			{
				continue;
			}

			//Graphic Start
			if( CMD_KIND(m_Inpt2) == '#' && CMD_TYPE(m_Inpt2) == 0x0050 && nWait != -1 )
			{
				SET_BYTE( m_Inpt2, 11, 1 );
				SET_BYTE( m_Inpt2, 12, nWait );
				nWait = -1;
			}

			//コマンド書き込み
			m_Stack.Write( &m_Inpt2 );

			//Graphic End
			if( CMD_KIND(m_Inpt2) == '#' && CMD_TYPE(m_Inpt2) == 0x0051 )
				break;
		}
		--nGraphic2;
	}
	if( nRet < 0 )	return	nRet-50;

	return	nRet;
}
int CStackArp::ProcessFooter(int nGraphic, int nMultipass, int nRasterBit, int nDataSize, int nStartPos, UINT nWait)
{
	int		nRet = 0;

	ULONGLONG	nPosion = m_Stack.m_File.GetPosition();
	DWORD		dwSize;
	TByteArray	baParam;
	CCmdInk		cmdInk;

	//コマンド読み込み
	while( ( nRet = m_Inpt1.Read() ) > 0 )
	{
		//ジョブレイアウト
		if( CMD_KIND(m_Inpt1) == '#' && CMD_TYPE(m_Inpt1) == 0x0054 )
		{
			dwSize = CMD_SIZE( m_Inpt1 );
			baParam.Copy( m_Inpt1.m_baParam );
		}
		// インク使用量
		else if( CMD_KIND(m_Inpt1) == '#' && CMD_TYPE(m_Inpt1) == 0x0053 )
		{
			cmdInk.GetParam( &m_Inpt1 );
		}
	}
	if( nRet < 0 )	return	nRet;

	//コマンド読み込み
	while( ( nRet = m_Inpt2.Read() ) > 0 )
	{
		//ジョブレイアウト
		if( CMD_KIND(m_Inpt2) == '#' && CMD_TYPE(m_Inpt2) == 0x0054 )
		{
			ADD_SIZE( m_Inpt2, dwSize );
			SET_BYTE( m_Inpt2, 11, 1 );
			SET_BYTE( m_Inpt2, 12, nWait );
			m_Stack.Write( &m_Inpt2.m_baHead );
			m_Stack.Write( &baParam );
			m_Stack.Write( &m_Inpt2.m_baParam );
			continue;
		}
		// インク使用量
		else if( CMD_KIND(m_Inpt2) == '#' && CMD_TYPE(m_Inpt2) == 0x0053 )
		{
			cmdInk.AddParam( &m_Inpt2 );
			cmdInk.SetParam( &m_Inpt2 );
		}
		//Job End
		else if( CMD_KIND(m_Inpt2) == 0x1B && JOB_TYPE(m_Inpt2) == '$' )
		{
			int	nFooter = (int)( m_Stack.m_File.GetPosition() - nPosion );	//Footerデータのサイズ
			SET_DWORD( m_Inpt2, 7, nFooter );

			m_Stack.Write( &m_Inpt2 );
			m_Stack.WriteLast();
			break;
		}
		//Preview
		else if( CMD_KIND(m_Inpt2) == '#' && CMD_TYPE(m_Inpt2) == 0x0065 )
		{
			continue;
		}

		//コマンド書き込み
		m_Stack.Write( &m_Inpt2 );
	}
	if( nRet < 0 )	return	nRet-50;

	return	nRet;
}


////////////////////////////////////////
//	カラーのみと白のみのARPを、１つに結合

CMergeArp::CMergeArp(void)
{

}
CMergeArp::~CMergeArp(void)
{
	Close();
}

int CMergeArp::Open(LPCTSTR szInW, LPCTSTR szInC, LPCTSTR szOut)
{
	int	nRet = m_White.Open( szInW, FALSE );
	if( nRet < 0 )	return -101;

	nRet = m_Color.Open( szInC, FALSE );
	if( nRet < 0 )	return -102;

	nRet = m_Merge.Open( szOut, TRUE  );
	if( nRet < 0 )	return -103;

	return	0;
}
int CMergeArp::Close()
{
	m_White.Close();
	m_Color.Close();
	m_Merge.Close();

	return	0;
}
int CMergeArp::Process()
{
	int		nGraphic = 0;
	int		nMultipass = 0;
	int		nRasterBit = 0;
	int		nDataSize = 0;
	int		nStartPos = 0;

	int				nRet = ProcessHeader( &nGraphic );
	if( nRet >= 0 )	nRet = ProcessGraphic( nGraphic, &nMultipass, &nRasterBit, &nDataSize, &nStartPos );
	if( nRet >= 0 )	nRet = ProcessFooter( nGraphic, nMultipass, nRasterBit, nDataSize, nStartPos );

	return	nRet;
}

//ヘッダのマージ
int CMergeArp::ProcessHeader(int* pGraphic)
{
	SIZE	szPlaten;

	int				nRet = ProcessHeader_Color( &szPlaten );
	if( nRet > 0 )	nRet = ProcessHeader_White( szPlaten, pGraphic );

	return	nRet;
}
//カラーファイルのヘッダの取得
int CMergeArp::ProcessHeader_Color(SIZE* pPlaten)
{
	int		nRet = 0;

	//コマンド読み込み
	while( ( nRet = m_Color.Read() ) > 0 )
	{
		//Job Start
		if( CMD_KIND(m_Color) == 0x1B && JOB_TYPE(m_Color) == '@' )
		{
			if((GET_BYTE( m_Color, 0 ) != 0x0A && GET_BYTE( m_Color, 0 ) != 0x0B && GET_BYTE( m_Color, 0 ) != 0x0C)	//コマンドバージョン
			||	GET_BYTE( m_Color, 1 ) != 0x50		//ジョブ種別
			||	GET_BYTE( m_Color, 7 ) != 0x10		//使用ヘッド
			||	GET_BYTE( m_Color, 8 ) != 0x01 ) {	//Graphic数
				nRet = -302;
				break;
			}
		}

		//ドライバ設定状況指定
		if( CMD_KIND(m_Color) == '#' && CMD_TYPE(m_Color) == 0x002D )
		{
			//TBD
		}

		//プラテン情報指定
		if( CMD_KIND(m_Color) == '#' && CMD_TYPE(m_Color) == 0x0004 )
		{
			pPlaten->cx	= GET_WORD( m_Color, 2 );
			pPlaten->cy	= GET_WORD( m_Color, 4 );
		}

		//ヘッド移動最適化モード指定		ヘッダの最終コマンド
		if( CMD_KIND(m_Color) == '#' && CMD_TYPE(m_Color) == 0x0008 )
			break;
	}
	if( nRet < 0 )	nRet -= 50;

	return	nRet;
}
//白ファイルのヘッダの判定・変更・コピー
int CMergeArp::ProcessHeader_White(SIZE szPlaten, int* pGraphic)
{
	int		nRet = 0;

	//コマンド読み込み
	while( ( nRet = m_White.Read() ) > 0 )
	{
		//Job Start
		if( CMD_KIND(m_White) == 0x1B && JOB_TYPE(m_White) == '@' )
		{
			if((GET_BYTE( m_White, 0 ) != 0x0A && GET_BYTE( m_White, 0 ) != 0x0B && GET_BYTE( m_White, 0 ) != 0x0C)	//コマンドバージョン
			||	GET_BYTE( m_White, 1 ) != 0x50		//ジョブ種別
			|| (GET_BYTE( m_White, 7 ) != 0x02 && GET_BYTE( m_White, 7 ) != 0x04) ) {	//使用ヘッド
				nRet = -303;
				break;
			}
			*pGraphic	= GET_BYTE( m_White, 8 );		//Graphic数
			OR_BYTE( m_White, 7, 0x10 );				//使用ヘッドにカラー追加
		}

		//ドライバ設定状況指定
		if( CMD_KIND(m_White) == '#' && CMD_TYPE(m_White) == 0x002D )
		{
			//TBD
		}

		//プラテン情報指定
		if( CMD_KIND(m_White) == '#' && CMD_TYPE(m_White) == 0x0004 )
		{
			if( szPlaten.cx != GET_WORD( m_White, 2 )
			||	szPlaten.cy != GET_WORD( m_White, 4 ) ) {
				nRet = -402;
				break;
			}
		}

		//コマンド書き込み
		m_Merge.Write( &m_White );

		//ヘッド移動最適化モード指定		ヘッダの最終コマンド
		if( CMD_KIND(m_White) == '#' && CMD_TYPE(m_White) == 0x0008 )
			break;
	}

	return	nRet;
}

//Grapicデータのマージ
int CMergeArp::ProcessGraphic(int nGraphic, int* pMultipass, int *pRasterBit, int* pDataSize, int* pStartPos)
{
	int		nRet = 0;

	//白のみのコピー
	while( --nGraphic && nRet >= 0 )
	{
		nRet = ProcessGraphic_WOnly();
	}

	//カラーと白の結合
	if( nRet >= 0 )
	{
		ULONGLONG	nPos = m_Merge.m_File.GetPosition();

		nRet = ProcessGraphic_CMYKW( pMultipass, pRasterBit, pStartPos );

		*pDataSize = (int)( m_Merge.m_File.GetPosition() - nPos );	//Grapicデータのサイズ
	}

	return	nRet;
}
//白のみのGraphicデータのコピー
int CMergeArp::ProcessGraphic_WOnly()
{
	int		nRet = 0;

	//コマンドコピー
	while( ( nRet = m_White.Read() ) > 0 )	//コマンド読み込み
	{
		//コマンド書き込み
		m_Merge.Write( &m_White );

		//GraphicEnd
		if( CMD_KIND(m_White) == '#' && CMD_TYPE(m_White) == 0x0051 )
			break;
	}

	return	nRet;
}
//白のみとカラーのみのGraphicデータのマージ
int CMergeArp::ProcessGraphic_CMYKW(int* pMultipass, int *pRasterBit, int* pStartPos)
{
	int		nRet = 0;

	//GraphicStartのマージ
	nRet = m_Color.Read();
	if( nRet <= 0 )		return	nRet-50;
	nRet = m_White.Read();
	if( nRet <= 0 )		return	nRet;

	//プレビュー削除
	if( CMD_KIND(m_Color) == '#' && CMD_TYPE(m_Color) == 0x0065 )
	{
		nRet = m_Color.Read();
		if( nRet <= 0 )		return	nRet-50;
	}
	if( CMD_KIND(m_White) == '#' && CMD_TYPE(m_White) == 0x0065 )
	{
		nRet = m_White.Read();
		if( nRet <= 0 )		return	nRet;
	}

	if( CMD_KIND(m_Color) != '#' || CMD_TYPE(m_Color) != 0x0050 )
		return	-305-50;
	if( CMD_KIND(m_White) != '#' || CMD_TYPE(m_White) != 0x0050 )
		return	-306;

	if( GET_BYTE( m_Color, 6 ) != GET_BYTE( m_White, 6 ) || GET_BYTE( m_Color, 7 ) != GET_BYTE( m_White, 7 )	//水平解像度
	||	GET_BYTE( m_Color, 8 ) != GET_BYTE( m_White, 8 ) || GET_BYTE( m_Color, 9 ) != GET_BYTE( m_White, 9 ) )	//垂直解像度
		return	-403;

//	if( m_Color.baParam[13] != m_White.baParam[13] >> 2 )											//ラスタbit数
//		return	-308;

	*pMultipass	= GET_BYTE( m_Color, 10 );											//マルチパス
	*pRasterBit	= (GET_BYTE( m_Color, 13 ) & 3) | (GET_BYTE( m_White, 13 ) & 12);	//ラスタbit数

	SET_BYTE( m_White,  0, 0x01 );			//CMYKデータあり
	SET_BYTE( m_White, 10, *pMultipass );	//マルチパス
	SET_BYTE( m_White, 13, *pRasterBit );	//ラスタbit数
	m_Merge.Write( &m_White );

	//ラスタデータのマージ
	int		nPosC = -1, nPosW = -1, nPosM = -1;		//画像行
	int		nCmpC =  1, nCmpW =  1, nCmpM = -1;		//圧縮方法
	*pStartPos = -1;

	while( nPosC != NO_LINE || nPosW != NO_LINE )	//画像行がある限り
	{
		//画像行番号指定のマージ
		if( nPosM < nPosC && nPosM < nPosW )
		{
			if( nPosC < nPosW ) {
				nPosM = nPosC;
				m_Merge.Write( &m_Color );			//行番号の書き込み
			} else {
				nPosM = nPosW;
				m_Merge.Write( &m_White );			//行番号の書き込み
			}
			if( *pStartPos == -1 )					//最初の行番号の取得
				*pStartPos  = nPosM;
		}

		//カラーラスタデータのマージ
		if( nPosM == nPosC )
		{
			//コマンド読み込み
			nRet = m_Color.Read();
			if( nRet <= 0 )
				return	nRet-50;

			//圧縮モード
			if( CMD_KIND(m_Color) == '#' && CMD_TYPE(m_Color) == 0x000B )
			{
				nCmpC = GET_BYTE( m_Color, 0 );
			}

			//ラスタグラフィックス転送
			if( CMD_KIND(m_Color) == '#' && 0x0057 <= CMD_TYPE(m_Color) && CMD_TYPE(m_Color) <= 0x0064 )
			{
				//圧縮モード書き込み
				if( nCmpM != nCmpC ) {
					nCmpM  = nCmpC;
					m_Merge.WriteCompMode( nCmpM );
				}

				//コマンド書き込み
				m_Merge.Write( &m_Color );
			}

			//画像行番号指定
			if( CMD_KIND(m_Color) == '#' && CMD_TYPE(m_Color) == 0x0056 )
			{
				nPosC = GET_WORD( m_Color, 0 );
			}

			//Graphic End
			if( CMD_KIND(m_Color) == '#' && CMD_TYPE(m_Color) == 0x0051 )
			{
				nPosC = NO_LINE;
			}
		}

		//白ラスタデータのマージ
		if( nPosM == nPosW )
		{
			//コマンド読み込み
			nRet = m_White.Read();
			if( nRet <= 0 )
				return	nRet;

			//圧縮モード
			if( CMD_KIND(m_White) == '#' && CMD_TYPE(m_White) == 0x000B )
			{
				nCmpW = GET_BYTE( m_White, 0 );
			}

			//ラスタグラフィックス転送
			if( CMD_KIND(m_White) == '#' && 0x0057 <= CMD_TYPE(m_White) && CMD_TYPE(m_White) <= 0x0064 )
			{
				//圧縮モード書き込み
				if( nCmpM != nCmpW ) {
					nCmpM  = nCmpW;
					m_Merge.WriteCompMode( nCmpM );
				}

				//コマンド書き込み
				m_Merge.Write( &m_White );
			}

			//画像行番号指定
			if( CMD_KIND(m_White) == '#' && CMD_TYPE(m_White) == 0x0056 )
			{
				nPosW = GET_WORD( m_White, 0 );
			}

			//Graphic End
			if( CMD_KIND(m_White) == '#' && CMD_TYPE(m_White) == 0x0051 )
			{
				nPosW = NO_LINE;
			}
		}
	}

	//GraphicEndのマージ
	SET_DWORD( m_White, 0, *pStartPos );		//ラスタデータの開始行
	m_Merge.Write( &m_White );

	return	nRet;
}

//フッタのマージ
int CMergeArp::ProcessFooter(int nGraphic, int nMultipass, int nRasterBit, int nDataSize, int nStartPos)
{
	int		nRet = 0;
	CCmdInk	cmdInk;

	//カラーファイルのフッタの取得
	while( ( nRet = m_Color.Read() ) > 0 )
	{
		//インク使用量
		if( CMD_KIND(m_Color) == '#' && CMD_TYPE(m_Color) == 0x0053 )
		{
			cmdInk.GetParam( &m_Color );
		}
	}
	if( nRet < 0 )	return	nRet-50;

	//白ファイルのフッタの変更・コピー
	while( ( nRet = m_White.Read() ) > 0 )
	{
		//プレビュー削除
		if( CMD_KIND(m_White) == '#' && CMD_TYPE(m_White) == 0x0065 )
		{
			continue;
		}

		//ジョブレイアウト
		if( CMD_KIND(m_White) == '#' && CMD_TYPE(m_White) == 0x0054 )
		{
			//最終Graphic = カラーと白のマージ
			UINT	nOffset = ( nGraphic - 1 ) * 32;

			//GraphicStart
			SET_BYTE( m_White, nOffset +  0, 0x01 );			//CMYKデータあり
			SET_BYTE( m_White, nOffset + 10, nMultipass );		//マルチパス
			SET_BYTE( m_White, nOffset + 13, nRasterBit );		//ラスタbit数
			//Graphicコマンド長
			SET_DWORD( m_White, nOffset + 16, nDataSize );
			//ラスタデータの開始行
			SET_DWORD( m_White, nOffset + 20, nStartPos );
		}

		//インク使用量
		if( CMD_KIND(m_White) == '#' && CMD_TYPE(m_White) == 0x0053 )
		{
			cmdInk.AddParam( &m_White );
			cmdInk.SetParam( &m_White );
		}

		//Job End
		else if( CMD_KIND(m_White) == 0x1B && JOB_TYPE(m_White) == '$' )
		{
			m_Merge.Write( &m_White );
			m_Merge.WriteLast();
			break;
		}

		//コマンド書き込み
		m_Merge.Write( &m_White );
	}

	return	nRet;
}


////////////////////////////////////////
//	カラー/白のARPを、カラーのみと白のみに分割

CSplitArp::CSplitArp(void)
{

}
CSplitArp::~CSplitArp(void)
{
	Close();
}

int CSplitArp::Open(LPCTSTR szIn, LPCTSTR szOutW, LPCTSTR szOutC, LPCTSTR szOutF, LPCTSTR szOutW2)
{
	int	nRet = m_Split.Open( szIn  , FALSE );
	if( nRet < 0 )	return -101;

	nRet = m_White.Open( szOutW, TRUE  );
	if( nRet < 0 )	return -102;

	nRet = m_Color.Open( szOutC, TRUE  );
	if( nRet < 0 )	return -103;

	nRet = m_Finishing.Open(szOutF, TRUE);
	if (nRet < 0)	return -104;

	nRet = m_White2.Open(szOutW2, TRUE);
	if (nRet < 0)	return -105;

	return	0;
}
int CSplitArp::Close()
{
	m_Split.Close();
	m_White.Close();
	m_Color.Close();
	m_Finishing.Close();
	m_White2.Close();

	return	0;
}
int CSplitArp::Process()
{
	int		nGraphic, nGraphicW, nGraphicC, nGraphicF, nGraphicW2;
	int		nSizeW[32], nSizeC[32], nSizeF[32], nSizeW2[32];		//Graphics Size
	int		nStartW[32], nStartC[32], nStartF[32], nStartW2[32];	//Start Line
	int		nLineW[32], nLineC[32], nLineF[32], nLineW2[32];		//Line Count

	int				nRet = ProcessHeader( nGraphic );
	//if( nRet >= 0 )	nRet = ProcessGraphic( nGraphic, nGraphicW, nGraphicC, nSizeW, nSizeC, nStartW, nStartC, nLineW, nLineC );
	if (nRet >= 0)	nRet = ProcessGraphic(nGraphic, nGraphicW, nGraphicC, nGraphicF, nGraphicW2, nSizeW, nSizeC, nSizeF, nSizeW2, nStartW, nStartC, nStartF, nStartW2, nLineW, nLineC, nLineF, nLineW2);
	//if( nRet >= 0 )	nRet = ProcessFooter( nGraphicW, nGraphicC, nSizeW, nSizeC, nStartW, nStartC, nLineW, nLineC );
	if (nRet >= 0)	nRet = ProcessFooter(nGraphicW, nGraphicC, nGraphicF, nGraphicW2, nSizeW, nSizeC, nSizeF, nSizeW2, nStartW, nStartC, nStartF, nStartW2, nLineW, nLineC, nLineF, nLineW2);

	return	nRet;
}

//ヘッダのセパレート
int CSplitArp::ProcessHeader(int& nGraphic)
{
	int		nRet = 0;

	//コマンド読み込み
	while( ( nRet = m_Split.Read() ) > 0 )
	{
		//コマンドのコピー
		m_Color.Copy( &m_Split );
		m_White.Copy( &m_Split );
		m_Finishing.Copy(&m_Split);
		m_White2.Copy(&m_Split);

		//Job Start
		if( CMD_KIND(m_Split) == 0x1B && JOB_TYPE(m_Split) == '@' )
		{
			if((GET_BYTE( m_Split, 0 ) != 0x0A && GET_BYTE( m_Split, 0 ) != 0x0B && GET_BYTE( m_Split, 0 ) != 0x0C)	//コマンドバージョン
			||	GET_BYTE( m_Split, 1 ) != 0x50		//ジョブ種別
			|| (GET_BYTE( m_Split, 7 ) != 0x12 && GET_BYTE( m_Split, 7 ) != 0x14) && GET_BYTE(m_Split, 7) != 0x24 && GET_BYTE(m_Split, 7) != 0x30 && GET_BYTE(m_Split, 7) != 0x34) {	//使用ヘッド
				nRet = -301;
				break;
			}

			nGraphic = GET_BYTE( m_Split, 8 );	//Graphic数

			//Color
			AND_BYTE( m_Color,  7, ~0x6F );
			SET_BYTE( m_Color, 10,  0x00 );
			if( nGraphic > 1 ) {
				SET_BYTE( m_Color, 8, 1 );
				SET_BYTE( m_Color, 9, 1 );
			}

			//White
			AND_BYTE( m_White,  7, ~0x70 );
			SET_BYTE( m_White, 10,  0x00 );
			//NOTE: Support		"W+C" , "W+W+C"
			//		Not support	"W+WC"
			//		Except		"WC"
			if( nGraphic > 1 ) {
				SET_BYTE(  m_White, 8, 1 );
				SET_BYTE(  m_White, 9, 1 );
			}

			//Finishing
			AND_BYTE(m_Finishing, 7, ~0x6F);
			SET_BYTE(m_Finishing, 10, 0x00);
			if (nGraphic > 1) {
				SET_BYTE(m_Finishing, 8, 1);
				SET_BYTE(m_Finishing, 9, 1);
			}

			//White2
			AND_BYTE(m_White2, 7, ~0x70);
			SET_BYTE(m_White2, 10, 0x00);
			//NOTE: Support		"W+C" , "W+W+C"
			//		Not support	"W+WC"
			//		Except		"WC"
			if (nGraphic > 1) {
				SET_BYTE(m_White2, 8, 1);
				SET_BYTE(m_White2, 9, 1);
			}
		}

		//ドライバー設定状況
		if( CMD_KIND(m_Split) == '#' && CMD_TYPE(m_Split) == 0x002D )
		{
			SET_BYTE( m_Color, 14, 4 );	//Time	//NOTE: not support multipass.
			SET_WORD( m_Color, 23, 0 );	//WMax

			SET_BYTE(m_Finishing, 14, 0);	//Time	//NOTE: not support multipass.
			SET_WORD(m_Finishing, 23, 0);	//WMax
		}

		//前処理
		if (CMD_KIND(m_Split) == '#' && CMD_TYPE(m_Split) == 0x002B)
		{
			m_Color.Write();
			m_White.Write();
			m_White2.Write();
			continue;
		}

		//コマンド書き込み
		m_Color.Write();
		m_White.Write();
		m_Finishing.Write();
		m_White2.Write();

		//ヘッド移動最適化モード指定		ヘッダの最終コマンド
		if( CMD_KIND(m_Split) == '#' && CMD_TYPE(m_Split) == 0x0008 )
			break;
	}

	return	nRet;
}

//Grapicデータのセパレート
int CSplitArp::ProcessGraphic(int nGraphic, int& nGraphicW, int& nGraphicC, int& nGraphicF, int& nGraphicW2, int nSizeW[], int nSizeC[], int nSizeF[], int nSizeW2[], int nStartW[], int nStartC[], int nStartF[], int nStartW2[], int nLineW[], int nLineC[], int nLineF[], int nLineW2[])
{
	int		nRet = 0;
	int		nWhite = 0, nColor = 0, nFinishing = 0;
	int		nPos = -1, nPosW = -1, nPosC = -1, nPosF = -1, nPosW2 = -1;		//画像行
	int		nCmp = 1, nCmpW = -1, nCmpC = -1, nCmpF = -1, nCmpW2 = -1;		//圧縮方法
	bool    bSecondLayer = FALSE;

	ULONGLONG	nPosionW, nPosionC, nPosionF, nPosionW2;
				nGraphicW = nGraphicC = nGraphicF = nGraphicW2 = 0;

	while( nGraphic-- )
	{
		while( ( nRet = m_Split.Read() ) > 0 )
		{
			//Graphic Start
			if( CMD_KIND(m_Split) == '#' && CMD_TYPE(m_Split) == 0x0050 )
			{
				nWhite = GET_BYTE( m_Split, 1 );
				if( nWhite ) {
					if (!bSecondLayer) {
						nStartW[nGraphicW] = -1;
						nLineW[nGraphicW] = 0;
						nPosionW = m_White.m_File.GetPosition();
						m_White.Copy(&m_Split);
						SET_BYTE(m_White, 0, 0x00);	//CMYK
						AND_BYTE(m_White, 13, ~0x07);	//bits per dot
						AND_BYTE(m_White, 14, ~0x01);	//devide
						if (nGraphicW == 0) {
							SET_BYTE(m_White, 11, 0x00);	//Wait
							SET_BYTE(m_White, 12, 0x00);
						}
						m_White.Write();
					}
					else {
						nStartW2[nGraphicW2] = -1;
						nLineW2[nGraphicW2] = 0;
						nPosionW2 = m_White2.m_File.GetPosition();
						m_White2.Copy(&m_Split);
						SET_BYTE(m_White2, 0, 0x00);	//CMYK
						AND_BYTE(m_White2, 13, ~0x07);	//bits per dot
						AND_BYTE(m_White2, 14, ~0x01);	//devide
						if (nGraphicW2 == 0) {
							SET_BYTE(m_White2, 11, 0x00);	//Wait
							SET_BYTE(m_White2, 12, 0x00);
						}
						m_White2.Write();
					}
				}

				nColor = GET_BYTE( m_Split, 0 );
				if( nColor ) {
					nStartC[nGraphicC] = -1;
					nLineC[nGraphicC] = 0;
					nPosionC = m_Color.m_File.GetPosition();
					m_Color.Copy( &m_Split );
					SET_BYTE( m_Color,  1, 0x00 );	//White
					SET_BYTE( m_Color,  3, 0x01 );	//Count
					AND_BYTE( m_Color, 13, 0x03 );	//bits per dot
					AND_BYTE( m_Color, 14, 0x01 );	//devide
					if( nGraphicC == 0 && GET_BYTE(m_Color, 14) == 0 ) {
						SET_BYTE( m_Color, 11, 0x00 );	//Wait
						SET_BYTE( m_Color, 12, 0x00 );
					}
					m_Color.Write();
				}

				if (!nWhite && !nColor) {
					nStartF[nGraphicF] = -1;
					nLineF[nGraphicF] = 0;
					nPosionF = m_Finishing.m_File.GetPosition();
					m_Finishing.Copy(&m_Split);
					SET_BYTE(m_Finishing, 0, 0x00);	//CMYK
					SET_BYTE(m_Finishing, 1, 0x00);	//White
					SET_BYTE(m_Finishing, 3, 0x01);	//Count
					AND_BYTE(m_Finishing, 13, 0x00);	//bits per dot
					AND_BYTE(m_Finishing, 14, 0x00);	//devide
					if (nGraphicF == 0 && GET_BYTE(m_Finishing, 14) == 0) {
						SET_BYTE(m_Finishing, 11, 0x00);	//Wait
						SET_BYTE(m_Finishing, 12, 0x00);
					}
					m_Finishing.Write();
				}

				nCmpW = nCmpC = nCmpF = -1;
			}

			//圧縮モード
			if( CMD_KIND(m_Split) == '#' && CMD_TYPE(m_Split) == 0x000B )
			{
				nCmp = GET_BYTE( m_Split, 0 );
			}
			//画像行番号指定
			if( CMD_KIND(m_Split) == '#' && CMD_TYPE(m_Split) == 0x0056 )
			{
				nPos = GET_WORD( m_Split, 0 );
			}

			//ラスタグラフィックス転送 (白)
			if( nWhite && CMD_KIND(m_Split) == '#' && 0x005B <= CMD_TYPE(m_Split) && CMD_TYPE(m_Split) <= 0x0064 )
			{
				if (!bSecondLayer) {
					if (nStartW[nGraphicW] == -1) {
						nStartW[nGraphicW] = nPos;
					}

					if (nCmpW != nCmp) {
						nCmpW = nCmp;
						m_White.WriteCompMode(nCmp);	//圧縮モード
					}
					if (nPosW != nPos) {
						nPosW = nPos;
						m_White.WriteLineNo(nPos);	//画像行番号指定
						++nLineW[nGraphicW];
					}
					m_White.Write(&m_Split);			//ラスタグラフィックス
				}
				else {
					if (nStartW2[nGraphicW2] == -1) {
						nStartW2[nGraphicW2] = nPos;
					}

					if (nCmpW != nCmp) {
						nCmpW = nCmp;
						m_White2.WriteCompMode(nCmp);	//圧縮モード
					}
					if (nPosW != nPos) {
						nPosW = nPos;
						m_White2.WriteLineNo(nPos);	//画像行番号指定
						++nLineW2[nGraphicW2];
					}
					m_White2.Write(&m_Split);			//ラスタグラフィックス
				}
			}

			//ラスタグラフィックス転送 (カラー)
			if( nColor && CMD_KIND(m_Split) == '#' && 0x0057 <= CMD_TYPE(m_Split) && CMD_TYPE(m_Split) <= 0x005A )
			{
				if( nStartC[nGraphicC] == -1 ) {
					nStartC[nGraphicC] = nPos;
				}

				if( nCmpC != nCmp ) {
					nCmpC  = nCmp;
					m_Color.WriteCompMode( nCmp );	//圧縮モード
				}
				if( nPosC != nPos ) {
					nPosC  = nPos;
					m_Color.WriteLineNo( nPos );	//画像行番号指定
					++nLineC[nGraphicC];
				}
				m_Color.Write( &m_Split );			//ラスタグラフィックス転送
			}

			//ラスタグラフィックス転送 (FF)
			if (!nColor && !nWhite && CMD_KIND(m_Split) == '#' && 0x0093 <= CMD_TYPE(m_Split) && CMD_TYPE(m_Split) <= 0x0096 )
			{
				if (nStartF[nGraphicF] == -1) {
					nStartF[nGraphicF] = nPos;
				}

				if (nCmpF != nCmp) {
					nCmpF = nCmp;
					m_Finishing.WriteCompMode(nCmp);	//圧縮モード
				}
				if (nPosF != nPos) {
					nPosF = nPos;
					m_Finishing.WriteLineNo(nPos);	//画像行番号指定
					++nLineF[nGraphicF];
				}
				m_Finishing.Write(&m_Split);			//ラスタグラフィックス転送
			}

			//Graphic End
			if( CMD_KIND(m_Split) == '#' && CMD_TYPE(m_Split) == 0x0051 )
			{
				if( nWhite ) {
					if (!bSecondLayer) {
						SET_DWORD(m_Split, 0, nStartW[nGraphicW]);
						m_White.Write(&m_Split);
						//
						nSizeW[nGraphicW] = (int)(m_White.m_File.GetPosition() - nPosionW);
						++nGraphicW;

						bSecondLayer = TRUE;
					}
					else {
						SET_DWORD(m_Split, 0, nStartW2[nGraphicW2]);
						m_White2.Write(&m_Split);
						//
						nSizeW2[nGraphicW2] = (int)(m_White2.m_File.GetPosition() - nPosionW2);
						++nGraphicW2;
					}				
				}

				if( nColor ) {
					SET_DWORD( m_Split, 0, nStartC[nGraphicC] );
					m_Color.Write( &m_Split );
					//
					nSizeC[nGraphicC] = (int)( m_Color.m_File.GetPosition() - nPosionC );
					++nGraphicC;
				}

				if (!nWhite && !nColor) {
					SET_DWORD(m_Split, 0, nStartF[nGraphicF]);
					m_Finishing.Write(&m_Split);
					//
					nSizeF[nGraphicF] = (int)(m_Finishing.m_File.GetPosition() - nPosionF );
					++nGraphicF;
				}

				break;
			}

			//Preview
		/*	if( CMD_KIND(m_Split) == '#' && CMD_TYPE(m_Split) == 0x0065 )
			{
				continue;
			}	*/
		}
	}

	return	nRet;
}

//フッタのセパレート
int CSplitArp::ProcessFooter(int nGraphicW, int nGraphicC, int nGraphicF, int nGraphicW2, int nSizeW[], int nSizeC[], int nSizeF[], int nSizeW2[], int nStartW[], int nStartC[], int nStartF[], int nStartW2[], int nLineW[], int nLineC[], int nLineF[], int nLineW2[])
{
	int		nRet = 0;

	ULONGLONG	nPosionW = m_White.m_File.GetPosition();
	ULONGLONG	nPosionC = m_Color.m_File.GetPosition();
	ULONGLONG	nPosionF = m_Finishing.m_File.GetPosition();
	ULONGLONG	nPosionW2 = m_White2.m_File.GetPosition();

	//コマンド読み込み
	while( ( nRet = m_Split.Read() ) > 0 )
	{
		//Preview
		if( CMD_KIND(m_Split) == '#' && CMD_TYPE(m_Split) == 0x0065 )
		{
			continue;
		}

		//インク使用量(特色)
		if (CMD_KIND(m_Split) == '#' && CMD_TYPE(m_Split) == 0x00A6 )
		{
			//m_Finishing.Copy(&m_Split);
			//m_Finishing.Write();
			continue;
		}

		m_White.Copy( &m_Split );
		m_Color.Copy( &m_Split );
		m_Finishing.Copy( &m_Split );
		m_White2.Copy( &m_Split );

		//ジョブレイアウト
		if( CMD_KIND(m_Split) == '#' && CMD_TYPE(m_Split) == 0x0054 )
		{
			//確保
			m_White.m_baHead[ 7 ] = nGraphicW * 32;
			m_White.m_baParam.SetSize( nGraphicW * 32 );
			m_Color.m_baHead[ 7 ] = nGraphicC * 32;
			m_Color.m_baParam.SetSize( nGraphicC * 32 );
			m_Finishing.m_baHead[7] = nGraphicF * 32;
			m_Finishing.m_baParam.SetSize(nGraphicF * 32);
			m_White2.m_baHead[7] = nGraphicW2 * 32;
			m_White2.m_baParam.SetSize(nGraphicW2 * 32);

			//レイヤーでループ
			int nLayer = m_Split.m_baHead[ 7 ] / 32;
			int nWhite = 0, nWhite2 = 0;
			int nColor = 0;
			int nFinishing = 0;
			for( int i = 0; i < nLayer; ++ i ) {
				//白あり
				if( m_Split.m_baParam[i * 32 +  1] ) {
					UINT	nOffset = nWhite * 32;
					memcpy( &m_White.m_baParam[nOffset], &m_Split.m_baParam[i * 32], 32);
					SET_BYTE( m_White, nOffset +  0,  0x00 );		//CMYK
					AND_BYTE( m_White, nOffset + 13, ~0x07 );		//bits per dot
					AND_BYTE( m_White, nOffset + 14, ~0x01 );		//devide
					if( nWhite == 0 ) {
						SET_BYTE( m_White, nOffset + 11,  0x00 );	//Wait
						SET_BYTE( m_White, nOffset + 12,  0x00 );
					}
					if( nWhite < nGraphicW ) {
						SET_DWORD( m_White, nOffset + 16, nSizeW[nWhite]  );	//Graphicコマンド長
						SET_DWORD( m_White, nOffset + 20, nStartW[nWhite] );	//ラスタデータの開始行
						SET_DWORD( m_White, nOffset + 24, nLineW[nWhite]  );	//ライン数
					}
					++nWhite;

					UINT	nOffset2 = nWhite2 * 32;
					memcpy(&m_White2.m_baParam[nOffset2], &m_Split.m_baParam[i * 32], 32);
					SET_BYTE(m_White2, nOffset2 + 0, 0x00);		//CMYK
					AND_BYTE(m_White2, nOffset2 + 13, ~0x07);		//bits per dot
					AND_BYTE(m_White2, nOffset2 + 14, ~0x01);		//devide
					if (nWhite2 == 0) {
						SET_BYTE(m_White2, nOffset2 + 11, 0x00);	//Wait
						SET_BYTE(m_White2, nOffset2 + 12, 0x00);
					}
					if (nWhite2 < nGraphicW2) {
						SET_DWORD(m_White2, nOffset2 + 16, nSizeW[nWhite2]);	//Graphicコマンド長
						SET_DWORD(m_White2, nOffset2 + 20, nStartW[nWhite2]);	//ラスタデータの開始行
						SET_DWORD(m_White2, nOffset2 + 24, nLineW[nWhite2]);	//ライン数
					}
					++nWhite2;
				}

				//カラーあり
				if( m_Split.m_baParam[i * 32 +  0] ) {
					UINT	nOffset = nColor * 32;
					memcpy( &m_Color.m_baParam[nOffset], &m_Split.m_baParam[i * 32], 32);
					SET_BYTE( m_Color, nOffset +  1, 0x00 );		//White
					SET_BYTE( m_Color, nOffset +  3, 0x01 );		//Count
					AND_BYTE( m_Color, nOffset + 13, 0x03 );		//bits per dot
					AND_BYTE( m_Color, nOffset + 14, 0x01 );		//devide
					if( nColor == 0 && GET_BYTE(m_Color, 14) == 0 ) {
						SET_BYTE( m_Color, nOffset + 11, 0x00 );	//Wait
						SET_BYTE( m_Color, nOffset + 12, 0x00 );
					}
					if( nColor < nGraphicC ) {
						SET_DWORD( m_Color, nOffset + 16, nSizeC[nColor]  );	//Graphicコマンド長
						SET_DWORD( m_Color, nOffset + 20, nStartC[nColor] );	//ラスタデータの開始行
						SET_DWORD( m_Color, nOffset + 24, nLineC[nColor]  );	//ライン数
					}
					++nColor;

					UINT	nOffsetF = nFinishing * 32;
					memcpy(&m_Finishing.m_baParam[nOffsetF], &m_Split.m_baParam[i * 32], 32);
					SET_BYTE(m_Finishing, nOffsetF + 1, 0x00);		//White
					SET_BYTE(m_Finishing, nOffsetF + 3, 0x01);		//Count
					AND_BYTE(m_Finishing, nOffsetF + 13, 0x03);		//bits per dot
					AND_BYTE(m_Finishing, nOffsetF + 14, 0x01);		//devide
					if (nColor == 0 && GET_BYTE(m_Finishing, 14) == 0) {
						SET_BYTE(m_Finishing, nOffsetF + 11, 0x00);	//Wait
						SET_BYTE(m_Finishing, nOffsetF + 12, 0x00);
					}
					if (nFinishing < nGraphicF) {
						SET_DWORD(m_Finishing, nOffsetF + 16, nSizeF[nFinishing]);	//Graphicコマンド長
						SET_DWORD(m_Finishing, nOffsetF + 20, nStartF[nFinishing]);	//ラスタデータの開始行
						SET_DWORD(m_Finishing, nOffsetF + 24, nLineF[nFinishing]);	//ライン数
					}
					++nFinishing;
				}
			}
		}

		//インク使用量
		if( CMD_KIND(m_Split) == '#' && CMD_TYPE(m_Split) == 0x0053 )
		{
			CCmdInk	cmdInk;

			cmdInk.GetParam( &m_Split );
			cmdInk.SetWhite( &m_White );
			cmdInk.SetColor( &m_Color );
			cmdInk.SetFinishing( &m_Finishing );
			cmdInk.SetWhite( &m_White2 );
		}

		//Job End
		if( CMD_KIND(m_Split) == 0x1B && JOB_TYPE(m_Split) == '$' )
		{
			//Footerデータのサイズ
			int	nFooterW = (int)( m_White.m_File.GetPosition() - nPosionW );
			int	nFooterC = (int)( m_Color.m_File.GetPosition() - nPosionC );
			int	nFooterF = (int)( m_Finishing.m_File.GetPosition() - nPosionF );
			int	nFooterW2 = (int)( m_White2.m_File.GetPosition() - nPosionW2 );
			SET_DWORD( m_White, 7, nFooterW );
			SET_DWORD( m_Color, 7, nFooterC );
			SET_DWORD( m_Finishing, 7, nFooterF);
			SET_DWORD( m_White2, 7, nFooterW2 );

			m_White.Write();
			m_Color.Write();
			m_Finishing.Write();
			m_White2.Write();
			m_White.WriteLast();
			m_Color.WriteLast();
			m_Finishing.WriteLast();
			m_White2.WriteLast();
			break;
		}

		//コマンド書き込み
		m_White.Write();
		m_Color.Write();
		m_Finishing.Write();
		m_White2.Write();
	}

	return	nRet;
}


////////////////////////////////////////
//	分割印刷の値を修正

CModifyDivide2::CModifyDivide2(void)
{

}
CModifyDivide2::~CModifyDivide2(void)
{
	Close();
}

int CModifyDivide2::Open(LPCTSTR szIn, LPCTSTR szOut)
{
	int	nRet = m_Input.Open( szIn , FALSE );
	if( nRet < 0 )	return -101;

	nRet = m_Output.Open( szOut , TRUE );
	if( nRet < 0 )	return -102;

	return	0;
}
int CModifyDivide2::Close()
{
	m_Input.Close();
	m_Output.Close();

	return	0;
}
int CModifyDivide2::Process(BYTE byDivide1, BYTE byDivide2)
{
	int				nRet = ProcessHeader();
	if( nRet >= 0 )	nRet = ProcessGraphic(byDivide1, byDivide2);
	if( nRet >= 0 )	nRet = ProcessFooter(byDivide1, byDivide2);

	return	nRet;
}

int CModifyDivide2::ProcessHeader()
{
	int		nRet = 0;

	while( ( nRet = m_Input.Read() ) > 0 )
	{
		m_Output.Write( &m_Input );

		//ヘッド移動最適化モード指定		ヘッダの最終コマンド
		if( CMD_KIND(m_Input) == '#' && CMD_TYPE(m_Input) == 0x0008 )
			break;
	}

	return	nRet;
}
int CModifyDivide2::ProcessGraphic(BYTE byDivide1, BYTE byDivide2)
{
	int		nRet = 0;
	int		nGraphic = 2;

	while( nGraphic > 0 && nRet >= 0 )
	{
		while( ( nRet = m_Input.Read() ) > 0 )
		{
			//Grahpcis Start
			if( CMD_KIND(m_Input) == '#' && CMD_TYPE(m_Input) == 0x0050 )
			{
				SET_BYTE( m_Input,  2, 0 );
				SET_BYTE( m_Input, 14, nGraphic == 2 ? byDivide1 : byDivide2 );
			}

			m_Output.Write( &m_Input );

			//Graphic End
			if( CMD_KIND(m_Input) == '#' && CMD_TYPE(m_Input) == 0x0051 )
				break;
		}
		--nGraphic;
	}
	if( nRet < 0 )	return	nRet;

	return	nRet;
}
int CModifyDivide2::ProcessFooter(BYTE byDivide1, BYTE byDivide2)
{
	int		nRet = 0;

	while( ( nRet = m_Input.Read() ) > 0 )
	{
		//ジョブレイアウト
		if( CMD_KIND(m_Input) == '#' && CMD_TYPE(m_Input) == 0x0054 )
		{
			SET_BYTE( m_Input,  2   ,         0 );
			SET_BYTE( m_Input, 14   , byDivide1 );
			SET_BYTE( m_Input,  2+32,         0 );
			SET_BYTE( m_Input, 14+32, byDivide2 );
		}

		m_Output.Write( &m_Input );

		//Job End
		if( CMD_KIND(m_Input) == 0x1B && JOB_TYPE(m_Input) == '$' )
		{
			m_Output.WriteLast();
			break;
		}
	}

	return	nRet;
}


////////////////////////////////////////
//	ポリE対応

CPolyEArp::CPolyEArp(void)
{
	m_byGraphics = 0;
}
CPolyEArp::~CPolyEArp(void)
{
	Close();
}

int CPolyEArp::Open(LPCTSTR szIn, LPCTSTR szOut)
{
	int	nRet = m_InFile.Open( szIn, FALSE );
	if( nRet < 0 )	return -101;

	nRet = m_OutFile.Open( szOut, TRUE );
	if( nRet < 0 )	return -102;

	return	0;
}
int CPolyEArp::Close()
{
	m_InFile.Close();
	m_OutFile.Close();

	return	0;
}
int CPolyEArp::Process(int nType)
{
    const int DIV_TBL[5] = { 0x0C, 0x18, 0x0E, 0x1A, 0x10 };

	int				nRet = ProcessHeader(nType);
	if( nRet >= 0 )	nRet = ProcessGraphic(DIV_TBL[nType]);
	if( nRet >= 0 )	nRet = ProcessFooter(nType, DIV_TBL[nType]);

	return	nRet;
}

int CPolyEArp::ProcessHeader(int nType)
{
	const int TIM_TBL[5] = {    0,    1,    2,    3,    4 };
	const int HIG_TBL[5] = {    5,    7,    9,   11,   13 };
    const int MAX_TBL[5] = {  400,  500,  600,  700,  800 };

	int		nRet = 0;

    while( ( nRet = m_InFile.Read() ) > 0 )
    {
		//Job Start
		if( CMD_KIND(m_InFile) == 0x1B && JOB_TYPE(m_InFile) == '@' )
		{
			if( GET_BYTE( m_InFile, 0 ) != 0x0C ) {	//コマンドバージョン
				nRet = -302;
				break;
			}
			if( GET_BYTE( m_InFile, 1 ) != 0x50 ) {	//ジョブ種別
				nRet = -303;
				break;
			}

            if( GET_BYTE( m_InFile, 7 ) != 0x14 
            &&  GET_BYTE( m_InFile, 7 ) != 0x04 ) { //使用ヘッド
				nRet = -401;
				break;
            }

			m_byGraphics = GET_BYTE( m_InFile, 7 ) > 0x10 ? 2 : 1;
			if( GET_BYTE( m_InFile, 8 ) != m_byGraphics ) {	//Graphics数
				nRet = -402;
				break;
			}
        }

		//ドライバ設定状況指定
		if( CMD_KIND(m_InFile) == '#' && CMD_TYPE(m_InFile) == 0x002D )
		{
            if( GET_BYTE( m_InFile, 10 ) != 0x00 ) { //片方向印刷
				nRet = -403;
				break;
            }
            if( GET_BYTE( m_InFile, 15 ) != 0x05 ) { //ハイライト
				nRet = -404;
				break;
            }


            SET_BYTE( m_InFile,  9,              3 );	 //ポリ対応
            BYTE byTime = GET_BYTE( m_InFile, 14 );      //印刷時間
            SET_BYTE( m_InFile, 14, TIM_TBL[nType] + byTime );
            SET_BYTE( m_InFile, 15, HIG_TBL[nType] );    //ハイライト
            SET_WORD( m_InFile, 23, MAX_TBL[nType] );    //白インク量
        }

		//高速印刷モード
		if( CMD_KIND(m_InFile) == '#' && CMD_TYPE(m_InFile) == 0x0090 )
		{
			continue;
		}

		//コマンド書き込み
        m_OutFile.Write( &m_InFile );

		//ヘッド移動最適化モード指定		ヘッダの最終コマンド
		if( CMD_KIND(m_InFile) == '#' && CMD_TYPE(m_InFile) == 0x0008 )
			break;
    }

	return	nRet;
}

int CPolyEArp::ProcessGraphic(int nDivide)
{
	int		nRet = 0;
    int     byGraphics = 0;

    while( byGraphics < m_byGraphics && nRet >= 0 )
    {
        while( ( nRet = m_InFile.Read() ) > 0 )
        {
            //Graphic Start
            if( CMD_KIND(m_InFile) == '#' && CMD_TYPE(m_InFile) == 0x0050 )
            {
                BYTE byColor = GET_BYTE( m_InFile, 0);
                BYTE byWhite = GET_BYTE( m_InFile, 1);

                //分割印刷
                if( byGraphics == 0 ) {
                    if( byWhite == 0 || byColor != 0 ) {
                        nRet = -405;
        				break;
                    }
                    else if( GET_BYTE( m_InFile, 10 ) != 0 ) {
                        nRet = -406;
                    }
                    else
                        SET_BYTE( m_InFile, 14, nDivide );
                }
                else if( byGraphics == 1 ) {
                    if( byWhite != 0 || byColor == 0 ) {
                        nRet = -407;
                        break;
                    }
                    else if( GET_BYTE( m_InFile, 10 ) != 0 ) {
                        nRet = -408;
                        break;
                    }
                    else
                        SET_BYTE( m_InFile, 14, 1 );
                }
            }

            //コマンド書き込み
            m_OutFile.Write( &m_InFile );

			//Graphic End
			if( CMD_KIND(m_InFile) == '#' && CMD_TYPE(m_InFile) == 0x0051 )
				break;
		}

		++byGraphics;
    }

	return	nRet;
}

int CPolyEArp::ProcessFooter(int nType, int nDivide)
{
	const int INK_TBL[5] = {    4,    5,    6,    7,    8 };

	int		nRet = 0;

    while( ( nRet = m_InFile.Read() ) > 0 )
    {
		//ジョブレイアウト
		if( CMD_KIND(m_InFile) == '#' && CMD_TYPE(m_InFile) == 0x0054 )
        {
            //分割印刷
            SET_BYTE( m_InFile, 14     , nDivide );
            if( m_byGraphics > 1 )
            SET_BYTE( m_InFile, 14 + 32,       1 );
        }
        //インク使用量
		if( CMD_KIND(m_InFile) == '#' && CMD_TYPE(m_InFile) == 0x0053 )
        {
            DWORD dwInk = GET_DWORD( m_InFile, 128 );
            if( dwInk > 0 ) {
				dwInk = (dwInk - 20) * INK_TBL[nType] / 4 + 20;
				SET_DWORD( m_InFile, 128, dwInk );
            }
        }

        //コマンド書き込み
        m_OutFile.Write( &m_InFile );

		//Job End
		if( CMD_KIND(m_InFile) == 0x1B && JOB_TYPE(m_InFile) == '$' )
		{
			m_OutFile.WriteLast();
			break;
		}
    }

	return	nRet;
}


////////////////////////////////////////
//	MMB対応で、２つのARPを、１つに重ねる

CStackArp_MMB::CStackArp_MMB(void)
{

}
CStackArp_MMB::~CStackArp_MMB(void)
{
	Close();
}

int CStackArp_MMB::Open(LPCTSTR szIn1, LPCTSTR szIn2, LPCTSTR szOut)
{
	int	nRet = m_Inpt1.Open( szIn1, FALSE );
	if( nRet < 0 )	return -101;

	nRet = m_Inpt2.Open( szIn2, FALSE );
	if( nRet < 0 )	return -102;

	nRet = m_Stack.Open( szOut, TRUE  );
	if( nRet < 0 )	return -103;

	return	0;
}
int CStackArp_MMB::Close()
{
	m_Inpt1.Close();
	m_Inpt2.Close();
	m_Stack.Close();

	return	0;
}
int CStackArp_MMB::Process(UINT nWait, BYTE byHighlight)
{
	int		nGraphic1, nGraphic2;
	int		nGraphic = 0;
	int		nMultipass = 0;
	int		nRasterBit = 0;
	int		nDataSize = 0;
	int		nStartPos = 0;

	int				nRet = ProcessHeader( &nGraphic1, &nGraphic2 );
	if( nRet >= 0 )	nRet = ProcessGraphic( nGraphic1, nGraphic2, nWait, byHighlight );
	if( nRet >= 0 )	nRet = ProcessFooter( nGraphic, nMultipass, nRasterBit, nDataSize, nStartPos, nWait, byHighlight );

	return	nRet;
}

int CStackArp_MMB::ProcessHeader(int* pGraphic1, int* pGraphic2)
{
	int		nRet = 0;

	BYTE	byHead;
	WORD	wWidth, wHeight;

	//コマンド読み込み
	while( ( nRet = m_Inpt1.Read() ) > 0 )
	{
		//Job Start
		if( CMD_KIND(m_Inpt1) == 0x1B && JOB_TYPE(m_Inpt1) == '@' )
		{
			if( GET_BYTE( m_Inpt1, 0 ) != 0x0C ) {	//コマンドバージョン
				nRet = -302;
				break;
			}
			if( GET_BYTE( m_Inpt1, 1 ) != 0x50 ) {	//ジョブ種別
				nRet = -303;
				break;
			}
			byHead = GET_BYTE( m_Inpt1, 7 );
			*pGraphic1 = GET_BYTE( m_Inpt1, 8 );
		}
		//Platen
		else if( CMD_KIND(m_Inpt1) == '#' && CMD_TYPE(m_Inpt1) == 0x0004 )
		{
			wWidth  = GET_WORD( m_Inpt1, 2 );
			wHeight = GET_WORD( m_Inpt1, 4 );
		}

		//ヘッド移動最適化モード指定		ヘッダの最終コマンド
		if( CMD_KIND(m_Inpt1) == '#' && CMD_TYPE(m_Inpt1) == 0x0008 )
			break;
	}
	if( nRet < 0 )	return	nRet;

	//コマンド読み込み
	while( ( nRet = m_Inpt2.Read() ) > 0 )
	{
		//Job Start
		if( CMD_KIND(m_Inpt2) == 0x1B && JOB_TYPE(m_Inpt2) == '@' )
		{
			if( GET_BYTE( m_Inpt2, 0 ) != 0x0C ) {	//コマンドバージョン
				nRet = -302;
				break;
			}
			if( GET_BYTE( m_Inpt2, 1 ) != 0x50 ) {	//ジョブ種別
				nRet = -303;
				break;
			}

			if( (GET_BYTE( m_Inpt2, 7 ) != 0x12 && GET_BYTE( m_Inpt2, 7 ) != 0x14) ) {	//使用ヘッド
				nRet = -413;
				break;
			}

			*pGraphic2 = GET_BYTE( m_Inpt2, 8 );
			if( *pGraphic2 != 1 ) {
				nRet = -412;
				break;
			}
			OR_BYTE(  m_Inpt2,  7, byHead );
			SET_BYTE( m_Inpt2,  8, *pGraphic1 + *pGraphic2 );
			SET_BYTE( m_Inpt2,  9, *pGraphic1 + *pGraphic2 );
			SET_BYTE( m_Inpt2, 10, 0 );
		}
		//Platen
		else if( CMD_KIND(m_Inpt2) == '#' && CMD_TYPE(m_Inpt2) == 0x0004 )
		{
			if( wWidth  != GET_WORD( m_Inpt2, 2 )
			||	wHeight != GET_WORD( m_Inpt2, 4 ) ) {
				nRet = -414;
				break;
			}
		}

		//コマンド書き込み
		m_Stack.Write( &m_Inpt2 );

		//ヘッド移動最適化モード指定		ヘッダの最終コマンド
		if( CMD_KIND(m_Inpt2) == '#' && CMD_TYPE(m_Inpt2) == 0x0008 )
			break;
	}
	if( nRet < -400 )	return	nRet;
	if( nRet <    0 )	return	nRet-50;

	return	nRet;
}
int CStackArp_MMB::ProcessGraphic(int nGraphic1, int nGraphic2, UINT nWait, BYTE byHighlight)
{
	int		nRet = 0;

	BYTE	byDivide1 = byHighlight > 7 ? 0x16 : 0x12;
	BYTE	byDivide2 = byHighlight > 5 ? 0x00 : 0x14;

	while( nGraphic1 > 0 && nRet >= 0 )
	{
		//コマンド読み込み
		while( ( nRet = m_Inpt1.Read() ) > 0 )
		{
			//Preview
			if( CMD_KIND(m_Inpt1) == '#' && CMD_TYPE(m_Inpt1) == 0x0065 )
			{
				continue;
			}

			//Graphic Start
			if( CMD_KIND(m_Inpt1) == '#' && CMD_TYPE(m_Inpt1) == 0x0050 )
			{
                SET_BYTE( m_Inpt1, 14, byDivide1 );
			}

			//コマンド書き込み
			m_Stack.Write( &m_Inpt1 );

			//Graphic End
			if( CMD_KIND(m_Inpt1) == '#' && CMD_TYPE(m_Inpt1) == 0x0051 )
				break;
		}
		--nGraphic1;
	}
	if( nRet < 0 )	return	nRet;

	while( nGraphic2 > 0 && nRet >= 0 )
	{
		//コマンド読み込み
		while( ( nRet = m_Inpt2.Read() ) > 0 )
		{
			//Preview
			if( CMD_KIND(m_Inpt2) == '#' && CMD_TYPE(m_Inpt2) == 0x0065 )
			{
				continue;
			}

			//Graphic Start
			if( CMD_KIND(m_Inpt2) == '#' && CMD_TYPE(m_Inpt2) == 0x0050 && nWait != -1 )
			{
				SET_BYTE( m_Inpt2, 11, 1 );
				SET_BYTE( m_Inpt2, 12, nWait );
				SET_BYTE( m_Inpt2, 14, byDivide2 );
				nWait = -1;
			}

			//コマンド書き込み
			m_Stack.Write( &m_Inpt2 );

			//Graphic End
			if( CMD_KIND(m_Inpt2) == '#' && CMD_TYPE(m_Inpt2) == 0x0051 )
				break;
		}
		--nGraphic2;
	}
	if( nRet < 0 )	return	nRet-50;

	return	nRet;
}
int CStackArp_MMB::ProcessFooter(int nGraphic, int nMultipass, int nRasterBit, int nDataSize, int nStartPos, UINT nWait, BYTE byHighlight)
{
	int		nRet = 0;

	BYTE	byDivide1 = byHighlight > 7 ? 0x16 : 0x12;
	BYTE	byDivide2 = byHighlight > 5 ? 0x00 : 0x14;

	ULONGLONG	nPosion = m_Stack.m_File.GetPosition();
	DWORD		dwSize;
	TByteArray	baParam;
	CCmdInk		cmdInk;

	//コマンド読み込み
	while( ( nRet = m_Inpt1.Read() ) > 0 )
	{
		//ジョブレイアウト
		if( CMD_KIND(m_Inpt1) == '#' && CMD_TYPE(m_Inpt1) == 0x0054 )
		{
            SET_BYTE( m_Inpt1, 14, byDivide1 );
			dwSize = CMD_SIZE( m_Inpt1 );
			baParam.Copy( m_Inpt1.m_baParam );
		}
		// インク使用量
		else if( CMD_KIND(m_Inpt1) == '#' && CMD_TYPE(m_Inpt1) == 0x0053 )
		{
			cmdInk.GetParam( &m_Inpt1 );
		}
	}
	if( nRet < 0 )	return	nRet;

	//コマンド読み込み
	while( ( nRet = m_Inpt2.Read() ) > 0 )
	{
		//ジョブレイアウト
		if( CMD_KIND(m_Inpt2) == '#' && CMD_TYPE(m_Inpt2) == 0x0054 )
		{
			ADD_SIZE( m_Inpt2, dwSize );
			SET_BYTE( m_Inpt2, 11, 1 );
			SET_BYTE( m_Inpt2, 12, nWait );
            SET_BYTE( m_Inpt2, 14, byDivide2 );
			m_Stack.Write( &m_Inpt2.m_baHead );
			m_Stack.Write( &baParam );
			m_Stack.Write( &m_Inpt2.m_baParam );
			continue;
		}
		// インク使用量
		else if( CMD_KIND(m_Inpt2) == '#' && CMD_TYPE(m_Inpt2) == 0x0053 )
		{
			cmdInk.AddParam_MMB( &m_Inpt2, byHighlight );
			cmdInk.SetParam( &m_Inpt2 );
		}
		//Job End
		else if( CMD_KIND(m_Inpt2) == 0x1B && JOB_TYPE(m_Inpt2) == '$' )
		{
			int	nFooter = (int)( m_Stack.m_File.GetPosition() - nPosion );	//Footerデータのサイズ
			SET_DWORD( m_Inpt2, 7, nFooter );

			m_Stack.Write( &m_Inpt2 );
			m_Stack.WriteLast();
			break;
		}
		//Preview
		else if( CMD_KIND(m_Inpt2) == '#' && CMD_TYPE(m_Inpt2) == 0x0065 )
		{
			continue;
		}

		//コマンド書き込み
		m_Stack.Write( &m_Inpt2 );
	}
	if( nRet < 0 )	return	nRet-50;

	return	nRet;
}


////////////////////////////////////////
//	Reversal対応

CReversalArp::CReversalArp(void)
{

}
CReversalArp::~CReversalArp(void)
{
	Close();
}

int CReversalArp::Open(LPCTSTR szIn, LPCTSTR szOut)
{
	int	nRet = m_InFile.Open( szIn, FALSE );
	if( nRet < 0 )	return -101;

	nRet = m_OutFile.Open( szOut, TRUE );
	if( nRet < 0 )	return -102;

	return	0;
}
int CReversalArp::Close()
{
	m_InFile.Close();
	m_OutFile.Close();

	return	0;
}
int CReversalArp::Process(BYTE byDoublePrint)
{
	const int TIM_TBL[5] = {    0,   25,   45,   70 };

	int				nRet = ProcessHeader();
	if( nRet >= 0 )	nRet = ProcessGraphic(TIM_TBL[byDoublePrint]);
	if( nRet >= 0 )	nRet = ProcessFooter(TIM_TBL[byDoublePrint]);

	return	nRet;
}

int CReversalArp::ProcessHeader()
{
	int		nRet = 0;
	BYTE	byPreviewPos = 0;

    while( ( nRet = m_InFile.Read() ) > 0 )
    {
		//Job Start
		if( CMD_KIND(m_InFile) == 0x1B && JOB_TYPE(m_InFile) == '@' )
		{
			if( GET_BYTE( m_InFile, 0 ) != 0x0C ) {	//コマンドバージョン
				nRet = -302;
				break;
			}
			if( GET_BYTE( m_InFile, 1 ) != 0x50 ) {	//ジョブ種別
				nRet = -303;
				break;
			}

            if( GET_BYTE( m_InFile, 7 ) != 0x14 ) { //使用ヘッド
				nRet = -401;
				break;
            }

			m_byGraphics = GET_BYTE( m_InFile, 8 );	//Graphics数
			byPreviewPos = GET_BYTE( m_InFile, 10 );//Preview位置
        }

		//コマンド書き込み
        m_OutFile.Write( &m_InFile );

		//ヘッド移動最適化モード指定		ヘッダの最終コマンド
		if( CMD_KIND(m_InFile) == '#' && CMD_TYPE(m_InFile) == 0x0008 && byPreviewPos != 0x01 )
			break;

		//プレビュー画像
		if( CMD_KIND(m_InFile) == '#' && CMD_TYPE(m_InFile) == 0x0065 )
			break;
    }

	return	nRet;
}

int CReversalArp::ProcessGraphic(UINT nWait)
{
	int		nRet = 0;

	UINT	nPosion = m_InFile.m_File.GetPosition();

	BYTE	byPauseSpan = 0;
    int     byGraphics = 0;
	BOOL	bSkip = FALSE;
    while( byGraphics < m_byGraphics && nRet >= 0 )
    {
        while( ( nRet = m_InFile.Read() ) > 0 )
        {
            //Graphic Start
            if( CMD_KIND(m_InFile) == '#' && CMD_TYPE(m_InFile) == 0x0050 )
            {
                BYTE byColor = GET_BYTE( m_InFile, 0 );
            //  BYTE byWhite = GET_BYTE( m_InFile, 1 );
				bSkip = ( byColor == 0 );

				if( ! bSkip ) {
					byPauseSpan = GET_BYTE( m_InFile, 12 );
					SET_BYTE( m_InFile, 14, nWait ? 1 : 0 );
					SET_BYTE( m_InFile, 11, nWait ? 1 : 0 );
					SET_BYTE( m_InFile, 12, nWait );
				}
            }

            //コマンド書き込み
			if( ! bSkip ) {
	            m_OutFile.Write( &m_InFile );
			}

			//Graphic End
			if( CMD_KIND(m_InFile) == '#' && CMD_TYPE(m_InFile) == 0x0051 )
				break;
		}

		++byGraphics;
    }

	m_InFile.m_File.Seek( nPosion, TFile::seekSet );

			byGraphics = 0;
			bSkip = FALSE;
	BOOL	bFirst = TRUE;
    while( byGraphics < m_byGraphics && nRet >= 0 )
    {
        while( ( nRet = m_InFile.Read() ) > 0 )
        {
            //Graphic Start
            if( CMD_KIND(m_InFile) == '#' && CMD_TYPE(m_InFile) == 0x0050 )
            {
            //  BYTE byColor = GET_BYTE( m_InFile, 0);
                BYTE byWhite = GET_BYTE( m_InFile, 1);
				bSkip = ( byWhite == 0 );

				if( !bSkip && bFirst ) {
					bFirst = FALSE;
					SET_BYTE( m_InFile, 11, byPauseSpan ? 1 : 0 );
					SET_BYTE( m_InFile, 12, byPauseSpan );
				}
            }

            //コマンド書き込み
			if( ! bSkip ) {
	            m_OutFile.Write( &m_InFile );
			}

			//Graphic End
			if( CMD_KIND(m_InFile) == '#' && CMD_TYPE(m_InFile) == 0x0051 )
				break;
		}

		++byGraphics;
    }

	return	nRet;
}

int CReversalArp::ProcessFooter(UINT nWait)
{
	int		nRet = 0;

    while( ( nRet = m_InFile.Read() ) > 0 )
    {
		//ジョブレイアウト
		if( CMD_KIND(m_InFile) == '#' && CMD_TYPE(m_InFile) == 0x0054 )
        {
			TByteArray baParam;
			baParam.Copy(m_InFile.m_baParam);

			const int LAYER_SIZE = 0x20;
			BYTE	byPauseSpan = 0;
		    int     byGraphics = 0;
			int		layers = baParam.GetSize() / LAYER_SIZE;

			for( int i=0; i < layers; ++i ) {
              	BYTE byColor = baParam[ 0 + i * LAYER_SIZE ];
            //	BYTE byWhite = baParam[ 1 + i * LAYER_SIZE ];
				if( byColor == 0 ) {
					continue;
				}

				memcpy( &m_InFile.m_baParam[ byGraphics * LAYER_SIZE ], &baParam[ i * LAYER_SIZE ], LAYER_SIZE );
				byPauseSpan = GET_BYTE( m_InFile, 12 + byGraphics * LAYER_SIZE );
				SET_BYTE( m_InFile, 14 + byGraphics * LAYER_SIZE, nWait ? 1 : 0 );
				SET_BYTE( m_InFile, 11 + byGraphics * LAYER_SIZE, nWait ? 1 : 0 );
				SET_BYTE( m_InFile, 12 + byGraphics * LAYER_SIZE, nWait );
				++byGraphics;
			}

			BOOL	bFirst = TRUE;
			for( int i=0; i < layers; ++i ) {
            	BYTE byWhite = baParam[ 1 + i * LAYER_SIZE ];
				if( byWhite == 0 ) {
					continue;
				}

				memcpy( &m_InFile.m_baParam[ byGraphics * LAYER_SIZE ], &baParam[ i * LAYER_SIZE ], LAYER_SIZE );
				if( bFirst ) {
					bFirst = FALSE;
					SET_BYTE( m_InFile, 11 + byGraphics * LAYER_SIZE, byPauseSpan ? 1 : 0 );
					SET_BYTE( m_InFile, 12 + byGraphics * LAYER_SIZE, byPauseSpan );
				}
				++byGraphics;
			}

        }

        //コマンド書き込み
        m_OutFile.Write( &m_InFile );

		//Job End
		if( CMD_KIND(m_InFile) == 0x1B && JOB_TYPE(m_InFile) == '$' )
		{
			m_OutFile.WriteLast();
			break;
		}
    }

	return	nRet;
}

