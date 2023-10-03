// FVerInfo.cpp: CFVerInfo クラスのインプリメンテーション
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FVerInfo.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// 構築/消滅
//////////////////////////////////////////////////////////////////////

CFVerInfo::CFVerInfo()
{
	m_lpstrVffInfo = NULL;
}

CFVerInfo::~CFVerInfo()
{
	Close();
}

BOOL CFVerInfo::LoadFileVersion(LPCTSTR pszModuleFile)
{
	if( m_lpstrVffInfo != NULL ){
		delete [] m_lpstrVffInfo;
		m_lpstrVffInfo = NULL;
	}
	TCHAR szFullPath[MAX_PATH];
	BOOL bResult = FALSE;
	if( pszModuleFile == NULL ){
		HINSTANCE hInst = AfxGetInstanceHandle( );
		GetModuleFileName (hInst, szFullPath, sizeof(szFullPath));
	}else{
		_tcscpy( szFullPath, pszModuleFile );
	}
	DWORD dwVerHnd;
	DWORD dwVerInfoSize = GetFileVersionInfoSize(szFullPath, &dwVerHnd);
	if( dwVerInfoSize != 0 ){
		m_lpstrVffInfo = new char[dwVerInfoSize];
		bResult = GetFileVersionInfo(szFullPath, dwVerHnd, dwVerInfoSize, m_lpstrVffInfo);
		if( ! bResult ){
			delete [] m_lpstrVffInfo;
			m_lpstrVffInfo = NULL;
		}
	}
	return bResult;
}

LPCTSTR CFVerInfo::GetProductVersionStr()
{
	m_csProductVer = _T("");
	UINT nVer1, nVer2, nVer3, nVer4;
	if( GetProductVer( &nVer1, &nVer2, &nVer3, &nVer4 ) ){
		m_csProductVer.Format(_T("%u.%u.%u.%u"), nVer1, nVer2, nVer3, nVer4 );
	}
	return m_csProductVer;
}



void CFVerInfo::Close()
{
	if( m_lpstrVffInfo != NULL ){
		delete [] m_lpstrVffInfo;
		m_lpstrVffInfo = NULL;
	}
}

CFVerInfo::CFVerInfo(LPCTSTR pFullPath)
{
	m_lpstrVffInfo = NULL;
	LoadFileVersion( pFullPath );
}

LPCTSTR CFVerInfo::GetFileVersionStr()
{
	m_csFileVer = _T("");
	UINT nVer1, nVer2, nVer3, nVer4;
	if( GetFileVer( &nVer1, &nVer2, &nVer3, &nVer4 ) ){
		m_csFileVer.Format(_T("%u.%u.%u.%u"), nVer1, nVer2, nVer3, nVer4 );
	}
	return m_csFileVer;
}

BOOL CFVerInfo::GetFileVer(UINT * pnVer1, UINT * pnVer2, UINT * pnVer3, UINT * pnVer4)
{
	BOOL bRet = FALSE;
	if( m_lpstrVffInfo != NULL ){
		VS_FIXEDFILEINFO* pVsFixedFileInfo;
		UINT nLen = 0;
		BOOL bResult = VerQueryValue( m_lpstrVffInfo, _T("\\"), (LPVOID*)&pVsFixedFileInfo, &nLen );
		if( bResult ){
			UINT nVer1 = pVsFixedFileInfo->dwFileVersionMS >> 16;
			UINT nVer2 = pVsFixedFileInfo->dwFileVersionMS & 0x0000FFFF;
			UINT nVer3 = pVsFixedFileInfo->dwFileVersionLS >> 16;
			UINT nVer4 = pVsFixedFileInfo->dwFileVersionLS & 0x0000FFFF;
			if( pnVer1 != NULL ) *pnVer1 = nVer1;
			if( pnVer2 != NULL ) *pnVer2 = nVer2;
			if( pnVer3 != NULL ) *pnVer3 = nVer3;
			if( pnVer4 != NULL ) *pnVer4 = nVer4;
			bRet = TRUE;
		}
	}
	return bRet;
}

BOOL CFVerInfo::GetProductVer(UINT * pnVer1, UINT * pnVer2, UINT * pnVer3, UINT * pnVer4)
{
	BOOL bRet = FALSE;
	if( m_lpstrVffInfo != NULL ){
		VS_FIXEDFILEINFO* pVsFixedFileInfo;
		UINT nLen = 0;
		BOOL bResult = VerQueryValue( m_lpstrVffInfo, _T("\\"), (LPVOID*)&pVsFixedFileInfo, &nLen );
		if( bResult ){
			UINT nVer1 = pVsFixedFileInfo->dwProductVersionMS >> 16;
			UINT nVer2 = pVsFixedFileInfo->dwProductVersionMS & 0x0000FFFF;
			UINT nVer3 = pVsFixedFileInfo->dwProductVersionLS >> 16;
			UINT nVer4 = pVsFixedFileInfo->dwProductVersionLS & 0x0000FFFF;
			if( pnVer1 != NULL ) *pnVer1 = nVer1;
			if( pnVer2 != NULL ) *pnVer2 = nVer2;
			if( pnVer3 != NULL ) *pnVer3 = nVer3;
			if( pnVer4 != NULL ) *pnVer4 = nVer4;
			bRet = TRUE;
		}
	}
	return bRet;
}
