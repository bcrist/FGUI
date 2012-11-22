#ifndef FGUI_EVENT_EVENT_H_
#include "event/event.h"
#else

FGUI_BEGIN

inline Event::Event(int type, FComponent *target)
      : cancelled(cancelled_),
        propagationStopped(propagationStopped_),
        type(type),
        target(target),
        cancelled_(false),
        propagationStopped_(false) {}

inline Event::Event(int type, FComponent *target, bool propagates)
      : cancelled(cancelled_),
        propagationStopped(propagationStopped_),
        type(type),
        target(target),
        cancelled_(false),
        propagationStopped_(!propagates) {}


inline void Event::cancel()
{
   cancelled = true;
   propagationStopped = true;
}

inline void Event::stopPropagation()
{
   propagationStopped = true;
}

inline bool Event::isCancelled() const
{
   return cancelled;
}

inline bool Event::isPropagationStopped() const
{
   return propagationStopped;
}

FGUI_END

#endif