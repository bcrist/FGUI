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
// File: component/f_component_cfg.h

#ifndef FGUI_COMPONENT_F_COMPONENT_CFG_H_
#define FGUI_COMPONENT_F_COMPONENT_CFG_H_
#include "fgui_std.h"

#include "dimension.h"
#include "point.h"

#include "renderer_interface.h"

FGUI_BEGIN

class LayoutManagerInterface;
class FocusManagerInterface;

struct FComponent_cfg
{
   FComponent_cfg():
      contents_locked(false),
      destroy_children(false),
      layout_mgr(NULL),
      min_size(Dimension(0, 0)),
      pref_size(Dimension(0, 0)),
      max_size(Dimension(0, 0)),
      position(Point(0, 0)),
      size(Dimension(0, 0)),
      visible(true),
      z_index(0),
      renderer(NULL),
      focusable(false),
      modal(false),
      focus_mgr(NULL) {}
   virtual ~FComponent_cfg() {}

   bool contents_locked;
   bool destroy_children;

   LayoutManagerInterface *layout_mgr;

   Dimension min_size;
   Dimension pref_size;
   Dimension max_size;

   Point position;
   Dimension size;

   bool visible;
   int z_index;
   RendererInterface *renderer;

   bool focusable;
   bool modal;
   FocusManagerInterface *focus_mgr;

   virtual bool getContentsLocked() const { return contents_locked; }
   virtual bool getDestroyChildren() const { return destroy_children; }

   virtual LayoutManagerInterface *getLayoutMgr() const { return layout_mgr; }
   virtual const Dimension &getMinimumSize() const { return min_size; }
   virtual const Dimension &getPreferredSize() const { return pref_size; }
   virtual const Dimension &getMaximumSize() const { return max_size; }

   virtual const Point &getPosition() const { return position; }
   virtual const Dimension &getSize() const { return size; }

   virtual bool getVisible() const { return visible; }
   virtual int getZIndex() const { return z_index; }
   virtual RendererInterface *getRenderer() const { return renderer; }

   virtual bool getFocusable() const { return focusable; }
   virtual bool getModal() const { return modal; }
   virtual FocusManagerInterface *getFocusMgr() const { return focus_mgr; }
};

FGUI_END

#endif