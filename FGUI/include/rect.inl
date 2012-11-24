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
// File: rect.inl

#ifdef FGUI_RECT_H_

FGUI_BEGIN

inline Rect::Rect()
      : x(position.x), y(position.y),
        width(size.width), height(size.height)
{
}

inline Rect::Rect(const Rect &other)
      : position(other.position),
        size(other.size),
        x(position.x), y(position.y),
        width(size.width), height(size.height)
{   
}

inline Rect::Rect(const Point &position, const Dimension &size)
      : position(position),
        size(size),
        x(position.x), y(position.y),
        width(size.width), height(size.height)
{
}

inline Rect::Rect(Point::component_t x, Point::component_t y,
                  Dimension::component_t width, Dimension::component_t height)
      : position(x, y),
        size(width, height),
        x(position.x), y(position.y),
        width(size.width), height(size.height)
{
}

inline bool Rect::operator==(const Rect &rhs) const
{
   return position == rhs.position && size == rhs.size;
}

inline bool Rect::operator!=(const Rect &rhs) const
{
   return !(*this == rhs);
}

inline Rect &Rect::operator=(const Rect &rhs)
{
   position = rhs.position;
   size = rhs.size;
   return *this;
}

inline Rect &Rect::setPosition(const Point &position)
{
   this->position = position;
   return *this;
}

inline Rect &Rect::setSize(const Dimension &size)
{
   this->size = size;
   return *this;
}

inline Rect &Rect::set(Point::component_t x, Point::component_t y,
      Dimension::component_t width, Dimension::component_t height)
{
   position.set(x, y);
   size.set(width, height);
   return *this;
}

FGUI_END

#endif