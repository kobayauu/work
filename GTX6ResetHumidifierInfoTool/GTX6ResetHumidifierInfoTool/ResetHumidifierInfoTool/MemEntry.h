// MemEntry.h: CMemEntry クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMENTRY_H__4B139600_6CC1_4F6E_9CD4_32BFFF1EF351__INCLUDED_)
#define AFX_MEMENTRY_H__4B139600_6CC1_4F6E_9CD4_32BFFF1EF351__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMemEntry
{
public:
	bool ChangeDataByStr( LPCSTR pStr );
	bool ChangeData( int nSize, const BYTE* pData );
	BYTE GetDataByte( unsigned int iByteIndex );
	void Clear();
	CString m_csDate;
	DWORD m_dwData1;
	DWORD m_dwData2;
	static bool qAtoDWORD( LPCSTR pszStr, DWORD* pData );
	LPCSTR SkipBlank( LPCSTR psz );
	static long q_atol( LPCSTR szNumStr );
	bool SetMemEntry( LPCSTR pszNum, LPCSTR pszSize, LPCSTR pszData, LPCSTR pszType, LPCSTR pszName, LPCSTR pszComment );
	int m_iNumber;
	CString m_csComment;
	int m_iType;
	CString m_csName;
	int m_nSize;
	DWORD m_dwAddr;
	CMemEntry();
	virtual ~CMemEntry();

protected:
	bool SetHexStr( LPCSTR pStr, int nByte );
};

#endif // !defined(AFX_MEMENTRY_H__4B139600_6CC1_4F6E_9CD4_32BFFF1EF351__INCLUDED_)
