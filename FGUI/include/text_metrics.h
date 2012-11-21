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
// File: text_metrics.h

#ifndef FGUI_TEXT_METRICS_H_
#define FGUI_TEXT_METRICS_H_
#include "fgui_std.h"

#include "point.h"

FGUI_BEGIN

struct TextMetrics
{
   TextMetrics(Point bounds_top_left, Point bounds_bottom_right, Point line_top_left, Point line_bottom_right, float_t line_height):
      bounds_top_left(bounds_top_left),
      bounds_bottom_right(bounds_bottom_right),
      line_top_left(line_top_left),
      line_bottom_right(line_bottom_right),
      line_height(line_height) {}

   const Point bounds_top_left;
   const Point bounds_bottom_right;

   const Point line_top_left;
   const Point line_bottom_right;

   const float_t line_height;
};

FGUI_END


#endif