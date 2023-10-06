/////////////
//Language.h
/////////////
#ifndef _AR_LANGUAGE_H
#define _AR_LANGUAGE_H

LCID SetLanguage( CString strExeBodyName );
int LangAfxMsgBox( int nStrID , int iErrNo = 0 );
int LangSetWndTxt( CWnd* pWnd , int nStrID );
int LangGetString( int nStrID , CString* pStr );
int LangCancelYesNoMsgBox();
int LangAccessDeniedMsgBox( CString strFile , int iErrNo = 0 );
int LangReplaceYesNoMsgBox( CString strFile );
int LangSetWndTxt_MinMax( CWnd* pWnd , int nStrID , int nMin , int nMax );
int LangAfxMsgBox_OutOfRange( int nTempC , int iErrNo  = 0 );
int LangAfxMsgBox( int nStrID , int iErrNo , DWORD dwExData );
int LangAfxMsgBox( int nStrID , int iErrNo , CString strExData );
int LangAfxMsgBox( int nStrID , int iErrNo , DWORD dwExData1 , DWORD dwExData2 );



#endif /*  _AR_LANGUAGE_H */