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
// File: component/f_colored_rectangle.cc

#include "component/f_colored_rectangle.h"

#include "platform/platform.h"

FGUI_BEGIN

const UID FColoredRectangle::uid_;

FColoredRectangle::FColoredRectangle():
   normal_color_(Color(1, 0, 0)),
   focused_color_(Color(1, 0, 0)),
   hover_color_(Color(1, 0, 0)),
   active_color_(Color(1, 0, 0)),
   active_(false),
   mouse_over_(false)
{
   setRenderer(getPlatform()->checkoutRenderer(uid_));
   addFocusListener(this);
   addKeyboardListener(this);
   addMouseListener(this);
   addSimulationListener(this);
   setFocusable(true);
}

FColoredRectangle::FColoredRectangle(const Color &color):
   normal_color_(color),
   focused_color_(color),
   hover_color_(color),
   active_color_(color),
   active_(false),
   mouse_over_(false)
{
   setRenderer(getPlatform()->checkoutRenderer(uid_));
   addFocusListener(this);
   addKeyboardListener(this);
   addMouseListener(this);
   addSimulationListener(this);
   setFocusable(true);
}

FColoredRectangle::FColoredRectangle(const Color &normalColor,
   const Color &focusedColor,
   const Color &hoverColor,
   const Color &activeColor):
      normal_color_(normalColor),
      focused_color_(focusedColor),
      hover_color_(hoverColor),
      active_color_(activeColor),
      active_(false),
      mouse_over_(false)
{
   setRenderer(getPlatform()->checkoutRenderer(uid_));
   addFocusListener(this);
   addKeyboardListener(this);
   addMouseListener(this);
   addSimulationListener(this);
   setFocusable(true);
}

FColoredRectangle::~FColoredRectangle()
{
   getPlatform()->returnRenderer(uid_, getRenderer());
}


void FColoredRectangle::onFocusIn(FocusEvent *evt)
{
   log("FocusIn");
}
void FColoredRectangle::onFocusOut(FocusEvent *evt)
{
   log("FocusOut");
}

void FColoredRectangle::onKeyDown(KeyboardEvent *evt)
{
   log("KeyDown");
   evt->consume();
}
void FColoredRectangle::onKeyUp(KeyboardEvent *evt)
{
   log("KeyUp");
   evt->consume();
}
void FColoredRectangle::onCharacterInput(KeyboardEvent *evt)
{
   log("CharacterInput");
   evt->consume();
}

void FColoredRectangle::onMouseMove(MouseEvent *evt)
{
   //log("MouseMove");
}
void FColoredRectangle::onMouseEnter(MouseEvent *evt)
{
   log("MouseEnter");
}
void FColoredRectangle::onMouseLeave(MouseEvent *evt)
{
   log("MouseLeave");
}
void FColoredRectangle::onMouseEnterDirect(MouseEvent *evt)
{
   log("MouseEnterDirect");
   setMouseOver(true);
}
void FColoredRectangle::onMouseLeaveDirect(MouseEvent *evt)
{
   log("MouseLeaveDirect");
   setMouseOver(false);
}
void FColoredRectangle::onMouseHover(MouseEvent *evt)
{
   log("MouseHover");
}
void FColoredRectangle::onMouseHoverDirect(MouseEvent *evt)
{
   log("MouseHoverDirect");
}
void FColoredRectangle::onMouseWheel(MouseEvent *evt)
{
   log("MouseWheel");
   evt->consume();
}
void FColoredRectangle::onMouseDown(MouseEvent *evt)
{
   log("MouseDown");
   if (mouse_over_ && evt->button == 1)
      setActive(true);
   evt->consume();
}
void FColoredRectangle::onMouseUp(MouseEvent *evt)
{
   log("MouseUp");
   setActive(false);
   evt->consume();
}
void FColoredRectangle::onMouseClick(MouseEvent *evt)
{
   log("MouseClick");
}
void FColoredRectangle::onMouseDoubleClick(MouseEvent *evt)
{
   log("MouseDoubleClick");
   logDebug();
}

void FColoredRectangle::onSimulate(SimulateEvent *evt)
{
   //log("Simulate");
}
void FColoredRectangle::onResetSimulation(SimulateEvent *evt)
{
   log("ResetSimulation");
}

void FColoredRectangle::setActive(bool active)
{
   if (active_ != active)
   {
      active_ = active;
      makeDirty();
   }
}

void FColoredRectangle::setMouseOver(bool mouse_over)
{
   if (mouse_over_ != mouse_over)
   {
      mouse_over_ = mouse_over;
      makeDirty();
   }
}

FGUI_END
