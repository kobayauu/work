// LogCode.h: CFirmLogCode クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LOGCODE_H__5DAAC888_BC66_4DF4_A242_D056BD8B3B31__INCLUDED_)
#define AFX_LOGCODE_H__5DAAC888_BC66_4DF4_A242_D056BD8B3B31__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFirmLogCode
{
public:
	bool GetLogCodeExplanation( CString& csMsg, DWORD dwCode, UINT nLevel, UINT nClass );
	void SetVersion( LPCTSTR pszLogVersion );
	CFirmLogCode();
	virtual ~CFirmLogCode();

protected:
};

#endif // !defined(AFX_LOGCODE_H__5DAAC888_BC66_4DF4_A242_D056BD8B3B31__INCLUDED_)
