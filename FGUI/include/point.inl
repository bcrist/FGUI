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
// File: point.inl

#ifdef FGUI_POINT_H_

FGUI_BEGIN

inline Point::Point() : x(val[0]), y(val[1]), v(&val[0])
{
   val[0] = 0.0;
   val[1] = 0.0;
}

inline Point::Point(const Point &other) : x(val[0]), y(val[1]), v(&val[0])
{
   val[0] = other.x;
   val[1] = other.y;
}

inline Point::Point(component_t x, component_t y) : x(val[0]), y(val[1]), v(&val[0])
{
   val[0] = x;
   val[1] = y;
}

inline Point::Point(const component_t *v) : x(val[0]), y(val[1]), v(&val[0])
{
   val[0] = v[0];
   val[1] = v[1];
}

inline bool Point::operator==(const Point &rhs) const
{
   return x == rhs.x && y == rhs.y;
}

inline bool Point::operator!=(const Point &rhs) const
{
   return !(*this == rhs);
}

inline Point &Point::operator=(const Point &rhs)
{
   val[0] = rhs.x;
   val[1] = rhs.y;
   return *this;
}

inline Point &Point::setX(component_t x)
{
   val[0] = x;
   return *this;
}

inline Point &Point::setY(component_t y)
{
   val[1] = x;
   return *this;
}

inline Point &Point::set(component_t x, component_t y)
{
   val[0] = x;
   val[1] = y;
   return *this;
}

FGUI_END

#endif