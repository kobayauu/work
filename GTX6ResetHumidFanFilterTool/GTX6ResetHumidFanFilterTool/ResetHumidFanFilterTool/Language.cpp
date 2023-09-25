///////////////
//Language.cpp
//言語対応
///////////////
#include "stdafx.h"
#include "BGJServTool.h"

#include "Language.h"


#define REGKEY_GT	_T("SOFTWARE\\Brother\\GTX-6 Tools")
#define REG_LANGID	_T("SetupLangID")

static WORD GetLangFromReg();
static WORD GetLangFromBodyName( CString strExeBodyName );
static int GetStringFromResource( UINT uStringID, LCID idLocale, wchar_t* pwchTemp );


//使用言語の設定 日本語あり
LCID SetLanguage( CString strExeBodyName )
{
	LANGID LangID = ::GetSystemDefaultLangID();

	//まずexe名から判断
	LANGID lid = GetLangFromBodyName( strExeBodyName );

//	lid = MAKELANGID( LANG_ENGLISH , SUBLANG_ENGLISH_US );

	if( lid == 0 )
	{
		////次に日本語環境なら日本語
		//if( LangID != 0x0411 )
		//{
		//	lid = MAKELANGID( LANG_ENGLISH , SUBLANG_ENGLISH_US );
		//}else
		//{
		//	lid = LangID;
		//}

		//レジストリから判断
		lid = GetLangFromReg();
	}
 
	return MAKELCID( lid , SORT_DEFAULT );
}

//exe名から判断
static WORD GetLangFromBodyName( CString strExeBodyName )
{
	WORD lid = 0;

	if( strExeBodyName.Find( _T("eng") ) >= 0 )
	{
		lid = MAKELANGID( LANG_ENGLISH , SUBLANG_ENGLISH_US );
	}
	else if( strExeBodyName.Find( _T("jpn") ) >= 0 )
	{
		lid = MAKELANGID( LANG_JAPANESE , SUBLANG_DEFAULT );
	}

	return lid;
}

// レジストリから判断
static WORD GetLangFromReg()
{
	WORD lid = MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US);

	HKEY hKey = NULL;
	LONG ret = RegOpenKeyEx(HKEY_LOCAL_MACHINE, REGKEY_GT, 0, KEY_EXECUTE | KEY_WOW64_32KEY, &hKey);
	if ((ret == ERROR_SUCCESS) && (hKey != NULL)) {
		DWORD buftype, bufsize;
		LONG ret2 = RegQueryValueEx(hKey, REG_LANGID, NULL, &buftype, NULL, &bufsize);
		if ((ret2 == ERROR_SUCCESS) && (buftype == REG_DWORD)) {
			DWORD* pdata = (DWORD*)new BYTE[bufsize];
			if (pdata != NULL) {
				LONG ret3 = RegQueryValueEx(hKey, REG_LANGID, NULL, NULL, (LPBYTE)pdata, &bufsize);
				if (ret3 == ERROR_SUCCESS) {
					switch (*pdata) {
						//Code to choose Japanese, if SetupLangID is for Japanese
					case 17:
					case 1041:
						//JAPANESE
						lid = MAKELANGID(LANG_JAPANESE, SUBLANG_DEFAULT);
						break;
					}
				}
				delete[] pdata;
			}
		}
		RegCloseKey(hKey);
	}

	return lid;
}



//Vista対応バージョン
int LangGetString( int nStrID , CString* pStr )
{
	int iRet = 0;

	wchar_t	wBuffer[1024] = {0};

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	iRet = GetStringFromResource( nStrID , pApp->GetLCID() , wBuffer );

	if( iRet >= 0 )
	{
		*pStr = wBuffer;
	}

	return iRet;
}

//CWndにテキスト出力する
int LangSetWndTxt( CWnd* pWnd , int nStrID )
{
	CString st;
	//リソースから文字列を取り出す
	int iRet = LangGetString( nStrID , &st );

	if( iRet >= 0 )
	{
		if( pWnd )
		{
			pWnd->SetWindowText( (LPCTSTR)st );
		}else
		{
			iRet = -101;
		}
	}
	return iRet;
}

//メッセージボックスを出す。
int LangAfxMsgBox( int nStrID , int iErrNo /* = 0 */ )
{
	CString st;
	//リソースから文字列を取り出す
	int iRet = LangGetString( nStrID , &st );

	if( iRet >= 0 )
	{
		CString st1;
		if( iErrNo != 0 )
		{
			st1.Format(_T("%s (%d)") , st , iErrNo );
		}else
		{
			st1 = st;
		}
		//AfxMessageBox( st1 );
		MessageBox(NULL, st1, _T("Brother GTX-6 Reset HumidFanFilter Tool"), MB_OK | MB_ICONEXCLAMATION);
	}
	return iRet;
}

//メッセージボックスを出す。
int LangAfxMsgBox( int nStrID , int iErrNo , DWORD dwExData )
{
	CString st;
	int iRet = LangGetString( nStrID , &st );

	if( iRet >= 0 )
	{
		CString st1;
		st1.Format(_T("%s (%d)(%d)") , st , iErrNo , dwExData );
	
		AfxMessageBox( st1 );
	}
	return iRet;
}

//メッセージボックスを出す。
int LangAfxMsgBox( int nStrID , int iErrNo , DWORD dwExData1 , DWORD dwExData2 )
{
	CString st;
	int iRet = LangGetString( nStrID , &st );

	if( iRet >= 0 )
	{
		CString st1;
		st1.Format(_T("%s (%d)(%d)(%d)") , st , iErrNo , dwExData1 , dwExData2 );
	
		AfxMessageBox( st1 );
	}
	return iRet;
}

//メッセージボックスを出す。
int LangAfxMsgBox( int nStrID , int iErrNo , CString strExData )
{
	CString st;
	int iRet = LangGetString( nStrID , &st );

	if( iRet >= 0 )
	{
		CString st1;
		st1.Format(_T("%s (%d)(%s)") , st , iErrNo , strExData );
	
		AfxMessageBox( st1 );
	}
	return iRet;
}

//置き換えますか？ Yes No のメッセージボックスを出す
int LangReplaceYesNoMsgBox( CString strFile )
{
	CString st;
	int iRet = LangGetString( IDS_REPLACE , &st );

	if( iRet >= 0 )
	{
		CString st1;
		st1.Format(_T("%s %s") , strFile , st );
		iRet = AfxMessageBox( st1 , MB_YESNO );
	}

	return iRet;
}

//AccessDeniedのメッセージボックス
int LangAccessDeniedMsgBox( CString strFile , int iErrNo /* = 0 */ )
{
	CString st;
	int iRet = LangGetString( IDS_ERR_ACCESS_DENIED , &st );

	if( iRet >= 0 )
	{
		CString st1;
		if( iErrNo != 0 )
		{
			st1.Format(_T("%s %s (%d)") , strFile , st , iErrNo );
		}else
		{
			st1.Format(_T("%s %s") , strFile , st );
		}
		AfxMessageBox( st1 );
	}
	return iRet;
}

//返り値は、エラー番号ではない
int LangCancelYesNoMsgBox()
{
	CString st;
	LangGetString( IDS_QUERY_CANCEL , &st );

	return AfxMessageBox( st, MB_YESNO );
}

//　"%s (%d - %d)"スタイルで、CWndにテキスト出力する。
int LangSetWndTxt_MinMax( CWnd* pWnd , int nStrID , int nMin , int nMax )
{
	CString st;
	int iRet = LangGetString( nStrID , &st );

	if( iRet >= 0 )
	{
		if( pWnd )
		{
			CString st1;
			st1.Format(_T("%s (%d - %d)") , st , nMin , nMax );
			pWnd->SetWindowText( st1 );
		}else
		{
			iRet = -101;
		}
	}

	return iRet;
}

//温度の範囲外メッセージボックス
int LangAfxMsgBox_OutOfRange( int nTempF , int iErrNo /* = 0 */ )
{
	CString st;
	int iRet = LangGetString( IDS_ERR_OUTOFRANGE , &st );

	if( iRet >= 0 )
	{
		CString st1;
		if( iErrNo != 0 )
		{
			st1.Format(_T("%s(%d) (%d F)") , st , iErrNo , nTempF );
		}else
		{
			st1.Format(_T("%s (%d F)") , st , nTempF );
		}
		AfxMessageBox( st1 );
	}
	return iRet;
}

//////////////////////////////////////////////////////////////////
//
//	指定した言語の文字列リソーステーブルから、文字列を取り出す。
//	文字列はワイド文字で取り出されるので注意すること。
//
//	引数
//			uStringID	: IN  : 取得したい文字列のリソースID
//			idLocale	: IN  : 取得したい文字列のロケールID
//			pwchTemp	: OUT : 取得した文字列の格納先ポインタ
//	戻り値
//			0:成功　-100:失敗
//
//////////////////////////////////////////////////////////////////
static int GetStringFromResource( UINT uStringID, LCID idLocale, wchar_t* pwchTemp )
{
	int iRet = 0;

	wchar_t		*pwchMem, *pwchCur;
	UINT		idRsrcBlk = uStringID / 16 + 1;
	int			strIndex  = uStringID % 16;
	HINSTANCE	hModule = NULL;
	HRSRC		hResource = NULL;

	hResource = FindResourceEx( AfxGetResourceHandle(),
								RT_STRING,
								MAKEINTRESOURCE(idRsrcBlk),
								(unsigned short)idLocale );
	if( hResource != NULL )
	{
		pwchMem = (wchar_t *)LoadResource( hModule, hResource );
		if( pwchMem != NULL )
		{
			pwchCur = pwchMem;
			for( int i = 0; i < 16; i++ )
			{
				if( *pwchCur )
				{
					int	cchString = *pwchCur;  // String size in characters.
					pwchCur++;
					if( i == strIndex )
					{
						// The string has been found in the string table.
//						wchar_t *pwchTemp = new wchar_t[ cchString ];
						wcsncpy( pwchTemp, pwchCur, cchString );
						return iRet;
					}
					pwchCur += cchString;
				}
				else
				{
					pwchCur++;
				}
			}
		}
	}
	iRet = -100;
	return iRet;
}

