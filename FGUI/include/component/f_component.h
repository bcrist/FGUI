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
// File: component/f_component.h

#ifndef FGUI_COMPONENT_F_COMPONENT_H_
#define FGUI_COMPONENT_F_COMPONENT_H_
#include "fgui_std.h"

#include <ostream>

#include <list>
#include <vector>
#include <set>
#include <map>

#include "component/f_component_cfg.h"

#include "platform/platform.h"
#include "uid.h"
#include "rect.h"
#include "fgui_event.h"
#include "platform/logger_interface.h"
#include "layout_manager_interface.h"
#include "focus_manager_interface.h"
#include "renderer_interface.h"

FGUI_BEGIN

class FUI;

class FComponent;

struct RenderTask
{
   RenderTask(FComponent *component, RendererInterface *renderer);
   RenderTask(const RenderTask &other);
   RenderTask &operator=(const RenderTask &rhs);   
   bool operator<(const RenderTask &rhs) const;
   
   FComponent* const &component;
   RendererInterface* const &renderer;

private:
   FComponent* component_;
   RendererInterface* renderer_;
};

class FComponent
{   
   // Events
private:
   std::list<FocusListenerInterface*> focus_listeners_;
   std::list<KeyboardListenerInterface*> keyboard_listeners_;
   std::list<MouseListenerInterface*> mouse_listeners_;
   std::list<SimulationListenerInterface*> simulation_listeners_;
public:
   void addFocusListener(FocusListenerInterface *listener) { focus_listeners_.push_back(listener); }
   void removeFocusListener(FocusListenerInterface *listener) { focus_listeners_.remove(listener); }
   bool fireFocusEvent(FocusEvent *evt);

   void addKeyboardListener(KeyboardListenerInterface *listener) { keyboard_listeners_.push_back(listener); }
   void removeKeyboardListener(KeyboardListenerInterface *listener) { keyboard_listeners_.remove(listener); }
   bool fireKeyboardEvent(KeyboardEvent *evt);

   void addMouseListener(MouseListenerInterface *listener) { mouse_listeners_.push_back(listener); }
   void removeMouseListener(MouseListenerInterface *listener) { mouse_listeners_.remove(listener); }
   bool fireMouseEvent(MouseEvent *evt);

   void addSimulationListener(SimulationListenerInterface *listener) { simulation_listeners_.push_back(listener); }
   void removeSimulationListener(SimulationListenerInterface *listener) { simulation_listeners_.remove(listener); }
   bool fireSimulateEvent(SimulateEvent *evt);
   

   // Contents
private:
   PlatformInterface *platform_;
   FUI *ui_;
   FComponent *parent_;
   std::vector<FComponent*> children_;
   
   bool contents_locked_;
   bool destroy_children_;

   bool checkRemoveComponent(FComponent *c, bool destroy, std::vector<FComponent*>::iterator &it);
   void uncheckedRemoveComponent(FComponent *c, bool destroy, std::vector<FComponent*>::iterator &it);

protected:

   void setContentsLocked(bool contents_locked) { contents_locked_ = contents_locked; }
   void lockContents() { contents_locked_ = true; }
   void unlockContents() { contents_locked_ = false; }
   
   void setChildrenDestroyedOnDeath(bool destroy_children) { destroy_children_ = destroy_children; }
   void destroyChildrenOnDeath() { destroy_children_ = true; }
   void ignoreChildrenOnDeath() { destroy_children_ = false; }

public:
   PlatformInterface *getPlatform() { return platform_; }
   FUI *getUI() { return ui_; }
   FComponent *getParent() { return parent_; }
   
   bool isChildOf(const FComponent *parent) const { return parent_ && (parent_ == parent); }
   bool isDescendantOf(const FComponent *ancestor) const;

   bool getContentsLocked() const { return contents_locked_; }
   bool getChildrenDestroyedOnDeath() const { return destroy_children_; }

   bool addComponent(FComponent *c);
   bool removeComponent(FComponent *c, bool destroy);

   int getComponentCount() const { return children_.size(); }
   int getComponentIndex(const FComponent *component) const;
   FComponent *getComponent(size_t index) { if (index < 0 || index > children_.size()) return NULL; return children_[index]; }


   // Layout
private:
   LayoutManagerInterface *layout_mgr_;
   bool valid_layout_;

   Point position_;
   Rect absolute_;

   Dimension min_size_;
   Dimension pref_size_;
   Dimension max_size_;

protected:
   void setLayoutManager(LayoutManagerInterface *layout_mgr) { layout_mgr_ = layout_mgr; invalidateLayout(); }

public:
   const Point &getPosition() const { return position_; }
   const Rect &getAbsoluteRect() const { return absolute_; }
   const Point &getAbsolutePosition() const { return absolute_.position; }
   virtual void setPosition(const Point &position);
   const Dimension &getSize() const { return absolute_.size; }
   virtual void setSize(const Dimension &size);

   virtual const Dimension &getMinimumSize() const { return min_size_; }
   virtual void setMinimumSize(const Dimension &size);
   virtual void setMinimumWidth(float width);
   virtual void setMinimumHeight(float height);
   
   virtual const Dimension &getPreferredSize() const { return pref_size_; }
   virtual void setPreferredSize(const Dimension &size);
   virtual void setPreferredWidth(float width);
   virtual void setPreferredHeight(float height);

   virtual const Dimension &getMaximumSize() const { return max_size_; }
   virtual void setMaximumSize(const Dimension &size);
   virtual void setMaximumWidth(float width);
   virtual void setMaximumHeight(float height);
   
   virtual void invalidateLayout();
   virtual void layoutComponent();


   // Rendering
private:
   bool visible_;
   int z_index_;
   RendererInterface *renderer_;
   Rect clip_;

protected:
   void setVisible(bool visible);
   void setZIndex(int z_index);
   void setRenderer(RendererInterface *renderer);

public:
   bool isVisible() const { return visible_; }
   int getZIndex() const { return z_index_; }
   RendererInterface *getRenderer() { return renderer_; }
   const Rect &getClip() const { return clip_; }

   virtual void makeDirty();
   virtual void getRenderTasks(std::vector<RenderTask> *tasks);
   virtual void setClip(const Rect &clip);


   // Coordinate Processing
   virtual Point clientToAbsolute(const Point &client_coord) const;
   virtual Point absoluteToClient(const Point &absolute_coord) const;
   virtual void getComponentsAt(std::vector<FComponent*> *components, const Point &absolute_coord);
   virtual bool checkPointOverComponent(const Point &absolute_coord) const;
   bool checkPointInBounds(const Point &absolute_coord) const;


   // Focus Management
private:
   bool focused_;
   bool child_focused_;
   bool focusable_;
   bool modal_;
   FocusManagerInterface *focus_mgr_;

   void setChildFocused(bool new_state);

protected:
   void setFocusable(bool focusable);
   void setModal(bool modal);
   void setFocusManager(FocusManagerInterface *focus_mgr) { focus_mgr_ = focus_mgr; }
public:
   bool isFocusable() const { return focusable_; }
   bool isModal() const { return modal_; }
   bool requestFocus();
   void blur();

   bool isFocused() const { return focused_; }
   bool isChildFocused() const { return child_focused_; }

   // called by root - don't use this to request focus!
   void setFocused(bool focused);

   FocusManagerInterface *getFocusManager() const;


   // Logging & debugging
private:
   LoggerInterface *logger_;
public:
   bool isLoggerAvailable() const { return logger_ != NULL; }
   void log(const char *txt);
   virtual const char *getComponentType() const { return "FComponent"; }
   virtual void printComponentIdentifier(std::ostream &os) const { os << getComponentType() << '@' << this; }

   virtual void printDebug(std::ostream &os) const;
   virtual void printDebugRecursive(std::ostream &os) const;
   virtual void logDebug() const;
   virtual void logDebugRecursive() const;

public:
   FComponent();
   FComponent(PlatformInterface *platform);
   FComponent(const FComponent_cfg &cfg);
   FComponent(PlatformInterface *platform, const FComponent_cfg &cfg);
   virtual ~FComponent();

private:
   friend class FUI;

   DISALLOW_COPY_AND_ASSIGN(FComponent);
};

std::ostream &operator<<(std::ostream &os, const FComponent &component);


FGUI_END

#include "render_task.inl"

#endif