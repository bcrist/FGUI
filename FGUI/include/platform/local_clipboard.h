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
// File: platform/local_clipboard.h

#ifndef FGUI_PLATFORM_LOCAL_CLIPBOARD_H_
#define FGUI_PLATFORM_LOCAL_CLIPBOARD_H_
#include "fgui_std.h"

#ifndef FGUI_DEFAULT_CLIPBOARD
#define FGUI_DEFAULT_CLIPBOARD LocalClipboard
#endif

#include "clipboard_interface.h"

#include <string>

FGUI_BEGIN

class LocalClipboard : public ClipboardInterface
{
public:
   LocalClipboard() {}
   virtual ~LocalClipboard() {}

   virtual std::string getClipboard() { return clipboard_; }
   virtual void setClipboard(const std::string &text) { clipboard_ = text; }

protected:
   std::string clipboard_;

private:
   DISALLOW_COPY_AND_ASSIGN(LocalClipboard);
};

FGUI_END

#endif
