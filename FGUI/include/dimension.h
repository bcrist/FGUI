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
// File: dimension.h

#ifndef FGUI_DIMENSION_H_
#define FGUI_DIMENSION_H_
#include "fgui_std.h"

#include <ostream>

FGUI_BEGIN

struct Dimension
{
   typedef float_t component_t;

   Dimension();
   Dimension(const Dimension &other);
   Dimension(component_t width, component_t height);
   explicit Dimension(const component_t *v);

   // comparison operators
   bool operator==(const Dimension &rhs) const;
   bool operator!=(const Dimension &rhs) const;

   // assignment operators
   Dimension &operator=(const Dimension &rhs);

   Dimension &setWidth(component_t width);
   Dimension &setHeight(component_t height);
   Dimension &set(component_t width, component_t height);

   const component_t &width;
   const component_t &height;
   const component_t* const v;

private:
   component_t dim[2];
};

std::ostream &operator<<(std::ostream &os, const Dimension &dim);

FGUI_END

#include "dimension.inl"

#endif
