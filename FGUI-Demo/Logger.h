#ifndef FGUI_DEMO_LOGGER_H_
#define FGUI_DEMO_LOGGER_H_
#include "bmc.h"

#include <allegro5/allegro_native_dialog.h>

#include "fgui.h"

BMC_BEGIN

class Logger : public fgui::LoggerInterface
{
public:
	Logger();
	virtual ~Logger();

	virtual void log(const char *txt);

private:
	ALLEGRO_TEXTLOG *alog;
};

BMC_END

#endif
