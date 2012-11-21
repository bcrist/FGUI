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
// File: platform/null_font_provider.h

#ifndef FGUI_PLATFORM_NULL_FONT_PROVIDER_H_
#define FGUI_PLATFORM_NULL_FONT_PROVIDER_H_
#include "fgui_std.h"

#ifndef FGUI_DEFAULT_FONT_PROVIDER
#define FGUI_DEFAULT_FONT_PROVIDER NullFontProvider
#endif

#include "font_provider_interface.h"
FGUI_BEGIN

class NullFontProvider : public FontProviderInterface
{
public:
   virtual ~NullFontProvider() {}

   virtual FontInterface *getFont(const std::string &typeface, const std::string &style, float_t size) { return NULL; }
   virtual void freeFont(FontInterface *font) {}

private:
   DISALLOW_COPY_AND_ASSIGN(NullFontProvider);
};

FGUI_END

#endif
