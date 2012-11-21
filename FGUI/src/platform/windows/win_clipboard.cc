#include "platform/windows/win_clipboard.h"

#ifdef FGUI_PLATFORM_WINDOWS_WIN_CLIPBOARD_H_

#include <Windows.h>
#include "platform/windows/win_unicode.h"

FGUI_BEGIN

void WindowsClipboard::setText(const std::string &text)
{
   // open clipboard
   if (!OpenClipboard(NULL))
      return;

   // allocate global memory for new clipboard contents
   std::wstring wstr = widen(text);
   HGLOBAL h_data = GlobalAlloc(GMEM_MOVEABLE, (wstr.size() + 1) * sizeof(wchar_t));
   if (h_data == NULL)
   {
      // if we can't allocate memory for the new contents, abort
      CloseClipboard();
      return;
   }

   // Remove old data from clipboard
   EmptyClipboard();

   // copy text to global memory
   LPWSTR data = (LPWSTR)GlobalLock(h_data);
   memcpy(data, &wstr[0], wstr.size() * sizeof(wchar_t));
   data[wstr.size()] = 0;   // null terminator
   GlobalUnlock(h_data);

   // put global memory handle on clipboard
   SetClipboardData(CF_UNICODETEXT, h_data);
   
   // Close clipboard
   CloseClipboard();
}

std::string WindowsClipboard::getText()
{
   // return a null string if there is no text on the clipboard or we can't open it
   if (!IsClipboardFormatAvailable(CF_UNICODETEXT))
      return "";
   if (!OpenClipboard(NULL))
      return "";

   // get a handle to the global memory where the text on the clipboard is stored
   std::string str;
   HGLOBAL h_data = GetClipboardData(CF_UNICODETEXT);
   if (h_data != NULL)
   {
      LPCWSTR data = (LPCWSTR)GlobalLock(h_data);
      if (data != NULL)
      {
         // convert text to utf8
         str = narrow(data);
         GlobalUnlock(h_data);
      }
   }
   CloseClipboard();
   return str;
}

FGUI_END

#endif