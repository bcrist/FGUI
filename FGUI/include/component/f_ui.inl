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
// File: component/f_ui.inl

#ifdef FGUI_COMPONENT_F_UI_H_

FGUI_BEGIN

inline void FUI::_swapComponentsUnderMousePointers()
{
   std::vector<FComponent*> *temp(components_under_mouse_);
   components_under_mouse_ = components_under_mouse_old_;
   components_under_mouse_old_ = temp;
}

inline void FUI::_removeHoveredComponent(FComponent *component)
{
   // remove component from hovered components vector
   std::vector<FComponent*>::iterator it = std::find(hovered_components_.begin(), hovered_components_.end(), component);
   if (it != hovered_components_.end())
      hovered_components_.erase(it);
}

inline void FUI::_removeComponentUnderMouse(FComponent *component)
{
   // remove component from hovered components vector

   std::vector<FComponent*>::iterator begin(components_under_mouse_->begin()),
               end(components_under_mouse_->end()),
               it(std::find(begin, end, component));
   if (it != end)
      components_under_mouse_->erase(it);
}

inline void FUI::_removeOldComponentUnderMouse(FComponent *component)
{
   // remove component from hovered components vector

   std::vector<FComponent*>::iterator begin(components_under_mouse_old_->begin()),
               end(components_under_mouse_old_->end()),
               it(std::find(begin, end, component));
   if (it != end)
      components_under_mouse_old_->erase(it);
}

inline void FUI::_removeLastClickComponent(FComponent *component)
{
   if (last_click_component_ == component)
   {
      last_click_component_ = NULL;
      last_click_ticks_ = -1;
   }
}

FGUI_END


#endif
