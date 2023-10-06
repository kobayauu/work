/**
 * LogArchive.cpp
 */

#include "stdafx.h"
#include "LogArchive.h"

/**
 * CLogArchive.
 */
CLogArchive::CLogArchive(CArchive& ar)
: m_ar(ar)
{
	m_readFile = true;
	m_pos = NULL;
}

/**
 * ~CLogArchive.
 */
CLogArchive::~CLogArchive()
{
}

/**
 * Close
 */
void CLogArchive::Close()
{
	m_ar.Close();
}

/**
 * GetFile
 */
CFile* CLogArchive::GetFile( ) const
{
	return m_ar.GetFile();
}

/**
 * ReadString
 */
BOOL CLogArchive::ReadString(CString& rString)
{
	return m_ar.ReadString(rString);
}

/**
 * ReadString
 */
LPTSTR CLogArchive::ReadString(LPTSTR lpsz, UINT nMax)
{
	return m_ar.ReadString(lpsz, nMax);
}

/**
 * 以降ファイルから読み込む
 */
void CLogArchive::readFile()
{
	m_readFile = true;
}

/**
 * 以降バックアップから読み込む
 */
void CLogArchive::readBackup()
{
	m_readFile = false;
	m_pos = m_backup.GetHeadPosition();
}

/**
 * バックアップのクリア
 */
void CLogArchive::clearBackup()
{
	if(NULL == m_pos)
		m_backup.RemoveAll();
	else
	{
		while(m_backup.GetHeadPosition() != m_pos)
			m_backup.RemoveHead();
	}
}

/**
 * 読み込む
 */
UINT CLogArchive::Read(void* lpBuf, UINT nMax)
{
	BYTE* pBuf = (BYTE*)lpBuf;

	if(m_readFile)
	{
		UINT bytes = m_ar.Read(pBuf, nMax);
		for(UINT i = 0; i < bytes; i++)
			m_backup.AddTail(*pBuf++);
		return bytes;
	}
	else
	{
		UINT bytes = 0;
		while(NULL != m_pos && bytes < nMax)
		{
			*pBuf++ = m_backup.GetNext(m_pos);
			bytes++;
		}

		if(bytes < nMax)
		{
			m_readFile = true;
			UINT readBytes = m_ar.Read(pBuf, nMax-bytes);
			for(UINT i = 0; i < readBytes; i++)
				m_backup.AddTail(*pBuf++);
			bytes += readBytes;
		}
		return bytes;
	}
}
