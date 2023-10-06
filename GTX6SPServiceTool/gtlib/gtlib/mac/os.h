#pragma once

#if defined(__OBJC_BOOL_IS_BOOL)
    // Honor __OBJC_BOOL_IS_BOOL when available.
#   if __OBJC_BOOL_IS_BOOL
#       define OBJC_BOOL_IS_BOOL 1
#   else
#       define OBJC_BOOL_IS_BOOL 0
#   endif
#else
    // __OBJC_BOOL_IS_BOOL not set.
#   if TARGET_OS_OSX || TARGET_OS_MACCATALYST || ((TARGET_OS_IOS || 0) && !__LP64__ && !__ARM_ARCH_7K)
#      define OBJC_BOOL_IS_BOOL 0
#   else
#      define OBJC_BOOL_IS_BOOL 1
#   endif
#endif
#if OBJC_BOOL_IS_BOOL
    typedef bool BOOL;
#else
    typedef signed char BOOL;
#endif

typedef int SOCKET;
typedef long long int64_t, LONGLONG;
typedef unsigned long long uint64_t, ULONGLONG;

typedef const char *LPCTSTR, *LPCSTR;
typedef char CHAR, *LPSTR, *LPTSTR;
typedef short int WCHAR;
typedef int INT, INT_PTR;
typedef int LONG;
typedef unsigned int UINT, *LPUINT;
typedef unsigned int ULONG, *LPULONG;
typedef unsigned char BYTE, *LPBYTE;
typedef unsigned short WORD, *LPWORD;
typedef unsigned int DWORD, *LPDWORD;
typedef unsigned int COLORREF;
typedef void VOID, *LPVOID, *HANDLE, *HWND;
typedef unsigned int WPARAM;
typedef unsigned int LPARAM;

typedef struct tagBITMAPINFOHEADER {
    DWORD   biSize;
    LONG    biWidth;
    LONG    biHeight;
    WORD    biPlanes;
    WORD    biBitCount;
    DWORD   biCompression;
    DWORD   biSizeImage;
    LONG    biXPelsPerMeter;
    LONG    biYPelsPerMeter;
    DWORD   biClrUsed;
    DWORD   biClrImportant;
} BITMAPINFOHEADER;

typedef struct tagRECT {
    LONG    left;
    LONG    top;
    LONG    right;
    LONG    bottom;
} RECT, *LPRECT;

typedef struct tagSIZE {
    LONG    cx;
    LONG    cy;
} SIZE, *LPSIZE;

#define far
#define FAR
#define WINAPI 
#ifdef __GNUC__
#define APIENTRY
#else
#define APIENTRY __stdcall
#endif
#define INVALID_HANDLE_VALUE (void*)(-1)
#define MAX_PATH (260)

#define _MSC_VER 2000
#define __time32_t int
#define _time32(x) *(x) = (int)time(NULL)
#define GetRValue(rgb) (BYTE) ((rgb))
#define GetGValue(rgb) (BYTE) ((rgb)>>8)
#define GetBValue(rgb) (BYTE) ((rgb)>>16)
#define RGB(r, g, b) ((DWORD) ((BYTE)(r)) | ((BYTE)(g) << 8) | ((BYTE)(b) << 16))
#define min(a, b) (((a)<(b)) ? (a) : (b))
#define max(a, b) (((a)>(b)) ? (a) : (b))
#define UNREFERENCED_PARAMETER(p) p
#define __declspec(p)

typedef char TCHAR, *LPTSTR;
#define	_T(x)		x
#define _tcscpy     strcpy
#define _tcscat     strcat
#define _tcsncpy    strncpy
#define _stprintf   sprintf
#define _sntprintf  snprintf
#define _tfopen     fopen
#define _tcsrchr    strrchr
#define _tcsicmp    strcasecmp
#define _tremove    remove
#define sprintf_s   snprintf


#ifndef __OBJC__
    #define TRUE true
    #define FALSE false
#endif	//__OBJC__
