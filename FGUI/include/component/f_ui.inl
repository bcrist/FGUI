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
