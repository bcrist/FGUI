#define FGUI_USE_ALLEGRO_FONTS
#include "platform/allegro/allegro_font.h"

#ifdef FGUI_PLATFORM_ALLEGRO_ALLEGRO_FONT_H_

#ifndef FGUI_NO_OPENGL
#include "platform/opengl/opengl.h"
#endif

FGUI_BEGIN

AllegroFont::AllegroFont(ALLEGRO_FONT *afont, float_t line_top, float_t line_height)
      : afont_(afont),
        line_top_(line_top),
        line_height_(line_height) {}

AllegroFont::~AllegroFont()
{
   al_destroy_font(afont_);
}

void AllegroFont::drawString(const std::string &str, const Point &position, const Color &color)
{
#  ifdef FGUI_NO_OPENGL
      ALLEGRO_COLOR acolor = al_map_rgba_f(color.r, color.g, color.b, color.a);
      al_draw_text(afont_, acolor, position.x, position.y, 0, str.c_str());
#  else
      glPushAttrib(GL_COLOR_BUFFER_BIT | GL_ENABLE_BIT);

      ALLEGRO_COLOR acolor = al_map_rgba_f(color.r, color.g, color.b, color.a);
      al_draw_text(afont_, acolor, position.x, position.y, 0, str.c_str());

      glPopAttrib();
#  endif
}

TextMetrics AllegroFont::getMetrics(const std::string &str)
{
   const char *cstr = str.c_str();

   int bbx, bby, bbw, bbh;

#  ifdef FGUI_NO_OPENGL
      al_get_text_dimensions(afont_, cstr, &bbx, &bby, &bbw, &bbh);
      int line_width = al_get_text_width(afont_, cstr);
#  else
      glPushAttrib(GL_COLOR_BUFFER_BIT | GL_ENABLE_BIT);

      al_get_text_dimensions(afont_, cstr, &bbx, &bby, &bbw, &bbh);
      int line_width = al_get_text_width(afont_, cstr);

      glPopAttrib();
#  endif

   return TextMetrics(Rect(bbx, bby, bbw, bbh), Rect(0, line_top_, line_width, line_height_));
}


FGUI_END

#endif