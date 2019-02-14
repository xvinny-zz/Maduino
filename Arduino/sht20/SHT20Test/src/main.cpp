
/****************************************************************
*  SHT21_Demo
*
*  An example sketch that reads the sensor and prints the
*  relative humidity to the serial port
* 
***************************************************************/
#include <Arduino.h>
#include <Wire.h>
#include "SHT21.h"
#include "wiring_private.h"

#define PIN_BMP_SDA             A1      // PB08 (SERCOM4/PAD[0])
#define PIN_BMP_SCL             A2      // PB09 (SERCOM4/PAD[1])

SHT21 mySHT21;
TwoWire wireBMP(&sercom4, PIN_BMP_SDA, PIN_BMP_SCL);

void setup()
{
    SerialUSB.begin(115200);
    SerialUSB.println("Inicializando o SHT20...");
    wireBMP.begin();
    pinPeripheral(PIN_BMP_SDA, PIO_SERCOM_ALT);
    pinPeripheral(PIN_BMP_SCL, PIO_SERCOM_ALT);
    mySHT21.begin(&wireBMP);
    SerialUSB.println("SHT20 inicializado!");
}

void loop()
{
    SerialUSB.print("Humidity(%RH): ");
    SerialUSB.print(mySHT21.getHumidity());
    SerialUSB.print("     Temperature(C): ");
    SerialUSB.println(mySHT21.getTemperature());

    delay(1000);
}