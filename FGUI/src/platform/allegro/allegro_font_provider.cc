#define FGUI_USE_ALLEGRO_FONTS
#include "platform/allegro/allegro_font_provider.h"

#ifdef FGUI_PLATFORM_ALLEGRO_ALLEGRO_FONT_PROVIDER_H_

#ifndef FGUI_NO_OPENGL
#include "platform/opengl/opengl.h"
#endif

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include "platform/allegro/allegro_font.h"

FGUI_BEGIN

FontInterface *AllegroFontProvider::getFont(const std::string &typeface, const std::string &style, float_t size)
{
   FontFileSpec ffs = getFFS(typeface, style);
   AFontSpec afs(ffs.getFilename(), size);

   std::map<AFontSpec,AFont>::iterator it = fonts_by_spec_.find(afs);
   if (it != fonts_by_spec_.end())
   {
      // font found
      ++(it->second.references_);
      return it->second.f_;
   }
   else
   {
      // create new font object
#     ifdef FGUI_NO_OPENGL
         ALLEGRO_FONT *afont = al_load_font(filename.c_str(), size, 0);
#     else
         glPushAttrib(GL_COLOR_BUFFER_BIT | GL_ENABLE_BIT);

         ALLEGRO_FONT *afont = al_load_font(ffs.getFilename().c_str(), size, 0);

         glPopAttrib();
#     endif
      
      if (!afont)   // couldn't load font
         return NULL;

      FontInterface *font = new AllegroFont(afont, ffs.getPadding() * size, ffs.getLineScale() * size);

      fonts_by_spec_[afs] = AFont(font);
      specs_by_font_[font] = afs;

      return font;
   }
}

void AllegroFontProvider::freeFont(FontInterface *font)
{
   std::map<FontInterface*,AFontSpec>::iterator it = specs_by_font_.find(font);
   if (it != specs_by_font_.end())
   {
      AFontSpec &afs = it->second;
      AFont &af = fonts_by_spec_[afs];
      int &refs = af.references_;
      --refs;

      if (refs == 0)   // if nobody is using the font anymore, clean it up
      {
         fonts_by_spec_.erase(afs);
         specs_by_font_.erase(it);
         delete font;
      }
   }
}


void AllegroFontProvider::addFont(const std::string &typeface, const std::string &style, const std::string &filename, float_t padding_top, float_t line_scale)
{
   font_files_.insert(FontFileSpec(typeface, style, padding_top, line_scale, filename));
}

AllegroFontProvider::FontFileSpec AllegroFontProvider::getFFS(const std::string &typeface, const std::string &style)
{
   // look for this typeface/style in the registered fonts map
   FontFileSpec ffs(typeface, style);
   std::set<FontFileSpec>::const_iterator it = font_files_.find(ffs);
   if (it != font_files_.end())
      return *it;

   // otherwise, guess at what the filename might be
   return ffs;
}

FGUI_END

#endif