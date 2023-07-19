// BGJServTool.h : BGJSERVTOOL アプリケーションのメイン ヘッダー ファイルです。
//

#if !defined(AFX_BGJSERVTOOL_H__257F0691_57C6_4667_98E5_E2C69366A1BF__INCLUDED_)
#define AFX_BGJSERVTOOL_H__257F0691_57C6_4667_98E5_E2C69366A1BF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// メイン シンボル
//#include "BGJPrinter.h"	// ClassView によって追加されました。
#include "EEPFile.h"
#include "GTlogFile.h"

typedef enum
{
	COURSE_NONE ,			
	COURSE_INIT_SETTING	,
	COURSE_REGULAR_CHECK ,
	COURSE_PARTS_CHANGE ,	
	COURSE_BATTERY_CHANGE ,
	COURSE_MAIN_BOARD_CHANGE ,
	COURSE_POWER_BOARD_CHANGE ,
	COURSE_CR_ADJ ,		
	COURSE_CR_BOARD_CHANGE ,	
	COURCE_FIRING_ADJUST ,
	COURSE_CR_MOTOR ,		
	COURSE_PUMP_CHANGE ,
	COURSE_SET_DATE ,
	COURSE_SET_LR   ,
	COURSE_RESET_TUBE , 
	COURSE_LCD_BOARD,
	COURSE_HUMID_FAN,

} COURSE_TYPE;


typedef enum 
{
		SIDE_NONE ,	
		SIDE_LEFT ,	
		SIDE_RIGHT ,	
		SIDE_BOTH ,
} SIDE_TYPE;


#define COLOR_K 0x0008
#define COLOR_C 0x0004
#define COLOR_M 0x0002
#define COLOR_Y 0x0001
#define COLOR_ALL (COLOR_K|COLOR_M|COLOR_C|COLOR_Y)

#define INDEX_K	0
#define INDEX_M	1
#define INDEX_C	2
#define INDEX_Y	3

#define COLOR4  4

/////////////////////////////////////////////////////////////////////////////
// CBGJServToolApp:
// このクラスの動作の定義に関しては BGJServTool.cpp ファイルを参照してください。
//

class CBGJServToolApp : public CWinApp
{
public:
	bool GetTimeZoneInfoStr( CString& csZone );
	int GetTimeZoneDiff();
	long GetCurrentGMTSecond(time_t dwTime=0);
	int m_iFirmUpdStepNumber;
	CString m_csExeFolder;
	LPCTSTR GetExeFolder();
	bool m_bTemplateIsInResource;
	bool SerialUpdate();
	bool SerialAndLotInit( int nPC, int nSerial, int nLot);
	bool SerialAndLotLoad( int* pPC, int* pSerial, int* pLot );
	int m_nFireAdjPatNum[4];
	int m_nChangedHeadColor;
	static void DebugMsg( LPCTSTR pszFmt, ... );
	CTime m_ctHDVoltStart;
	LPCTSTR GetNewFirmPath();
	CString m_csLogFileName;
	CString m_csLogVersion;
	LPCTSTR GetPrinterDataSavePath();
	bool SetPrinterDataSavePath( LPCTSTR lpszSavePath );
	void SetCourse( COURSE_TYPE Course );
	COURSE_TYPE GetCourse();
	void SetSide( SIDE_TYPE Side );
	SIDE_TYPE GetSide();
	bool IsOnline();
	void IDDClear();
	int IDDPop();
	int IDDPush( int nIDD );
	int IDDPeek();
	CString m_csDataSaveDir;
	LPCTSTR GetToolStartDateStr();
	int GetPrevIDD();
	int SetPrevIDD( int nPrevIDD );
	bool CheckFolder( LPCTSTR pszPath );
//	CBGJPrinter m_Prn;
	bool IsEng();
	LPCTSTR GetPrinterName();
	void SetPrinterName( LPCTSTR pszPrinterName );
	LPCTSTR GetTemplatePath();
	LPCTSTR GetLogPath();
	LPCTSTR GetDataPath();
	CString m_csPrinterName;
	void LocalMessageLoopExec();
	CBGJServToolApp();
	LCID GetLCID();
	void RunMaintenanceTool();
	int GetGTPrinters( CComboBox* pPrinterComBox );
	int ResetEEPROM8014();
	int ResetIpAddress();
	int ResetMoter();
	int ResetBattery();
	int ResetTubeClearning();
	int ResetTubePump();
	int AdjustCRSpeed();
	int SetTemperature(DWORD dwTemperature);
	int SetRTC( DWORD dwInternal );
	int SetEighteenCode( CString csCode );
	int SetSerialCode( CString csCode );
	int RestoreEEPROMAndSetRTCAndBackup(DWORD dwInternal);
	int SetRTCAndResetEEPROM8014( DWORD dwInternal );
	int BackupEEPROM();
	int SetInitInkState(DWORD dwK, DWORD dwYCM, DWORD dwW1, DWORD dwW2W4);
	int SetAssembleFlag(DWORD dwParam);
	int SetWhiteHalt(DWORD dwParam);
	int SetRTCAndBattery( DWORD dwInternal );
	int ResetHumidFanFilter();

	// 小林追加
	void SetDemo();
	void RunFirmUpdate_GTX6();
	void RunFirmUpdate_GTX6SP();
	int FetchFirmwareVersion(DWORD* pdwFirmVer);
	int CheckVersion(DWORD dwVersion);


// オーバーライド
	// ClassWizard は仮想関数のオーバーライドを生成します。
	//{{AFX_VIRTUAL(CBGJServToolApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// インプリメンテーション

	//{{AFX_MSG(CBGJServToolApp)
		// メモ - ClassWizard はこの位置にメンバ関数を追加または削除します。
		//        この位置に生成されるコードを編集しないでください。
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
protected:
	bool m_bServiceTool;
	void SerialAndLotFileName();
	CString m_csSerialAndLot;
	CString m_csNewFirmPath;
	CString m_csPrinterDataSavePath;
	COURSE_TYPE m_Course;
	SIDE_TYPE   m_Side;
	bool m_bOffTest;
	CArray<int, int> m_IDDArray;
	CString m_csStartDate;
	int m_nPrevIDD;
	bool m_bIsJapanese;
	CString m_csExecuteDate;
	CString m_csPrinterProductNumber;
	CString m_csTemplatePath;
	CString m_csLogPath;
	CString m_csDataPath;
	CString m_csExePath;
	LCID m_lcid;

	int GetProgramFilesPath( CString* pstrPath );

public:
	int m_iMBChangeFlag;

};


/////////////////////////////////////////////////////////////////////////////

static const TCHAR cszServSection[] = _T("GTX6Service");
static const TCHAR cszPrinterName[] = _T("PrinterName");
static const TCHAR csDefaultPrinterName[] = _T("Brother GTX-6");
static const TCHAR cszTempUnit[] = _T("TempUnit");
static const TCHAR cszEmptyReadCount[] = _T("EmptyReadCount");
static const TCHAR cszOneReadByte[] = _T("OneReadByte");
static const TCHAR cszReadWaitMillisec[] = _T("ReadWaitMillisec");
static const TCHAR cszWaitAfterSendMillisec[] = _T("WaitAfterSendMillisec");
static const TCHAR cszHeadCheckMovePos[] = _T("HeadCheckmovePos");

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ は前行の直前に追加の宣言を挿入します。

#endif // !defined(AFX_BGJSERVTOOL_H__257F0691_57C6_4667_98E5_E2C69366A1BF__INCLUDED_)
