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
// File: rect.cc

#include "rect.h"

FGUI_BEGIN

Rect &Rect::expand(const Point &point)
{
   // horizontal direction
   if (width > 0)
   {
      Point::component_t temp = point.x - x;

      if (temp < 0)
      {
         position.setX(point.x);
         size.setWidth(width - temp);
      }
      else if (temp - width > 0)
         size.setWidth(temp);
   }
   else
      position.setX(point.x);

   // vertical direction
   if (height > 0)
   {
      Point::component_t temp = point.y - y;

      if (temp < 0)
      {
         position.setY(point.y);
         size.setHeight(height - temp);
      }
      else if (temp - height > 0)
         size.setHeight(temp);
   }
   else
      position.setY(point.y);

   return *this;
}

Rect &Rect::expand(const Rect &other)
{
   // horizontal direction
   if (width > 0)
   {
      Dimension::component_t other_w = other.width;
      Point::component_t temp = other.x - x;

      if (temp < 0)
      {
         position.setX(other.x);
         size.setWidth(width - temp);
      }
      else
         other_w -= temp;

      if (other_w > width)
         size.setWidth(other_w);
   }
   else
   {
      position.setX(other.x);
      size.setWidth(other.width);
   }

   // vertical direction
   if (height > 0)
   {
      Dimension::component_t other_h = other.height;
      Point::component_t temp = other.y - y;

      if (temp < 0)
      {
         position.setY(other.y);
         size.setHeight(height - temp);
      }
      else
         other_h -= temp;

      if (other_h > height)
         size.setHeight(other_h);
   }
   else
   {
      position.setY(other.y);
      size.setHeight(other.height);
   }

   return *this;
}

Rect &Rect::intersect(const Rect &other)
{
   Point::component_t x0(max(x, other.x));
   Point::component_t y0(max(y, other.y));

   Point::component_t x1(min(getRight(), other.getRight()));
   Point::component_t y1(min(getBottom(), other.getBottom()));

   set(x0, y0, x1 - x0, y1 - y0);
   return *this;
}

bool Rect::isInside(const Point &p) const
{
   return p.x >= getLeft() && p.x < getRight() &&
          p.y >= getTop() && p.y < getBottom();
}

std::ostream &operator<<(std::ostream &os, const Rect &rect)
{
   return os << rect.position << '|' << rect.size;
}

FGUI_END