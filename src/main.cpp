#include <Arduino.h>
#include <MQUnifiedsensor.h> // MQ-sensor library
#include <CayenneLPP.h> // Cayenne-LPP library
#include "sensors.h"
#include "config.h"
#include "lorawan.h"
#include "boards.h"

CayenneLPP lpp(51);
DynamicJsonDocument jsonBuffer(1024);

void setup() {
  //Init the serial port communication - to debug the library
  Serial.begin(115200); //Init serial port

  initBoard();

  // Init sensors
  init_sensors();

  if (CALIBRATE_SENSORS)
  {
    calibrate_sensor(&MQ4, RatioMQ4CleanAir);
  }  

  // Init lorawan
  setupLMIC();

  // 2-minute warm up time
  // delay(2*60*1000);

  // Encode the data to send to Cayenne
  JsonObject root = jsonBuffer.to<JsonObject>();
  Serial.println();
  lpp.reset();
  lpp.addAnalogInput(1, 0.12);
  lpp.addAnalogInput(2, 0.34);
  lpp.addAnalogInput(3, 0.56);

  lpp.decodeTTN(lpp.getBuffer(), lpp.getSize(), root);
  
  serializeJsonPretty(root, Serial);
  Serial.println();
}

void loop() {
  // take reading
  // float MQ4_ppm = take_reading(&MQ4);
  // float MQ9_ppm = take_reading(&MQ9);
  // float MQ131_ppm = take_reading(&MQ131);
  // Serial.print("MQ4 ppm: ");
  // Serial.print(MQ4_ppm);
  // Serial.print(", MQ9 ppm: ");
  // Serial.print(MQ9_ppm);
  // Serial.print(", MQ131 ppm: ");
  // Serial.print(MQ131_ppm);
  // MQ4.serialDebug(); // Will print the table on the serial port



  // Send data via lorawan
  loopLMIC();

 
  // wait
  // delay(1000);
}