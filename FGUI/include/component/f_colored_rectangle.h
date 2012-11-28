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
// File: component/f_colored_rectangle.h

#ifndef FGUI_COMPONENT_F_COLORED_RECTANGLE_H_
#define FGUI_COMPONENT_F_COLORED_RECTANGLE_H_
#include "fgui_std.h"

#include "platform/opengl/colored_rectangle_renderer.h"

#include "component/f_component.h"

#include "color.h"

FGUI_BEGIN

class FColoredRectangle
      : public FComponent,
        public FocusListenerInterface,
        public KeyboardListenerInterface,
        public MouseListenerInterface,
        public SimulationListenerInterface
{
public:
   FColoredRectangle();
   FColoredRectangle(const Color &color);
   FColoredRectangle(const Color &normalColor,
      const Color &focusedColor,
      const Color &hoverColor,
      const Color &activeColor);

   virtual ~FColoredRectangle();

   static const UID uid_;

   virtual const char *getComponentType() const { return "FColoredRectangle"; }

   const Color &getNormalColor() const { return normal_color_; }
   const Color &getFocusedColor() const { return focused_color_; }
   const Color &getMouseOverColor() const { return hover_color_; }
   const Color &getActiveColor() const { return active_color_; }
   
   bool isActive() const { return active_ && mouse_over_; }
   bool isMouseOver() const { return mouse_over_; }

   virtual void onFocusIn(FocusEvent &evt);
   virtual void onFocusOut(FocusEvent &evt);

   virtual void onKeyDown(KeyboardEvent &evt);
   virtual void onKeyUp(KeyboardEvent &evt);
   virtual void onCharacterInput(KeyboardEvent &evt);

   virtual void onMouseMove(MouseEvent &evt);
   virtual void onMouseEnter(MouseEvent &evt);
   virtual void onMouseLeave(MouseEvent &evt);
   virtual void onMouseEnterDirect(MouseEvent &evt);
   virtual void onMouseLeaveDirect(MouseEvent &evt);
   virtual void onMouseHover(MouseEvent &evt);
   virtual void onMouseHoverDirect(MouseEvent &evt);
   virtual void onMouseWheel(MouseEvent &evt);
   virtual void onMouseDown(MouseEvent &evt);
   virtual void onMouseUp(MouseEvent &evt);
   virtual void onMouseClick(MouseEvent &evt);
   virtual void onMouseDoubleClick(MouseEvent &evt);

   virtual void onSimulate(SimulateEvent &evt);
   virtual void onResetSimulation(SimulateEvent &evt);

protected:
   void setActive(bool active);
   void setMouseOver(bool mouse_over);

private:
   bool active_;
   bool mouse_over_;

   Color normal_color_;
   Color focused_color_;
   Color hover_color_;
   Color active_color_;
};

FGUI_END

#endif