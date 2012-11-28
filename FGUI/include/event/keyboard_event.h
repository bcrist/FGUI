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
// File: event/keyboard_event.h

#ifndef FGUI_EVENT_KEYBOARD_EVENT_H_
#define FGUI_EVENT_KEYBOARD_EVENT_H_
#include "fgui_std.h"

#include "event/event.h"

FGUI_BEGIN

struct KeyboardEvent : Event
{
   enum Type
   {
      kKEY_DOWN = FGUI_EVENT_TYPE_KEYBOARD,
      kKEY_UP,
      kCHARACTER_INPUT
   };

   KeyboardEvent(int type, FComponent *target, int keycode, int codepoint)
         : Event(type, target, false),
           keycode(keycode),
           codepoint(codepoint),
           consumed(false) {}

   // if something is using a key event, usually it doesn't want anything else
   // to also use it.
   void consume() { consumed = true; stopPropagation(); }
   bool isConsumed() const { return consumed; }

   const int keycode;
   const int codepoint;

private:
   bool consumed;
};

FGUI_END

#endif