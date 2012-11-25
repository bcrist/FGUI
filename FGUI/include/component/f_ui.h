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
// File: component/f_ui.h

#ifndef FGUI_COMPONENT_F_UI_H_
#define FGUI_COMPONENT_F_UI_H_
#include "fgui_std.h"

#include "component/f_component.h"

#include <stdint.h>
#include <vector>
#include <list>
#include <algorithm>

#include "component/f_ui_cfg.h"
#include "mouse.h"
#include "keyboard.h"
#include "default_focus_manager.h"

FGUI_BEGIN

class FUI : public FComponent
{
   // Modal Component support
private:
   std::list<FComponent*> modal_components_; // changes infrequently, so no need for set or vector
   FComponent *modal_component_;
public:
   virtual FComponent *getModalComponent() const { return modal_component_; }
   virtual bool checkModalDescendant(FComponent *component) const { return !modal_component_ || component->isDescendantOf(modal_component_); }
   virtual void registerModal(FComponent *component);
   virtual void unregisterModal(FComponent *component);
   

   // Focusing
private:
   DefaultFocusManager default_focus_manager_;
   FComponent *focused_component_;      // the component with keyboard focus

protected:
   virtual bool setFocus(FComponent *component, FocusEvent::Cause cause);
public:
   virtual FComponent *getFocusedComponent() const { return focused_component_; }
   virtual bool setFocus(FComponent *component) { return setFocus(component, FocusEvent::kREQUEST); }
   virtual bool focusNext();
   virtual bool focusPrev();


   // Mouse/Keyboard/Window Events
private:
   bool active_ui_;

   Keyboard keyboard_state_;
   Mouse mouse_state_;
   bool under_mouse_key_events_enabled_;

   std::vector<FComponent*> *components_under_mouse_;
   std::vector<FComponent*> *components_under_mouse_old_;
   std::vector<FComponent*> components_under_mouse_1_;
   std::vector<FComponent*> components_under_mouse_2_;
   std::vector<FComponent*> components_under_mouse_temp_;
   
   std::vector<FComponent*> hovered_components_;
   FComponent *last_click_component_;

   int min_hover_delay_;
   int max_double_click_interval_;

   int64_t hover_start_ticks_;
   int64_t last_click_ticks_;

   void _swapComponentsUnderMousePointers();
   void _removeHoveredComponent(FComponent *component);
   void _removeComponentUnderMouse(FComponent *component);
   void _removeOldComponentUnderMouse(FComponent *component);
   void _removeLastClickComponent(FComponent *component);
   void componentRemoved(FComponent *component);

public:
   virtual bool getUnderMouseKeyEventsEnabled() const { return under_mouse_key_events_enabled_; }
   virtual void setUnderMouseKeyEventsEnabled(bool enabled) { under_mouse_key_events_enabled_ = enabled; }
   virtual void enableUnderMouseKeyEvents() { under_mouse_key_events_enabled_ = true; }
   virtual void disableUnderMouseKeyEvents() { under_mouse_key_events_enabled_ = false; }

   virtual int getMinimumHoverDelay() const { return min_hover_delay_; }
   virtual void setMinimumHoverDelay(int delay) { min_hover_delay_ = delay; }

   virtual int getMaximumDoubleClickInterval() const { return max_double_click_interval_; }
   virtual void setMaximumDoubleClickInterval(int interval) { max_double_click_interval_ = interval; }

   virtual void uiActiveStatus(bool active);
   virtual bool uiResize(const Dimension &size);

   virtual bool uiMouseMove(const Point &location);
   virtual bool uiMouseButton(int button, bool is_down);
   virtual bool uiMouseWheel(int delta_z, int delta_w);

   virtual bool uiKeyState(int key, bool is_down);
   virtual bool uiCharacterEntry(int codepoint);
   

   // Rendering
private:
   RendererInterface *prepare_renderer_;
   RendererInterface *cleanup_renderer_;

   std::vector<RenderTask> render_tasks_;
   bool render_tasks_valid_;

   Rect dirty_;
   bool dirty_set_;

   void populateRenderTasks();

public:
   static const UID prepare_renderer_uid_;
   static const UID cleanup_renderer_uid_;

   virtual bool uiDrawRequested() const { return dirty_set_; }
   virtual void uiDraw();
   virtual void makeDirty(const Rect &absolute_rect);
   virtual void invalidateRenderTasks() { render_tasks_valid_ = false; }


   // Simulation
private:
   int ticks_per_second_;
   int min_simulate_event_interval_;  // min ticks between triggering simulate events
   int64_t ticks_;
   int64_t last_simulate_ticks_;
public:
   virtual int getTicksPerSecond() const { return ticks_per_second_; }
   virtual int getMinimumSimulateEventInterval() const { return min_simulate_event_interval_; }
   virtual int64_t getTicks() const { return ticks_; }

   virtual void uiSimulate(int delta);    // TODO: check hover events, all_components_laid_out_, render_tasks_valid_
   virtual void uiResetSimulation();
   virtual void uiResetSimulation(int ticks_per_sec, int min_simulate_event_interval);


   // Clipboard
private:
   ClipboardInterface *clipboard_;
public:
   ClipboardInterface &getClipboard() { return *clipboard_; }


   // Fonts
private:
   FontProviderInterface *font_provider_;
public:
   FontProviderInterface &getFontProvider() { return *font_provider_; }


   // FComponent overrides
public:
   virtual bool checkPointOverComponent(const Point &absolute_coord) const { return false; }
   virtual void layoutComponent() { FComponent::layoutComponent(); uiMouseMove(mouse_state_.getPosition()); }


   // (De|Con)structors
public:
   FUI();
   FUI(PlatformInterface &platform);
   FUI(const FUI_cfg &cfg);
   FUI(PlatformInterface &platform, const FUI_cfg &cfg);
   virtual ~FUI();

private:
   friend class FComponent;
   DISALLOW_COPY_AND_ASSIGN(FUI);
};

FGUI_END

#include "component/f_ui.inl"

#endif