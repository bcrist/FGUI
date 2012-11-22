#ifndef FGUI_DEMO_BMC_H_
#define FGUI_DEMO_BMC_H_

#define _USE_MATH_DEFINES

#ifdef WIN32
#define ALLEGRO_NO_MAGIC_MAIN
#endif

#pragma comment (lib, "opengl32.lib")
#pragma comment (lib, "allegro-5.0.7-monolith-md-debug.lib")
#include <allegro5/allegro.h>
#include <allegro5/allegro_opengl.h>

#define BMC_BEGIN namespace bmc {
#define BMC_END }

#endif
