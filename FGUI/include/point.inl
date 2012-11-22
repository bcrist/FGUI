#ifdef FGUI_POINT_H_

FGUI_BEGIN

inline Point::Point() : x(val[0]), y(val[1]), v(&val[0])
{
   val[0] = 0.0;
   val[1] = 0.0;
}

inline Point::Point(const Point &other) : x(val[0]), y(val[1]), v(&val[0])
{
   val[0] = other.x;
   val[1] = other.y;
}

inline Point::Point(component_t x, component_t y) : x(val[0]), y(val[1]), v(&val[0])
{
   val[0] = x;
   val[1] = y;
}

inline Point::Point(const component_t *v) : x(val[0]), y(val[1]), v(&val[0])
{
   val[0] = v[0];
   val[1] = v[1];
}

inline bool Point::operator==(const Point &rhs) const
{
   return x == rhs.x && y == rhs.y;
}

inline bool Point::operator!=(const Point &rhs) const
{
   return !(*this == rhs);
}

inline Point &Point::operator=(const Point &rhs)
{
   val[0] = rhs.x;
   val[1] = rhs.y;
   return *this;
}

inline Point &Point::setX(component_t x)
{
   val[0] = x;
   return *this;
}

inline Point &Point::setY(component_t y)
{
   val[1] = x;
   return *this;
}

inline Point &Point::set(component_t x, component_t y)
{
   val[0] = x;
   val[1] = y;
   return *this;
}

FGUI_END

#endif