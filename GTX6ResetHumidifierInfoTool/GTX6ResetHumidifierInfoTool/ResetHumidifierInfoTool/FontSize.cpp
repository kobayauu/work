#include "StdAfx.h"
#include ".\fontsize.h"

//初めにブロックを１つ作成する。
//ブロック１つに付き、フォントをiBLOCK_SIZE個
//保存できる。ブロックが一杯になったら、
//ArrocOneBlockを呼んでブロックを追加する

static const int iBLOCK_SIZE = 10;	//１つのブロックにいくつフォントを保存するか

CFontSize::CFontSize(void)
{
	m_iNum		= 0;
	m_iBlockNum = 0;
	m_ppFont	= NULL;
	//初めにブロックを１つ作成する。
	ArrocOneBlock();
}


CFontSize::~CFontSize(void)
{
	//m_ppFontの開放
	for( int i=0 ; i < m_iBlockNum ; i++ )
	{
		delete [] m_ppFont[i];//DeleteObject()は必要なし
	}
	if( m_ppFont ) delete [] m_ppFont;
}

//ブロック(CFontのポインタ)をm_ppFontに追加する
BOOL CFontSize::ArrocOneBlock()
{
	BOOL bRet = FALSE;

	//CFontポインタの配列を作成　m_ppFontより１つ多くブロックを作成する
	CFont** ppFont = (CFont**) new CFont*[ ( m_iBlockNum + 1 ) ];

	if( ppFont )
	{
		for( int i=0 ; i < m_iBlockNum ; i++ )
		{//既存ブロックをコピー
			ppFont[i] = m_ppFont[i];
		}
		//m_ppFontを削除し、ppFontをm_ppFontとする
		if( m_ppFont ) delete [] m_ppFont;
		m_ppFont = ppFont;

		//新たに作ったブロックにiBLOCK_SIZE個の領域を確保する
		m_ppFont[ m_iBlockNum ] = (CFont*) new CFont[ iBLOCK_SIZE ];
		if( m_ppFont[ m_iBlockNum ] )
		{
			m_iBlockNum++;
			bRet = TRUE;
		}
	}
	return bRet;
}

//フォントサイズを変更する
BOOL CFontSize::ChangeFontSize( CWnd* pWnd , int iSize , int iWeight /* = FW_NORMAL */ )
{
	BOOL bRet = TRUE;

	if(  m_iBlockNum == 0 || m_iNum == iBLOCK_SIZE )
	{//ブロックが無いか、一杯の時
		//ブロックを追加する
		bRet = ArrocOneBlock();
		m_iNum = 0;
	}

	if( bRet )
	{
		CFont *pOldfont;
		LOGFONT Logfont;

		pOldfont = pWnd->GetFont();//現在のフォントを取得　（テンポラリポインタ）
		pOldfont->GetLogFont( &Logfont );//フォント情報の取得

		//フォント情報の変更
		Logfont.lfHeight = iSize;
		Logfont.lfWeight = iWeight;
		
		//変更したフォント情報からフォントの作成　
		//m_ppFont[ m_iBlockNum - 1 ][ m_iNum ]を開放するとフォントも開放されるので
		//あとでDeleteOblect()は必要ない
		m_ppFont[ m_iBlockNum - 1 ][ m_iNum ].CreateFontIndirect( &Logfont );
		//フォントをセットする
		pWnd->SetFont( &m_ppFont[ m_iBlockNum - 1 ][ m_iNum ] );
		m_iNum++;
	}

	return bRet;
}