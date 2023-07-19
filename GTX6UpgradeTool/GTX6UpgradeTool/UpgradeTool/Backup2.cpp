// Backup2.cpp : 実装ファイル
//

#include "stdafx.h"
#include "BGJServTool.h"
#include "Backup2.h"
#include "afxdialogex.h"
#include "Language.h"

// CBackup2 ダイアログ

IMPLEMENT_DYNAMIC(CBackup2, CPropertyPage)

CBackup2::CBackup2()
	: CPropertyPage(CBackup2::IDD)
{

}

CBackup2::~CBackup2()
{
}

void CBackup2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CBackup2, CPropertyPage)
END_MESSAGE_MAP()


// CBackup2 メッセージ ハンドラー
