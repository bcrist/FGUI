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
// File: event/mouse_listener_interface.h

#ifndef FGUI_EVENT_MOUSE_LISTENER_INTERFACE_H_
#define FGUI_EVENT_MOUSE_LISTENER_INTERFACE_H_
#include "fgui_std.h"

FGUI_BEGIN

struct MouseEvent;

class MouseListenerInterface
{
public:
   virtual ~MouseListenerInterface() {}

   virtual void onMouseMove(MouseEvent &) = 0;
   virtual void onMouseEnter(MouseEvent &) = 0;
   virtual void onMouseLeave(MouseEvent &) = 0;
   virtual void onMouseEnterDirect(MouseEvent &) = 0;
   virtual void onMouseLeaveDirect(MouseEvent &) = 0;
   virtual void onMouseHover(MouseEvent &) = 0;
   virtual void onMouseHoverDirect(MouseEvent &) = 0;
   virtual void onMouseWheel(MouseEvent &) = 0;
   virtual void onMouseDown(MouseEvent &) = 0;
   virtual void onMouseUp(MouseEvent &) = 0;
   virtual void onMouseClick(MouseEvent &) = 0;
   virtual void onMouseDoubleClick(MouseEvent &) = 0;

};

FGUI_END

#endif