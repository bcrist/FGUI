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
// File: default_focus_manager.cc

#include "default_focus_manager.h"

#include "component/f_component.h"

FGUI_BEGIN

FComponent *DefaultFocusManager::getNext(FComponent *current_focus)
{
   if (current_focus == NULL)
      return getFirstFocusableDescendant(focus_root_);

   int children = current_focus->getComponentCount();
   for (int i = 0; i < children; ++i)
   {
      FComponent *child = current_focus->getComponent(i);
      FComponent *focusable = getFirstFocusableDescendant(child);

      if (focusable != NULL)
         return focusable;
   }

   // if we get here, no descendants are focusable
      
   // if the current component is the root, we can't look upwards in the tree
   if (current_focus == focus_root_)
      return current_focus;

   // otherwise look upwards in the tree
   FComponent *parent = current_focus->getParent();
   if (parent == NULL)
      return current_focus;

   return getFirstFocusableAfter(parent, parent->getComponentIndex(current_focus)); 
}

FComponent *DefaultFocusManager::getPrev(FComponent *current_focus)
{
   if (current_focus == NULL || current_focus == focus_root_)
      return getLastFocusableDescendant(focus_root_);

   FComponent *parent = current_focus->getParent();
   if (parent == NULL)
      return getLastFocusableDescendant(focus_root_);

   return getLastFocusableBefore(parent, parent->getComponentIndex(current_focus));
}


FComponent *DefaultFocusManager::getFirstFocusableDescendant(FComponent *comp)
{
   if (comp == NULL)
      return NULL;

   if (comp->isFocusable())
      return comp;

   int children = comp->getComponentCount();
   for (int i = 0; i < children; ++i)
   {
      FComponent *focusable = getFirstFocusableDescendant(comp->getComponent(i));

      if (focusable != NULL)
         return focusable;
   }

   return NULL;
}

FComponent *DefaultFocusManager::getLastFocusableDescendant(FComponent *comp)
{
   if (comp == NULL)
      return NULL;

   int children = comp->getComponentCount();
   while (--children >= 0)
   {
      FComponent *focusable = getLastFocusableDescendant(comp->getComponent(children));

      if (focusable != NULL)
         return focusable;
   }

   if (comp->isFocusable())
      return comp;

   return NULL;
}


FComponent *DefaultFocusManager::getFirstFocusableAfter(FComponent *parent, int index)
{
   int siblings = parent->getComponentCount();
   while (++index < siblings)
   {
      FComponent *focusable = getFirstFocusableDescendant(parent->getComponent(index));

      if (focusable != NULL)
         return focusable;
   }

   // if the current component is the root, we can't look upwards in the tree
   if (parent == focus_root_)
      return getFirstFocusableDescendant(focus_root_);

   // if there were no focusables in the remainder of the paren't children, look
   // at the parent's siblings that appear after the parent.
   FComponent *parents_parent = parent->getParent();

   if (parents_parent == NULL)
      return getFirstFocusableDescendant(focus_root_);

   return getFirstFocusableAfter(parents_parent, parents_parent->getComponentIndex(parent));
}

FComponent *DefaultFocusManager::getLastFocusableBefore(FComponent *parent, int index)
{
   while (--index >= 0)
   {
      FComponent *focusable = getLastFocusableDescendant(parent->getComponent(index));

      if (focusable != NULL)
         return focusable;
   }

   if (parent->isFocusable())
      return parent;

   if (parent == focus_root_)
      return getLastFocusableDescendant(focus_root_);

   FComponent *parents_parent = parent->getParent();

   if (parents_parent == NULL)
      return getLastFocusableDescendant(focus_root_);

   return getLastFocusableBefore(parents_parent, parents_parent->getComponentIndex(parent));
}

FGUI_END