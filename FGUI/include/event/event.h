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
// File: event/event.h

#ifndef FGUI_EVENT_EVENT_H_
#define FGUI_EVENT_EVENT_H_
#include "fgui_std.h"

#define FGUI_EVENT_TYPE_MOUSE 200
#define FGUI_EVENT_TYPE_KEYBOARD 300
#define FGUI_EVENT_TYPE_FOCUS 400
#define FGUI_EVENT_TYPE_SIMULATE 500

FGUI_BEGIN

class FComponent;

struct Event
{
   Event(int type, FComponent *target)
         : cancelled(cancelled_),
           propagation_stopped(propagation_stopped_),
           type(type),
           target(target),
           cancelled_(false),
           propagation_stopped_(false) {}

   Event(int type, FComponent *target, bool propagates)
         : cancelled(cancelled_),
           propagation_stopped(propagation_stopped_),
           type(type),
           target(target),
           cancelled_(false),
           propagation_stopped_(!propagates) {}

   virtual ~Event() {}
   
   // don't notify any remaining listeners on the current component
   // and don't process the event on the parent object
   void cancel() { cancelled = true; propagation_stopped = true; }
   bool isCancelled() const { return cancelled; }

   // don't process the event on the parent object
   void stopPropagation() { propagation_stopped = true; }
   bool isPropagationStopped() const { return propagation_stopped; }

   const int type;
   FComponent * const target;

private:
   Event &operator=(const Event &other);  // disallow assignment

   // allows copying of event objects where copies are linked to the original's state
   bool &cancelled;
   bool &propagation_stopped;

   bool cancelled_;
   bool propagation_stopped_;
};

FGUI_END

#endif
