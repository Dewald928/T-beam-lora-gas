#pragma once

#include <Arduino.h>
#include <lmic.h>
#include <hal/hal.h>
#include "boards.h"
#include <CayenneLPP.h> // Cayenne-LPP library
#include "sensors.h"

extern CayenneLPP lpp;

void setupLMIC(void);
void loopLMIC(void);
void takeReadings();