#include <Arduino.h>
#include <MQUnifiedsensor.h> // MQ-sensor library
#include <CayenneLPP.h> // Cayenne-LPP library
#include "sensors.h"
#include "config.h"
#include "lorawan.h"
#include "boards.h"

CayenneLPP lpp(51);

void setup() {
  //Init the serial port communication - to debug the library
  Serial.begin(115200); //Init serial port

  initBoard();

  // Init sensors
  init_sensors();
  init_externalADC();

  if (CALIBRATE_SENSORS)
  {
    calibrate_sensor(&MQ4, RatioMQ4CleanAir);
    // calibrate_sensor(&MQ9, RatioMQ9CleanAir);
    // calibrate_sensor(&MQ131, RatioMQ131CleanAir);
  }  

  // Init lorawan
  setupLMIC();

  // 2-minute warm up time
  // delay(2*60*1000);

  
}

void loop() {
  // Send data via lorawan
  loopLMIC();

  // wait
  // delay(1000);
}