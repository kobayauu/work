#include "gtx.h"
#include "gtx6sp.h"
#include "modpal.h"


///////////////////////////////////////////////////////////
// 関数：内部関数


namespace {


PLATEN_INFO OptionToPlatenInfo( GTX6SPOPTION Option )
{
	PLATEN_INFO listPlaten[7] = {
		{ "16x21",  9600,12600,  -600, -591 },
		{ "16x18",  9600,10800,  -600, -600 },
		{ "14x16",  8400, 9600,     0,    0 },
		{ "10x12",  6000, 7200,  1200, 1200 },
		{ "7 x 8",  4200, 4800,  2100, 1800 },
		{ "24x24", 14400,14400, -3000,-1169 },
		{ "18x22", 10800,13200, -1200, -694 },
	};

	return	listPlaten[ Option.byPlatenSize ];
}

PLATEN_HEIGHT OptionToPlatenHeight( GTX6SPOPTION Option )
{
	PLATEN_HEIGHT PlatenInfo = {
		Option.bPlatenHeight,
		Option.byPlatenHeightPos
	};
	return	PlatenInfo;
}

WHITEDATA_TYPE OptionToWhiteData( GTX6SPOPTION Option )
{
	int listCalVolue[6] = { 20, 0, 10, 20, 30, 40 };

	WHITEDATA_TYPE	WhiteDataType;
	memset( &WhiteDataType, 0, sizeof(WhiteDataType) );

	WhiteDataType.bWhite			= UseWhite( Option.byInk );
	WhiteDataType.InType			= ( UseWhiteColor( Option.byInk ) ? Option.bMaterialBlack ? WHITE_IN_WCMY : WHITE_IN_WCMY_PLUS_K : WHITE_IN_MONO );
	WhiteDataType.bW4				= FALSE;

	WhiteDataType.iWhiteTime		= GTX6SP_GetPrintTime( Option );
	WhiteDataType.iCutOutline_X		= 
	WhiteDataType.iCutOutline_Y		= Option.byChoke;
	WhiteDataType.bNotCutOnlyWhite	= TRUE;
	WhiteDataType.iCalVolume		= listCalVolue[ Option.byMask ];
	WhiteDataType.iMaskVolume		= Option.byMask;
	WhiteDataType.iWhiteLight		= Option.byHighlight;
//	WhiteDataType.iWhiteInkMax
//	WhiteDataType.iWhiteInkMin
//	WhiteDataType.iWhiteCount
	WhiteDataType.iWhiteMax			= GTX6SP_GetWhiteness( Option );
	WhiteDataType.iWhiteMin			= Option.byMinWhite;

	//Highlight
	WhiteDataType.iWhiteCompact		= AR_WRC_ALL_a;
	if( WhiteDataType.bWhite //&& Option.byHighlight > 5
	&& ( ! Option.bMultiple || Option.bPause || (Option.bDivide && (Option.byResolution == 1 || Option.byResolution == 4)) ) ) {
	//	WhiteDataType.iWhiteCompact	= AR_WRC_DIVIDE;	// 2pass
		WhiteDataType.iWhiteCompact	= AR_WRC_INTRLC;	// 1pass
	}
	WhiteDataType.bWhitePale        = TRUE;
	WhiteDataType.bEcoMode          = Option.bEcoMode;
	WhiteDataType.bNonBleed         = Option.bNonBleed;
//	WhiteDataType.bFastMode         = Option.bFastMode;

	return	WhiteDataType;
}

ENVIRONMENT_TYPE GTX6SP_SUB_OptionToEnvironData( GTX6SPOPTION Option )
{
	ENVIRONMENT_TYPE	EnvironType = {};

    BYTE    byAppType = Option.uiReserved1 & 0xFF;
	EnvironType.byAppType = byAppType ? byAppType : 4;

	if( EnvironType.byAppType == 3 )
	{
		EnvironType.dwVersion[0] = -1;	//Application
		EnvironType.dwVersion[2] = Option.uiReserved2;
	}
	else
	{
		EnvironType.dwVersion[0] = Option.uiReserved2;
		EnvironType.dwVersion[1] = -1;	//API
	}
	GTX_SUB_OptionToEnvironData( (BYTE *) &EnvironType, TYPE_GTX6SP );

	return	EnvironType;
}


}	//namespace


///////////////////////////////////////////////////////////
// 関数：印刷変数


PRINT_INFO GTX6SP_OptionToPrintInfo( GTX6SPOPTION Option )
{
    PRINT_INFO	PrintInfo = {};

	PrintInfo.PrintMode				= (PRINT_MODE) Option.byInk;
	PrintInfo.PrintSubMode			= (PRINT_SUBMODE) Option.bySubInk;
	PrintInfo.PlatenInfo			= OptionToPlatenInfo( Option );
	PrintInfo.PlatenHeight			= OptionToPlatenHeight( Option );
	PrintInfo.CompressionType		= COMPRESSION_TYPE_TIFF;
	PrintInfo.iRateOfCompress		= RATEOFDOORDONOTCOMPRESS;
	PrintInfo.iNumOfCopies			= (int) Option.uiCopies;
//	strncpy( PrintInfo.cJobComent, Option.szJobComment, JOB_COMENT_MAX_SIZE );
	strncpy( PrintInfo.cJobName  , Option.szJobName   , JOB_NAME_MAX_SIZE   );
	PrintInfo.bHeadFastMoving		= TRUE;
	PrintInfo.DoublePrint			= DOUBLE_PRINT_OFF;
//	PrintInfo.bReturnPrint
	PrintInfo.bUniDirection			= Option.bUniDirection;

//	PrintInfo.byCRTimes
//	PrintInfo.byCR_CLR

	PrintInfo.bChksum				= FALSE;
	PrintInfo.bEndlessPrn			= FALSE;

	PrintInfo.MachineMode			= MACHINE_MODE_GTX622;  //(MACHINE_MODE) Option.byMachineMode;
	PrintInfo.bBlackTs				= Option.bMaterialBlack;
	PrintInfo.bMultiPass			= Option.bMultiple;
	PrintInfo.iEnhancedBlack		= Option.byDoublePrint;

	PrintInfo.bColorToWhite			= 0;

	return	PrintInfo;
}

OUTPUT_INFO GTX6SP_OptionToOutputInfo( GTX6SPOPTION Option, BOOL bHeaderPreview )
{
    OUTPUT_INFO	OutPutInfo = {};

	RESOLUTION_X const IDArrayX[] = { RESOLUTION_X_600, RESOLUTION_X_1200, RESOLUTION_X_1200, RESOLUTION_X_1200, RESOLUTION_X_1200 };
	RESOLUTION_Y const IDArrayY[] = { RESOLUTION_Y_600, RESOLUTION_Y_1200, RESOLUTION_Y_900 , RESOLUTION_Y_600 , RESOLUTION_Y_1200 };
	OutPutInfo.Resolution.XRes		= IDArrayX[ Option.byResolution ];
	OutPutInfo.Resolution.YRes		= IDArrayY[ Option.byResolution ];
	OutPutInfo.bHighQuality			= (Option.byResolution == 4);
	OutPutInfo.DoublePrint			= DOUBLE_PRINT_OFF;
	OutPutInfo.PreviewPos			= ( Option.byTransLayer == TRANS_LAYER_CREATE ? PREVIEW_POS_NONE : 
										bHeaderPreview ? PREVIEW_POS_HEADER : PREVIEW_POS_FOOTER );
	OutPutInfo.bAutoSetting			= TRUE;
	OutPutInfo.WhiteDataType		= OptionToWhiteData( Option );

	OutPutInfo.bTransColor			= Option.bTransColor;
	OutPutInfo.colorTrans			= Option.colorTrans;
	OutPutInfo.iTRRange				= Option.byTolerance + 1;
	OutPutInfo.iVivid				= Option.byContrast;
	OutPutInfo.iBrightness			= Option.byBrightness;
	OutPutInfo.iChromaUp			= Option.bySaturation;
	OutPutInfo.bDivide				= Option.bDivide;
	OutPutInfo.iDivideSpan			= Option.byDivideSpan;
	OutPutInfo.bPause				= Option.bPause;
	OutPutInfo.iPauseSpan			= Option.byPauseSpan;

	OutPutInfo.iCyanBalance			= Option.iCyanBalance;
	OutPutInfo.iMagentaBalance		= Option.iMagentaBalance;
	OutPutInfo.iYellowBalance		= Option.iYellowBalance;
	OutPutInfo.iBlackBalance		= Option.iBlackBalance;
	OutPutInfo.iSpecial1Balance		= Option.iSpecial1Balance;
	OutPutInfo.iSpecial2Balance		= Option.iSpecial2Balance;
	OutPutInfo.ColorMode			= (COLOR_MODE) Option.byColorMode;

	OutPutInfo.InkVolume			= (INK_VOLUME) ( 10 - Option.byInkVolume );
//	OutPutInfo.cCalFilePath
//	OutPutInfo.cProfileFilePath
//	OutPutInfo.cImproveFilePath

	OutPutInfo.iInkLimit			= INK_LIMIT;
//	OutPutInfo.colormatch_type
//	OutPutInfo.BinarizationType
	OutPutInfo.bUseCalInInputCMYK	= FALSE;
//	OutPutInfo.fInkLimit_A_Param

	OutPutInfo.MachineMode			= MACHINE_MODE_GTX622;	//(MACHINE_MODE) Option.byMachineMode;
	OutPutInfo.bWhiteGrad			= FALSE;	//! Option.bCMYGray;

	OutPutInfo.TransLayer			= (TRANS_LAYER) Option.byTransLayer;
	strncpy( OutPutInfo.cTransFilePath, Option.szTransFile, MAX_PATH );
	OutPutInfo.bPureCMYK			= 0;
	OutPutInfo.bInputCMYK			= 0;

	OutPutInfo.EnvironType			= GTX6SP_SUB_OptionToEnvironData( Option );

	return	OutPutInfo;
}
