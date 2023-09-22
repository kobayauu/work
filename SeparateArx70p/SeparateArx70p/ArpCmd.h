////////////////////////////////////////////////////////////
//					ArpCmd.h
////////////////////////////////////////////////////////////


#pragma once

#include <stdio.h>
#include <tchar.h>


//ファイル
class TFile
{
public:
	TFile(void);
	~TFile(void);

	BOOL Open(LPCTSTR szFile, UINT nFlags);
	void Close();

	UINT Read(void* buffer, UINT nCount);
	UINT Write(const void* buffer, UINT nCount);
	UINT Seek(UINT lOffset, UINT nForm);
	UINT GetPosition() const;
	UINT GetLength() const;

	static const UINT modeRead = 0;
	static const UINT modeWrite = 1;
	static const UINT modeCreate = 2;
	static const UINT seekSet = 0;
	static const UINT seekCurrent = 1;
	static const UINT seekEnd = 2;

private:
	FILE* m_fp;
};


//バッファ
class TByteArray
{
public:
	TByteArray(void);
	~TByteArray(void);
	void Copy(const TByteArray& src);
	void Copy(const size_t size, const BYTE *data);
	void Clear();

	size_t GetSize() const;
	void SetSize(size_t size);
	void RemoveAll();
	BYTE* GetData() const;
	BYTE& operator[](int n);

	BYTE GetByte(int n) const;
	WORD GetWord(int n) const;
	DWORD GetDWord(int n) const;
	void SetByte(int n, BYTE v);
	void SetWord(int n, WORD v);
	void SetDWord(int n, DWORD v);

private:
	BYTE* m_buffer;
	size_t m_size;
	const size_t sizeMax = 0x10000;
};


//ARPコマンドの操作
class CArpCmd
{
public:			//コンストラクタ
	CArpCmd(void);
	~CArpCmd(void);

public:			//public関数
	int Open(LPCTSTR strFile, BOOL bSave=FALSE);
	int Close();
	int Copy(CArpCmd* pArpCmd);
	int	Read();
	int Write();
	int Write(CArpCmd* pArpCmd);
	int Write(TByteArray* pBuff);
	int WriteCompMode(int nMode);
	int WriteLineNo(int nLine);
	int WriteLast();

public:			//データ
	TFile		m_File;
	TByteArray	m_baHead;
	TByteArray	m_baParam;

private:		//コマンド
	int CopyCommand(CArpCmd* pArpCmd);
	int ReadCommand();
	int ReadNullCommand();
	int ReadEscapeCommand();
	int ReadArxCommand();
	int WriteCommand();
	int WriteCommand(CArpCmd* pArpCmd);
	int WriteCommand_Compress(int nMode);
	int WriteCommand_LineNo(int nLine);
	int WriteLastNULL();

private:		//ファイル
	int ReadBuff(TByteArray* pBuff, UINT nCount);
	int ReReadBuff(TByteArray* pBuff, UINT nCount);
	int WriteBuff(TByteArray* pBuff);
};


//インク量の計算
class CCmdInk
{
public:			//コンストラクタ
	CCmdInk(void);
	~CCmdInk(void);

public:			//public関数
	void GetParam(CArpCmd* pArpCmd);
	void AddParam(CArpCmd* pArpCmd);
	void AddParam_MMB(CArpCmd* pArpCmd, BYTE byHighlight);
	void SetParam(CArpCmd* pArpCmd);
	void SetColor(CArpCmd* pArpCmd);
	void SetWhite(CArpCmd* pArpCmd);
	void SetFF(CArpCmd* pArpCmd);

private:		//データ
	DWORD	dwDots[8][3];
	DWORD	dwInkC, dwInkW;
};


//マクロ関数
#define	CMD_KIND(x)		((x).m_baHead.GetByte(0))
#define	CMD_TYPE(x)		((x).m_baHead.GetWord(2))
#define	JOB_TYPE(x)		((x).m_baHead.GetByte(4))
#define	CMD_SIZE(x)		((x).m_baHead.GetDWord(4))
//#define SET_SIZE(x,v)	((x).m_baHead.SetDWord(4,v))
#define ADD_SIZE(x,v)	((x).m_baHead.SetDWord(4, (x).m_baHead.GetDWord(4) + v))
//
#define GET_BYTE(x,n)		((x).m_baParam.GetByte(n))
#define GET_WORD(x,n)		((x).m_baParam.GetWord(n))
#define	GET_DWORD(x,n)		((x).m_baParam.GetDWord(n))
#define SET_BYTE(x,n,v)		((x).m_baParam.SetByte(n,v))
#define SET_WORD(x,n,v)		((x).m_baParam.SetWord(n,v))
#define SET_DWORD(x,n,v)	((x).m_baParam.SetDWord(n,v))
#define ADD_BYTE(x,n,v)		((x).m_baParam.SetByte(n, (x).m_baParam.GetByte(n) + v))
#define ADD_WORD(x,n,v)		((x).m_baParam.SetWord(n, (x).m_baParam.GetWord(n) + v))
#define AND_BYTE(x,n,v)		((x).m_baParam.SetByte(n, (x).m_baParam.GetByte(n) & v))
#define OR_BYTE(x,n,v)		((x).m_baParam.SetByte(n, (x).m_baParam.GetByte(n) | v))

