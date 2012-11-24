#ifndef FGUI_DEMO_APP_H_
#define FGUI_DEMO_APP_H_
#include "bmc.h"

#define FGUI_USE_ALLEGRO_FONTS

#pragma comment(lib, "FGUI.lib")
#include "fgui.h"

#include "Logger.h"

BMC_BEGIN

class App
{
public:
	Logger log_;

	App();
	~App();

	int run();

	void setWindowTitle(const char *title);

private:
	bool init_successful_;

	ALLEGRO_DISPLAY *display_;
	ALLEGRO_EVENT_QUEUE *queue_;
    ALLEGRO_TIMER *timer_;
	
	fgui::FUI *ui_;

    int64_t last_timer_val;

	bool initOpenGL();
	void initUI();
	void startupError(const char *msg);
};

BMC_END

#endif
