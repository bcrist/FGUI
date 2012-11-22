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
// File: color.h

#ifndef FGUI_COLOR_H_
#define FGUI_COLOR_H_
#include "fgui_std.h"

#include <ostream>

FGUI_BEGIN

struct Color
{
   typedef float_t component_t;

   static const component_t kMUL_2;
   static const component_t kMUL_3;
   static const component_t kMUL_4;
   static const component_t kMUL_5;
   static const component_t kMUL_6;
   static const component_t kMUL_7;
   static const component_t kMUL_8;
   static const component_t kMUL_9;
   static const component_t kMUL_10;
   static const component_t kMUL_11;
   static const component_t kMUL_12;
   static const component_t kMUL_13;
   static const component_t kMUL_14;
   static const component_t kMUL_15;
   static const component_t kMUL_16;

   // constructors
   Color();
   Color(const Color &other);
   Color(const Color &other, component_t rgba_mul);
   Color(const Color &other, component_t rgb_mul, component_t a_mul);
   explicit Color(component_t lum);
   Color(component_t lum, component_t alpha);
   Color(component_t red, component_t green, component_t blue);
   Color(component_t red, component_t green, component_t blue, component_t alpha);
   explicit Color(const component_t *components);
   Color(const component_t *components, size_t component_count);
   Color(const Color &first, const Color &second, float f);
   Color(const Color &first, const Color &second, double f);
   
   // assignment operators
   Color &operator=(const Color &rhs);
   Color &operator+=(const Color &rhs);
   Color &operator-=(const Color &rhs);
   Color &operator*=(const Color &rhs);
   Color &operator/=(const Color &rhs);
   
   // arithmetic operators
   const Color operator+(const Color &rhs) const;
   const Color operator-(const Color &rhs) const;
   const Color operator*(const Color &rhs) const;
   const Color operator/(const Color &rhs) const;

   Color &invert();
   Color &clamp();
   Color &clamp(const Color &max);
   Color &clamp(const Color &min, const Color &max);

   component_t &r;
   component_t &g;
   component_t &b;
   component_t &a;

   component_t v[4];
};

std::ostream &operator<<(std::ostream &os, const Color &v);

FGUI_END

#include "color.inl"

#endif
