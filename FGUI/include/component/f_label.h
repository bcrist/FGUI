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
// File: component/f_label.h

#ifndef FGUI_COMPONENT_F_LABEL_H_
#define FGUI_COMPONENT_F_LABEL_H_
#include "fgui_std.h"

#include "component/f_component.h"

#include <cstdint>

#include "platform/opengl/label_renderer.h"



#include "platform/font_interface.h"

#include "color.h"

FGUI_BEGIN

class FLabel : public FComponent
{
public:
   enum VAlign { kALIGN_MIDDLE = 0, kALIGN_TOP = 1, kALIGN_BOTTOM = 2 };
   enum HAlign { kALIGN_CENTER = 0, kALIGN_LEFT = 16, kALIGN_RIGHT = 32 };
   
   FLabel();
   FLabel(PlatformInterface &platform);
   FLabel(const std::string &text);
   FLabel(PlatformInterface &platform, const std::string &text);
   virtual ~FLabel();

   static const UID uid_;
   static const UID typeface_uid_;
   static const UID font_style_uid_;

   virtual const char *getComponentType() const { return "FLabel"; }

   const std::string &getText() const { return text_; }
   virtual void setText(const std::string &text);

   uint8_t getAlign() const { return vertical_align_ | horizontal_align_; }
   uint8_t getVerticalAlign() const { return vertical_align_; }
   uint8_t getHorizontalAlign() const { return horizontal_align_; }
   virtual void setAlign(uint8_t align);
   virtual void setVerticalAlign(uint8_t align);
   virtual void setHorizontalAlign(uint8_t align);

   virtual void setFont(const std::string &typeface, const std::string &style, float_t size);
   FontInterface *getFont() { return font_; }

   virtual void setColor(const Color &color);
   const Color &getColor() const { return color_; }

   virtual void setStyle(const Color &color, const std::string &typeface, const std::string &style, float_t size, uint8_t align);

   const Point &getTextOrigin() const { return text_origin_; }
   const TextMetrics &getTextMetrics() const { return metrics_; }

   virtual void layoutComponent() { FComponent::layoutComponent(); recalcTextOrigin(); }

private:
   void recalcMetrics();
   void recalcTextOrigin();

   std::string text_;

   uint8_t vertical_align_;
   uint8_t horizontal_align_;

   Color color_;
   FontInterface *font_;

   Point text_origin_;
   TextMetrics metrics_;

   DISALLOW_COPY_AND_ASSIGN(FLabel);
};

FGUI_END

#endif