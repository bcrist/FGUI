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
// File: event/component_listener.h

#ifndef FGUI_EVENT_COMPONENT_LISTENER_H_
#define FGUI_EVENT_COMPONENT_LISTENER_H_
#include "fgui_std.h"

#include "event/focus_event.h"
#include "event/keyboard_event.h"
#include "event/mouse_event.h"
#include "event/simulate_event.h"

FGUI_BEGIN

class ComponentListener
{
public:
   virtual ~ComponentListener() {}

   virtual void onMouseMove(MouseEvent &) {}
   virtual void onMouseWheel(MouseEvent &) {}
   virtual void onMouseDown(MouseEvent &) {}
   virtual void onMouseUp(MouseEvent &) {}
   virtual void onMouseClick(MouseEvent &) {}
   virtual void onMouseDoubleClick(MouseEvent &) {}

   virtual void onKeyDown(KeyboardEvent &) {}
   virtual void onKeyUp(KeyboardEvent &) {}
   virtual void onCharacterInput(KeyboardEvent &) {}

   virtual void onFocusIn(FocusEvent &) {}
   virtual void onFocusOut(FocusEvent &) {}

   virtual void onSimulate(SimulateEvent &) {}
   virtual void onResetSimulation(SimulateEvent &) {}
};

FGUI_END

#endif