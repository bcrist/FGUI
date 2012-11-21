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
// File: component/f_colored_rectangle.cc

#include "component/f_colored_rectangle.h"

FGUI_BEGIN

FColoredRectangle::FColoredRectangle():
   normalColor(Color(1, 0, 0)),
   focusedColor(Color(1, 0, 0)),
   hoverColor(Color(1, 0, 0)),
   activeColor(Color(1, 0, 0))
{
   setFocusable(true);
}

FColoredRectangle::FColoredRectangle(const Color &color):
   normalColor(color),
   focusedColor(color),
   hoverColor(color),
   activeColor(color)
{
   setFocusable(true);
}

FColoredRectangle::FColoredRectangle(const Color &normalColor,
   const Color &focusedColor,
   const Color &hoverColor,
   const Color &activeColor):
      normalColor(normalColor),
      focusedColor(focusedColor),
      hoverColor(hoverColor),
      activeColor(activeColor)
{
   setFocusable(true);
}

FColoredRectangle::~FColoredRectangle()
{
}
/*
void FColoredRectangle::paint()
{
   if (isFocused())
      glColor4fv(focusedColor.v);
   else
      glColor4fv(normalColor.v);
   glBegin(GL_QUADS);
      glVertex2fv(position.v);
      glVertex2f(position.x + size.width, position.y);
      glVertex2f(position.x + size.width, position.y + size.height);
      glVertex2f(position.x, position.y + size.height);
   glEnd();
}
*/
FGUI_END
