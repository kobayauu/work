/**
 * FolderDialog.cpp
 */

#include "stdafx.h"
#include "FolderDialog.h"

static int _stdcall CallBackProc(HWND hWnd, UINT uiMsg, LPARAM lParam, LPARAM lpData);

/**
 * CFolderDialog.
 * @param lpszFolder �f�t�H���g�t�H���_
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
 * �t�H���_�I���_�C�A���O��\������.
 * @return IDOK:OK�������ꂽ, IDCANCEL:�L�����Z���������ꂽ
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
 * �I�����ꂽ�t�H���_�p�X���擾����.
 * @return �I�����ꂽ�t�H���_�p�X
 */
CString CFolderDialog::getFolderPath() const
{
	return m_strFolder;
}

/**
 * �_�C�A���O�̃^�C�g����ݒ肷��.
 * @param lpszTitle �^�C�g��
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
 * SHBrowseForFolder�̃R�[���o�b�N.
 * @param hWnd 
 * @param uiMsg 
 * @param lParam 
 * @param lpData SHBrowseForFolder�̃f�t�H���g�t�H���_
 * @return 
 */
int _stdcall CallBackProc(HWND hWnd, UINT uiMsg, LPARAM lParam, LPARAM lpData)
{
	if(uiMsg == BFFM_INITIALIZED)
	{
		// ����������
		if(lpData != NULL)
			SendMessage(hWnd, BFFM_SETSELECTION, TRUE, lpData );
	}
	return 0;
}
