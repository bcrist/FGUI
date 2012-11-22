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
// File: color.cc

#include "color.h"

FGUI_BEGIN

const Color::component_t Color::kMUL_2 =  1.0f / 3.0f;
const Color::component_t Color::kMUL_3 =  1.0f / 7.0f;
const Color::component_t Color::kMUL_4 =  1.0f / 15.0f;
const Color::component_t Color::kMUL_5 =  1.0f / 31.0f;
const Color::component_t Color::kMUL_6 =  1.0f / 63.0f;
const Color::component_t Color::kMUL_7 =  1.0f / 127.0f;
const Color::component_t Color::kMUL_8 =  1.0f / 255.0f;
const Color::component_t Color::kMUL_9 =  1.0f / 511.0f;
const Color::component_t Color::kMUL_10 = 1.0f / 1023.0f;
const Color::component_t Color::kMUL_11 = 1.0f / 2047.0f;
const Color::component_t Color::kMUL_12 = 1.0f / 4095.0f;
const Color::component_t Color::kMUL_13 = 1.0f / 8191.0f;
const Color::component_t Color::kMUL_14 = 1.0f / 16383.0f;
const Color::component_t Color::kMUL_15 = 1.0f / 32767.0f;
const Color::component_t Color::kMUL_16 = 1.0f / 65535.0f;



Color::Color(const component_t *components, size_t component_count) : r(v[0]), g(v[1]), b(v[2]), a(v[3])
{
   if (component_count > 0 && component_count <= 4)
      memcpy(v, components, component_count * sizeof(component_t));
   else
      component_count = 0;

   while (component_count < 4)
      v[component_count++] = 1.0f;
}

Color::Color(const Color &first, const Color &second, float f) : r(v[0]), g(v[1]), b(v[2]), a(v[3])
{
   f = f < 0.0f ? 0.0f : (f > 1.0f ? 1.0f : f);
   float fi = 1.0f - f;

   r = (component_t)(second.r * f + first.r * fi);
   g = (component_t)(second.g * f + first.g * fi);
   b = (component_t)(second.b * f + first.b * fi);
   a = (component_t)(second.a * f + first.a * fi);
}

Color::Color(const Color &first, const Color &second, double f) : r(v[0]), g(v[1]), b(v[2]), a(v[3])
{
   f = f < 0.0 ? 0.0 : (f > 1.0 ? 1.0 : f);
   double fi = 1.0 - f;

   r = (component_t)(second.r * f + first.r * fi);
   g = (component_t)(second.g * f + first.g * fi);
   b = (component_t)(second.b * f + first.b * fi);
   a = (component_t)(second.a * f + first.a * fi);
}

Color &Color::clamp()
{
   if (r > 1.0f) r = 1.0f; else if (r < 0.0f) r = 0.0f;
   if (g > 1.0f) g = 1.0f; else if (g < 0.0f) g = 0.0f;
   if (b > 1.0f) b = 1.0f; else if (b < 0.0f) b = 0.0f;
   if (a > 1.0f) a = 1.0f; else if (a < 0.0f) a = 0.0f;
   return *this;
}

Color &Color::clamp(const Color &max)
{
   if (r > max.r) r = max.r; else if (r < 0.0f) r = 0.0f;
   if (g > max.g) g = max.g; else if (g < 0.0f) g = 0.0f;
   if (b > max.b) b = max.b; else if (b < 0.0f) b = 0.0f;
   if (a > max.a) a = max.a; else if (a < 0.0f) a = 0.0f;
   return *this;
}

Color &Color::clamp(const Color &min, const Color &max)
{
   if (r > max.r) r = max.r; else if (r < min.r) r = min.r;
   if (g > max.g) g = max.g; else if (g < min.g) g = min.g;
   if (b > max.b) b = max.b; else if (b < min.b) b = min.b;
   if (a > max.a) a = max.a; else if (a < min.a) a = min.a;
   return *this;
}

std::ostream &operator<<(std::ostream &os, const Color &v)
{
   return os << "rgba(" << v.r << ',' << v.g << ',' << v.b << ',' << v.a << ')';
}

FGUI_END