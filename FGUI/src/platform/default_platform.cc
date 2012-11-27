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
// File: platform/default_platform.cc

#include "platform/default_platform.h"

#include "component/f_ui.h"
#include "component/f_colored_rectangle.h"
#include "component/f_label.h"

#include "fgui_renderers.h"

FGUI_BEGIN

DefaultPlatform::DefaultPlatform() : default_logger_(NULL)
{
   #ifndef FGUI_NO_OPENGL

   renderers_.insert(std::pair<UID, RendererInterface*>(FUI::prepare_renderer_uid_, &default_ui_prepare_r_));
   renderers_.insert(std::pair<UID, RendererInterface*>(FUI::cleanup_renderer_uid_, &default_ui_cleanup_r_));

   renderers_.insert(std::pair<UID, RendererInterface*>(FColoredRectangle::renderer_uid_, &default_colored_rectangle_r_));
   renderers_.insert(std::pair<UID, RendererInterface*>(FLabel::renderer_uid_, &default_label_r_));

   #endif
}

RendererInterface *DefaultPlatform::checkoutRenderer(const UID &uid)
{
   std::map<UID, RendererInterface*>::iterator it(renderers_.find(uid));
   return it == renderers_.end() ? NULL : it->second;
}

FGUI_END
