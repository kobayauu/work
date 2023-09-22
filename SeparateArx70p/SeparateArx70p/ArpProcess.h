////////////////////////////////////////////////////////////
//					ArpProcess.h
////////////////////////////////////////////////////////////


#pragma once

#include <stdio.h>
#include <tchar.h>
#include "ArpCmd.h"


//２つのARPを、１つに重ねる
class CStackArp
{
public:		//コンストラクタ
	CStackArp(void);
	~CStackArp(void);

public:		//public関数
	int Open(LPCTSTR szIn1, LPCTSTR szIn2, LPCTSTR szOut);
	int Close();
	int Process(UINT nWait);

private:	//ARPコマンド
	CArpCmd m_Inpt1;
	CArpCmd m_Inpt2;
	CArpCmd m_Stack;

private:	//実行
	int ProcessHeader(int* pGraphic1, int* pGraphic2);
	int ProcessGraphic(int nGraphic1, int nGraphic2, UINT nWait);
	int ProcessFooter(int nGraphic, int nMultipass, int nRasterBit, int nDataSize, int nStartPos, UINT nWait);
};


//カラーのみと白のみのARPを、１つに結合
class CMergeArp
{
public:		//コンストラクタ
	CMergeArp(void);
	~CMergeArp(void);

public:		//public関数
	int Open(LPCTSTR szInW, LPCTSTR szInC, LPCTSTR szOut);
	int Close();
	int Process();

private:	//ARPコマンド
	CArpCmd m_White;
	CArpCmd m_Color;
	CArpCmd m_Merge;

private:	//実行
	int ProcessHeader(int* pGraphic);
	int ProcessHeader_Color(SIZE* pPlaten);
	int ProcessHeader_White(SIZE szPlaten, int* pGraphic);
	int ProcessGraphic(int nGraphic, int* pMultipass, int* pRasterBit, int* pDataSize, int* pStartPos);
	int ProcessGraphic_CMYKW(int* pMultipass, int *pRasterBit, int* pStartPos);
	int ProcessGraphic_WOnly();
	int ProcessFooter(int nGraphic, int nMultipass, int nRasterBit, int nDataSize, int nStartPos);
};


//カラー/白のARPを、カラーのみと白のみに分割
class CSplitArp
{
public:		//コンストラクタ
	CSplitArp(void);
	~CSplitArp(void);

public:		//public関数
	int Open(LPCTSTR szIn, LPCTSTR szOutW1, LPCTSTR szOutW2, LPCTSTR szOutC, LPCTSTR szOutF);
	int Close();
	int Process();

private:	//ARPコマンド
	CArpCmd m_Split;
	CArpCmd m_White1;
	CArpCmd m_White2;
	CArpCmd m_Color;
	CArpCmd m_FF;

private:	//実行
	int ProcessHeader(int& nGraphic);
	//int ProcessGraphic(int nGraphic, int& nGraphicW, int& nGraphicC, int nSizeW[], int nSizeC[], int nStartW[], int nStartC[], int nLineW[], int nLineC[]);
	int ProcessGraphic(int nGraphic, int& nGraphicW1, int& nGraphicW2, int& nGraphicC, int& nGraphicFF, int nSizeW1[], int nSizeW2[], int nSizeC[], int nSizeFF[], int nStartW1[], int nStartW2[], int nStartC[], int nStartFF[], int nLineW1[], int nLineW2[], int nLineC[], int nLineFF[]);
	//int ProcessFooter(int nGraphicW, int nGraphicC, int nSizeW[], int nSizeC[], int nStartW[], int nStartC[], int nLineW[], int nLineC[]);
	int ProcessFooter(int nGraphicW1, int nGraphicW2, int nGraphicC, int nGraphicFF, int nSizeW1[], int nSizeW2[], int nSizeC[], int nSizeFF[], int nStartW1[], int nStartW2[], int nStartC[], int nStartFF[], int nLineW1[], int nLineW2[], int nLineC[], int nLineFF[]);
};

//分割印刷の値を修正
class CModifyDivide2
{
public:		//コンストラクタ
	CModifyDivide2(void);
	~CModifyDivide2(void);

public:		//public関数
	int Open(LPCTSTR szIn, LPCTSTR szOut);
	int Close();
	int Process(BYTE byDivide1, BYTE byDivide2);

private:	//ARPコマンド
	CArpCmd m_Input;
	CArpCmd m_Output;

	int ProcessHeader();
	int ProcessGraphic(BYTE byDivide1, BYTE byDivide2);
	int ProcessFooter(BYTE byDivide1, BYTE byDivide2);
};

//ポリE対応
class CPolyEArp
{
public:		//コンストラクタ
	CPolyEArp(void);
	~CPolyEArp(void);

public:		//public関数
	int Open(LPCTSTR szIn, LPCTSTR szOut);
	int Close();
	int Process(int nType);

private:	//ARPコマンド
	CArpCmd m_InFile;
	CArpCmd m_OutFile;
	BYTE	m_byGraphics;

private:	//実行
	int ProcessHeader(int nType);
	int ProcessGraphic(int nDivide);
	int ProcessFooter(int nType, int nDivide);
};

//MMB対応で、２つのARPを、１つに重ねる
class CStackArp_MMB
{
public:		//コンストラクタ
	CStackArp_MMB(void);
	~CStackArp_MMB(void);

public:		//public関数
	int Open(LPCTSTR szIn1, LPCTSTR szIn2, LPCTSTR szOut);
	int Close();
	int Process(UINT nWait, BYTE byHighlight);

private:	//ARPコマンド
	CArpCmd m_Inpt1;
	CArpCmd m_Inpt2;
	CArpCmd m_Stack;

private:	//実行
	int ProcessHeader(int* pGraphic1, int* pGraphic2);
	int ProcessGraphic(int nGraphic1, int nGraphic2, UINT nWait, BYTE byHighlight);
	int ProcessFooter(int nGraphic, int nMultipass, int nRasterBit, int nDataSize, int nStartPos, UINT nWait, BYTE byHighlight);
};

//Reversal対応
class CReversalArp
{
public:		//コンストラクタ
	CReversalArp(void);
	~CReversalArp(void);

public:		//public関数
	int Open(LPCTSTR szIn, LPCTSTR szOut);
	int Close();
	int Process(BYTE byDoublePrint);

private:	//ARPコマンド
	CArpCmd m_InFile;
	CArpCmd m_OutFile;
	BYTE	m_byGraphics;

private:	//実行
	int ProcessHeader();
	int ProcessGraphic(UINT nWait);
	int ProcessFooter(UINT nWait);
};
