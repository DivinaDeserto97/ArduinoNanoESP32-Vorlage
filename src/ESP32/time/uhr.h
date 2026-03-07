#ifndef UHR_H
#define UHR_H

// ============================================================
// UHR SYSTEM
// verwaltet Zeit und NTP Synchronisation
// ============================================================

#include <Arduino.h>
#include <time.h>

// startet Zeit Synchronisation
void initClock();

// gibt zurück ob Zeit synchronisiert wurde
bool isClockReady();

// gibt aktuelle Schweizer Zeit zurück
String getSwissTimeString();

// gibt Boot Zeit als Text zurück
String getBootTimeString();

// gibt uptime Sekunden zurück
unsigned long getUptimeSeconds();

// gibt die gespeicherte Boot Epoch zurück
time_t getBootEpoch();

// gibt millis vom ersten Zeitanker zurück
unsigned long getBootMillis();

// wandelt eine beliebige millis Zeit in echte Uhrzeit um
String millisToTimeString(unsigned long eventMillis);

// wandelt einen millis Offset seit Boot in echte Uhrzeit um
String millisOffsetToTimeString(unsigned long eventOffset);

// gibt echte Epoch für einen millis Wert zurück
time_t millisToEpoch(unsigned long eventMillis);

// gibt echte Epoch für einen millis Offset seit Boot zurück
time_t millisOffsetToEpoch(unsigned long eventOffset);

#endif