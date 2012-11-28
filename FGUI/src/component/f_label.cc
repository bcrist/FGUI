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
// File: component/f_label.cc

#include "component/f_label.h"

#include "platform/platform.h"

FGUI_BEGIN

const UID FLabel::uid_;
const UID FLabel::typeface_uid_;
const UID FLabel::font_style_uid_;

FLabel::FLabel()
      : text_(""),
        vertical_align_(kALIGN_MIDDLE),
        horizontal_align_(kALIGN_CENTER),
        color_(getPlatform().getColor(font_style_uid_))
{
   PlatformInterface &platform = getPlatform();
   setRenderer(platform.checkoutRenderer(uid_));
   font_ = platform.getFont(
      platform.getProperty(typeface_uid_), 
      platform.getProperty(font_style_uid_),
      platform.getReal(font_style_uid_));
   recalcMetrics();
}

FLabel::FLabel(PlatformInterface &platform)
      : FComponent(platform),
        text_(""),
        vertical_align_(kALIGN_MIDDLE),
        horizontal_align_(kALIGN_CENTER),
        color_(getPlatform().getColor(font_style_uid_))
{
   setRenderer(platform.checkoutRenderer(uid_));
   font_ = platform.getFont(
      platform.getProperty(typeface_uid_), 
      platform.getProperty(font_style_uid_),
      platform.getReal(font_style_uid_));
   recalcMetrics();
}

FLabel::FLabel(const std::string &text)
      : text_(text),
        vertical_align_(kALIGN_MIDDLE),
        horizontal_align_(kALIGN_CENTER),
        color_(getPlatform().getColor(font_style_uid_))
{
   PlatformInterface &platform = getPlatform();
   setRenderer(platform.checkoutRenderer(uid_));
   font_ = platform.getFont(
      platform.getProperty(typeface_uid_), 
      platform.getProperty(font_style_uid_),
      platform.getReal(font_style_uid_));
   recalcMetrics();
}

FLabel::FLabel(PlatformInterface &platform, const std::string &text)
      : FComponent(platform),
        text_(text),
        vertical_align_(kALIGN_MIDDLE),
        horizontal_align_(kALIGN_CENTER),
        color_(getPlatform().getColor(font_style_uid_))
{
   setRenderer(platform.checkoutRenderer(uid_));
   font_ = platform.getFont(
      platform.getProperty(typeface_uid_), 
      platform.getProperty(font_style_uid_),
      platform.getReal(font_style_uid_));
   recalcMetrics();
}

FLabel::~FLabel()
{
   getPlatform().returnRenderer(uid_, getRenderer());
   getPlatform().freeFont(font_);
}

void FLabel::setText(const std::string &text)
{
   text_ = text;

   if (font_)
      recalcMetrics();
}

void FLabel::setAlign(uint8_t align)
{
   uint8_t v_align(align & 0x0F),
           h_align(align & 0xF0);
   
   if (vertical_align_ != v_align || horizontal_align_ != h_align)
   {
      vertical_align_ = v_align;
      horizontal_align_ = h_align;
      recalcTextOrigin();
   }
}

void FLabel::setVerticalAlign(uint8_t align)
{
   align &= 0x0F;
   
   if (vertical_align_ != align)
   {
      vertical_align_ = align;
      recalcTextOrigin();
   }
}

void FLabel::setHorizontalAlign(uint8_t align)
{
   align &= 0xF0;
   
   if (horizontal_align_ != align)
   {
      horizontal_align_ = align;
      recalcTextOrigin();
   }
}

void FLabel::setFont(const std::string &typeface, const std::string &style, float_t size)
{
   FontInterface *font = getPlatform().getFont(typeface, style, size);

   if (font && font_ != font)
   {
      font_ = font;
      recalcMetrics();
   }
}

void FLabel::setColor(const Color &color)
{
   if (color_ != color)
   {
      color_ = color;
      makeDirty();
   }
}

void FLabel::setStyle(const Color &color, const std::string &typeface, const std::string &style, float_t size, uint8_t align)
{
   setFont(typeface, style, size);
   setAlign(align);
   setColor(color);
}

void FLabel::recalcMetrics()
{
   if (font_)
   {
      metrics_ = font_->getMetrics(text_);

      setMinimumSize(metrics_.bounds.size);
      setPreferredSize(metrics_.bounds.size);
      setMaximumSize(Dimension(Dimension::kBIG, Dimension::kBIG));

      setSize(getPreferredSize());
   }
}

void FLabel::recalcTextOrigin()
{
   Point::component_t x, y;
   const Rect &absolute(getAbsoluteRect());

   switch (vertical_align_)
   {
      case kALIGN_TOP:
         y = absolute.getTop() + metrics_.bounds.getTop();
         break;

      case kALIGN_BOTTOM:
         y = absolute.getBottom() - metrics_.bounds.getBottom();
         break;

      default: // kALIGN_MIDDLE
         y = 0.5f * (absolute.getTop() + absolute.getBottom() -
            (metrics_.line.getTop() + metrics_.line.getBottom()));

         // if part of the text would be outside the component bounds, move it inside.
         Point::component_t temp_y = absolute.getBottom() - metrics_.bounds.getBottom();
         if (y > temp_y)
            y = temp_y;

         temp_y = absolute.getTop() + metrics_.bounds.getTop();
         if (y < temp_y)
            y = temp_y;
   }

   switch (horizontal_align_)
   {
      case kALIGN_LEFT:
         x = absolute.getLeft() + metrics_.bounds.getLeft();
         break;

      case kALIGN_RIGHT:
         x = absolute.getRight() - metrics_.bounds.getRight();
         break;

      default: // kALIGN_CENTER
         x = 0.5f * (absolute.getLeft() + absolute.getRight() -
            (metrics_.line.getLeft() + metrics_.line.getRight()));

         // if part of the text would be outside the component bounds, move it inside.
         Point::component_t temp_x = absolute.getRight() - metrics_.bounds.getRight();
         if (x > temp_x)
            x = temp_x;

         temp_x = absolute.getLeft() + metrics_.bounds.getLeft();
         if (x < temp_x)
            x = temp_x;
   }

   text_origin_ = Point(x, y);

   makeDirty();
}

FGUI_END
