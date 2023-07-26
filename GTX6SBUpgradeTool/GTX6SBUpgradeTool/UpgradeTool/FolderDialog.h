/**
 * FolderDialog.h
 */

#ifndef _FolderDialog_H
#define _FolderDialog_H

/**
 * ::SHBrowseForFolderÇÃÉâÉbÉpÅ[
 */
class CFolderDialog
{
public:
	CFolderDialog(LPCTSTR lpszFolder=NULL);
	virtual ~CFolderDialog();

	int doModal();
	CString getFolderPath() const;
	void setTitle(LPCTSTR lpszTitle);

protected:
	BROWSEINFO m_bi;
	CString m_strFolder;
	CString m_strTitle;
};

#endif
