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
// File: platform/platform_interface.h

#ifndef FGUI_PLATFORM_PLATFORM_INTERFACE_H_
#define FGUI_PLATFORM_PLATFORM_INTERFACE_H_
#include "fgui_std.h"

#include "font_provider_interface.h"
#include "clipboard_interface.h"

FGUI_BEGIN

class UID;
class RendererInterface;
class LoggerInterface;
struct Color;

class PlatformInterface : public FontProviderInterface, public ClipboardInterface
{
public:
   virtual ~PlatformInterface() {}

   virtual RendererInterface *checkoutRenderer(const UID &uid) = 0;
   virtual void returnRenderer(const UID &uid, RendererInterface *renderer) = 0;

   virtual LoggerInterface *checkoutLogger() = 0;
   virtual void returnLogger(LoggerInterface *logger) = 0;

   virtual const std::string &getProperty(const UID &uid) = 0;
   virtual const Color &getColor(const UID &uid) = 0;
   virtual float_t getReal(const UID &uid) = 0;
};

FGUI_END

#endif
