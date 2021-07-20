#pragma once

#include <Arduino.h>
#include <stdint.h>

#define ADC_RESOLUTION 12 // for 10bit analog to digital converter.
#define retries 2
#define retry_interval 20

class MHSensor
{
private:
    /************************Private vars************************************/
    byte _pin;
    byte _firstFlag = false;
    byte _VOLT_RESOLUTION  = 3.3; // if 3.3v use 3.3
    byte _ADC_BIT_RESOLUTION = 12;
    
    float _adc, _sensor_volt;
    float _PPM;  
    
    char _type[6];
    char _placa[20]; 
public:
    MHSensor(String Placa, float VOLTAGE_RESOLUTION, int ADC_BIT_RESOLUTION = 12, int pin = 1, String type = "CUSTOM MH");

    void init();
    void update();

    float readSensor();

    float getVoltage(int read = true);
};

float mapf(float, float, float, float, float);



