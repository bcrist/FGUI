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
// File: component/f_ui.cc

#include "component/f_ui.h"

#include <sstream>
#include <algorithm>
#include <iterator>

FGUI_BEGIN

typedef std::vector<FComponent*> cvec_t;
typedef std::vector<FComponent*>::iterator cvec_iter_t;

// Modal Components

bool compareComponentsZIndex(FComponent *a, FComponent *b)
{
   return a->getZIndex() < b->getZIndex();
}

void FUI::registerModal(FComponent *component)
{
   std::list<FComponent*>::iterator begin(modal_components_.begin()),
                                    end(modal_components_.end()),
                                    it;

   it = std::find(begin, end, component);

   if (it != end)
   {
      modal_components_.push_back(component);
      modal_components_.sort(compareComponentsZIndex);

      FComponent *new_modal = modal_components_.empty() ? NULL : modal_components_.back();

      if (new_modal != modal_component_)
      {
         modal_component_ = new_modal;

         if (modal_component_ &&
             focused_component_ &&
             !focused_component_->isDescendantOf(modal_component_))
         {
            setFocus(NULL, FocusEvent::kSYSTEM);
         }
      }
   }
}

void FUI::unregisterModal(FComponent *component)
{
   std::list<FComponent*>::iterator begin(modal_components_.begin()),
                                    end(modal_components_.end()),
                                    it;

   it = std::find(begin, end, component);

   if (it != end)
   {
      modal_components_.erase(it);

      if (component == modal_component_)
      {
         modal_component_ = modal_components_.empty() ? NULL : modal_components_.back();

         if (modal_component_ &&
             focused_component_ &&
             !focused_component_->isDescendantOf(modal_component_))
         {
            setFocus(NULL, FocusEvent::kSYSTEM);
         }
      }
   }
}

// Focusing

bool FUI::setFocus(FComponent *component, FocusEvent::Cause cause)
{
   if (focused_component_ == component)
      return true;

   if (component && (
       !component->isFocusable() ||
       (modal_component_ && !component->isDescendantOf(modal_component_))))
      return false;

   if (focused_component_)
      if (!focused_component_->fireFocusEvent(FocusEvent(
            FocusEvent::kFOCUS_OUT, focused_component_,
            cause, focused_component_, component)))
         return false;

   if (component)
      if (!component->fireFocusEvent(FocusEvent(
            FocusEvent::kFOCUS_IN, component,
            cause, focused_component_, component)))
         return false;

   if (focused_component_)
      focused_component_->setFocused(false);

   if (component)
      component->setFocused(true);

   focused_component_ = component;

   return true;
}

bool FUI::focusNext()
{
   FComponent *comp = focused_component_ ? focused_component_ : this;
   FocusManagerInterface *fm = comp->getFocusManager();

   // TODO: make defaultfocusmanager check modal_component_.
   if (fm)
      return setFocus(fm->getNext(focused_component_), FocusEvent::kMANAGER);
   
   return false;
}

bool FUI::focusPrev()
{
   FComponent *comp = focused_component_ ? focused_component_ : this;
   FocusManagerInterface *fm = comp->getFocusManager();

   // TODO: make defaultfocusmanager check modal_component_.
   if (fm)
      return setFocus(fm->getPrev(focused_component_), FocusEvent::kMANAGER);
   
   return false;
}


// Mouse/Keyboard/Window Events

void FUI::_swapComponentsUnderMousePointers()
{
   cvec_t *temp(components_under_mouse_);
   components_under_mouse_ = components_under_mouse_old_;
   components_under_mouse_old_ = temp;
}

void FUI::_removeHoveredComponent(FComponent *component)
{
   // remove component from hovered components vector
   cvec_iter_t it = std::find(hovered_components_.begin(), hovered_components_.end(), component);
   if (it != hovered_components_.end())
      hovered_components_.erase(it);
}

void FUI::_removeComponentUnderMouse(FComponent *component)
{
   // remove component from hovered components vector

   cvec_iter_t begin(components_under_mouse_->begin()),
               end(components_under_mouse_->end()),
               it(std::find(begin, end, component));
   if (it != end)
      components_under_mouse_->erase(it);
}

void FUI::_removeOldComponentUnderMouse(FComponent *component)
{
   // remove component from hovered components vector

   cvec_iter_t begin(components_under_mouse_old_->begin()),
               end(components_under_mouse_old_->end()),
               it(std::find(begin, end, component));
   if (it != end)
      components_under_mouse_old_->erase(it);
}

void FUI::_removeLastClickComponent(FComponent *component)
{
   if (last_click_component_ == component)
   {
      last_click_component_ = NULL;
      last_click_ticks_ = -1;
   }
}

void FUI::componentRemoved(FComponent *component)
{
   if (!component)
      return;

   unregisterModal(component);
   _removeHoveredComponent(component);
   _removeComponentUnderMouse(component);
   _removeOldComponentUnderMouse(component);
   _removeLastClickComponent(component);
   mouse_state_.removeDownComponent(component);

   if (focused_component_ == component)
      focused_component_ = NULL;
}



void FUI::uiActiveStatus(bool active)
{
   if (active_ui_ != active)
   {
      active_ui_ = active;

      if (!active)
         keyboard_state_.allUp();

      if (focused_component_)
      {
         if (active)
         {
            focused_component_->fireFocusEvent(FocusEvent(
               FocusEvent::kFOCUS_IN, focused_component_,
               FocusEvent::kSYSTEM, focused_component_, NULL));
            focused_component_->setFocused(true);
         }
         else
         {
            focused_component_->fireFocusEvent(FocusEvent(
               FocusEvent::kFOCUS_OUT, focused_component_,
               FocusEvent::kSYSTEM, NULL, focused_component_));
            focused_component_->setFocused(false);
         }
      }
   }
}

bool FUI::uiResize(const Dimension &size)
{
   setPosition(Point(0,0));

   Dimension constrainedSize(size);
   Dimension minSize(getMinimumSize());
   Dimension maxSize(getMaximumSize());
   constrainedSize.set(min(max(constrainedSize.width, minSize.width), maxSize.width),
      min(max(constrainedSize.height, minSize.height), maxSize.height));
   setSize(constrainedSize);

   return constrainedSize == size;
}

bool FUI::uiMouseMove(const Point &location)
{
   if (mouse_state_.getPosition() == location)
      return true;
   
   mouse_state_.setPosition(location);

   // reset hover timer
   hover_start_ticks_ = ticks_;

   _swapComponentsUnderMousePointers();
   cvec_t &comps = *components_under_mouse_,
          &old_comps = *components_under_mouse_old_,
          &temp = components_under_mouse_temp_;

   // get components under the mouse's new position and sort by z-index
   comps.clear();
   getComponentsAt(comps, location);
   std::stable_sort(comps.begin(), comps.end(), compareComponentsZIndex);

   // compare with components under old mouse position and
   // trigger events as needed
   if (!old_comps.empty())
   {
      if (comps.empty() || comps.back() != old_comps.back())
         old_comps.back()->fireMouseEvent(MouseEvent(
               MouseEvent::kMOUSE_LEAVE_DIRECT, old_comps.back(), location));

      temp.clear();
      // components that are no longer under the mouse 
      std::set_difference(old_comps.begin(), old_comps.end(),
                          comps.begin(), comps.end(),
                          std::back_inserter(temp), compareComponentsZIndex);
      for (cvec_iter_t it(temp.begin()); it != temp.end(); ++it)
      {
         (*it)->fireMouseEvent(MouseEvent(
               MouseEvent::kMOUSE_LEAVE, *it, location));

         _removeHoveredComponent(*it);
      }
   }

   if (!comps.empty())
   {
      temp.clear();
      // components that weren't, but now are under the mouse 
      std::set_difference(comps.begin(), comps.end(),
                          old_comps.begin(), old_comps.end(),
                          std::back_inserter(temp), compareComponentsZIndex);
      for (cvec_iter_t it(temp.begin()); it != temp.end(); ++it)
         (*it)->fireMouseEvent(MouseEvent(
               MouseEvent::kMOUSE_ENTER, *it, location));

      if (old_comps.empty() || comps.back() != old_comps.back())
         comps.back()->fireMouseEvent(MouseEvent(
               MouseEvent::kMOUSE_ENTER_DIRECT, comps.back(), location));
   }
   
   // mouse move events for components that are under the mouse
   bool retval(false);
   for (cvec_iter_t it(comps.begin()); it != comps.end(); ++it)
         retval = (*it)->fireMouseEvent(MouseEvent(
               MouseEvent::kMOUSE_MOVE, *it, location));

   return retval;
}

bool FUI::uiMouseButton(int button, bool is_down)
{
   FComponent *consuming_component(NULL);

   if (!components_under_mouse_->empty())
   {
      std::vector<FComponent*>::reverse_iterator rit(components_under_mouse_->rbegin());
      consuming_component = *rit;

      while (consuming_component && !(checkModalDescendant(consuming_component) &&
             consuming_component->fireMouseEvent(MouseEvent(
             is_down ? MouseEvent::kMOUSE_DOWN : MouseEvent::kMOUSE_UP,
             consuming_component, mouse_state_.getPosition(), button, 0, 0,
             is_down ? Point(-1, -1) : mouse_state_.downPosition(button),
             is_down ? NULL : mouse_state_.downComponent(button)))))
         consuming_component = (rit == components_under_mouse_->rend() ? NULL : *(--rit));

      if (consuming_component)
      {
         if (is_down && button == 1)
            setFocus(consuming_component, FocusEvent::kMOUSE);

         if (!is_down && consuming_component == mouse_state_.downComponent(button))
         {
            // click
            consuming_component->fireMouseEvent(MouseEvent(
                  MouseEvent::kMOUSE_CLICK, consuming_component,
                  mouse_state_.getPosition(), button, 0, 0,
                  mouse_state_.downPosition(button), mouse_state_.downComponent(button)));

            if (last_click_ticks_ > 0 && ticks_ - last_click_ticks_ <= max_double_click_interval_ &&
                last_click_component_ == consuming_component)
            {
               // double click
               consuming_component->fireMouseEvent(MouseEvent(
                     MouseEvent::kMOUSE_DOUBLE_CLICK, consuming_component,
                     mouse_state_.getPosition(), button, 0, 0,
                     mouse_state_.downPosition(button), mouse_state_.downComponent(button)));
               last_click_ticks_ = -1;
               last_click_component_ = NULL;
            }
            else
            {
               last_click_ticks_ = ticks_;
               last_click_component_ = consuming_component;
            }
         }
      }
      
   }

   if (is_down)
      mouse_state_.down(button, consuming_component);
   else
      mouse_state_.up(button);

   return consuming_component != NULL;
}

bool FUI::uiMouseWheel(int delta_z, int delta_w)
{
   // try focused component first
   if (focused_component_ && checkModalDescendant(focused_component_) &&
       focused_component_->fireMouseEvent(MouseEvent(
       MouseEvent::kMOUSE_WHEEL, focused_component_,
       mouse_state_.getPosition(), 0, delta_z, delta_w)))
   {
      return true;
   }

   FComponent *consuming_component(NULL);

   // then try components under mouse
   if (!components_under_mouse_->empty())
   {
      std::vector<FComponent*>::reverse_iterator rit(components_under_mouse_->rbegin());
      consuming_component = *rit;

      while (consuming_component && !(checkModalDescendant(consuming_component) &&
             consuming_component->fireMouseEvent(MouseEvent(
             MouseEvent::kMOUSE_WHEEL, consuming_component,
             mouse_state_.getPosition(),0, delta_z, delta_w))))
         consuming_component = (rit == components_under_mouse_->rend() ? NULL : *(--rit));
   }

   return consuming_component != NULL;
}

bool FUI::uiKeyState(int key, bool is_down)
{
   if (is_down)
      keyboard_state_.down(key);
   else
      keyboard_state_.up(key);

   // first try focused component
   if (focused_component_ && checkModalDescendant(focused_component_) &&
       focused_component_->fireKeyboardEvent(KeyboardEvent(
       is_down ? KeyboardEvent::kKEY_DOWN : KeyboardEvent::kKEY_UP,
       focused_component_, key, -1)))
   {
      return true;
   }

   FComponent *consuming_component(NULL);

   // then try components under mouse
   if (under_mouse_key_events_enabled_ && !components_under_mouse_->empty())
   {
      std::vector<FComponent*>::reverse_iterator rit(components_under_mouse_->rbegin());
      consuming_component = *rit;

      while (consuming_component && !(checkModalDescendant(consuming_component) &&
             consuming_component->fireKeyboardEvent(KeyboardEvent(
             is_down ? KeyboardEvent::kKEY_DOWN : KeyboardEvent::kKEY_UP,
             consuming_component, key, -1))))
         consuming_component = (rit == components_under_mouse_->rend() ? NULL : *(--rit));
   }

   return consuming_component != NULL;
}

bool FUI::uiCharacterEntry(int codepoint)
{
   // first try focused component
   if (focused_component_ && checkModalDescendant(focused_component_) &&
       focused_component_->fireKeyboardEvent(KeyboardEvent(
       KeyboardEvent::kCHARACTER_INPUT, focused_component_, -1, codepoint)))
   {
      return true;
   }

   FComponent *consuming_component(NULL);

   // then try components under mouse
   if (under_mouse_key_events_enabled_ && !components_under_mouse_->empty())
   {
      std::vector<FComponent*>::reverse_iterator rit(components_under_mouse_->rbegin());
      consuming_component = *rit;

      while (consuming_component && !(checkModalDescendant(consuming_component) &&
             consuming_component->fireKeyboardEvent(KeyboardEvent(
             KeyboardEvent::kCHARACTER_INPUT, consuming_component, -1, codepoint))))
         consuming_component = (rit == components_under_mouse_->rend() ? NULL : *(--rit));
   }

   return consuming_component != NULL;
}


// Rendering

void FUI::populateRenderTasks()
{
   if (render_tasks_valid_)
      return;

   render_tasks_.clear();
   getRenderTasks(render_tasks_);

   std::stable_sort(render_tasks_.begin(), render_tasks_.end());

   render_tasks_valid_ = true;
   makeDirty(getPosition(), getSize());
}

void FUI::uiDraw()
{
   layoutComponent();   // do layout if necessary
   populateRenderTasks();

   clip_top_left_ = dirty_top_left_;
   clip_bottom_right_ = dirty_bottom_right_;

   if (prepare_renderer_)
      prepare_renderer_->draw(this);

   setClip(clip_top_left_, clip_bottom_right_);

   for (std::vector<RenderTask>::iterator it(render_tasks_.begin()); it != render_tasks_.end(); ++it)
      it->renderer->draw(it->component);

   if (cleanup_renderer_)
      cleanup_renderer_->draw(this);

   dirty_top_left_.set(0.0f, 0.0f);
   dirty_bottom_right_.set(0.0f, 0.0f);
   dirty_ = false;
}

void FUI::makeDirty(const Point &absolute_position, const Dimension &size)
{
   if (size.width > 0 && size.height > 0)
   {
      const Point &p0 = absolute_position;
      Point p1(absolute_position.x + size.width, absolute_position.y + size.height);
      if (dirty_)
      {
         dirty_top_left_.setX(min(p0.x, dirty_top_left_.x));
         dirty_top_left_.setY(min(p0.y, dirty_top_left_.y));

         dirty_bottom_right_.setX(max(p1.x, dirty_bottom_right_.x));
         dirty_bottom_right_.setY(max(p1.y, dirty_bottom_right_.y));
      }
      else 
      {
         dirty_top_left_ = p0;
         dirty_bottom_right_ = p1;
      }
   }
}


// Simulation

void FUI::uiSimulate(int delta)
{
   ticks_ += delta;

   layoutComponent();
   populateRenderTasks();

   // trigger hover events if necessary
   if (hover_start_ticks_ >= 0 && ticks_ - hover_start_ticks_ > min_hover_delay_)
   {
      cvec_t &comps = *components_under_mouse_,
             &hovered = hovered_components_,
             &temp = components_under_mouse_temp_;

      // find components under the mouse which have not received
      // a hover event since the mouse entered it.
      temp.clear();
      std::set_difference(comps.begin(), comps.end(),
                          hovered.begin(), hovered.end(),
                          std::back_inserter(temp), compareComponentsZIndex);
      if (!temp.empty())
      {
         for (cvec_iter_t it(temp.begin()); it != temp.end(); ++it)
         {
            (*it)->fireMouseEvent(MouseEvent(
                  MouseEvent::kMOUSE_HOVER, *it, mouse_state_.getPosition()));

            hovered.push_back(*it);
         }
         // sort hovered components vector
         std::stable_sort(hovered.begin(), hovered.end(), compareComponentsZIndex);
      }

      // disable hover timer until next mouse move
      hover_start_ticks_ = -1;
   }

   // trigger simulate events if necessary
   if (last_simulate_ticks_ < 0 || ticks_ - last_simulate_ticks_ >= min_simulate_event_interval_)
   {
      fireSimulateEvent(SimulateEvent(
            SimulateEvent::kSIMULATE, this, delta, ticks_, ticks_per_second_));

      last_simulate_ticks_ = ticks_;
   }
}

void FUI::uiResetSimulation()
{
   ticks_ = 0;
   hover_start_ticks_ = -1;
   last_click_ticks_ = -1;
   last_click_component_ = NULL;

   fireSimulateEvent(SimulateEvent(
         SimulateEvent::kSIM_RESET, this, -1, ticks_, ticks_per_second_));
}

void FUI::uiResetSimulation(int ticks_per_sec, int min_simulate_event_interval)
{
   ticks_per_second_ = ticks_per_sec;
   min_simulate_event_interval_ = min_simulate_event_interval;
   uiResetSimulation();
}


// (De|Con)structors
FUI::FUI()
      : modal_component_(NULL),
        focused_component_(NULL),
        active_ui_(false),
        under_mouse_key_events_enabled_(true),
        components_under_mouse_(&components_under_mouse_1_),
        components_under_mouse_old_(&components_under_mouse_2_),
        last_click_component_(NULL),
        min_hover_delay_(600),
        max_double_click_interval_(350),
        hover_start_ticks_(-1),
        last_click_ticks_(-1),
        prepare_renderer_(&default_prepare_renderer_),
        cleanup_renderer_(&default_cleanup_renderer_),
        render_tasks_valid_(false),
        dirty_(true),
        ticks_per_second_(1000),
        min_simulate_event_interval_(10),
        ticks_(0),
        last_simulate_ticks_(0),
        clipboard_(default_clipboard_),
        font_provider_(default_font_provider_)
{
   default_focus_manager_.setFocusRoot(this);
   ui_ = this;
   destroyChildrenOnDeath();
   setFocusManager(&default_focus_manager_);
}

FUI::FUI(const FUI_cfg &cfg)
      : FComponent(cfg),
        modal_component_(NULL),
        focused_component_(NULL),
        active_ui_(false),
        under_mouse_key_events_enabled_(cfg.getUnderMouseKeyEventsEnabled()),
        components_under_mouse_(&components_under_mouse_1_),
        components_under_mouse_old_(&components_under_mouse_2_),
        last_click_component_(NULL),
        min_hover_delay_(cfg.getMinimumHoverDelay()),
        max_double_click_interval_(cfg.getMaximumDoubleClickInterval()),
        hover_start_ticks_(-1),
        last_click_ticks_(-1),
        prepare_renderer_(cfg.getUseDefaultPrepareRenderer() ? &default_prepare_renderer_ : cfg.getPrepareRenderer()),
        cleanup_renderer_(cfg.getUseDefaultCleanupRenderer() ? &default_cleanup_renderer_ : cfg.getCleanupRenderer()),
        render_tasks_valid_(false),
        dirty_(true),
        ticks_per_second_(cfg.getTicksPerSecond()),
        min_simulate_event_interval_(cfg.getMinimumSimulateEventInterval()),
        ticks_(0),
        last_simulate_ticks_(0),
        clipboard_(cfg.getClipboard() == NULL ? default_clipboard_ : *(cfg.getClipboard())),
        font_provider_(cfg.getFontProvider() == NULL ? default_font_provider_ : *(cfg.getFontProvider()))
{
   default_focus_manager_.setFocusRoot(this);
   ui_ = this;
   destroyChildrenOnDeath();
   FocusManagerInterface *fm = cfg.getFocusMgr();
   setFocusManager(fm ? fm : &default_focus_manager_);
}

FUI::~FUI() {}

FGUI_END