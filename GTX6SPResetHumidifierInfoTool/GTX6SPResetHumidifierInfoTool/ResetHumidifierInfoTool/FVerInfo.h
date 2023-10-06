// FVerInfo.h: CFVerInfo クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FVERINFO_H__4E875C20_BC6D_452F_B2BC_0EA1C11ABFB9__INCLUDED_)
#define AFX_FVERINFO_H__4E875C20_BC6D_452F_B2BC_0EA1C11ABFB9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFVerInfo  
{
public:
	CFVerInfo();
	virtual ~CFVerInfo();
	BOOL GetProductVer( UINT* pnVer1, UINT* pnVer2, UINT* pnVer3, UINT* pnVer4);
	BOOL GetFileVer( UINT* pnVer1, UINT* pnVer2, UINT* pnVer3, UINT* pnVer4 );
	LPCTSTR GetFileVersionStr();
	 CFVerInfo( LPCTSTR pFullPath );
	void Close();
	LPCTSTR GetProductVersionStr();
	char* m_lpstrVffInfo;
	BOOL LoadFileVersion( LPCTSTR pszModuleFile = NULL );

protected:
	CString m_csFileVer;
	CString m_csProductVer;

};

#endif // !defined(AFX_FVERINFO_H__4E875C20_BC6D_452F_B2BC_0EA1C11ABFB9__INCLUDED_)
