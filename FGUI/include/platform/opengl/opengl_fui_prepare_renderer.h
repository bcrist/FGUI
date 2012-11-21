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
// File: platform/opengl/opengl_fui_prepare_renderer.h

#ifndef FGUI_PLATFORM_OPENGL_OPENGL_FUI_PREPARE_RENDERER_H_
#ifndef FGUI_NO_OPENGL
#define FGUI_PLATFORM_OPENGL_OPENGL_FUI_PREPARE_RENDERER_H_
#include "fgui_std.h"
#include "platform/opengl/opengl.h"

#include "renderer_interface.h"

#ifndef FGUI_DEFAULT_FUI_PREPARE_RENDERER
#define FGUI_DEFAULT_FUI_PREPARE_RENDERER stdgl::FUIPrepareRenderer
#endif

FGUI_BEGIN

namespace stdgl {

class FUIPrepareRenderer : public RendererInterface
{
public:
   FUIPrepareRenderer() {}
   virtual ~FUIPrepareRenderer() {}

   virtual bool checkPointOverComponent(const FComponent *component, const Point &absolute_coord) const
   {
      return false;
   }
   virtual void draw(FComponent *component);

private:
   DISALLOW_COPY_AND_ASSIGN(FUIPrepareRenderer);
};

}
FGUI_END

#endif
#endif
