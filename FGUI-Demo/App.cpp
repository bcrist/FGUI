#include "App.h"

#include <sstream>

#ifdef WIN32
#include <Windows.h>
#include <tchar.h>
#endif

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

using fgui::Platform;
using fgui::DefaultPlatform;
using fgui::FComponent;
using fgui::FUI;
using fgui::FColoredRectangle;
using fgui::Dimension;
using fgui::Point;
using fgui::Color;
using fgui::Rect;
using fgui::AllegroFontProvider;
using fgui::FLabel;

BMC_BEGIN

   App::App()
   : init_successful_(true),
   display_(NULL),
   queue_(NULL),
   ui_(NULL)
{
   al_set_org_name("Magic / More Magic");
   al_set_app_name("FGUI Demo");

   if (!al_init())
   {
      startupError("The Allegro engine failed to initialize properly!");
      return;
   }

   al_init_font_addon();

   if (!al_init_ttf_addon())
   {
      startupError("There was a problem initializing the font loader!");
      return;
   }

   if (!al_install_keyboard())
      log_.log("Failed to install keyboard!\n");

   if (!al_install_mouse())
      log_.log("Failed to install mouse!\n");

   if (!initOpenGL())
   {
      startupError("There was a problem creating the OpenGL context!");
      return;
   }

   queue_ = al_create_event_queue();
   if (!queue_)
   {
      startupError("There was a problem creating the event queue!");
      return;
   }

   timer_ = al_create_timer(0.01);
   if (!timer_)
   {
      startupError("There was a problem creating the allegro timer!");
      return;
   }

   al_register_event_source(queue_, al_get_keyboard_event_source());
   al_register_event_source(queue_, al_get_mouse_event_source());
   al_register_event_source(queue_, al_get_display_event_source(display_));
   al_register_event_source(queue_, al_get_timer_event_source(timer_));

   initUI();
}

// attempt to create an openGL context with multisampling,
// and try one without multisampling if it fails.
bool App::initOpenGL()
{
   al_set_new_window_position(25, 25);

   al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);

   al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_REQUIRE);
   al_set_new_display_option(ALLEGRO_SAMPLES, 4, ALLEGRO_SUGGEST);

   display_ = al_create_display(640, 480);
   if (!display_)
   {
      al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 0, ALLEGRO_DONTCARE);
      al_set_new_display_option(ALLEGRO_SAMPLES, 0, ALLEGRO_DONTCARE);

      display_ = al_create_display(640, 480);
      if (!display_)
         return false;
   }

   glClearColor(0.75, 0.75, 0.75, 0);
   
   glEnable (GL_BLEND);
   glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   //debugGL();

   return true;
}

void App::initUI()
{
   DefaultPlatform &dp = static_cast<DefaultPlatform&>(Platform::get());
   dp.setLogger(&log_);

   AllegroFontProvider &afp = static_cast<AllegroFontProvider&>(dp.getFontProvider());
   afp.addFont("segoe ui", "regular", "segoe_ui.ttf", 0.29, 1);

   //debugGL();

   ui_ = new FUI();

   //debugGL();

   ui_->setMinimumSize(Dimension(100, 100));
   ui_->setMaximumSize(Dimension(800, 600));
   ui_->setPreferredSize(Dimension(400, 300));

   std::ostringstream oss;
   oss << ui_->getPreferredSize() << std::endl;
   log_.log(oss.str().c_str());

   ui_->uiResize(Dimension(640, 480)); //ui_->getPreferredSize());

   /*FColoredRectangle *cr1 = new FColoredRectangle(Color(1, 0, 0, 0.5), Color(0, 1, 0, 0.5), Color(0, 0, 1, 0.5), Color(1, 1, 0, 0.5));
   FColoredRectangle *cr2 = new FColoredRectangle(Color(1, 0, 0, 0.5), Color(0, 1, 0, 0.5), Color(0, 0, 1, 0.5), Color(1, 1, 0, 0.5));
   FColoredRectangle *cr3 = new FColoredRectangle(Color(1, 0, 0, 0.5), Color(0, 1, 0, 0.5), Color(0, 0, 1, 0.5), Color(1, 1, 0, 0.5));
   FColoredRectangle *cr4 = new FColoredRectangle(Color(1, 0, 0, 0.5), Color(0, 1, 0, 0.5), Color(0, 0, 1, 0.5), Color(1, 1, 0, 0.5));

   ui_->addComponent(cr1);
   ui_->addComponent(cr2);
   ui_->addComponent(cr3);
   ui_->addComponent(cr4);

   cr1->setPosition(Point(5, 300));
   cr1->setSize(Dimension(200, 250));

   cr2->setPosition(Point(100, 10));
   cr2->setSize(Dimension(200, 250));

   cr3->setPosition(Point(50, 100));
   cr3->setSize(Dimension(200, 250));

   cr4->setPosition(Point(400, 0));
   cr4->setSize(Dimension(100, 125));
   */
   //debugGL();

   FLabel *label = new FLabel("Testing 1 2 3...");

   //debugGL();

   ui_->addComponent(label);

   label->setPosition(Point(10, 10));
   label->setSize(Dimension(200, 325));

   ui_->uiSimulate(0);
}

void App::debugGL()
{
   std::ostringstream oss;
   GLboolean bool_[1];
   GLfloat float_[4];
   GLint int_[1];

   glGetFloatv(GL_COLOR_CLEAR_VALUE, float_);
   oss << "GL_COLOR_CLEAR_VALUE: " << Color(float_) << std::endl;

   glGetBooleanv(GL_BLEND, bool_);
   oss << "GL_BLEND:       " << (bool_[0] ? "enabled" : "disabled") << std::endl;

   glGetFloatv(GL_BLEND_COLOR, float_);
   oss << "GL_BLEND_COLOR: " << Color(float_) << std::endl;

   glGetIntegerv(GL_BLEND_EQUATION_RGB, int_);
   oss << "GL_BLEND_EQUATION_RGB: ";
   switch (int_[0])
   {
      case GL_FUNC_ADD:              oss << "GL_FUNC_ADD"; break;
      case GL_FUNC_SUBTRACT:         oss << "GL_FUNC_SUBTRACT"; break;
      case GL_FUNC_REVERSE_SUBTRACT: oss << "GL_FUNC_REVERSE_SUBTRACT"; break;
      case GL_MIN:                   oss << "GL_MIN"; break;
      case GL_MAX:                   oss << "GL_MAX"; break;
   }
   oss << std::endl;

   glGetIntegerv(GL_BLEND_SRC_RGB, int_);
   oss << "GL_BLEND_SRC_RGB: ";
   switch (int_[0])
   {
      case GL_ZERO:                     oss << "GL_ZERO"; break;
      case GL_ONE:                      oss << "GL_ONE"; break;
      case GL_SRC_COLOR:                oss << "GL_SRC_COLOR"; break;
      case GL_ONE_MINUS_SRC_COLOR:      oss << "GL_ONE_MINUS_SRC_COLOR"; break;
      case GL_DST_COLOR:                oss << "GL_DST_COLOR"; break;
      case GL_ONE_MINUS_DST_COLOR:      oss << "GL_ONE_MINUS_DST_COLOR"; break;
      case GL_SRC_ALPHA:                oss << "GL_SRC_ALPHA"; break;
      case GL_ONE_MINUS_SRC_ALPHA:      oss << "GL_ONE_MINUS_SRC_ALPHA"; break;
      case GL_DST_ALPHA:                oss << "GL_DST_ALPHA"; break;
      case GL_ONE_MINUS_DST_ALPHA:      oss << "GL_ONE_MINUS_DST_ALPHA"; break;
      case GL_CONSTANT_COLOR:           oss << "GL_CONSTANT_COLOR"; break;
      case GL_ONE_MINUS_CONSTANT_COLOR: oss << "GL_ONE_MINUS_CONSTANT_COLOR"; break;
      case GL_CONSTANT_ALPHA:           oss << "GL_CONSTANT_ALPHA"; break;
      case GL_ONE_MINUS_CONSTANT_ALPHA: oss << "GL_ONE_MINUS_CONSTANT_ALPHA"; break;

      case GL_SRC_ALPHA_SATURATE:	   oss << "GL_SRC_ALPHA_SATURATE"; break;
      case GL_SRC1_COLOR:	           oss << "GL_SRC1_COLOR"; break;
      case GL_ONE_MINUS_SRC1_COLOR:	   oss << "GL_ONE_MINUS_SRC1_COLOR"; break;
      case GL_SRC1_ALPHA:	           oss << "GL_SRC1_ALPHA"; break;
      case GL_ONE_MINUS_SRC1_ALPHA:    oss << "GL_ONE_MINUS_SRC1_ALPHA"; break;
   }
   oss << std::endl;

   glGetIntegerv(GL_BLEND_DST_RGB, int_);
   oss << "GL_BLEND_DST_RGB: ";
   switch (int_[0])
   {
      case GL_ZERO:                     oss << "GL_ZERO"; break;
      case GL_ONE:                      oss << "GL_ONE"; break;
      case GL_SRC_COLOR:                oss << "GL_SRC_COLOR"; break;
      case GL_ONE_MINUS_SRC_COLOR:      oss << "GL_ONE_MINUS_SRC_COLOR"; break;
      case GL_DST_COLOR:                oss << "GL_DST_COLOR"; break;
      case GL_ONE_MINUS_DST_COLOR:      oss << "GL_ONE_MINUS_DST_COLOR"; break;
      case GL_SRC_ALPHA:                oss << "GL_SRC_ALPHA"; break;
      case GL_ONE_MINUS_SRC_ALPHA:      oss << "GL_ONE_MINUS_SRC_ALPHA"; break;
      case GL_DST_ALPHA:                oss << "GL_DST_ALPHA"; break;
      case GL_ONE_MINUS_DST_ALPHA:      oss << "GL_ONE_MINUS_DST_ALPHA"; break;
      case GL_CONSTANT_COLOR:           oss << "GL_CONSTANT_COLOR"; break;
      case GL_ONE_MINUS_CONSTANT_COLOR: oss << "GL_ONE_MINUS_CONSTANT_COLOR"; break;
      case GL_CONSTANT_ALPHA:           oss << "GL_CONSTANT_ALPHA"; break;
      case GL_ONE_MINUS_CONSTANT_ALPHA: oss << "GL_ONE_MINUS_CONSTANT_ALPHA"; break;

      case GL_SRC_ALPHA_SATURATE:	   oss << "GL_SRC_ALPHA_SATURATE"; break;
      case GL_SRC1_COLOR:	           oss << "GL_SRC1_COLOR"; break;
      case GL_ONE_MINUS_SRC1_COLOR:	   oss << "GL_ONE_MINUS_SRC1_COLOR"; break;
      case GL_SRC1_ALPHA:	           oss << "GL_SRC1_ALPHA"; break;
      case GL_ONE_MINUS_SRC1_ALPHA:    oss << "GL_ONE_MINUS_SRC1_ALPHA"; break;
   }
   oss << std::endl;

   

   glGetIntegerv(GL_BLEND_EQUATION_ALPHA, int_);
   oss << "GL_BLEND_EQUATION_ALPHA: ";
   switch (int_[0])
   {
      case GL_FUNC_ADD:              oss << "GL_FUNC_ADD"; break;
      case GL_FUNC_SUBTRACT:         oss << "GL_FUNC_SUBTRACT"; break;
      case GL_FUNC_REVERSE_SUBTRACT: oss << "GL_FUNC_REVERSE_SUBTRACT"; break;
      case GL_MIN:                   oss << "GL_MIN"; break;
      case GL_MAX:                   oss << "GL_MAX"; break;
   }
   oss << std::endl;
   
      glGetIntegerv(GL_BLEND_SRC_ALPHA, int_);
   oss << "GL_BLEND_SRC_ALPHA: ";
   switch (int_[0])
   {
      case GL_ZERO:                     oss << "GL_ZERO"; break;
      case GL_ONE:                      oss << "GL_ONE"; break;
      case GL_SRC_COLOR:                oss << "GL_SRC_COLOR"; break;
      case GL_ONE_MINUS_SRC_COLOR:      oss << "GL_ONE_MINUS_SRC_COLOR"; break;
      case GL_DST_COLOR:                oss << "GL_DST_COLOR"; break;
      case GL_ONE_MINUS_DST_COLOR:      oss << "GL_ONE_MINUS_DST_COLOR"; break;
      case GL_SRC_ALPHA:                oss << "GL_SRC_ALPHA"; break;
      case GL_ONE_MINUS_SRC_ALPHA:      oss << "GL_ONE_MINUS_SRC_ALPHA"; break;
      case GL_DST_ALPHA:                oss << "GL_DST_ALPHA"; break;
      case GL_ONE_MINUS_DST_ALPHA:      oss << "GL_ONE_MINUS_DST_ALPHA"; break;
      case GL_CONSTANT_COLOR:           oss << "GL_CONSTANT_COLOR"; break;
      case GL_ONE_MINUS_CONSTANT_COLOR: oss << "GL_ONE_MINUS_CONSTANT_COLOR"; break;
      case GL_CONSTANT_ALPHA:           oss << "GL_CONSTANT_ALPHA"; break;
      case GL_ONE_MINUS_CONSTANT_ALPHA: oss << "GL_ONE_MINUS_CONSTANT_ALPHA"; break;

      case GL_SRC_ALPHA_SATURATE:	   oss << "GL_SRC_ALPHA_SATURATE"; break;
      case GL_SRC1_COLOR:	           oss << "GL_SRC1_COLOR"; break;
      case GL_ONE_MINUS_SRC1_COLOR:	   oss << "GL_ONE_MINUS_SRC1_COLOR"; break;
      case GL_SRC1_ALPHA:	           oss << "GL_SRC1_ALPHA"; break;
      case GL_ONE_MINUS_SRC1_ALPHA:    oss << "GL_ONE_MINUS_SRC1_ALPHA"; break;
   }
   oss << std::endl;

   glGetIntegerv(GL_BLEND_DST_ALPHA, int_);
   oss << "GL_BLEND_DST_ALPHA: ";
   switch (int_[0])
   {
      case GL_ZERO:                     oss << "GL_ZERO"; break;
      case GL_ONE:                      oss << "GL_ONE"; break;
      case GL_SRC_COLOR:                oss << "GL_SRC_COLOR"; break;
      case GL_ONE_MINUS_SRC_COLOR:      oss << "GL_ONE_MINUS_SRC_COLOR"; break;
      case GL_DST_COLOR:                oss << "GL_DST_COLOR"; break;
      case GL_ONE_MINUS_DST_COLOR:      oss << "GL_ONE_MINUS_DST_COLOR"; break;
      case GL_SRC_ALPHA:                oss << "GL_SRC_ALPHA"; break;
      case GL_ONE_MINUS_SRC_ALPHA:      oss << "GL_ONE_MINUS_SRC_ALPHA"; break;
      case GL_DST_ALPHA:                oss << "GL_DST_ALPHA"; break;
      case GL_ONE_MINUS_DST_ALPHA:      oss << "GL_ONE_MINUS_DST_ALPHA"; break;
      case GL_CONSTANT_COLOR:           oss << "GL_CONSTANT_COLOR"; break;
      case GL_ONE_MINUS_CONSTANT_COLOR: oss << "GL_ONE_MINUS_CONSTANT_COLOR"; break;
      case GL_CONSTANT_ALPHA:           oss << "GL_CONSTANT_ALPHA"; break;
      case GL_ONE_MINUS_CONSTANT_ALPHA: oss << "GL_ONE_MINUS_CONSTANT_ALPHA"; break;

      case GL_SRC_ALPHA_SATURATE:	   oss << "GL_SRC_ALPHA_SATURATE"; break;
      case GL_SRC1_COLOR:	           oss << "GL_SRC1_COLOR"; break;
      case GL_ONE_MINUS_SRC1_COLOR:	   oss << "GL_ONE_MINUS_SRC1_COLOR"; break;
      case GL_SRC1_ALPHA:	           oss << "GL_SRC1_ALPHA"; break;
      case GL_ONE_MINUS_SRC1_ALPHA:    oss << "GL_ONE_MINUS_SRC1_ALPHA"; break;
   }
   oss << std::endl;

      


   log_.log(oss.str().c_str());
}

void App::startupError(const char *msg)
{
   al_show_native_message_box(NULL, "Startup Error", "Error", msg, NULL, ALLEGRO_MESSAGEBOX_ERROR);
   init_successful_ = false;
}

App::~App()
{
   if (ui_ != NULL)
      delete ui_;

   al_destroy_event_queue(queue_);
   al_destroy_display(display_);
}

void App::setWindowTitle(const char *title)
{
   al_set_window_title(display_, title);
}

int App::run()
{
   if (!init_successful_)
      return -1;

   std::ostringstream oss;
   oss << "sizeof(FComponent): " << sizeof(FComponent) << std::endl;
   oss << "sizeof(FUI):        " << sizeof(FUI) << std::endl;

   log_.log(oss.str().c_str());

   ui_->logDebugRecursive();

   al_start_timer(timer_);

   while (true) {
      ALLEGRO_EVENT ae;
      bool windowResized = false;
      al_wait_for_event(queue_, &ae);
      do
      {
         switch (ae.type)
         {
            case ALLEGRO_EVENT_TIMER:
               ui_->uiSimulate(10);
               break;

            case ALLEGRO_EVENT_DISPLAY_CLOSE:
               return 0;

            case ALLEGRO_EVENT_DISPLAY_RESIZE:
               windowResized = true;
               break;

            case ALLEGRO_EVENT_DISPLAY_SWITCH_OUT:
               ui_->uiActiveStatus(false);
               break;

            case ALLEGRO_EVENT_DISPLAY_SWITCH_IN:
               ui_->uiActiveStatus(true);
               break;

            case ALLEGRO_EVENT_KEY_DOWN:
               ui_->uiKeyState(ae.keyboard.keycode, true);

               if (ae.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
                  return 0;
               break;

            case ALLEGRO_EVENT_KEY_UP:
               ui_->uiKeyState(ae.keyboard.keycode, false);
               break;

            case ALLEGRO_EVENT_KEY_CHAR:
               if ((ae.keyboard.modifiers & (ALLEGRO_KEYMOD_CTRL | ALLEGRO_KEYMOD_ALT | ALLEGRO_KEYMOD_LWIN | ALLEGRO_KEYMOD_RWIN | ALLEGRO_KEYMOD_MENU | ALLEGRO_KEYMOD_COMMAND)) == 0)
                  ui_->uiCharacterEntry(ae.keyboard.unichar);
               break;

            case ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY:
               ui_->uiMouseMove(Point(-9999, -9999));
               break;

            case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
            case ALLEGRO_EVENT_MOUSE_AXES:
            case ALLEGRO_EVENT_MOUSE_WARPED:
               ui_->uiMouseMove(Point(ae.mouse.x + 0.5f, ae.mouse.y + 0.5f));
               if (ae.mouse.dz != 0 || ae.mouse.dw != 0)
                  ui_->uiMouseWheel(ae.mouse.dz, ae.mouse.dw);
               break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
               ui_->uiMouseButton(ae.mouse.button, true);
               break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
               ui_->uiMouseButton(ae.mouse.button, false);
               break;
         }
      } while (al_get_next_event(queue_, &ae));


      if (windowResized)
      {
         if (ui_->uiResize(Dimension(ae.display.width, ae.display.height)))
            al_acknowledge_resize(display_);
         else
            al_resize_display(display_, ceil(ui_->getSize().width), ceil(ui_->getSize().height));
      }

      if (ui_->uiDrawRequested())
      {
         //debugGL();
         glClear(GL_COLOR_BUFFER_BIT);
         ui_->makeDirty(ui_->getAbsoluteRect());
         ui_->uiDraw();
         al_flip_display();
      }
   }

   return 0;
}

BMC_END

#ifdef WIN32

   int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
   bmc::App a;
   return a.run();
}

#else

   int main(int argc, char** argv)
{
   bmc::App a;
   return a.run();
}

#endif