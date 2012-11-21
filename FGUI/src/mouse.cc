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
// File: mouse.cc

#include "mouse.h"

#include "component/f_component.h"

FGUI_BEGIN

const Point Mouse::kINVALID(-1, -1);

Mouse::Mouse() : position_(Point(-1, -1))
{
}

void Mouse::down(int button, FComponent *component)
{
   if (button > 0 && button <= FGUI_MOUSE_BUTTON_COUNT)
   {
      ButtonState &btn = buttons_[button];
      btn.component = component;
      btn.down = true;
      btn.pos = position_;
   }
}

void Mouse::up(int button)
{
   if (button > 0 && button <= FGUI_MOUSE_BUTTON_COUNT)
   {
      ButtonState &btn = buttons_[button];
      btn.down = false;
      btn.pos = kINVALID;
      btn.component = NULL;
   }
}

bool Mouse::isDown(int button) const
{
   if (button > 0 && button <= FGUI_MOUSE_BUTTON_COUNT)
      return buttons_[button].down;
   return false;
}

const Point &Mouse::downPosition(int button) const
{
   if (button > 0 && button <= FGUI_MOUSE_BUTTON_COUNT)
      return buttons_[button].pos;
   return kINVALID;
}

FComponent *Mouse::downComponent(int button) const
{
   if (button > 0 && button <= FGUI_MOUSE_BUTTON_COUNT)
      return buttons_[button].component;
   return NULL;
}

void Mouse::removeDownComponent(FComponent *component)
{
   for (int i = 0; i < FGUI_MOUSE_BUTTON_COUNT; ++i)
      if(buttons_[i].component == component)
         buttons_[i].component = NULL;
}

FGUI_END