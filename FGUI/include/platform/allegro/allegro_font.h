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
// File: platform/allegro/allegro_font.h

#ifndef FGUI_PLATFORM_ALLEGRO_ALLEGRO_FONT_H_
#ifdef FGUI_USE_ALLEGRO_FONTS
#define FGUI_PLATFORM_ALLEGRO_ALLEGRO_FONT_H_
#include "fgui_std.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "platform/font_interface.h"

FGUI_BEGIN

class AllegroFont : public FontInterface
{
public:
   explicit AllegroFont(ALLEGRO_FONT *afont);
   virtual ~AllegroFont();

   virtual void drawString(const std::string &str, const Point &position, const Color &color);
   virtual TextMetrics getMetrics(const std::string &str);

private:
   ALLEGRO_FONT *afont_;
   int line_ascent_;
   int line_height_;

   DISALLOW_COPY_AND_ASSIGN(AllegroFont);
};

FGUI_END

#endif
#endif
