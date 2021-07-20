#include "MHSensor.h"

MHSensor::MHSensor(String Placa, float VOLTAGE_RESOLUTION, int ADC_BIT_RESOLUTION, int pin, String type)
{
    this->_pin = pin;
    Placa.toCharArray(this->_placa, 20);
    type.toCharArray(this->_type, 6);
    //this->_type = type; //MQ-2, MQ-3 ... MQ-309A
    this->_VOLT_RESOLUTION = VOLTAGE_RESOLUTION;
    this->_ADC_BIT_RESOLUTION = ADC_BIT_RESOLUTION;
}

void MHSensor::init()
{
    pinMode(_pin, INPUT);
}

float MHSensor::getVoltage(int read)
{
    float voltage;
    if (read)
    {
        float avg = 0.0;
        for (int i = 0; i < retries; i++)
        {
            _adc = analogRead(this->_pin);
            avg += _adc;
            delay(retry_interval);
        }
        voltage = (avg / retries) * _VOLT_RESOLUTION / ((pow(2, _ADC_BIT_RESOLUTION)) - 1);
    }
    else
    {
        voltage = _sensor_volt;
    }
    return voltage;
}

void MHSensor::update()
{
    _sensor_volt = this->getVoltage();
}

float MHSensor::readSensor()
{
    //More explained in: https://www.winsen-sensor.com/d/files/MH-440D.pdf
    // Get voltage
    _sensor_volt = this->getVoltage();
    // If voltage below 0.4V, return fault value
    if (_sensor_volt < 0.4)
    {
        return 0.0f;
    }
    else if (_sensor_volt >= 0.4)
    {
        // If voltage above 0.4V, return ppm value
        return mapf(_sensor_volt, 0.4, 2, 0, 100000);
    }

    return _sensor_volt;
}

float mapf(float val, float in_min, float in_max, float out_min, float out_max)
{
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}