#pragma once

#include <cstring>
#include <string>

////////////////////////////////////////////////////////////

namespace gtlib {

class Utf16String : public std::wstring {
public:
  Utf16String(const wchar_t *str) : std::wstring(str) {}
  Utf16String(const char *str) {
    const int size = ::MultiByteToWideChar(CP_ACP, 0, str, -1, NULL, 0) + 1;
    resize(size);
    ::MultiByteToWideChar(CP_ACP, 0, str, -1, (wchar_t *)data(), size);
  }
  template <typename Arg, typename... Args>
  Utf16String(const wchar_t *fmt, Arg arg, Args... args) {
    std::size_t size = std::swprintf(nullptr, 0, fmt, arg, args...) + 1;
    resize(size);
    std::swprintf((wchar_t *)data(), size, fmt, arg, args...);
  }
  operator const wchar_t *() { return c_str(); }
  static bool copy(const char* str, wchar_t* buffer, size_t size) {
    return ::MultiByteToWideChar(CP_ACP, 0, str, -1, buffer, (int)size);
  }
  static bool copy(const wchar_t* str, wchar_t* buffer, size_t size) {
    return std::wcsncpy(buffer, str, size);
  }
};

class Utf8String : public std::string {
  void init(const wchar_t *str) {
    int size = ::WideCharToMultiByte(CP_UTF8, 0, str, -1, NULL, 0, NULL, NULL) + 1;
    resize(size);
    ::WideCharToMultiByte(CP_UTF8, 0, str, -1, (char *)c_str(), size, NULL, NULL);
  }
public:
  Utf8String(const char *str) { Utf16String buff(str); init(buff); }
  Utf8String(const wchar_t *str) { init(str); }
  template <typename Arg, typename... Args>
  Utf8String(const char *fmt, Arg arg, Args... args) {
    std::size_t size = std::snprintf(nullptr, 0, fmt, arg, args...) + 1;
    resize(size);
    std::snprintf((char *)data(), size, fmt, arg, args...);
  }
  operator const char *() { return c_str(); }
  static bool copy(const char *str, char *buffer, size_t size) {
    Utf16String buff(str);
    return copy(buff, buffer, size);
  }
  static bool copy(const wchar_t *str, char *buffer, size_t size) {
    return ::WideCharToMultiByte(CP_UTF8, 0, str, -1, buffer, (int)size, NULL, NULL);
  }
};

class AnsiString : public std::string {
public:
  AnsiString(const char *str) : std::string(str) {}
  AnsiString(const wchar_t *str) {
    int size = ::WideCharToMultiByte(CP_ACP, 0, str, -1, NULL, 0, NULL, NULL) + 1;
    resize(size);
    ::WideCharToMultiByte(CP_ACP, 0, str, -1, (char *)c_str(), size, NULL, NULL);
  }
  template <typename Arg, typename... Args>
  AnsiString(const char *fmt, Arg arg, Args... args) {
    std::size_t size = std::snprintf(nullptr, 0, fmt, arg, args...) + 1;
    resize(size);
    std::snprintf((char *)data(), size, fmt, arg, args...);
  }
  operator const char *() { return c_str(); }
  static bool copy(const char *str, char *buffer, size_t size) {
    return std::strncpy(buffer, str, size);
  }
  static bool copy(const wchar_t *str, char *buffer, size_t size) {
    return ::WideCharToMultiByte(CP_ACP, 0, str, -1, buffer, (int)size, NULL, NULL);
  }
};

#ifdef UNICODE
using TString = Utf16String;
#else
using TString = AnsiString;
#endif

} // namespace gtlib

using CT2UTF8 = gtlib::Utf8String;
