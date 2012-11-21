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
// File: mouse.h

#ifndef FGUI_MOUSE_H_
#define FGUI_MOUSE_H_
#include "fgui_std.h"

#include "point.h"

FGUI_BEGIN

#define FGUI_MOUSE_BUTTON_COUNT 5

class FComponent;

class Mouse
{
public:
   Mouse();

   void setPosition(const Point &position) { position_ = position; }
   const Point &getPosition() const { return position_; }

   void down(int button, FComponent *component);
   void up(int button);

   bool isDown(int button) const;
   const Point &downPosition(int button) const;
   FComponent *downComponent(int button) const;

   void removeDownComponent(FComponent *component);

private:
   Point position_;
   struct ButtonState
   {
      ButtonState(): down(false), pos(Point(-1, -1)), component(NULL) {}
      bool down;
      Point pos;
      FComponent *component;
   } buttons_[FGUI_MOUSE_BUTTON_COUNT];

   static const Point kINVALID;
};

FGUI_END

#endif