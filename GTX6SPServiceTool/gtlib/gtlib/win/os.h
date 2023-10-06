#pragma once

#undef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <tchar.h>
// #include <commdlg.h>
// #include <shlobj.h>

typedef __int64 int64_t;
typedef unsigned __int64 uint64_t;

#define S_ISDIR(x)  ((x) & _S_IFDIR)
