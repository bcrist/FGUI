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
// File: dimension.inl

#ifdef FGUI_DIMENSION_H_

FGUI_BEGIN

inline Dimension::Dimension() : width(dim[0]), height(dim[1]), v(&dim[0])
{
   dim[0] = 0.0;
   dim[1] = 0.0;
}

inline Dimension::Dimension(const Dimension &other) : width(dim[0]), height(dim[1]), v(&dim[0])
{
   dim[0] = other.width;
   dim[1] = other.height;
}

inline Dimension::Dimension(component_t width, component_t height) : width(dim[0]), height(dim[1]), v(&dim[0])
{
   dim[0] = width < 0.0f ? 0.0f : width;
   dim[1] = height < 0.0f ? 0.0f : height;
}

inline Dimension::Dimension(const component_t *v) : width(dim[0]), height(dim[1]), v(&dim[0])
{
   dim[0] = v[0] < 0.0f ? 0.0f : v[0];
   dim[1] = v[1] < 0.0f ? 0.0f : v[1];
}

inline Dimension &Dimension::operator=(const Dimension &rhs)
{
   dim[0] = rhs.width;
   dim[1] = rhs.height;
   return *this;
}

inline bool Dimension::operator==(const Dimension &rhs) const
{
   return width == rhs.width && height == rhs.height;
}

inline bool Dimension::operator!=(const Dimension &rhs) const
{
   return !(*this == rhs);
}

inline Dimension &Dimension::setWidth(component_t width)
{
   dim[0] = width < 0.0f ? 0.0f : width;
   return *this;
}

inline Dimension &Dimension::setHeight(component_t height)
{
   dim[1] = height < 0.0f ? 0.0f : height;
   return *this;
}

inline Dimension &Dimension::set(component_t width, component_t height)
{
   dim[0] = width < 0.0f ? 0.0f : width;
   dim[1] = height < 0.0f ? 0.0f : height;
   return *this;
}

FGUI_END

#endif
