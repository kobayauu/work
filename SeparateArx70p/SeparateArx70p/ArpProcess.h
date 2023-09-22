////////////////////////////////////////////////////////////
//					ArpProcess.h
////////////////////////////////////////////////////////////


#pragma once

#include <stdio.h>
#include <tchar.h>
#include "ArpCmd.h"


//�Q��ARP���A�P�ɏd�˂�
class CStackArp
{
public:		//�R���X�g���N�^
	CStackArp(void);
	~CStackArp(void);

public:		//public�֐�
	int Open(LPCTSTR szIn1, LPCTSTR szIn2, LPCTSTR szOut);
	int Close();
	int Process(UINT nWait);

private:	//ARP�R�}���h
	CArpCmd m_Inpt1;
	CArpCmd m_Inpt2;
	CArpCmd m_Stack;

private:	//���s
	int ProcessHeader(int* pGraphic1, int* pGraphic2);
	int ProcessGraphic(int nGraphic1, int nGraphic2, UINT nWait);
	int ProcessFooter(int nGraphic, int nMultipass, int nRasterBit, int nDataSize, int nStartPos, UINT nWait);
};


//�J���[�݂̂Ɣ��݂̂�ARP���A�P�Ɍ���
class CMergeArp
{
public:		//�R���X�g���N�^
	CMergeArp(void);
	~CMergeArp(void);

public:		//public�֐�
	int Open(LPCTSTR szInW, LPCTSTR szInC, LPCTSTR szOut);
	int Close();
	int Process();

private:	//ARP�R�}���h
	CArpCmd m_White;
	CArpCmd m_Color;
	CArpCmd m_Merge;

private:	//���s
	int ProcessHeader(int* pGraphic);
	int ProcessHeader_Color(SIZE* pPlaten);
	int ProcessHeader_White(SIZE szPlaten, int* pGraphic);
	int ProcessGraphic(int nGraphic, int* pMultipass, int* pRasterBit, int* pDataSize, int* pStartPos);
	int ProcessGraphic_CMYKW(int* pMultipass, int *pRasterBit, int* pStartPos);
	int ProcessGraphic_WOnly();
	int ProcessFooter(int nGraphic, int nMultipass, int nRasterBit, int nDataSize, int nStartPos);
};


//�J���[/����ARP���A�J���[�݂̂Ɣ��݂̂ɕ���
class CSplitArp
{
public:		//�R���X�g���N�^
	CSplitArp(void);
	~CSplitArp(void);

public:		//public�֐�
	int Open(LPCTSTR szIn, LPCTSTR szOutW1, LPCTSTR szOutW2, LPCTSTR szOutC, LPCTSTR szOutF);
	int Close();
	int Process();

private:	//ARP�R�}���h
	CArpCmd m_Split;
	CArpCmd m_White1;
	CArpCmd m_White2;
	CArpCmd m_Color;
	CArpCmd m_FF;

private:	//���s
	int ProcessHeader(int& nGraphic);
	//int ProcessGraphic(int nGraphic, int& nGraphicW, int& nGraphicC, int nSizeW[], int nSizeC[], int nStartW[], int nStartC[], int nLineW[], int nLineC[]);
	int ProcessGraphic(int nGraphic, int& nGraphicW1, int& nGraphicW2, int& nGraphicC, int& nGraphicFF, int nSizeW1[], int nSizeW2[], int nSizeC[], int nSizeFF[], int nStartW1[], int nStartW2[], int nStartC[], int nStartFF[], int nLineW1[], int nLineW2[], int nLineC[], int nLineFF[]);
	//int ProcessFooter(int nGraphicW, int nGraphicC, int nSizeW[], int nSizeC[], int nStartW[], int nStartC[], int nLineW[], int nLineC[]);
	int ProcessFooter(int nGraphicW1, int nGraphicW2, int nGraphicC, int nGraphicFF, int nSizeW1[], int nSizeW2[], int nSizeC[], int nSizeFF[], int nStartW1[], int nStartW2[], int nStartC[], int nStartFF[], int nLineW1[], int nLineW2[], int nLineC[], int nLineFF[]);
};

//��������̒l���C��
class CModifyDivide2
{
public:		//�R���X�g���N�^
	CModifyDivide2(void);
	~CModifyDivide2(void);

public:		//public�֐�
	int Open(LPCTSTR szIn, LPCTSTR szOut);
	int Close();
	int Process(BYTE byDivide1, BYTE byDivide2);

private:	//ARP�R�}���h
	CArpCmd m_Input;
	CArpCmd m_Output;

	int ProcessHeader();
	int ProcessGraphic(BYTE byDivide1, BYTE byDivide2);
	int ProcessFooter(BYTE byDivide1, BYTE byDivide2);
};

//�|��E�Ή�
class CPolyEArp
{
public:		//�R���X�g���N�^
	CPolyEArp(void);
	~CPolyEArp(void);

public:		//public�֐�
	int Open(LPCTSTR szIn, LPCTSTR szOut);
	int Close();
	int Process(int nType);

private:	//ARP�R�}���h
	CArpCmd m_InFile;
	CArpCmd m_OutFile;
	BYTE	m_byGraphics;

private:	//���s
	int ProcessHeader(int nType);
	int ProcessGraphic(int nDivide);
	int ProcessFooter(int nType, int nDivide);
};

//MMB�Ή��ŁA�Q��ARP���A�P�ɏd�˂�
class CStackArp_MMB
{
public:		//�R���X�g���N�^
	CStackArp_MMB(void);
	~CStackArp_MMB(void);

public:		//public�֐�
	int Open(LPCTSTR szIn1, LPCTSTR szIn2, LPCTSTR szOut);
	int Close();
	int Process(UINT nWait, BYTE byHighlight);

private:	//ARP�R�}���h
	CArpCmd m_Inpt1;
	CArpCmd m_Inpt2;
	CArpCmd m_Stack;

private:	//���s
	int ProcessHeader(int* pGraphic1, int* pGraphic2);
	int ProcessGraphic(int nGraphic1, int nGraphic2, UINT nWait, BYTE byHighlight);
	int ProcessFooter(int nGraphic, int nMultipass, int nRasterBit, int nDataSize, int nStartPos, UINT nWait, BYTE byHighlight);
};

//Reversal�Ή�
class CReversalArp
{
public:		//�R���X�g���N�^
	CReversalArp(void);
	~CReversalArp(void);

public:		//public�֐�
	int Open(LPCTSTR szIn, LPCTSTR szOut);
	int Close();
	int Process(BYTE byDoublePrint);

private:	//ARP�R�}���h
	CArpCmd m_InFile;
	CArpCmd m_OutFile;
	BYTE	m_byGraphics;

private:	//���s
	int ProcessHeader();
	int ProcessGraphic(UINT nWait);
	int ProcessFooter(UINT nWait);
};
