// FirmLogCode.cpp: CFirmLogCode クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
//#include "SendBuff.h"
//#include "BGJPrinter.h"
#include "BGJServTool.h"
#include "FirmLogCode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#include "logcode.c"



//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CFirmLogCode::CFirmLogCode()
{
}

CFirmLogCode::~CFirmLogCode()
{

}

void CFirmLogCode::SetVersion(LPCTSTR pszLogVersion)
{
	CString csVersion = pszLogVersion;
	if( csVersion == "1000" ){
	}
}

bool CFirmLogCode::GetLogCodeExplanation(CString& csMsg, DWORD dwCode, UINT nLevel, UINT nClass)
{
	bool bRet = true;
	int i;

	for( i = 0; s_LogCode[i].dwCode != dwCode && s_LogCode[i].dwCode != 0x99990000; ++i ) {
		;
	}

	CBGJServToolApp* pApp = (CBGJServToolApp*)AfxGetApp();
	if( pApp->GetLCID() == MAKELCID( 0x0411 , SORT_DEFAULT ) ) {
		csMsg += s_LogCode[i].szMsgJ;
	}
	else {
		csMsg += s_LogCode[i].szMsgE;
	}

	return bRet;
}
