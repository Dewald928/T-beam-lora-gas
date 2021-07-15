#include <Arduino.h>
#include <MQUnifiedsensor.h> // MQ-sensor library
#include <CayenneLPP.h> // Cayenne-LPP library
#include "sensors.h"
#include "config.h"

CayenneLPP lpp(51);
DynamicJsonDocument jsonBuffer(1024);

void setup() {
  //Init the serial port communication - to debug the library
  Serial.begin(115200); //Init serial port

  // Init sensors
  init_sensors();

  if (CALIBRATE_SENSORS)
  {
    calibrate_sensor(&MQ4, RatioMQ4CleanAir);
  }  

  // Init lorawan


  // 2-minute warm up time
  // delay(2*60*1000);
}

void loop() {
  // take reading
  float MQ4_ppm = take_reading(&MQ4);
  float MQ9_ppm = take_reading(&MQ9);
  float MQ131_ppm = take_reading(&MQ131);
  Serial.print("MQ4 ppm: ");
  Serial.print(MQ4_ppm);
  Serial.print(", MQ9 ppm: ");
  Serial.print(MQ9_ppm);
  Serial.print(", MQ131 ppm: ");
  Serial.print(MQ131_ppm);
  // MQ4.serialDebug(); // Will print the table on the serial port


  // send reading via cayenne
  JsonObject root = jsonBuffer.to<JsonObject>();
  Serial.println();
  lpp.reset();
  lpp.addAnalogInput(1, MQ4_ppm);
  lpp.addAnalogInput(2, MQ9_ppm);
  lpp.addAnalogInput(3, MQ131_ppm);

  lpp.decodeTTN(lpp.getBuffer(), lpp.getSize(), root);
  
  serializeJsonPretty(root, Serial);
  Serial.println();

  // wait
  delay(1000);
}