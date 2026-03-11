#ifndef SYSTEM_STATE_H
#define SYSTEM_STATE_H

// ============================================================
// SYSTEM STATE
// globale Trigger und Statusvariablen für das ganze Projekt
// ============================================================

// ------------------------------------------------------------
// RELAY TRIGGER
// wenn true wird ein 0.5s Puls auf D2 ausgelöst
// das relay modul setzt den wert danach wieder auf false
// ------------------------------------------------------------
inline bool relayPulseRequest = false;

#endif