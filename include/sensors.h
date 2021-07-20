#pragma once

#include <Arduino.h>
#include <MQUnifiedsensor.h> // MQ-sensor library
#include "config.h"
#include "lorawan.h"
#include "MHSensor.h"

void calibrate_sensor(MQUnifiedsensor *, int);
void init_sensors();
float take_reading(MQUnifiedsensor *);

/*****************************Globals***********************************************/
extern MQUnifiedsensor MQ4;
extern MQUnifiedsensor MQ9;
extern MQUnifiedsensor MQ131;
extern MHSensor MH440;

/* MQ-2
    Exponential regression:
    Gas    | a      | b
    H2     | 987.99 | -2.162
    LPG    | 574.25 | -2.222
    CO     | 36974  | -3.109
    Alcohol| 3616.1 | -2.675
    Propane| 658.71 | -2.168
  */
/* MQ-4
    Exponential regression:
  Gas    | a      | b
  LPG    | 3811.9 | -3.113
  CH4    | 1012.7 | -2.786
  CO     | 200000000000000 | -19.05
  Alcohol| 60000000000 | -14.01
  smoke  | 30000000 | -8.308
  */
/* MQ- 9
    Exponential regression:
  GAS     | a      | b
  LPG     | 1000.5 | -2.186
  CH4     | 4269.6 | -2.648
  CO      | 599.65 | -2.244
  */
/* MQ-131
    Exponential regression:
  GAS     | a      | b
  NOx     | -462.43 | -2.204
  CL2     | 47.209 | -1.186
  O3      | 23.943 | -1.11
  */