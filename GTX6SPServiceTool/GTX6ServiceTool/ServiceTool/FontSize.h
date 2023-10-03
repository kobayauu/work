#pragma once

//簡単にCWndオブジェクトのフォントサイズを変更する
//CFontSizeオブジェクトは、オート変数で作成しないでください。

class CFontSize
{
public:

	CFontSize(void);
	virtual ~CFontSize(void);

	BOOL ChangeFontSize( CWnd* pWnd , int iSize , int iWeight = FW_NORMAL );

protected:

	CFont** m_ppFont;
	int     m_iNum;		 //1ブロック中の変更したフォントの数　0～iBLOCK_SIZEのカウンタ
	int     m_iBlockNum; //ブロックをいくつ使っているか

	BOOL ArrocOneBlock();
};
