// Copyright (c) 2012 Benjamin M. Crist
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
//
// Author: Benjamin Crist
// File: platform/windows/win_clipboard.h

#ifndef FGUI_PLATFORM_WINDOWS_WIN_CLIPBOARD_H_
#ifdef WIN32
#define FGUI_PLATFORM_WINDOWS_WIN_CLIPBOARD_H_
#include "fgui_std.h"

#include "platform/clipboard_interface.h"

#ifndef FGUI_DEFAULT_CLIPBOARD
#define FGUI_DEFAULT_CLIPBOARD WindowsClipboard
#endif

FGUI_BEGIN

class WindowsClipboard : public ClipboardInterface
{
public:
   virtual ~WindowsClipboard() {}

   virtual std::string getText();
   virtual void setText(const std::string &text);

private:
   DISALLOW_COPY_AND_ASSIGN(WindowsClipboard);
};

FGUI_END

#endif
#endif
