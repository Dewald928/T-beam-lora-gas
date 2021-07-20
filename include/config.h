/************************Hardware Related Macros************************************/
#define         Board                   ("ESP-32") // TTGO T-beam in this case.
/***********************Software Related Macros************************************/
#define         Voltage_Resolution      (3.3) // 3V3 <- IMPORTANT. Source: https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/
#define         ADC_Bit_Resolution      (12) // ESP-32 bit resolution. Source: https://randomnerdtutorials.com/esp32-adc-analog-read-arduino-ide/
#define         RatioMQ2CleanAir        (9.83) //RS / R0 = 9.83 ppm . Ratio of your sensor, for this example an MQ-2 0.08V
#define         RatioMQ4CleanAir        (4.4) //RS / R0 = 60 ppm 
#define         RatioMQ9CleanAir        (9.6) //RS / R0 = 60 ppm 
#define         RatioMQ131CleanAir      (15) //RS / R0 = 15 ppm

#define PIN_MQ4 25
#define PIN_MQ9 14
#define PIN_MQ131 13
#define PIN_MH440 2

#define CALIBRATE_SENSORS true
// will use the following values if sensor is already calibrated
#define MQ4_R0 (0.08) // R0 = 0.08V
#define MQ9_R0 (0.60) // R0 = 0.60V
#define MQ131_R0 (1.5) // R0 = 1.5V
