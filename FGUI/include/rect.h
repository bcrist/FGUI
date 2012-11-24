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
// File: rect.h

#ifndef FGUI_RECT_H_
#define FGUI_RECT_H_
#include "fgui_std.h"

#include <ostream>

#include "dimension.h"
#include "point.h"

FGUI_BEGIN

struct Rect
{
   Rect();
   Rect(const Rect &other);
   Rect(const Point &position, const Dimension &size);
   Rect(Point::component_t x, Point::component_t y,
        Dimension::component_t width, Dimension::component_t height);

   // comparison operators
   bool operator==(const Rect &rhs) const;
   bool operator!=(const Rect &rhs) const;

   // assignment operators
   Rect &operator=(const Rect &rhs);

   Rect &setPosition(const Point &position);
   Rect &setSize (const Dimension &size);
   Rect &set(Point::component_t x, Point::component_t y,
      Dimension::component_t width, Dimension::component_t height);

   Rect &expand(const Point &point);
   Rect &expand(const Rect &other);

   Point::component_t getLeft() const { return position.x; }
   Point::component_t getRight() const { return position.x + size.width; }

   Point::component_t getTop() const { return position.y; }
   Point::component_t getBottom() const { return position.y + size.height; }

   Point position;
   const Point::component_t &x;
   const Point::component_t &y;

   Dimension size;
   const Dimension::component_t &width;
   const Dimension::component_t &height;
};

std::ostream &operator<<(std::ostream &os, const Rect &rect);

FGUI_END

#include "rect.inl"

#endif
