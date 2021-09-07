#include "sensors.h"

DynamicJsonDocument jsonBuffer(1024);
DFRobot_ADS1115 ads(&Wire);

MQUnifiedsensor MQ4(Board, Voltage_Resolution, ADC_Bit_Resolution, PIN_MQ4, ("MQ-4"));
MQUnifiedsensor MQ9(Board, Voltage_Resolution, ADC_Bit_Resolution, PIN_MQ9, ("MQ-9"));
MQUnifiedsensor MQ131(Board, Voltage_Resolution, ADC_Bit_Resolution, PIN_MQ131, ("MQ-131"));
MHSensor MH440(Board, Voltage_Resolution, ADC_Bit_Resolution, PIN_MH440, ("MH-440"));

void calibrate_sensor(MQUnifiedsensor *MQsensor, int CleanAirRatio)
{
    /*****************************  MQ CAlibration ********************************************/
    // Explanation:
    // In this routine the sensor will measure the resistance of the sensor supposing before was pre-heated
    // and now is on clean air (Calibration conditions), and it will setup R0 value.
    // We recomend execute this routine only on setup or on the laboratory and save on the eeprom of your arduino
    // This routine not need to execute to every restart, you can load your R0 if you know the value
    // Acknowledgements: https://jayconsystems.com/blog/understanding-a-gas-sensor
    Serial.print("Calibrating please wait.");
    float calcR0 = 0;
    for (int i = 1; i <= 10; i++)
    {
        MQsensor->update(); // Update data, the arduino will be read the voltage on the analog pin
        calcR0 += MQsensor->calibrate(CleanAirRatio);
        Serial.print(".");
    }
    MQsensor->setR0(calcR0 / 10);
    Serial.println("  done!.");
    Serial.print("R0 = ");
    Serial.println(calcR0);

    if (isinf(calcR0))
    {
        Serial.println("Warning: Conection issue founded, R0 is infite (Open circuit detected) please check your wiring and supply");
        while (1)
            ;
    }
    if (calcR0 == 0)
    {
        Serial.println("Warning: Conection issue founded, R0 is zero (Analog pin with short circuit to ground) please check your wiring and supply");
        while (1)
            ;
    }
    /*****************************  MQ CAlibration ********************************************/

    MQsensor->serialDebug(true);
}

void init_externalADC()
{
    ads.setAddr_ADS1115(ADS1115_IIC_ADDRESS1); // 0x49
    ads.setGain(eGAIN_TWOTHIRDS);              // 2/3x gain
    ads.setMode(eMODE_SINGLE);                 // single-shot mode
    ads.setRate(eRATE_128);                    // 128SPS (default)
    ads.setOSMode(eOSMODE_SINGLE);             // Set to start a single-conversion
    ads.init();
}

void init_sensors()
{
    //Set math model to calculate the PPM concentration and the value of constants
    MQ4.setRegressionMethod(1);   //_PPM =  a*ratio^b
    MQ9.setRegressionMethod(1);   //_PPM =  a*ratio^b
    MQ131.setRegressionMethod(1); //_PPM =  a*ratio^b

    MQ4.setA(3811.9);
    MQ4.setB(-3.113); // Configurate the ecuation values to get LPG concentration
    MQ9.setA(599.65);
    MQ9.setB(-2.244); // Configurate the ecuation values to get CO concentration
    MQ131.setA(23.943);
    MQ131.setB(-1.11); // Configurate the ecuation values to get O3 concentration

    MQ4.init();
    MQ9.init();
    MQ131.init();
    MH440.init();
    /* 
    //If the RL value is different from 10K please assign your RL value with the following method:
    MQ2.setRL(10); Done by measuring resistance of Aout and GND on breakout board
  */
    MQ4.setRL(1);
    MQ9.setRL(1);
    MQ131.setRL(1);

    // If not calibrating, use the following method to set R0 value
    if (!CALIBRATE_SENSORS)
    {
        MQ4.setR0(MQ4_R0);
        MQ9.setR0(MQ9_R0);
        MQ131.setR0(MQ131_R0);
    }
}

float take_reading(MQUnifiedsensor *MQsensor)
{
    MQsensor->update(); // Update data, the arduino will be read the voltage on the analog pin
    // MQsensor.serialDebug(); // Will print the table on the serial port
    return MQsensor->readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup
}

float take_readingMH(MHSensor *MHsensor)
{
    int adc0;
    // read external adc voltage
    if (ads.checkADS1115())
    {
        adc0 = ads.readVoltage(0);
    }
    else
    {
        Serial.println("ADS1115 Disconnected!");
    }

    MHsensor->setADC(adc0);
    return MHsensor->readSensor(); // Sensor will read PPM concentration using the model and a and b values setted before or in the setup
}

void takeReadings()
{
    // take reading
    // float MQ4_ppm = take_reading(&MQ4);
    // float MQ9_ppm = take_reading(&MQ9);
    // float MQ131_ppm = take_reading(&MQ131);
    int MH440_V = 0;
    if (ads.checkADS1115())
    {
        MH440_V = ads.readVoltage(0);
    }
    else
    {
        Serial.println("ADS1115 Disconnected!");
    }
    float MH440_ppm = take_readingMH(&MH440);
    // Serial.print("MQ4 ppm: ");
    // Serial.print(MQ4_ppm);
    // Serial.print(", MQ4 Voltage: ");
    // Serial.print(MQ4_V);
    // Serial.print(", MQ9 ppm: ");
    // Serial.print(MQ9_ppm);
    // Serial.print(", MQ131 ppm: ");
    // Serial.print(MQ131_ppm);
    Serial.print("MH440 voltage: ");
    Serial.print(MH440_V);
    Serial.print(", MH440 ppm: ");
    Serial.println(MH440_ppm);
    // MQ4.serialDebug(); // Will print the table on the serial port

    // Encode the data to send to Cayenne
    JsonObject root = jsonBuffer.to<JsonObject>();
    Serial.println();
    lpp.reset();
    // lpp.addLuminosity(1, MQ4_ppm); //FIXME problem with signed int, addLuminosity instead or / 100
    // lpp.addLuminosity(2, MQ9_ppm);
    // lpp.addLuminosity(3, MQ131_ppm);
    lpp.addLuminosity(1, MH440_V);
    lpp.addLuminosity(2, MH440_ppm);

    lpp.decodeTTN(lpp.getBuffer(), lpp.getSize(), root);

    serializeJsonPretty(root, Serial);
    Serial.println();
}