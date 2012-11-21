#include "platform/windows/win_unicode.h"

#ifdef FGUI_PLATFORM_WINDOWS_WIN_UNICODE_H_

#include <Windows.h>

FGUI_BEGIN

std::string narrow(const wchar_t *s)
{
   int wide_size = std::char_traits<wchar_t>::length(s);
   int narrow_size = WideCharToMultiByte(CP_UTF8, 0,
                                         s, wide_size,
                                         NULL, 0,
                                         NULL, NULL);
   std::string narrow_str(narrow_size, 0);
   WideCharToMultiByte(CP_UTF8, 0,
                       s, wide_size,
                       &narrow_str[0], narrow_size,
                       NULL, NULL);
   return narrow_str;
}


std::string narrow(const std::wstring &s)
{
   int narrow_size = WideCharToMultiByte(CP_UTF8, 0,
                                         &s[0], (int)s.size(),
                                         NULL, 0,
                                         NULL, NULL);
   std::string narrowStr(narrow_size, 0);
   WideCharToMultiByte(CP_UTF8, 0,
                       &s[0], (int)s.size(),
                       &narrowStr[0], narrow_size,
                       NULL, NULL);
   return narrowStr;
}

std::wstring widen(const char *s)
{
   int narrowSize = std::char_traits<char>::length(s);
   int wideSize = MultiByteToWideChar(CP_UTF8, 0,
                                      s, narrowSize,
                                      NULL, 0);
   std::wstring wideStr(wideSize, 0);
   MultiByteToWideChar(CP_UTF8, 0,
                       s, narrowSize,
                       &wideStr[0], wideSize);
   return wideStr;
}


std::wstring widen(const std::string &s)
{
   int wideSize = MultiByteToWideChar(CP_UTF8, 0,
                                      &s[0], (int)s.size(),
                                      NULL, 0);
   std::wstring wideStr(wideSize, 0);
   MultiByteToWideChar(CP_UTF8, 0,
                       &s[0], (int)s.size(),
                       &wideStr[0], wideSize);
   return wideStr;
}

FGUI_END

#endif