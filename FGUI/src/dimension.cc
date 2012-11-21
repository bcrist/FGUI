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
// File: dimension.cc

#include "dimension.h"

#define FGUI_DIMENSION_INITLIST width(dim[0]), height(dim[1]), v(&dim[0])

FGUI_BEGIN

Dimension::Dimension() : FGUI_DIMENSION_INITLIST
{
   dim[0] = 0.0;
   dim[1] = 0.0;
}

Dimension::Dimension(const Dimension &other) : FGUI_DIMENSION_INITLIST
{
   dim[0] = other.width;
   dim[1] = other.height;
}

Dimension::Dimension(component_t width, component_t height) : FGUI_DIMENSION_INITLIST
{
   dim[0] = width < 0.0f ? 0.0f : width;
   dim[1] = height < 0.0f ? 0.0f : height;
}

Dimension::Dimension(const component_t *v) : FGUI_DIMENSION_INITLIST
{
   dim[0] = v[0] < 0.0f ? 0.0f : v[0];
   dim[1] = v[1] < 0.0f ? 0.0f : v[1];
}

Dimension &Dimension::operator=(const Dimension &rhs)
{
   dim[0] = rhs.width;
   dim[1] = rhs.height;
   return *this;
}

bool Dimension::operator==(const Dimension &rhs) const
{
   return width == rhs.width && height == rhs.height;
}

bool Dimension::operator!=(const Dimension &rhs) const
{
   return !(*this == rhs);
}

Dimension &Dimension::setWidth(component_t width)
{
   dim[0] = width < 0.0f ? 0.0f : width;
   return *this;
}

Dimension &Dimension::setHeight(component_t height)
{
   dim[1] = height < 0.0f ? 0.0f : height;
   return *this;
}

Dimension &Dimension::set(component_t width, component_t height)
{
   dim[0] = width < 0.0f ? 0.0f : width;
   dim[1] = height < 0.0f ? 0.0f : height;
   return *this;
}


std::ostream &operator<<(std::ostream &os, const Dimension &dim)
{
   return os << dim.width << 'x' << dim.height;
}

FGUI_END