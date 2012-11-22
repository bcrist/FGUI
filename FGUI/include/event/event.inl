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
// File: event/event.inl

#ifdef FGUI_EVENT_EVENT_H_

FGUI_BEGIN

inline Event::Event(int type, FComponent *target)
      : cancelled(cancelled_),
        propagation_stopped(propagation_stopped_),
        type(type),
        target(target),
        cancelled_(false),
        propagation_stopped_(false) {}

inline Event::Event(int type, FComponent *target, bool propagates)
      : cancelled(cancelled_),
        propagation_stopped(propagation_stopped_),
        type(type),
        target(target),
        cancelled_(false),
        propagation_stopped_(!propagates) {}


inline void Event::cancel()
{
   cancelled = true;
   propagation_stopped = true;
}

inline void Event::stopPropagation()
{
   propagation_stopped = true;
}

inline bool Event::isCancelled() const
{
   return cancelled;
}

inline bool Event::isPropagationStopped() const
{
   return propagation_stopped;
}

FGUI_END

#endif