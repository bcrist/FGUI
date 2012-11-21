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
// File: event/mouse_event.h

#ifndef FGUI_EVENT_MOUSE_EVENT_H_
#define FGUI_EVENT_MOUSE_EVENT_H_
#include "fgui_std.h"

#include "event/event.h"

#include "point.h"

FGUI_BEGIN

class FComponent;

struct MouseEvent : Event
{
   enum Type
   {
      kMOUSE_MOVE = FGUI_EVENT_TYPE_MOUSE,
      kMOUSE_WHEEL,
      kMOUSE_DOWN,
      kMOUSE_UP,
      kMOUSE_CLICK,
      kMOUSE_DOUBLE_CLICK,

      kMOUSE_ENTER,
      kMOUSE_ENTER_DIRECT,
      kMOUSE_LEAVE,
      kMOUSE_LEAVE_DIRECT,

      kMOUSE_HOVER
   };

   MouseEvent(int type, FComponent *target, const Point &loc)
         : Event(type, target),
           location(loc),
           button(0),
           deltaZ(0),
           deltaW(0),
           down_location(Point(-1,-1)),
           down_component(NULL) {}

   MouseEvent(int type, FComponent *target, const Point &loc, int button)
         : Event(type, target),
           location(loc),
           button(button),
           deltaZ(0),
           deltaW(0),
           down_location(Point(-1,-1)),
           down_component(NULL) {}
   
   MouseEvent(int type, FComponent *target, const Point &loc, int button, int deltaZ, int deltaW)
         : Event(type, target),
           location(loc),
           button(button),
           deltaZ(deltaZ),
           deltaW(deltaW),
           down_location(Point(-1,-1)),
           down_component(NULL) {}

   MouseEvent(int type, FComponent *target, const Point &loc, int button, int deltaZ, int deltaW, const Point &dloc, FComponent *dcomp)
         : Event(type, target),
           location(loc),
           button(button),
           deltaZ(deltaZ),
           deltaW(deltaW),
           down_location(dloc),
           down_component(dcomp) {}

   const Point location;
   const int button;
   const int deltaZ;
   const int deltaW;
   const Point down_location;
   FComponent* const down_component;
};

FGUI_END

#endif