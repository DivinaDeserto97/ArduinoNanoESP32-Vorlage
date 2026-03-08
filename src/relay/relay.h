#ifndef RELAY_H
#define RELAY_H

// ============================================================
// RELAY
// steuert den D2 Ausgang für einen kurzen Puls
// ============================================================

// initialisiert den Relay Ausgang
void initRelay();

// verarbeitet Relay Trigger aus system_state.h
void updateRelay();

#endif