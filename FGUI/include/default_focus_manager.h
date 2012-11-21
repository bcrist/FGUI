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
// File: default_focus_manager.h

#ifndef FGUI_DEFAULT_FOCUS_MANAGER_H_
#define FGUI_DEFAULT_FOCUS_MANAGER_H_
#include "fgui_std.h"

#include "focus_manager_interface.h"

FGUI_BEGIN

   class DefaultFocusManager : public FocusManagerInterface
   {
   public:
      DefaultFocusManager() : focus_root_(NULL) {}
      virtual ~DefaultFocusManager() {}

      // TODO: make sure component selected is a descendant of the modal component (if present)
      virtual FComponent *getNext(FComponent *current_focus);
      virtual FComponent *getPrev(FComponent *current_focus);

      void setFocusRoot(FComponent *focus_root) { focus_root_ = focus_root; }

   protected:
      FComponent *getFirstFocusableDescendant(FComponent *comp);
      FComponent *getLastFocusableDescendant(FComponent *comp);
      FComponent *getFirstFocusableAfter(FComponent *parent, int index);
      FComponent *getLastFocusableBefore(FComponent *parent, int index);

   private:
      FComponent *focus_root_;
   };

FGUI_END

#endif