#include "ota_manager.h"

#include <ArduinoOTA.h>

#include "../../Debug/logger.h"
#include "../../../include/env.h"

void initOTA()
{
    // Gerätename im Netzwerk
    ArduinoOTA.setHostname(DEVICE_ID);

    ArduinoOTA.onStart([]()
    {
        log(INFO,"OTA Update gestartet");
    });

    ArduinoOTA.onEnd([]()
    {
        log(SUCCESS,"OTA Update fertig");
    });

    ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
    {
        int percent = (progress * 100) / total;
        log(INFO,"OTA Fortschritt", percent);
    });

    ArduinoOTA.onError([](ota_error_t error)
    {
        log(ERROR,"OTA Fehler", error);
    });

    ArduinoOTA.begin();

    log(SUCCESS,"OTA bereit");
}

void updateOTA()
{
    ArduinoOTA.handle();
}