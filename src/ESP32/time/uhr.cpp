// ============================================================
// UHR IMPLEMENTATION
// NTP Zeit Synchronisation und Zeitanker für millis
// ============================================================

#include "uhr.h"

#include <time.h>

#include "../../Debug/logger.h"

// echte Zeit beim ersten erfolgreichen Sync
static time_t bootEpoch = 0;

// millis Wert beim ersten erfolgreichen Sync
static unsigned long bootMillis = 0;

// merkt ob die Uhr erfolgreich synchronisiert wurde
static bool clockReady = false;

// formatiert eine Epoch Zeit als lesbaren Text
static String epochToString(time_t epochValue)
{
    if (epochValue <= 0)
    {
        return "nicht synchronisiert";
    }

    struct tm timeinfo;
    localtime_r(&epochValue, &timeinfo);

    char buffer[32];
    strftime(buffer, sizeof(buffer), "%d.%m.%Y %H:%M:%S", &timeinfo);

    return String(buffer);
}

// synchronisiert Zeit
void initClock()
{
    // setzt Schweizer Zeitzone mit Sommer- und Winterzeit
    setenv("TZ", "CET-1CEST,M3.5.0/2,M10.5.0/3", 1);
    tzset();

    // startet NTP Synchronisation
    configTime(0, 0, "ch.pool.ntp.org", "pool.ntp.org", "time.google.com");

    log(INFO, "Zeit Sync gestartet");

    struct tm timeinfo;
    int retry = 0;
    const int maxRetries = 20;

    // wartet kurz auf gültige Zeit
    while (!getLocalTime(&timeinfo) && retry < maxRetries)
    {
        delay(500);
        retry++;
    }

    // speichert den ersten Zeitanker
    if (getLocalTime(&timeinfo))
    {
        time(&bootEpoch);
        bootMillis = millis();
        clockReady = true;

        log(SUCCESS, "Zeit synchronisiert");
        log(INFO, "Boot Zeit", epochToString(bootEpoch));
        log(INFO, "Boot Epoch", (unsigned long)bootEpoch);
        log(INFO, "Boot millis", bootMillis);
    }
    else
    {
        clockReady = false;
        log(WARN, "Zeit Sync fehlgeschlagen");
    }
}

// gibt zurück ob die Uhr bereit ist
bool isClockReady()
{
    return clockReady;
}

// gibt aktuelle Schweizer Zeit zurück
String getSwissTimeString()
{
    if (!clockReady)
    {
        return "nicht synchronisiert";
    }

    time_t nowEpoch = bootEpoch + ((millis() - bootMillis) / 1000);

    return epochToString(nowEpoch);
}

// gibt Boot Zeit zurück
String getBootTimeString()
{
    if (!clockReady)
    {
        return "nicht synchronisiert";
    }

    return epochToString(bootEpoch);
}

// uptime Sekunden
unsigned long getUptimeSeconds()
{
    return millis() / 1000;
}

// gibt gespeicherte Boot Epoch zurück
time_t getBootEpoch()
{
    return bootEpoch;
}

// gibt gespeicherte Boot millis zurück
unsigned long getBootMillis()
{
    return bootMillis;
}

// rechnet einen beliebigen millis Wert in Epoch um
time_t millisToEpoch(unsigned long eventMillis)
{
    if (!clockReady)
    {
        return 0;
    }

    // eventMillis ist ein absoluter millis Wert
    unsigned long eventOffset = eventMillis - bootMillis;

    return bootEpoch + (eventOffset / 1000);
}

// rechnet einen Offset seit Boot in Epoch um
time_t millisOffsetToEpoch(unsigned long eventOffset)
{
    if (!clockReady)
    {
        return 0;
    }

    return bootEpoch + (eventOffset / 1000);
}

// wandelt einen beliebigen millis Wert in lesbare Zeit um
String millisToTimeString(unsigned long eventMillis)
{
    return epochToString(millisToEpoch(eventMillis));
}

// wandelt einen Offset seit Boot in lesbare Zeit um
String millisOffsetToTimeString(unsigned long eventOffset)
{
    return epochToString(millisOffsetToEpoch(eventOffset));
}