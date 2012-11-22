#ifndef FGUI_COLOR_H_
#include "color.h"
#else

FGUI_BEGIN

inline Color::Color() : r(v[0]), g(v[1]), b(v[2]), a(v[3])
{
   r = g = b = a = 0.0f;
}

inline Color::Color(const Color &other) : r(v[0]), g(v[1]), b(v[2]), a(v[3])
{
   memcpy(v, other.v, 4 * sizeof(component_t));
}

inline Color::Color(const Color &other, component_t rgba_mul) : r(v[0]), g(v[1]), b(v[2]), a(v[3])
{
   r = other.r / rgba_mul;
   g = other.g / rgba_mul;
   b = other.b / rgba_mul;
   a = other.a / rgba_mul;
}

inline Color::Color(const Color &other, component_t rgb_mul, component_t a_mul) : r(v[0]), g(v[1]), b(v[2]), a(v[3])
{
   r = other.r / rgb_mul;
   g = other.g / rgb_mul;
   b = other.b / rgb_mul;
   a = other.a / a_mul;
}

inline Color::Color(component_t lum) : r(v[0]), g(v[1]), b(v[2]), a(v[3])
{
   r = g = b = lum;
   a = 1.0f;
}

inline Color::Color(component_t lum, component_t alpha) : r(v[0]), g(v[1]), b(v[2]), a(v[3])
{
   r = g = b = lum;
   a = alpha;
}

inline Color::Color(component_t r, component_t g, component_t b) : r(v[0]), g(v[1]), b(v[2]), a(v[3])
{
   v[0] = r;
   v[1] = g;
   v[2] = b;
   a = 1.0f;
}

inline Color::Color(component_t r, component_t g, component_t b, component_t a) : r(v[0]), g(v[1]), b(v[2]), a(v[3])
{
   v[0] = r;
   v[1] = g;
   v[2] = b;
   v[3] = a;
}

inline Color::Color(const component_t *components) : r(v[0]), g(v[1]), b(v[2]), a(v[3])
{
   memcpy(v, components, 4 * sizeof(component_t));
}


inline Color &Color::operator=(const Color &rhs)
{
   memcpy(v, rhs.v, 4 * sizeof(component_t));
   return *this;
}

inline Color &Color::operator+=(const Color &rhs)
{
   r += rhs.r;
   g += rhs.g;
   b += rhs.b;
   a += rhs.a;
   return *this;
}

inline Color &Color::operator-=(const Color &rhs)
{
   r -= rhs.r;
   g -= rhs.g;
   b -= rhs.b;
   a -= rhs.a;
   return *this;
}

inline Color &Color::operator*=(const Color &rhs)
{
   r *= rhs.r;
   g *= rhs.g;
   b *= rhs.b;
   a *= rhs.a;
   return *this;
}

inline Color &Color::operator/=(const Color &rhs)
{
   r /= rhs.r;
   g /= rhs.g;
   b /= rhs.b;
   a /= rhs.a;
   return *this;
}


inline const Color Color::operator+(const Color &rhs) const
{
   return Color(*this) += rhs;
}

inline const Color Color::operator-(const Color &rhs) const
{
   return Color(*this) -= rhs;
}

inline const Color Color::operator*(const Color &rhs) const
{
   return Color(*this) *= rhs;
}

inline const Color Color::operator/(const Color &rhs) const
{
   return Color(*this) /= rhs;
}


inline Color &Color::invert()
{
   r = 1.0f - r;
   g = 1.0f - g;
   b = 1.0f - b;
}

FGUI_END

#endif
