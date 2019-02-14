#include <Arduino.h>
#include "Wire.h"
#include "BMP280.h"

#define PIN_BMP_SDA 4
#define PIN_BMP_SCL 3

TwoWire myWire(&sercom2, PIN_BMP_SDA, PIN_BMP_SCL);
BMP280 bmp;

void setup()
{
    SerialUSB.begin(115200);
    SerialUSB.println("Inicializando o BMP280...");

    bmp.begin(&myWire, PIN_BMP_SDA, PIN_BMP_SCL);
}

void loop()
{
    SerialUSB.println("Testando...");
    double T, P;
    char result = bmp.startMeasurment();
    if (result != 0)
    {
        delay(result);
        result = bmp.getTemperatureAndPressure(T, P);
        if (result != 0)
        {
            SerialUSB.print("T = \t");
            SerialUSB.print(T, 2);
            SerialUSB.print(" degC\t");
            SerialUSB.print("P = \t");
            SerialUSB.print(P, 2);
            SerialUSB.println(" mBar\t");
        }
    }
    delay(1000);
}