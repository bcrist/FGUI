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
// File: component/f_component.cc

#include "component/f_component.h"

#include <sstream>
#include <algorithm>

#include "component/f_ui.h"

FGUI_BEGIN

typedef std::vector<FComponent*>::iterator cvec_iter_t;


// Events

// returns false if the focus operation was cancelled
bool FComponent::fireFocusEvent(FocusEvent &evt)
{
   std::list<FocusListenerInterface*>::iterator it = focus_listeners_.begin();
   std::list<FocusListenerInterface*>::iterator end = focus_listeners_.end();

   switch(evt.type)
   {
      case FocusEvent::kFOCUS_IN: 
         while (!evt.isCancelled() && it != end) 
         { 
            (*it)->onFocusIn(evt); 
            ++it; 
         } 
         break;
      case FocusEvent::kFOCUS_OUT: 
         while (!evt.isCancelled() && it != end) 
         { 
            (*it)->onFocusOut(evt); 
            ++it;
         } 
         break;
      default:  
         return false;
   }

   if (parent_ != NULL && !evt.isPropagationStopped())
      return parent_->fireFocusEvent(evt);

   return !evt.isCancelled();
}

// returns true if the component consumed the event
bool FComponent::fireKeyboardEvent(KeyboardEvent &evt)
{
   std::list<KeyboardListenerInterface*>::iterator it = keyboard_listeners_.begin();
   std::list<KeyboardListenerInterface*>::iterator end = keyboard_listeners_.end();

   switch(evt.type)
   {
      case KeyboardEvent::kKEY_DOWN:  
         while (!evt.isCancelled() && it != end) 
         {
            (*it)->onKeyDown(evt);
            ++it;
         }
         break;

      case KeyboardEvent::kKEY_UP:     
         while (!evt.isCancelled() && it != end)
         { 
            (*it)->onKeyUp(evt);
            ++it;
         }
         break;

      case KeyboardEvent::kCHARACTER_INPUT:
         while (!evt.isCancelled() && it != end)
         { 
            (*it)->onCharacterInput(evt); 
            ++it;
         }
         break;

      default:  
         return false;
   }

   if (parent_ != NULL && !evt.isPropagationStopped())
      return parent_->fireKeyboardEvent(evt);

   return evt.isConsumed();
}

// returns true if the component consumed the event
bool FComponent::fireMouseEvent(MouseEvent &evt)
{
   std::list<MouseListenerInterface*>::iterator it = mouse_listeners_.begin();
   std::list<MouseListenerInterface*>::iterator end = mouse_listeners_.end();

   switch(evt.type)
   {
      case MouseEvent::kMOUSE_MOVE:
         while (!evt.isCancelled() && it != end)
         {
            (*it)->onMouseMove(evt);
            ++it;
         }
         break;

      case MouseEvent::kMOUSE_ENTER:
         while (!evt.isCancelled() && it != end)
         {
            (*it)->onMouseEnter(evt);
            ++it;
         }
         break;

      case MouseEvent::kMOUSE_ENTER_DIRECT:
         while (!evt.isCancelled() && it != end)
         {
            (*it)->onMouseEnterDirect(evt);
            ++it;
         }
         break;

      case MouseEvent::kMOUSE_LEAVE:
         while (!evt.isCancelled() && it != end)
         {
            (*it)->onMouseLeave(evt);
            ++it;
         }
         break;

      case MouseEvent::kMOUSE_LEAVE_DIRECT:
         while (!evt.isCancelled() && it != end)
         {
            (*it)->onMouseLeaveDirect(evt);
            ++it;
         }
         break;

      case MouseEvent::kMOUSE_HOVER:
         while (!evt.isCancelled() && it != end)
         {
            (*it)->onMouseHover(evt);
            ++it;
         }
         break;

      case MouseEvent::kMOUSE_HOVER_DIRECT:
         while (!evt.isCancelled() && it != end)
         {
            (*it)->onMouseHoverDirect(evt);
            ++it;
         }
         break;

      case MouseEvent::kMOUSE_WHEEL:
         while (!evt.isCancelled() && it != end)
         {
            (*it)->onMouseWheel(evt);
            ++it;
         }
         break;
      
      case MouseEvent::kMOUSE_DOWN:
         while (!evt.isCancelled() && it != end)
         {
            (*it)->onMouseDown(evt); 
            ++it; 
         }
         break;

      case MouseEvent::kMOUSE_UP:
         while (!evt.isCancelled() && it != end)
         { 
            (*it)->onMouseUp(evt); 
            ++it; 
         } 
         break;

      case MouseEvent::kMOUSE_CLICK:
         while (!evt.isCancelled() && it != end)
         { 
            (*it)->onMouseClick(evt); 
            ++it; 
         }
         break;

      case MouseEvent::kMOUSE_DOUBLE_CLICK:
         while (!evt.isCancelled() && it != end)
         { 
            (*it)->onMouseDoubleClick(evt); 
            ++it; 
         } 
         break;

      default:   
         return false;
   }

   if (parent_ != NULL && !evt.isPropagationStopped())
      return parent_->fireMouseEvent(evt);

   return evt.isConsumed();
}

// returns false if propagation was stopped at this element
// (may return true if a child component cancels)
bool FComponent::fireSimulateEvent(SimulateEvent &evt)
{
   std::list<SimulationListenerInterface*>::iterator it = simulation_listeners_.begin();
   std::list<SimulationListenerInterface*>::iterator end = simulation_listeners_.end();

   switch(evt.type)
   {
      case SimulateEvent::kSIMULATE:  
         while (!evt.isCancelled() && it != end) 
         { 
            (*it)->onSimulate(evt); 
            ++it;
         }
         break;
      case SimulateEvent::kSIM_RESET:   
         while (!evt.isCancelled() && it != end) 
         { 
            (*it)->onResetSimulation(evt); 
            ++it; 
         } 
         break;
      default:   
         return false;
   }

   // unlike most events, simulation events propagate down, not up
   if (!evt.isPropagationStopped())
   {
      cvec_iter_t child_it = children_.begin(),
                  child_end = children_.end();
      while (child_it != child_end)
      {
         (*child_it)->fireSimulateEvent(SimulateEvent(
            evt.type, evt.target, evt.delta, evt.ticks, evt.ticksPerSecond));
         ++child_it;
      }

      return true;
   }
   return false;
}


// Contents
bool FComponent::isDescendantOf(const FComponent *ancestor) const
{
   return ancestor && (parent_ == ancestor || parent_->isDescendantOf(ancestor));
}

bool FComponent::checkRemoveComponent(FComponent *component,
                                      bool destroy,
                                      std::vector<FComponent*>::iterator &it)
{
   it = std::find(children_.begin(), children_.end(), component);

   if (it == children_.end())
      return true;   // if the component isn't a child of this component removing it will always be allowed

   if (contents_locked_)
      return false;

   return true;
}

void FComponent::uncheckedRemoveComponent(FComponent *component,
                                          bool destroy,
                                          std::vector<FComponent*>::iterator &it)
{
   if (it != children_.end())
   {
      if (component->ui_)
      {
         if (component->modal_ && component->visible_)
            component->ui_->unregisterModal(component);

         component->ui_->componentRemoved(component);
      }

      children_.erase(it);
      
      if (destroy)
         delete component;
      else
      {
         component->parent_ = NULL;
         component->ui_ = NULL;
      }
      invalidateLayout();
      if (ui_)
         ui_->invalidateRenderTasks();
   }
}

bool FComponent::addComponent(FComponent *c)
{
   if (c == NULL)
      return false;   // null components are forbidden

   if (c->parent_ == this)
      return true;   // if its already a child of this component, we've succeeded

   if (contents_locked_)
      return false;   // if changes aren't allowed right now

   if (&platform_ != &c->platform_)
      return false;  // if the component was created using a different PlatformInterface

   if (c->parent_)
      if (!c->parent_->removeComponent(c, false))
         return false;   // if the component can't be removed from its previous parent

   // add component to this component
   children_.push_back(c);
   c->parent_ = this;
   c->absolute_.position = clientToAbsolute(c->position_);
   c->ui_ = ui_;
   if (c->logger_ == NULL)
      c->logger_ = logger_;

   if (ui_)
   {
      if (c->modal_ && c->visible_)
         ui_->registerModal(c);

      if (c->focused_)
         ui_->setFocus(c);

      ui_->invalidateRenderTasks();
   }
   invalidateLayout();
   return true;
}

bool FComponent::removeComponent(FComponent *c, bool destroyComponent)
{
   std::vector<FComponent*>::iterator it;
   if (checkRemoveComponent(c, destroyComponent, it))
   {
      uncheckedRemoveComponent(c, destroyComponent, it);
      return true;
   }
   return false;
}

int FComponent::getComponentIndex(const FComponent *component) const
{
   if (component == NULL)
      return -1;

   std::vector<FComponent*>::const_iterator it(children_.begin());
   std::vector<FComponent*>::const_iterator end(children_.end());
   int index = 0;
   while (it != end)
   {
      if (*it == component)
         return index;

      ++it;
      ++index;
   }

   return -1;
}

// Layout
void FComponent::setPosition(const Point &newPosition)
{
   if (position_ != newPosition)
   {
      makeDirty(); // the old position is dirty
      position_ = newPosition;
      invalidateLayout(); // the new position is made dirty when laid out
   }
}
void FComponent::setSize(const Dimension &size)
{
   if (absolute_.size != size)
   {
      absolute_.size = size;
      invalidateLayout();
   }
}

void FComponent::setMinimumSize(const Dimension &size)
{
   if (min_size_ != size)
   {
      min_size_ = size;
      invalidateLayout();
   }
}
void FComponent::setMinimumWidth(float width)
{
   if (width != min_size_.width)
   {
      min_size_.setWidth(width);
      invalidateLayout();
   }
}
void FComponent::setMinimumHeight(float height)
{
   if (height != min_size_.height)
   {
      min_size_.setHeight(height);
      invalidateLayout();
   }
}

void FComponent::setPreferredSize(const Dimension &size)
{
   if (pref_size_ != size)
   {
      pref_size_ = size;
      invalidateLayout();
   }
}
void FComponent::setPreferredWidth(float width)
{
   if (width != pref_size_.width)
   {
      pref_size_.setWidth(width);
      invalidateLayout();
   }
}
void FComponent::setPreferredHeight(float height)
{
   if (height != pref_size_.height)
   {
      pref_size_.setHeight(height);
      invalidateLayout();
   }
}

void FComponent::setMaximumSize(const Dimension &size)
{
   if (max_size_ != size)
   {
      max_size_ = size;
      invalidateLayout();
   }
}
void FComponent::setMaximumWidth(float width)
{
   if (width != max_size_.width)
   {
      max_size_.setWidth(width);
      invalidateLayout();
   }
}
void FComponent::setMaximumHeight(float height)
{
   if (height != max_size_.height)
   {
      max_size_.setHeight(height);
      invalidateLayout();
   }
}
   
void FComponent::invalidateLayout()
{
   if (valid_layout_)
   {
      valid_layout_ = false;
      if (parent_)
         parent_->invalidateLayout();
   }
}

void FComponent::layoutComponent()
{
   if (!valid_layout_)
   {
      if (layout_mgr_)
         // layout manager is responsible for making sure children are laid out
         layout_mgr_->layoutComponent(this);
      else
         for (cvec_iter_t it(children_.begin()); it != children_.end(); ++it)
            (*it)->layoutComponent();

      absolute_.position = parent_ == NULL ? position_ : parent_->clientToAbsolute(position_);

      valid_layout_ = true;
      makeDirty();
   }
}


// Rendering
void FComponent::setVisible(bool visible)
{
   if (visible_ != visible)
   {
      visible_ = visible;
      if (ui_)
      {
         if (modal_)
         {
            if (visible_)
               ui_->registerModal(this);
            else
               ui_->unregisterModal(this);
         }
         ui_->invalidateRenderTasks();
      }
   }
}

void FComponent::setZIndex(int z_index)
{
   if (z_index_ != z_index)
   {
      z_index_ = z_index;
      if (ui_)
         ui_->invalidateRenderTasks();
   }
}

void FComponent::setRenderer(RendererInterface *renderer)
{
   if (renderer_ != renderer)
   {
      renderer_ = renderer;
      if (ui_)
         ui_->invalidateRenderTasks();
   }
}

void FComponent::makeDirty()
{
   if (ui_)
      ui_->makeDirty(absolute_);
}

void FComponent::getRenderTasks(std::vector<RenderTask> &tasks)
{
   if (visible_)
   {
      if (renderer_)
         tasks.push_back(RenderTask(this, renderer_));

      for(cvec_iter_t it(children_.begin()); it != children_.end(); ++it)
         (*it)->getRenderTasks(tasks);
   }
}

void FComponent::setClip(const Rect &clip)
{
   clip_ = clip;

   for(cvec_iter_t it(children_.begin()); it != children_.end(); ++it)
      (*it)->setClip(clip);
}


// Coordinate Processing

Point FComponent::clientToAbsolute(const Point &client_coord) const
{
   return Point(absolute_.position.x + client_coord.x, absolute_.position.y + client_coord.y);
}

Point FComponent::absoluteToClient(const Point &absolute_coord) const
{
   return Point(absolute_coord.x - absolute_.position.x, absolute_coord.y - absolute_.position.y);
}

void FComponent::getComponentsAt(std::vector<FComponent*> &components, const Point &absolute_coord)
{
   if (visible_)
   {
      if (checkPointOverComponent(absolute_coord))
         components.push_back(this);

      for (cvec_iter_t it(children_.begin()); it != children_.end(); ++it)
      {
         FComponent &child = **it;
         child.getComponentsAt(components, absolute_coord);
      }
   }
}

bool FComponent::checkPointOverComponent(const Point &absolute_coord) const
{
   if (renderer_)
      return renderer_->checkPointOverComponent(this, absolute_coord);

   return checkPointInBounds(absolute_coord);
}

bool FComponent::checkPointInBounds(const Point &absolute_coord) const
{
   return (absolute_coord.x >= absolute_.getLeft() &&
           absolute_coord.x < absolute_.getRight() && 
           absolute_coord.y >= absolute_.getTop() &&
           absolute_coord.y < absolute_.getBottom());
}


// Focus Management

void FComponent::setFocusable(bool focusable)
{
   if (focusable_ != focusable)
   {
      focusable_ = focusable;
      if (!focusable_)
         blur();
   }
}

void FComponent::setModal(bool modal)
{
   if (modal_ != modal)
   {
      modal_ = modal;

      if (ui_ && visible_)
      {
         if (modal_)
            ui_->registerModal(this);
         else
            ui_->unregisterModal(this);
      }
   }
}

bool FComponent::requestFocus()
{
   if (focused_)
      return true;

   if (!focusable_)
      return false;

   if (!ui_)
      return false;

   return ui_->setFocus(this);
}

void FComponent::blur()
{
   if (focused_)
   {
      if (ui_)
      {
         ui_->focusNext();
         if (focused_)
            ui_->setFocus(NULL);
      }
      else
      {
         focused_ = false;
         makeDirty();
      }
   }
}
   
void FComponent::setFocused(bool focused)
{
   if (focusable_ && focused_ != focused)
   {
      focused_ = focused;
      if (parent_)
         parent_->setChildFocused(focused);

      makeDirty();
   }
}

void FComponent::setChildFocused(bool focused)
{
   if (child_focused_ != focused)
   {
      child_focused_ = focused;
      if (parent_)
         parent_->setChildFocused(focused);
   }
}

FocusManagerInterface *FComponent::getFocusManager() const
{
   if (focus_mgr_)
      return focus_mgr_;

   if (parent_)
      return parent_->getFocusManager();

   return NULL;
}


// Logging & Debugging
void FComponent::log(const char *txt)
{
   if (logger_ == NULL)
      return;
   
   std::ostringstream oss;
   printComponentIdentifier(oss);
   oss << ": " << txt << std::endl;
   logger_->log(oss.str().c_str());
}

void FComponent::printDebug(std::ostream &os) const
{
   os << "+- ";
   printComponentIdentifier(os);
   os << "\n| rel:  " << position_ << " abs: " << absolute_;
   if (!valid_layout_)
      os << " LAYOUT INVALID!";

   os << "\n| min:  " << min_size_;
   os << "\n| pref: " << pref_size_;
   os << "\n| max:  " << max_size_;
   os << "\n| layoutmgr: " << layout_mgr_;

   os << "\n|\n| visible:  " << (visible_ ? "yes" : "no");
   os << "\n| z-index:  " << z_index_;
   os << "\n| clip:     " << clip_;
   os << "\n| renderer: " << renderer_;

   os << "\n|\n| modal:     " << (modal_ ? "yes" : "no");
   if (focusable_)
      os << "\n| focusable: " << (focused_ ? "focused" : "not focused");
   if (child_focused_)
      os << "\n| descendant focused";
   os << "\n| focusmgr: " << focus_mgr_ << " (" << getFocusManager() << ")";

   os << "\n|\n| focus listeners:      " << focus_listeners_.size();
   os << "\n| keyboard listeners:   " << keyboard_listeners_.size();
   os << "\n| mouse listeners:      " << mouse_listeners_.size();
   os << "\n| simulation listeners: " << simulation_listeners_.size();

   os << "\n|\n| platform: " << &platform_;
   os << "\n| ui:       " << ui_;
   os << "\n| parent:   " << parent_;
   if (contents_locked_)
      os << "\n| contents locked.";
   if (destroy_children_)
      os << "\n| children destroyed on destruction.";

   os << "\n| children: " << children_.size();

   for (std::vector<FComponent*>::const_iterator it(children_.begin()); it != children_.end(); ++it)
   {
      os << "\n|    ";
      (*it)->printComponentIdentifier(os);
   }

   os << "\n\n";

}

void FComponent::printDebugRecursive(std::ostream &os) const
{
   printDebug(os);

   for (std::vector<FComponent*>::const_iterator it(children_.begin()); it != children_.end(); ++it)
      (*it)->printDebugRecursive(os);
}

void FComponent::logDebug() const
{
   std::ostringstream oss;
   printDebug(oss);
   logger_->log(oss.str().c_str());
}

void FComponent::logDebugRecursive() const
{
   logDebug();

   for (std::vector<FComponent*>::const_iterator it(children_.begin()); it != children_.end(); ++it)
      (*it)->logDebugRecursive();
}


// (De|Con)structors
FComponent::FComponent()
      : platform_(Platform::get()),

        ui_(NULL),
        parent_(NULL),

        contents_locked_(false),
        destroy_children_(false),

        layout_mgr_(NULL),
        valid_layout_(false),

        visible_(true),
        z_index_(0),
        renderer_(NULL),
      
        focused_(false),
        child_focused_(false),
        modal_(false),
        focusable_(false),
        focus_mgr_(NULL),

        logger_(platform_.checkoutLogger())
{}

FComponent::FComponent(PlatformInterface &platform)
      : platform_(platform),

        ui_(NULL),
        parent_(NULL),

        contents_locked_(false),
        destroy_children_(false),

        layout_mgr_(NULL),
        valid_layout_(false),

        visible_(true),
        z_index_(0),
        renderer_(NULL),
      
        focused_(false),
        child_focused_(false),
        modal_(false),
        focusable_(false),
        focus_mgr_(NULL),

        logger_(platform_.checkoutLogger())
{}

FComponent::FComponent(const FComponent_cfg &cfg)
      : platform_(Platform::get()),
      
        ui_(NULL),
        parent_(NULL),
        
        contents_locked_(cfg.getContentsLocked()),
        destroy_children_(cfg.getDestroyChildren()),

        layout_mgr_(cfg.getLayoutMgr()),
        valid_layout_(false),

        min_size_(cfg.getMinimumSize()),
        pref_size_(cfg.getPreferredSize()),
        max_size_(cfg.getMaximumSize()),

        position_(cfg.getPosition()),

        visible_(cfg.getVisible()),
        z_index_(cfg.getZIndex()),
        renderer_(cfg.getRenderer()),
        
        focused_(false),
        child_focused_(false),
        modal_(cfg.getModal()),
        focusable_(cfg.getFocusable()),
        focus_mgr_(cfg.getFocusMgr()),

        logger_(platform_.checkoutLogger())
{
   absolute_.position = parent_ == NULL ? position_ : parent_->clientToAbsolute(position_);
   absolute_.size = cfg.getSize();
}

FComponent::FComponent(PlatformInterface &platform, const FComponent_cfg &cfg)
      : platform_(platform),
      
        ui_(NULL),
        parent_(NULL),
        
        contents_locked_(cfg.getContentsLocked()),
        destroy_children_(cfg.getDestroyChildren()),

        layout_mgr_(cfg.getLayoutMgr()),
        valid_layout_(false),

        min_size_(cfg.getMinimumSize()),
        pref_size_(cfg.getPreferredSize()),
        max_size_(cfg.getMaximumSize()),

        position_(cfg.getPosition()),

        visible_(cfg.getVisible()),
        z_index_(cfg.getZIndex()),
        renderer_(cfg.getRenderer()),
        
        focused_(false),
        child_focused_(false),
        modal_(cfg.getModal()),
        focusable_(cfg.getFocusable()),
        focus_mgr_(cfg.getFocusMgr()),

        logger_(platform_.checkoutLogger())
{
   absolute_.position = parent_ == NULL ? position_ : parent_->clientToAbsolute(position_);
   absolute_.size = cfg.getSize();
}

FComponent::~FComponent()
{
   platform_.returnLogger(logger_);

   if (destroy_children_)
      for (cvec_iter_t it(children_.begin()); it != children_.end(); ++it)
         delete *it;
}

std::ostream &operator<<(std::ostream &os, const FComponent &component)
{
   component.printComponentIdentifier(os);
   return os;
}

FGUI_END