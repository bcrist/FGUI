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
// File: render_task.cc

#include "render_task.h"

#include "component/f_component.h"

FGUI_BEGIN

RenderTask::RenderTask(FComponent *component, RendererInterface *renderer)
      : component(component_), renderer(renderer_),
        component_(component), renderer_(renderer) {}

RenderTask::RenderTask(const RenderTask &other)
      : component(component_), renderer(renderer_),
        component_(other.component_), renderer_(other.renderer_) {}

RenderTask &RenderTask::operator=(const RenderTask &rhs)
{
   component_ = rhs.component_;
   renderer_ = rhs.renderer_;
}

bool RenderTask::operator<(const RenderTask &rhs) const
{
   if (component && rhs.component)
      return component->getZIndex() < rhs.component->getZIndex();
      
   return false;
}

FGUI_END
