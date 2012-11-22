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
// File: point.h

#ifndef FGUI_POINT_H_
#define FGUI_POINT_H_
#include "fgui_std.h"

#include <ostream>

FGUI_BEGIN

struct Point
{
   typedef float_t component_t;

   Point();
   Point(const Point &other);
   Point(component_t x, component_t y);
   explicit Point(const component_t *v);

   // comparison operators
   bool operator==(const Point &rhs) const;
   bool operator!=(const Point &rhs) const;

   // assignment operators
   Point &operator=(const Point &rhs);

   Point &setX(component_t x);
   Point &setY(component_t y);
   Point &set(component_t x, component_t y);

   const component_t &x;
   const component_t &y;
   const component_t* const v;

private:
   component_t val[2];
};

std::ostream &operator<<(std::ostream &os, const Point &point);

FGUI_END

#include "point.inl"

#endif
