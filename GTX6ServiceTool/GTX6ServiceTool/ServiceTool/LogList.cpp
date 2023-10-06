/**
 * LogList.cpp
 */

#include "stdafx.h"
#include "LogList.h"

/**
 * CLogList.
 */
CLogList::CLogList()
{
}

/**
 * ~CLogList.
 */
CLogList::~CLogList()
{
}


#define BUFSIZE 0x4000
/**
 * load.
 * @param ar 
 */
void CLogList::load(CArchive& ar)
{
	unsigned long cnt = seekEdge(ar);
	if(cnt > 0) // ログファイルとして読み込み
	{
		unsigned long cntMax = 0;
		char buf[BUFSIZE];
		unsigned long id = 0;

		while(cnt)
		{
			cnt = seekEdge(ar, buf, BUFSIZE);
			if(0 < cnt && cnt <= BUFSIZE)
			{
				CLogRecord* pRecord = new CLogRecord;
				pRecord->setID(id++);
				pRecord->setData(buf, cnt);
				AddTail(pRecord);
			}
		}
	}
	else // テキストファイルとして読み込み
	{
		CFile* pFile = ar.GetFile();
		pFile->SeekToBegin();
		CArchive arText(pFile, CArchive::load);

		CString string;
		bool bCaption = false;
		CLogRecord* pRecord = NULL;
		while(arText.ReadString(string))
		{
			if(isRecord(string))			// id code date class level
			{
				pRecord = new CLogRecord;
				AddTail(pRecord);
				if(!pRecord->setRecord(string))
					AfxThrowArchiveException(CArchiveException::badIndex, NULL);
				bCaption = true;
			}
			else if(bCaption)				// caption
			{
				pRecord->setCaption(string);
				bCaption = false;
			}
			else								// addition
			{
				if(NULL != pRecord)
					pRecord->setAddition(string);
			}
		}
	}
}

/**
 * "EdGe"までファイルから読み飛ばす.
 * @param ar 
 * @return Edgeまでのバイト数,Edgeがなければ0
 */
unsigned long CLogList::seekEdge(CArchive& ar)
{
	int state = 0;
	unsigned long cnt = 0;
	while(1)
	{
		char c;
		if(1 != ar.Read(&c, 1))
			return 0;

		cnt++;

		switch(c)
		{
		case 'E':
			state = 1;
			break;
		case 'd':
			if(1 == state)
				state = 2;
			else
				state = 0;
			break;
		case 'G':
			if(2 == state)
				state = 3;
			else
				state = 0;
			break;
		case 'e':
			if(3 == state)
				return cnt;
			else
				state = 0;
			break;
		default:
			state = 0;
			break;
		}
	}
}

/**
 * "EdGe"までファイルからバッファに読み込む.
 * @param ar 
 * @param buf[] バッファ
 * @param bufsize バッファサイズ
 * @return 読み込みバイト数
 */
unsigned long CLogList::seekEdge(CArchive& ar, char buf[], unsigned long bufsize)
{
	const char match[] = "EdGe";

	unsigned long cnt = 0;
	while(1)
	{
		char c;
		if(1 != ar.Read(&c, 1))
			return cnt;

		if(cnt < bufsize)
			buf[cnt++] = c;
		else
			return bufsize;

		int j = cnt-1;
		int i;
		for(i = 3; i >= 0 && j >= 0; i--, j--)
		{
			if(match[i] != buf[j])
				break;
		}
		if(i < 0)
			return cnt;
	} 
}
/// ar　を使わないバージョン
int CLogList::load( CString strFilePath )
{
	int iRet = 0;
	FILE* fp = _tfopen( strFilePath , _T("rb") );
	if( fp == NULL )
	{
		iRet = -1;
	}else
	{
		unsigned long cnt = seekEdge( fp );
		if(cnt > 0) // ログファイルとして読み込み
		{
			unsigned long cntMax = 0;
			char buf[BUFSIZE];
			unsigned long id = 0;
			while(cnt)
			{
				cnt = seekEdge( fp, buf, BUFSIZE );
				if(0 < cnt && cnt <= BUFSIZE)
				{
					CLogRecord* pRecord = new CLogRecord;
					pRecord->setID(id++);
					pRecord->setData(buf, cnt);
					AddTail(pRecord);
				}
			}
		}
		fclose( fp );
	}
	return iRet;
}

/**
 * "EdGe"までファイルから読み飛ばす.
 * @param fp 
 * @return Edgeまでのバイト数,Edgeがなければ0
 */
unsigned long CLogList::seekEdge( FILE* fp )
{
	int state = 0;
	unsigned long cnt = 0;
	while(1)
	{
		char c;
		if(1 != fread( &c, 1, sizeof(c), fp ))
			return 0;

		cnt++;

		switch(c)
		{
		case 'E':
			state = 1;
			break;
		case 'd':
			if(1 == state)
				state = 2;
			else
				state = 0;
			break;
		case 'G':
			if(2 == state)
				state = 3;
			else
				state = 0;
			break;
		case 'e':
			if(3 == state)
				return cnt;
			else
				state = 0;
			break;
		default:
			state = 0;
			break;
		}
	}
}

/**
 * "EdGe"までファイルからバッファに読み込む.
 * @param fp 
 * @param buf[] バッファ
 * @param bufsize バッファサイズ
 * @return 読み込みバイト数
 */
unsigned long CLogList::seekEdge(FILE* fp , char buf[], unsigned long bufsize)
{
	const char match[] = "EdGe";

	unsigned long cnt = 0;
	while(1)
	{
		char c;
		if(1 != fread( &c, 1, sizeof(c), fp ))
			return cnt;

		if(cnt < bufsize)
			buf[cnt++] = c;
		else
			return bufsize;

		int j = cnt-1;
		int i;
		for(i = 3; i >= 0 && j >= 0; i--, j--)
		{
			if(match[i] != buf[j])
				break;
		}
		if(i < 0)
			return cnt;
	} 
}

/**
 * 文字列がログ情報？
 * @param string 
 * @return true: , false: 
 */
bool CLogList::isRecord(const CString& string)
{
	if("" == string)
		return false;
	return ('0' <= string[0] && string[0] <= '9') ? true : false;
}

/**
 * store.
 * @param ar 
 */
void CLogList::store(CArchive& ar)
{
	POSITION pos = GetHeadPosition();
	while(NULL != pos)
	{
		CLogRecord* pRecord = GetNext(pos);
		if(pRecord->isSelected())
		{
			// id code date class level
			CString string = pRecord->toString();
			ar.WriteString(string);
			ar.WriteString(_T("\n"));

			// caption
			string = _T("       ") + pRecord->getCaption();
			ar.WriteString(string);
			ar.WriteString(_T("\n"));

			// addition
			int cnt = pRecord->getCountAddition();
			for(int i = 0; i < cnt; i++)
			{
				string = pRecord->getAddition(i);
				ar.WriteString(string);
				ar.WriteString(_T("\n"));
			}
		}
	}
}

/**
 * 指定されたログの次のログで最初の選択されているログを得る.
 * @param pRecord
 * @return 
 */
CLogRecord* CLogList::getNextSelected(CLogRecord* pRecord)
{
	POSITION pos = Find(pRecord);
	ASSERT(NULL != pos);
	GetNext(pos);
	while(NULL != pos)
	{
		CLogRecord* pNextRecord = GetNext(pos);
		if(pNextRecord->isSelected())
			return pNextRecord;
	}
	return NULL;
}

/**
 * 指定されたログの前のログで最初の選択されているログを得る.
 * @param pRecord
 * @return 
 */
CLogRecord* CLogList::getPrevSelected(CLogRecord* pRecord)
{
	POSITION pos = Find(pRecord);
	ASSERT(NULL != pos);
	GetPrev(pos);
	while(NULL != pos)
	{
		CLogRecord* pPrevRecord = GetPrev(pos);
		if(pPrevRecord->isSelected())
			return pPrevRecord;
	}
	return NULL;
}
