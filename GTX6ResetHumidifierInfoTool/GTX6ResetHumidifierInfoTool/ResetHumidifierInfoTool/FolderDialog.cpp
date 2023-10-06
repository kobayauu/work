/**
 * FolderDialog.cpp
 */

#include "stdafx.h"
#include "FolderDialog.h"

static int _stdcall CallBackProc(HWND hWnd, UINT uiMsg, LPARAM lParam, LPARAM lpData);

/**
 * CFolderDialog.
 * @param lpszFolder デフォルトフォルダ
 */
CFolderDialog::CFolderDialog(LPCTSTR lpszFolder)
{
	m_strTitle = "";
	m_strFolder = lpszFolder;

	m_bi.hwndOwner = NULL;
	m_bi.pidlRoot = NULL;
	m_bi.pszDisplayName = NULL;
	m_bi.lpszTitle = NULL;
	m_bi.ulFlags = BIF_RETURNONLYFSDIRS;
	m_bi.lpfn = (BFFCALLBACK) CallBackProc;
	m_bi.lParam = (LPARAM) lpszFolder;
	m_bi.iImage = 0;
}

/**
 * ~CFolderDialog.
 */
CFolderDialog::~CFolderDialog()
{

}

/**
 * フォルダ選択ダイアログを表示する.
 * @return IDOK:OKが押された, IDCANCEL:キャンセルが押された
 */
int CFolderDialog::doModal()
{
	int rc = IDCANCEL;
	LPITEMIDLIST pidl = ::SHBrowseForFolder(&m_bi);
	if(pidl != NULL)
	{
		TCHAR path[_MAX_PATH];
		::SHGetPathFromIDList(pidl, path);
		m_strFolder = path;
		rc = IDOK;
	}
	::CoTaskMemFree( pidl );
	return rc;
}

/**
 * 選択されたフォルダパスを取得する.
 * @return 選択されたフォルダパス
 */
CString CFolderDialog::getFolderPath() const
{
	return m_strFolder;
}

/**
 * ダイアログのタイトルを設定する.
 * @param lpszTitle タイトル
 */
void CFolderDialog::setTitle(LPCTSTR lpszTitle)
{
	m_strTitle = lpszTitle;
	if("" == m_strTitle)
		m_bi.lpszTitle = NULL;
	else
		m_bi.lpszTitle = (LPCTSTR) m_strTitle;
}

/**
 * SHBrowseForFolderのコールバック.
 * @param hWnd 
 * @param uiMsg 
 * @param lParam 
 * @param lpData SHBrowseForFolderのデフォルトフォルダ
 * @return 
 */
int _stdcall CallBackProc(HWND hWnd, UINT uiMsg, LPARAM lParam, LPARAM lpData)
{
	if(uiMsg == BFFM_INITIALIZED)
	{
		// 初期化処理
		if(lpData != NULL)
			SendMessage(hWnd, BFFM_SETSELECTION, TRUE, lpData );
	}
	return 0;
}
