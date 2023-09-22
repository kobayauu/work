// SeparateArx70p.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです。
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'stdafx.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル


// CSeparateArx70pApp:
// このクラスの実装についてSeparateArx6eC.cpp を参照してください。
//

class CSeparateArx70pApp : public CWinApp
{
public:
	CSeparateArx70pApp();

// オーバーライド
	public:
	virtual BOOL InitInstance();

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CSeparateArx70pApp theApp;