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
// File: platform/opengl/ui_prepare_renderer.cc

#include "platform/opengl/ui_prepare_renderer.h"

#ifdef FGUI_PLATFORM_OPENGL_UI_PREPARE_RENDERER_H_

#include "component/f_ui.h"

#include "dimension.h"
#include "point.h"

FGUI_BEGIN
namespace stdgl {

void UIPrepareRenderer::draw(FComponent *component)
{
   FUI *comp = static_cast<FUI*>(component);

   Dimension size = comp->getSize();

   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();
   glOrtho(0, size.width, size.height, 0, -1, 1);

   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();

   const Rect &clip = comp->getClip();

   glEnable(GL_SCISSOR_TEST);
   const Dimension &wnd = comp->getWindowSize();
   GLfloat top = wnd.height - clip.y;
   GLint sx((GLint)floor(clip.x)),
         sy((GLint)floor(top - clip.height)),
         sw((GLint)ceil(clip.width)),
         sh((GLint)ceil(top));
   glScissor(sx, sy, sw, sh);
}

}
FGUI_END

#endif
