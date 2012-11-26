#define FGUI_USE_ALLEGRO_FONTS
#include "platform/allegro/allegro_font.h"

#ifdef FGUI_PLATFORM_ALLEGRO_ALLEGRO_FONT_H_

FGUI_BEGIN

AllegroFont::AllegroFont(ALLEGRO_FONT *afont) : afont_(afont)
{
   line_ascent_ = al_get_font_ascent(afont);
   line_height_ = al_get_font_line_height(afont);
}


AllegroFont::~AllegroFont()
{
   al_destroy_font(afont_);
}

void AllegroFont::drawString(const std::string &str, const Point &position, const Color &color)
{
   ALLEGRO_COLOR acolor = al_map_rgba_f(color.r, color.g, color.b, color.a);
   al_draw_text(afont_, acolor, position.x, position.y, 0, str.c_str());
}

TextMetrics AllegroFont::getMetrics(const std::string &str)
{
   const char *cstr = str.c_str();

   int bbx, bby, bbw, bbh;
   al_get_text_dimensions(afont_, cstr, &bbx, &bby, &bbw, &bbh);
   int line_width = al_get_text_width(afont_, cstr);

   return TextMetrics(Rect(bbx, bby, bbw, bbh), Rect(0, 0, line_width, line_ascent_), line_height_);
}


FGUI_END

#endif