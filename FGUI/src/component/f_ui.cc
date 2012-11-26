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

#include "platform/platform.h"

#include <iterator>
#include <sstream>

FGUI_BEGIN

typedef std::vector<FComponent*> cvec_t;
typedef std::vector<FComponent*>::iterator cvec_iter_t;
typedef std::vector<FComponent*>::const_iterator cvec_citer_t;

// static members
const UID FUI::prepare_renderer_uid_;
const UID FUI::cleanup_renderer_uid_;

// helper functions
namespace detail {

inline bool zIndexLess(FComponent *a, FComponent *b)
{
   return a->getZIndex() < b->getZIndex();
}

cvec_iter_t scvecFind(cvec_t &vec, FComponent *comp)
{
   cvec_iter_t end(vec.end());
   cvec_iter_t it(vec.begin());
   while (it != end)
   {
      if (*it == comp)
         return it;
      
      if (zIndexLess(comp, *it))
         break;

      ++it;
   }

   return end;
}

bool scvecDiff(FUI *that, cvec_t &va, cvec_t &vb, void (*callback)(FUI *, FComponent *))
{
   // pass components in va which are not in vb to callback function

   cvec_iter_t aend(va.end());
   cvec_iter_t bend(vb.end());

   cvec_iter_t sbit(vb.begin());

   bool ret_val(false);

   // for each component in va...
   for (cvec_iter_t ait(va.begin()); ait != aend; ++ait)
   {
      FComponent* comp = *ait;

      if (sbit != bend && *sbit == comp)
      {
         ++sbit;
         continue;
      }

      bool call(true);
      cvec_iter_t bit(sbit);
      while (bit != bend)
      {
         if (*bit == comp)
         {
            call = false;
            break;
         }

         if (zIndexLess(comp, *bit))
            break;

         ++bit;
      }
      
      if (call)
      {
         callback(that, comp);
         ret_val = true;
      }
   }

   return ret_val;
}

void uimmFireLeave(FUI *that, FComponent *comp)
{
   comp->fireMouseEvent(MouseEvent(
         MouseEvent::kMOUSE_LEAVE, comp, that->mouse_state_.getPosition()));

   // remove from hovered components vector
   cvec_iter_t it(scvecFind(that->hovered_components_, comp));
   if (it != that->hovered_components_.end())
      that->hovered_components_.erase(it);
}

void uimmFireEnter(FUI *that, FComponent *comp)
{
   comp->fireMouseEvent(MouseEvent(
         MouseEvent::kMOUSE_ENTER, comp, that->mouse_state_.getPosition()));
}

void uisimHover(FUI *that, FComponent *comp)
{
   if (comp == that->components_under_mouse_->back())
      comp->fireMouseEvent(MouseEvent(
            MouseEvent::kMOUSE_HOVER_DIRECT, comp, that->mouse_state_.getPosition()));

   comp->fireMouseEvent(MouseEvent(
         MouseEvent::kMOUSE_HOVER, comp, that->mouse_state_.getPosition()));

   that->hovered_components_.push_back(comp);
}

} // namespace detail

// Modal Components
void FUI::registerModal(FComponent *component)
{
   cvec_iter_t it(detail::scvecFind(modal_components_, component));
   if (it != modal_components_.end())
   {
      modal_components_.push_back(component);
      std::stable_sort(modal_components_.begin(), modal_components_.end(), detail::zIndexLess);

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
   cvec_iter_t it(detail::scvecFind(modal_components_, component));
   if (it != modal_components_.end())
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

void FUI::componentRemoved(FComponent *component)
{
   if (!component || component == this)
      return;

   // remove from modal list
   unregisterModal(component);

   // remove from hovered components vector
   cvec_iter_t it(detail::scvecFind(hovered_components_, component));
   if (it != hovered_components_.end())
      hovered_components_.erase(it);

   // remove from under mouse vectors
   it = detail::scvecFind(*components_under_mouse_, component);
   if (it != components_under_mouse_->end())
      components_under_mouse_->erase(it);

   it = detail::scvecFind(*components_under_mouse_old_, component);
   if (it != components_under_mouse_old_->end())
      components_under_mouse_old_->erase(it);

   // remove from last click component
   if (last_click_component_ == component)
   {
      last_click_component_ = NULL;
      last_click_ticks_ = -1;
   }

   // remove from mouse state
   mouse_state_.removeDownComponent(component);

   // remove from focused component
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

   cvec_t *swap_temp(components_under_mouse_);
   components_under_mouse_ = components_under_mouse_old_;
   components_under_mouse_old_ = swap_temp;

   cvec_t &comps = *components_under_mouse_,
          &old_comps = *components_under_mouse_old_;

   // get components under the mouse's new position and sort by z-index
   comps.clear();
   getComponentsAt(comps, location);
   std::stable_sort(comps.begin(), comps.end(), detail::zIndexLess);

   // compare with components under old mouse position and
   // trigger events as needed
   if (!old_comps.empty())
   {
      if (comps.empty() || comps.back() != old_comps.back())
         old_comps.back()->fireMouseEvent(MouseEvent(
               MouseEvent::kMOUSE_LEAVE_DIRECT, old_comps.back(), location));

      // components that are no longer under the mouse 
      detail::scvecDiff(this, old_comps, comps, detail::uimmFireLeave);
   }

   if (!comps.empty())
   {
      // components that weren't, but now are under the mouse
      detail::scvecDiff(this, comps, old_comps, detail::uimmFireEnter);

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

   FComponent *down_component = is_down ? NULL : mouse_state_.downComponent(button);

   if (down_component)
      down_component->fireMouseEvent(MouseEvent(
            MouseEvent::kMOUSE_UP, down_component, mouse_state_.getPosition(), button, 0, 0,
            mouse_state_.downPosition(button), down_component));

   if (!components_under_mouse_->empty())
   {
      std::vector<FComponent*>::reverse_iterator rit(components_under_mouse_->rbegin());
      consuming_component = *rit;
      ++rit;

      while (consuming_component && consuming_component != down_component &&
             !(checkModalDescendant(consuming_component) &&
             consuming_component->fireMouseEvent(MouseEvent(
             is_down ? MouseEvent::kMOUSE_DOWN : MouseEvent::kMOUSE_UP,
             consuming_component, mouse_state_.getPosition(), button, 0, 0,
             is_down ? Point(-1, -1) : mouse_state_.downPosition(button),
             down_component))))
      {
         if (rit == components_under_mouse_->rend())
            consuming_component = NULL;
         else
         {
            consuming_component = *rit;
            ++rit;
         }
      }

      if (consuming_component)
      {
         if (is_down && button == 1)
            setFocus(consuming_component, FocusEvent::kMOUSE);

         if (consuming_component == down_component)
         {
            // click
            consuming_component->fireMouseEvent(MouseEvent(
                  MouseEvent::kMOUSE_CLICK, consuming_component,
                  mouse_state_.getPosition(), button, 0, 0,
                  mouse_state_.downPosition(button), down_component));

            if (last_click_ticks_ > 0 && ticks_ - last_click_ticks_ <= max_double_click_interval_ &&
                last_click_component_ == consuming_component)
            {
               // double click
               consuming_component->fireMouseEvent(MouseEvent(
                     MouseEvent::kMOUSE_DOUBLE_CLICK, consuming_component,
                     mouse_state_.getPosition(), button, 0, 0,
                     mouse_state_.downPosition(button), down_component));
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
      ++rit;

      while (consuming_component && !(checkModalDescendant(consuming_component) &&
             consuming_component->fireMouseEvent(MouseEvent(
             MouseEvent::kMOUSE_WHEEL, consuming_component,
             mouse_state_.getPosition(),0, delta_z, delta_w))))
      {
         if (rit == components_under_mouse_->rend())
            consuming_component = NULL;
         else
         {
            consuming_component = *rit;
            ++rit;
         }
      }
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
      ++rit;

      while (consuming_component && !(checkModalDescendant(consuming_component) &&
             consuming_component->fireKeyboardEvent(KeyboardEvent(
             is_down ? KeyboardEvent::kKEY_DOWN : KeyboardEvent::kKEY_UP,
             consuming_component, key, -1))))
      {
         if (rit == components_under_mouse_->rend())
            consuming_component = NULL;
         else
         {
            consuming_component = *rit;
            ++rit;
         }
      }
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
      ++rit;

      while (consuming_component && !(checkModalDescendant(consuming_component) &&
             consuming_component->fireKeyboardEvent(KeyboardEvent(
             KeyboardEvent::kCHARACTER_INPUT, consuming_component, -1, codepoint))))
      {
         if (rit == components_under_mouse_->rend())
            consuming_component = NULL;
         else
         {
            consuming_component = *rit;
            ++rit;
         }
      }
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
   makeDirty(absolute_);
}

void FUI::uiDraw()
{
   layoutComponent();   // do layout if necessary
   populateRenderTasks();

   clip_ = dirty_;

   if (prepare_renderer_)
      prepare_renderer_->draw(this);

   setClip(clip_);

   for (std::vector<RenderTask>::iterator it(render_tasks_.begin()); it != render_tasks_.end(); ++it)
      it->renderer->draw(it->component);

   if (cleanup_renderer_)
      cleanup_renderer_->draw(this);

   dirty_.set(0.0f, 0.0f, 0.0f, 0.0f);
   dirty_set_ = false;
}

void FUI::makeDirty(const Rect &absolute_rect)
{
   dirty_.expand(absolute_rect);
   dirty_set_ = true;
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
             &hovered = hovered_components_;

      // find components under the mouse which have not received
      // a hover event since the mouse entered it and send them
      // hover events
      cvec_temp_.assign(hovered.begin(), hovered.end());
      if (detail::scvecDiff(this, comps, cvec_temp_, detail::uisimHover))
         std::stable_sort(hovered.begin(), hovered.end(), detail::zIndexLess);

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
        active_ui_(true),
        under_mouse_key_events_enabled_(true),
        components_under_mouse_(&components_under_mouse_1_),
        components_under_mouse_old_(&components_under_mouse_2_),
        last_click_component_(NULL),
        min_hover_delay_(700),
        max_double_click_interval_(350),
        hover_start_ticks_(-1),
        last_click_ticks_(-1),
        prepare_renderer_(platform_.checkoutRenderer(prepare_renderer_uid_)),
        cleanup_renderer_(platform_.checkoutRenderer(cleanup_renderer_uid_)),
        render_tasks_valid_(false),
        dirty_set_(true),
        ticks_per_second_(1000),
        min_simulate_event_interval_(10),
        ticks_(0),
        last_simulate_ticks_(0)
{
   default_focus_manager_.setFocusRoot(this);
   ui_ = this;
   destroyChildrenOnDeath();
   setFocusManager(&default_focus_manager_);
}

FUI::FUI(PlatformInterface &platform)
      : FComponent(platform),
        modal_component_(NULL),
        focused_component_(NULL),
        active_ui_(true),
        under_mouse_key_events_enabled_(true),
        components_under_mouse_(&components_under_mouse_1_),
        components_under_mouse_old_(&components_under_mouse_2_),
        last_click_component_(NULL),
        min_hover_delay_(700),
        max_double_click_interval_(350),
        hover_start_ticks_(-1),
        last_click_ticks_(-1),
        prepare_renderer_(platform_.checkoutRenderer(prepare_renderer_uid_)),
        cleanup_renderer_(platform_.checkoutRenderer(cleanup_renderer_uid_)),
        render_tasks_valid_(false),
        dirty_set_(true),
        ticks_per_second_(1000),
        min_simulate_event_interval_(10),
        ticks_(0),
        last_simulate_ticks_(0)
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
        active_ui_(true),
        under_mouse_key_events_enabled_(cfg.getUnderMouseKeyEventsEnabled()),
        components_under_mouse_(&components_under_mouse_1_),
        components_under_mouse_old_(&components_under_mouse_2_),
        last_click_component_(NULL),
        min_hover_delay_(cfg.getMinimumHoverDelay()),
        max_double_click_interval_(cfg.getMaximumDoubleClickInterval()),
        hover_start_ticks_(-1),
        last_click_ticks_(-1),
        prepare_renderer_(platform_.checkoutRenderer(prepare_renderer_uid_)),
        cleanup_renderer_(platform_.checkoutRenderer(cleanup_renderer_uid_)),
        render_tasks_valid_(false),
        dirty_set_(true),
        ticks_per_second_(cfg.getTicksPerSecond()),
        min_simulate_event_interval_(cfg.getMinimumSimulateEventInterval()),
        ticks_(0),
        last_simulate_ticks_(0)
{
   default_focus_manager_.setFocusRoot(this);
   ui_ = this;
   destroyChildrenOnDeath();
   FocusManagerInterface *fm = cfg.getFocusMgr();
   setFocusManager(fm ? fm : &default_focus_manager_);
}

FUI::FUI(PlatformInterface &platform, const FUI_cfg &cfg)
      : FComponent(platform, cfg),
        modal_component_(NULL),
        focused_component_(NULL),
        active_ui_(true),
        under_mouse_key_events_enabled_(cfg.getUnderMouseKeyEventsEnabled()),
        components_under_mouse_(&components_under_mouse_1_),
        components_under_mouse_old_(&components_under_mouse_2_),
        last_click_component_(NULL),
        min_hover_delay_(cfg.getMinimumHoverDelay()),
        max_double_click_interval_(cfg.getMaximumDoubleClickInterval()),
        hover_start_ticks_(-1),
        last_click_ticks_(-1),
        prepare_renderer_(platform_.checkoutRenderer(prepare_renderer_uid_)),
        cleanup_renderer_(platform_.checkoutRenderer(cleanup_renderer_uid_)),
        render_tasks_valid_(false),
        dirty_set_(true),
        ticks_per_second_(cfg.getTicksPerSecond()),
        min_simulate_event_interval_(cfg.getMinimumSimulateEventInterval()),
        ticks_(0),
        last_simulate_ticks_(0)
{
   default_focus_manager_.setFocusRoot(this);
   ui_ = this;
   destroyChildrenOnDeath();
   FocusManagerInterface *fm = cfg.getFocusMgr();
   setFocusManager(fm ? fm : &default_focus_manager_);
}

FUI::~FUI()
{
   platform_.returnRenderer(prepare_renderer_uid_, prepare_renderer_);
   platform_.returnRenderer(cleanup_renderer_uid_, cleanup_renderer_);
}

FGUI_END