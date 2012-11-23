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
// File: platform/default_platform.h

#ifndef FGUI_PLATFORM_DEFAULT_PLATFORM_H_
#define FGUI_PLATFORM_DEFAULT_PLATFORM_H_
#include "fgui_std.h"

#include <map>

#include "platform/platform_interface.h"

#include "uid.h"
#include "fgui_clipboard.h"
#include "fgui_font.h"
#include "fgui_renderers.h"

FGUI_BEGIN

class DefaultPlatform : public PlatformInterface
{
public:
   DefaultPlatform();
   virtual ~DefaultPlatform() {}

   virtual ClipboardInterface *checkoutClipboard() { return &default_clipboard_; }
   virtual void returnClipboard(ClipboardInterface *clipboard) {}

   virtual FontProviderInterface *checkoutFontProvider() { return &default_font_provider_; }
   virtual void returnFontProvider(FontProviderInterface *font_provider) {}

   void setLogger(LoggerInterface *logger) { default_logger_ = logger; }
   virtual LoggerInterface *checkoutLogger() { return default_logger_; }
   virtual void returnLogger(LoggerInterface *logger) {}

   virtual RendererInterface *checkoutRenderer(const UID &uid);
   virtual void returnRenderer(const UID &uid, RendererInterface *renderer) {}

   

private:
   LoggerInterface *default_logger_;

   FGUI_DEFAULT_CLIPBOARD default_clipboard_;
   FGUI_DEFAULT_FONT_PROVIDER default_font_provider_;
   
   std::map<UID, RendererInterface*> renderers_;
   
#ifndef FGUI_NO_OPENGL

   stdgl::UIPrepareRenderer default_ui_prepare_r_;
   stdgl::UICleanupRenderer default_ui_cleanup_r_;

   stdgl::ColoredRectangleRenderer default_colored_rectangle_r_;

#endif

   DISALLOW_COPY_AND_ASSIGN(DefaultPlatform);
};

FGUI_END

#endif