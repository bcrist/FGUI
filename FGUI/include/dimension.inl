#ifdef FGUI_DIMENSION_H_

FGUI_BEGIN

inline Dimension::Dimension() : width(dim[0]), height(dim[1]), v(&dim[0])
{
   dim[0] = 0.0;
   dim[1] = 0.0;
}

inline Dimension::Dimension(const Dimension &other) : width(dim[0]), height(dim[1]), v(&dim[0])
{
   dim[0] = other.width;
   dim[1] = other.height;
}

inline Dimension::Dimension(component_t width, component_t height) : width(dim[0]), height(dim[1]), v(&dim[0])
{
   dim[0] = width < 0.0f ? 0.0f : width;
   dim[1] = height < 0.0f ? 0.0f : height;
}

inline Dimension::Dimension(const component_t *v) : width(dim[0]), height(dim[1]), v(&dim[0])
{
   dim[0] = v[0] < 0.0f ? 0.0f : v[0];
   dim[1] = v[1] < 0.0f ? 0.0f : v[1];
}

inline Dimension &Dimension::operator=(const Dimension &rhs)
{
   dim[0] = rhs.width;
   dim[1] = rhs.height;
   return *this;
}

inline bool Dimension::operator==(const Dimension &rhs) const
{
   return width == rhs.width && height == rhs.height;
}

inline bool Dimension::operator!=(const Dimension &rhs) const
{
   return !(*this == rhs);
}

inline Dimension &Dimension::setWidth(component_t width)
{
   dim[0] = width < 0.0f ? 0.0f : width;
   return *this;
}

inline Dimension &Dimension::setHeight(component_t height)
{
   dim[1] = height < 0.0f ? 0.0f : height;
   return *this;
}

inline Dimension &Dimension::set(component_t width, component_t height)
{
   dim[0] = width < 0.0f ? 0.0f : width;
   dim[1] = height < 0.0f ? 0.0f : height;
   return *this;
}

FGUI_END

#endif
