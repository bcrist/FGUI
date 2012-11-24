#include "App.h"

#include <sstream>

#ifdef WIN32
#include <Windows.h>
#include <tchar.h>
#endif

using fgui::Platform;
using fgui::DefaultPlatform;
using fgui::FComponent;
using fgui::FUI;
using fgui::FColoredRectangle;
using fgui::Dimension;
using fgui::Point;
using fgui::Color;
using fgui::Rect;


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

   return true;
}

void App::initUI()
{
   DefaultPlatform &dp = static_cast<DefaultPlatform&>(Platform::get());
   dp.setLogger(&log_);

   ui_ = new FUI();

   ui_->setMinimumSize(Dimension(100, 100));
   ui_->setMaximumSize(Dimension(800, 600));
   ui_->setPreferredSize(Dimension(400, 300));

   std::ostringstream oss;
   oss << ui_->getPreferredSize() << std::endl;
   log_.log(oss.str().c_str());

   ui_->setSize(Dimension(640, 480)); //ui_->getPreferredSize());

   FColoredRectangle *cr1 = new FColoredRectangle(Color(1, 0, 0), Color(0, 1, 0), Color(0, 0, 1), Color(1, 1, 0));

   ui_->addComponent(cr1);

   cr1->setPosition(Point(5, 10));
   cr1->setSize(Dimension(50, 25));

   ui_->uiSimulate(0);
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
               log_.log("Mouse Left\n");
               ui_->uiMouseMove(Point(-9999, -9999));
               break;

            case ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY:
               log_.log("Mouse Entered\n");
            case ALLEGRO_EVENT_MOUSE_AXES:
            case ALLEGRO_EVENT_MOUSE_WARPED:
               ui_->uiMouseMove(Point(ae.mouse.x, ae.mouse.y));
               if (ae.mouse.dz != 0 || ae.mouse.dw != 0)
               {
                  log_.log("Mouse Wheel\n");
                  ui_->uiMouseWheel(ae.mouse.dz, ae.mouse.dw);
               }
               break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
               log_.log("Button Down\n");
               ui_->uiMouseButton(ae.mouse.button, true);
               break;
            case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
               log_.log("Button Up\n");
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
         log_.log("uiDraw()\n");
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