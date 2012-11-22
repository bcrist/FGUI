#include "Logger.h"

BMC_BEGIN

Logger::Logger() : alog(NULL)
{
}


Logger::~Logger()
{
	if (alog != NULL)
		al_close_native_text_log(alog);
}

void Logger::log(const char *txt)
{
	if (alog == NULL)
		alog = al_open_native_text_log("Application Warnings", ALLEGRO_TEXTLOG_NO_CLOSE | ALLEGRO_TEXTLOG_MONOSPACE);

	al_append_native_text_log(alog, txt);
}

BMC_END