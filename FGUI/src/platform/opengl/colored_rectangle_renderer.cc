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
// File: platform/opengl/colored_rectangle_renderer.cc

#include "platform/opengl/colored_rectangle_renderer.h"

#ifdef FGUI_PLATFORM_OPENGL_COLORED_RECTANGLE_RENDERER_H_

#include "component/f_component.h"
#include "component/f_colored_rectangle.h"

FGUI_BEGIN
namespace stdgl {

bool ColoredRectangleRenderer::checkPointOverComponent(const FComponent *component, const Point &absolute_coord) const
{
   if (component)
      return component->checkPointInBounds(absolute_coord);

   return false;
}

void ColoredRectangleRenderer::draw(FComponent *component)
{
   FColoredRectangle *cr = static_cast<FColoredRectangle*>(component);

   if (cr->isFocused())
      glColor4fv(cr->getFocusedColor().v);
   else
      glColor4fv(cr->getNormalColor().v);

   glBegin(GL_QUADS);
      const Point &pos = cr->getAbsolutePosition();
      const Dimension &size = cr->getSize();

      glVertex2fv(pos.v);
      glVertex2f(pos.x + size.width, pos.y);
      glVertex2f(pos.x + size.width, pos.y + size.height);
      glVertex2f(pos.x, pos.y + size.height);
   glEnd();
}

}
FGUI_END

#endif
