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
// File: component/f_ui_cfg.h

#ifndef FGUI_COMPONENT_F_UI_CFG_H_
#define FGUI_COMPONENT_F_UI_CFG_H_
#include "fgui_std.h"

#include "component/f_component_cfg.h"

FGUI_BEGIN

class ClipboardInterface;
class FontProviderInterface;

struct FUI_cfg : public FComponent_cfg
{
   FUI_cfg()
         : clipboard(NULL),
           font_provider(NULL),
           under_mouse_key_events_enabled(true),
           ticks_per_second(1000),
           min_hover_delay(600),
           max_double_click_interval(350),
           min_simulate_event_interval(10),
           use_default_prepare_renderer(true),
           use_default_cleanup_renderer(true),
           prepare_renderer(NULL),
           cleanup_renderer(NULL)
   {
      destroy_children = true;
   }
   virtual ~FUI_cfg() {}

   ClipboardInterface *clipboard;
   FontProviderInterface *font_provider;
   bool under_mouse_key_events_enabled;
   int ticks_per_second;
   int min_hover_delay;
   int max_double_click_interval;
   int min_simulate_event_interval;
   bool use_default_prepare_renderer;
   bool use_default_cleanup_renderer;
   RendererInterface *prepare_renderer;
   RendererInterface *cleanup_renderer;

   virtual ClipboardInterface *getClipboard() const { return clipboard; }
   virtual FontProviderInterface *getFontProvider() const { return font_provider; }
   virtual bool getUnderMouseKeyEventsEnabled() const { return under_mouse_key_events_enabled; }
   virtual int getTicksPerSecond() const { return ticks_per_second; }

   virtual int getMinimumHoverDelay() const { return min_hover_delay; }
   virtual int getMaximumDoubleClickInterval() const { return max_double_click_interval; }
   virtual int getMinimumSimulateEventInterval() const { return min_simulate_event_interval; }
   virtual bool getUseDefaultPrepareRenderer() const { return use_default_prepare_renderer; }
   virtual bool getUseDefaultCleanupRenderer() const { return use_default_cleanup_renderer; }
   virtual RendererInterface *getPrepareRenderer() const { return prepare_renderer; }
   virtual RendererInterface *getCleanupRenderer() const { return cleanup_renderer; }
};

FGUI_END

#endif