/************************Hardware Related Macros************************************/
#define         Board                   ("ESP-32") // TTGO T-beam in this case.
/***********************Software Related Macros************************************/
#define         Voltage_Resolution      (3.3) // 3V3 <- IMPORTANT. Source: https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/
#define         ADC_Bit_Resolution      (16) // ESP-32 bit resolution. Source: https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/
#define         RatioMQ2CleanAir        (9.83) //RS / R0 = 9.83 ppm . Ratio of your sensor, for this example an MQ-2 0.08V
#define         RatioMQ4CleanAir        (4.4) //RS / R0 = 60 ppm 
#define         RatioMQ9CleanAir        (9.6) //RS / R0 = 60 ppm 
#define         RatioMQ131CleanAir      (15) //RS / R0 = 15 ppm

#define PIN_MQ4 25
#define PIN_MQ9 14
#define PIN_MQ131 13
#define PIN_MH440 2

#define CALIBRATE_SENSORS false
// will use the following values if sensor is already calibrated
#define MQ4_R0 (20.0429) // R0 at 0.037V
#define MQ9_R0 (2.9926) // R0 0.111
#define MQ131_R0 (11.5122) // R0 0.019

#define T_INTERVAL (20) // time interval between two measurements
