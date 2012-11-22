#ifdef FGUI_COMPONENT_F_COMPONENT_H_

FGUI_BEGIN

inline RenderTask::RenderTask(FComponent *component, RendererInterface *renderer)
      : component(component_), renderer(renderer_),
        component_(component), renderer_(renderer) {}

inline RenderTask::RenderTask(const RenderTask &other)
      : component(component_), renderer(renderer_),
        component_(other.component_), renderer_(other.renderer_) {}

inline RenderTask &RenderTask::operator=(const RenderTask &rhs)
{
   component_ = rhs.component_;
   renderer_ = rhs.renderer_;
   return *this;
}

inline bool RenderTask::operator<(const RenderTask &rhs) const
{
   if (component && rhs.component)
      return component->getZIndex() < rhs.component->getZIndex();
      
   return false;
}

FGUI_END

#endif
