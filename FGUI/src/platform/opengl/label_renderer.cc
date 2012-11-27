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
// File: platform/opengl/label_renderer.cc

#include "platform/opengl/label_renderer.h"

#ifdef FGUI_PLATFORM_OPENGL_LABEL_RENDERER_H_

#include <sstream>

#include "component/f_ui.h"
#include "component/f_label.h"

FGUI_BEGIN
namespace stdgl {

bool LabelRenderer::checkPointOverComponent(const FComponent *component, const Point &absolute_coord) const
{
   if (!component)
      return false;

   const FLabel *comp = static_cast<const FLabel*>(component);

   const Point &to = comp->getTextOrigin();
   const Rect &tm = comp->getTextMetrics().line;
   
   return absolute_coord.x >= to.x + tm.getLeft() && absolute_coord.x < to.x + tm.getRight() &&
          absolute_coord.y >= to.y + tm.getTop() && absolute_coord.y < to.y + tm.getBottom();
}

void LabelRenderer::draw(FComponent *component)
{
   if (!component)
      return;

   FLabel *comp = static_cast<FLabel*>(component);

   const Rect &r = comp->getAbsoluteRect();
   Rect clip = comp->getClip();

   clip.intersect(r);   // get intersection of clip and bounds
   if (!clip.hasSize())
      return;

   const Dimension &wnd = comp->getUI()->getWindowSize();
   GLfloat top = wnd.height - clip.y;
   GLint sx((GLint)floor(clip.x)),
         sy((GLint)floor(top - clip.height)),
         sw((GLint)ceil(clip.width)),
         sh((GLint)ceil(top));
   glScissor(sx, sy, sw, sh);
   /*
   glColor4f(0, 1, 1, 0.2f);
   Point p1(r.getLeft(), r.getTop()),
         p2(r.getLeft(), r.getBottom()),
         p3(r.getRight(), r.getBottom()),
         p4(r.getRight(), r.getTop());

   glBegin(GL_QUADS);
      glVertex2fv(p1.v);
      glVertex2fv(p2.v);
      glVertex2fv(p3.v);
      glVertex2fv(p4.v);
   glEnd();
   */

   FontInterface *font = comp->getFont();
   if (font)
      font->drawString(comp->getText(), comp->getTextOrigin(), comp->getColor());
}

}
FGUI_END

#endif
