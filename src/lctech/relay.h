#include "Arduino.h"

//  The 2x LcTech relay module
//    +------------------------------------+
//    | +---+ +--------+   +--+  +---------|
//    | |   | |        |   +--+  |Relay   ||
//    | +---+ | ESP    |         |index 0 ||
//    | +VCC  | 8266   |         |        ||
//    | +RX   |        |         +---------|
//    | +TX   |        |         +---------|
//    | +     +--------+         |Relay   ||
//    | +                        |index 1 ||
//    | +GND                     |        ||
//    |                          +---------|
//    +------------------------------------+
//
// Keep in mind that sometimes the S1 button 
// is required to be held down during first 
// boot of the relay module.
//
// VCC needs to be +5V, Ampere required is
// unknown. But a normal USB seems to work perfect.

#define RELAY_ONE 0
#define RELAY_TWO 1

void enableRelay(int index);
void disableRelay(int index);
