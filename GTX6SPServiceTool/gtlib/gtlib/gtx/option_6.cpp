#include "gtx.h"
#include "gtx6.h"
#include <sys/stat.h>


///////////////////////////////////////////////////////////
// 関数：印刷設定

//印刷設定の修正
void GTX6_ModifyOption( GTX6OPTION* pOption )
{
	bool bReversal	= pOption->uiReserved1 & CONFIG_REVERSAL;

	if( ! UseWhiteColor( pOption->byInk ) ) {
			pOption->byChoke		= 0;
		//	pOption->bFastMode		= ( pOption->byInk == PRINT_MODE_WHITE_ONLY );
			pOption->bEcoMode		= FALSE;
	}
	if( pOption->byInk == PRINT_MODE_WHITE_ONLY ) {
			pOption->bMultiple		= FALSE;
	}

	if( ! UseWhite( pOption->byInk ) ) {
			pOption->bTransColor	= FALSE;
			pOption->colorTrans		= 0xFFFFFF;
	}
	else if( ! bReversal ) {
			pOption->byDoublePrint	= DOUBLE_PRINT_OFF;
			pOption->byInkVolume	= 10;
	}

	if( pOption->byResolution != 1 
	&&	pOption->byResolution != 4 ) {
			pOption->bDivide		= FALSE;
			pOption->bPause			= FALSE;
			pOption->bMultiple		= FALSE;
			pOption->bUniDirection	= FALSE;
			pOption->byDoublePrint	= DOUBLE_PRINT_OFF;
	}
}

//白インク量
int GTX6_GetWhiteness( GTX6OPTION Option )
{
	bool bReversal	= Option.uiReserved1 & CONFIG_REVERSAL;

	int tblWhiteness[14] = { 0, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800 };
	int tblReversal [14] = { 0,  50,  75, 100, 125, 150, 175, 200, 225, 250, 275, 300, 325, 350 };

	if( ! UseWhite( Option.byInk ) ) {
		return	0;
	}

	return	bReversal ? tblReversal [ Option.byHighlight ]
				  	  : tblWhiteness[ Option.byHighlight ];
}

//印刷時間
int GTX6_GetPrintTime( GTX6OPTION Option )
{
	int tblWhiteTime[2][5][14] = {
		{ { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },	//GTX611
		  { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 },
		  { 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3 },
		  { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },
		  { 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 } },
		{ { 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 },	//GTX622
		  { 4, 4, 4, 4, 4, 4, 5, 5, 6, 6, 8, 8, 8, 8 },
		  { 3, 3, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8 },
		  { 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8 },
		  { 4, 4, 4, 4, 4, 4, 5, 5, 6, 6, 8, 8, 8, 8 } },
	};
	int tblColorTime[5] = { 2, 4, 3, 2, 4 };

    if( Option.bDivide )	Option.byHighlight = 0;
	int byMachine  = ( Option.uiReserved1 & CONFIG_REVERSAL ) ? 0 : 1;
	int nWhiteTime = tblWhiteTime[ byMachine ][ Option.byResolution ][ Option.byHighlight ];
	int nColorTime = tblColorTime[ Option.byResolution ] * ( Option.bMultiple ? 2 : 1 );

	if     ( ! UseWhite( Option.byInk ) )				return	nColorTime;
	else if( Option.byInk == PRINT_MODE_WHITE_ONLY )	return	nWhiteTime * ( Option.bDivide ? 2 : 1 );
    else if( Option.bPause && Option.bDivide )			return  nWhiteTime * 2 + nColorTime;
    else if( Option.bPause || Option.bDivide )			return  nWhiteTime + nColorTime;
	else												return	max( nWhiteTime, nColorTime );
}
int GTX6_GetPrintTimeDisp( GTX6OPTION Option, GTX_PRINTER_TYPE type )
{
	int		nPrintTime	= GTX6_GetPrintTime( Option ) * 25;
	int		nPassRate 	= ( Option.byResolution == 4 ? (GTX_GetCustomMode(type) & 4 ? 15 : 14) : 10 );

	if( Option.bMultiple )		nPrintTime  = (nPrintTime - 200) * nPassRate / 10 + 200;
	else						nPrintTime  = nPrintTime * nPassRate / 10;

	return	nPrintTime * ( Option.bUniDirection ? 2 : 1 );
}

//オプションの値のチェック
int GTX6_CheckOption( GTX6OPTION Option, GTX_PRINTER_TYPE type, BOOL bFreeCustom )
{
	#define OVER(x,l,h) (x<l || h<x)

	bool bRes0606	= bFreeCustom || GTX_GetCustomMode(type) & 1;
	bool bMinWhite0	= bFreeCustom || GTX_GetCustomMode(type) & 2;
	bool bReversal	= Option.uiReserved1 & CONFIG_REVERSAL;
	bool bMMC		= Option.uiReserved1 & CONFIG_MMC;
	bool bCMYK		= ( Option.byInk == PRINT_MODE_WHITE_COLOR || Option.byInk == PRINT_MODE_COLOR_ONLY );

    if( Option.szFileName[0] )
    {
        struct stat buf;
        int ret = stat( Option.szFileName, &buf );
        if( ret != 0 && S_ISDIR(buf.st_mode) )			return	-1101;
    }
	    if( OVER( Option.uiCopies     , 1, 999 ) )		return	-1102;

//		Option.byMachineMode									-1103
//		Option.szJobName										-1104
		if( OVER( Option.byPlatenSize , 1,   6 ) )		return	-1105;
//		Option.bPlatenHeight									-1139
	if( Option.bPlatenHeight ) {
		if( OVER( Option.byPlatenHeightPos , 0 , 7 ) )	return	-1039;
	}
		if( OVER( Option.byInk        , 0,   3 ) )		return	-1106;
//		Option.bySubInk											-1140
//		Option.byColorMode										-1141
//		Option.bEcoMode											-1134
//		Option.bNonBleed										-1144
		BYTE	b = bRes0606 ? 0 : 1;
		BYTE	t = UseWhite( Option.byInk ) ? 4 : 3;
		if( OVER( Option.byResolution , b,   t ) )		return	-1107;
	if( ! UseWhite( Option.byInk )
	||	bReversal ) {
		if( OVER( Option.byInkVolume    , 1,  10 ) )	return	-1110;
		if( OVER( Option.byDoublePrint  , 0,   3 ) )	return	-1111;
	}
	if( UseWhite( Option.byInk ) ) {
		BYTE	b;
		if( ! bReversal )
		{
			b = Option.byResolution == 1 ? ( Option.bDivide ? 13 : 9 ) :
				Option.byResolution == 4 ? 5 :
				Option.byResolution == 2 ? 3 : 1;
		}
		else
		{
			b = Option.byResolution == 3 ?  7 :
				Option.byResolution == 2 ? 11 : 13;
		}
		if( OVER( Option.byHighlight  , 1,   b ) )		return	-1108;
		if( OVER( Option.byMask       , 1,   5 ) )		return	-1109;
	}
//		Option.bFastMode										-1138
    if( UseWhiteColor( Option.byInk ) && Option.bPause )
    {
//		Option.bPause											-1119
		if( OVER( Option.byPauseSpan  , 0,  60 ) )		return	-1135;
    }
	if( UseWhite( Option.byInk ) && Option.bDivide )
    {
//		Option.bDivide											-1136
		if( OVER( Option.byDivideSpan , 0,  60 ) )		return	-1137;
    }

//		Option.bMaterialBlack									-1112
//		Option.bMultiple										-1113

	//Advanced
//		Option.bTransColor										-1114
//		Option.colorTrans										-1115
	if( UseWhite( Option.byInk ) && Option.bTransColor )
	{
		if( OVER( Option.byTolerance  , 0,  50 ) )		return	-1116;
	}
	if( UseWhiteColor( Option.byInk ) )
	{
		BYTE	b = bMinWhite0 ? 0 : 1;
		if( OVER( Option.byMinWhite   , b,  6  ) )		return	-1117;
				b = bMMC ?  4 :  0;
		BYTE	t = bMMC ? 14 : 10;
		if( OVER( Option.byChoke      , b,   t ) )		return	-1118;
	}
		if( OVER( Option.bySaturation , 0,  40 ) )		return	-1120;
		if( OVER( Option.byBrightness , 0,  40 ) )		return	-1121;
		if( OVER( Option.byContrast   , 0,  40 ) )		return	-1122;
	if( bCMYK ) {
		if( OVER( Option.iCyanBalance    , -5, 5 ) )	return	-1123;
		if( OVER( Option.iMagentaBalance , -5, 5 ) )	return	-1124;
		if( OVER( Option.iYellowBalance  , -5, 5 ) )	return	-1125;
	}
	if( bCMYK || Option.byInk == PRINT_MODE_COLOR_MONO ) {
		if( OVER( Option.iBlackBalance   , -5, 5 ) )	return	-1133;
	}
//		Option.iSpecial1Balance									-1142
//		Option.iSpecial2Balance									-1143
//		Option.bUniPrint										-1126

    //Other
		if( OVER( Option.byTransLayer , 0,   2 ) )		return	-1127;
    if( Option.byTransLayer == TRANS_LAYER_IMPORT )
    {
        //ARTRファイルの読み込み
        FILE* fp = fopen( Option.szTransFile, "rb" );
        if( fp == NULL )								return	-1128;
        
        BYTE		szBuff[16];
        size_t      szRead = fread( szBuff, 1, 16, fp );
        fclose( fp );
        if( szRead != 16 )								return	-1129;
        
        //内容の確認
        const BYTE	ARCMD[] = { '#','#',0,0, 0,0,0,8 };
        if( memcmp( szBuff, ARCMD, 8 ) != 0 )			return	-1130;
	   	if( Option.byResolution != szBuff[10] )			return  -1131;
        if( Option.byPlatenSize != szBuff[11] )			return	-1132;
    }
    
    return	0;

#undef OVER
}
