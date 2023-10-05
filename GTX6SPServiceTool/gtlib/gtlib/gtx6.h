#pragma once

#include <stdio.h>
#include <memory.h>

#include "ospal.h"
#include "gtx.h"
#include "Gtx6Info.h"


#ifdef GTX6API
    #include "GTApi.h"
#else	//GTX6API

#define	MAX_JOBCOMMENT	128
#define	MAX_JOBNAME		128
#define	MAX_PLATENSIZE	8
#define	MAX_DATESIZE	20

#pragma pack(push,1)
typedef struct _GTX6_OPTION
{
	CHAR		szFileName[MAX_PATH];	//Output File Name				NONE = not output file
	UINT		uiCopies;				//Number of Copies				1-999

	//MainSetting
//	BYTE		byMachineMode;			//Machine Mode					0:GTX-6

	CHAR		szJobName[MAX_JOBNAME];	//Job Name = Document name		NONE = "No Name"
	BYTE		byPlatenSize;			//Platen Size					1:16x18 2:14x16 3:10x12 4:7x8 5:24x24 6:18x22
	BOOL		bPlatenHeight;			//Platen Height
	BYTE		byPlatenHeightPos;		//								0-7:A-H
	BYTE		byInk;					//Ink							0:Color Only 1:White Only 2:Color+White 3:Black Only
	BYTE		byResolution;			//Resolution					0:600x600dpi 1:1200x1200dpi 2:1200x900dpi 3:1200x600dpi 4:1200x1200HQ
	BOOL		bEcoMode;				//Eco Mode

	BYTE		byHighlight;			//Highlight		(White)			1-9
	BYTE		byMask;					//Mask			(White)			1-5
	BYTE		byInkVolume;			//Ink Volume	(Color Only)	1-10
	BYTE		byDoublePrint;			//Double Print	(Color Only)	0-3

//	BOOL		bFastMode;				//Fast Mode
	BOOL		bDivide;				//2 Layer White
	BYTE		byDivideSpan;
	BOOL		bPause;					//White/Color Pause
	BYTE		byPauseSpan;

	BOOL		bMaterialBlack;			//Show Material as Black
	BOOL		bMultiple;				//Color Multiple Pass Printing

	//Advanced
	BOOL		bTransColor;			//Transparent Color
	COLORREF	colorTrans;				//Transparent Color
	BYTE		byTolerance;			//Tolerance						0-50
	BYTE		byMinWhite;				//Minimum White					1-6
	BYTE		byChoke;				//Choke							0-10

	BYTE		bySaturation;			//Saturation					0-40
	BYTE		byBrightness;			//Brightness					0-40
	BYTE		byContrast;				//Contrast						0-40

	INT			iCyanBalance;			//Color Balance	(Cyan)			-5 +5
	INT			iMagentaBalance;		//Color Balance	(Magenta)		-5 +5
	INT			iYellowBalance;			//Color Balance	(Yellow)		-5 +5
	INT			iBlackBalance;			//Color Balance	(blacK)			-5 +5

	BOOL		bUniDirection;			//Uni-Directional Printing

	//Other
	BYTE		byTransLayer;			//Transparent Layer				0:OFF 1:Create ARTR 2:Import ARTR
	CHAR		szTransFile[MAX_PATH];	//Import ARTR File

	UINT		uiReserved1;			//Reserved
	UINT		uiReserved2;			//Reserved
	UINT		uiReserved3;			//Reserved
	UINT		uiReserved4;			//Reserved

} GTX6OPTION;
#pragma pack(pop)

#endif  //GTX6API


#define CONFIG_MMC		(1 << 16)
#define CONFIG_REVERSAL	(2 << 16)

#define IsValiedHandle(x)   ( (x) != NULL && (x) != INVALID_HANDLE_VALUE )

#define UseWhiteColor(X)	( X == PRINT_MODE_WHITE_COLOR )
#define UseWhite(X)			( X == PRINT_MODE_WHITE_COLOR || X == PRINT_MODE_WHITE_ONLY )


#ifdef __cplusplus
extern "C" {
#endif


//option.cpp
void GTX6_ModifyOption( GTX6OPTION* pOption );
int GTX6_GetWhiteness( GTX6OPTION Option );
int GTX6_GetPrintTime( GTX6OPTION Option );
int GTX6_GetPrintTimeDisp( GTX6OPTION Option, GTX_PRINTER_TYPE type );
int GTX6_CheckOption( GTX6OPTION Option, GTX_PRINTER_TYPE type, BOOL bFreeCustom );

//info.cpp
PRINT_INFO GTX6_OptionToPrintInfo( GTX6OPTION Option );
OUTPUT_INFO GTX6_OptionToOutputInfo( GTX6OPTION Option, BOOL bHeaderPreview );


#ifdef __cplusplus
}   //extern "C"
#endif
