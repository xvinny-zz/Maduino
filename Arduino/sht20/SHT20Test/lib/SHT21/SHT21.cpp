/*
  SHT21 - Library for ESP8266 and Arduino for the Sensirion Temperature and Humidity sensor

  Created by Markus Ulsass, Hamburg, Germany
  github@tradewire.de
  23-5-2016
  https://github.com/markbeee/SHT21
  
  With credits to:
  
  HTU21D Humidity Sensor Library
  By: Nathan Seidle
  SparkFun Electronics
  Date: September 22nd, 2013
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).

*/

#include <Wire.h>
#include "SHT21.h"
#include "wiring_private.h"

TwoWire *m_shtWire;

SHT21::SHT21() {}

void SHT21::begin(TwoWire *shtWire)
{
    m_shtWire = shtWire;
}

float SHT21::getHumidity(void)

{
    return (-6.0 + 125.0 / 65536.0 * (float)(readSHT21(TRIGGER_HUMD_MEASURE_NOHOLD)));
}

float SHT21::getTemperature(void)
{
    return (-46.85 + 175.72 / 65536.0 * (float)(readSHT21(TRIGGER_TEMP_MEASURE_NOHOLD)));
}

uint16_t SHT21::readSHT21(uint8_t command)
{
    uint16_t result;

    m_shtWire->beginTransmission(SHT21_ADDRESS);
    m_shtWire->write(command);
    m_shtWire->endTransmission();
    delay(100);

    m_shtWire->requestFrom(SHT21_ADDRESS, 3);
    while (m_shtWire->available() < 3)
    {
        delay(1);
    }

    // return result
    result = ((m_shtWire->read()) << 8);
    result += m_shtWire->read();
    result &= ~0x0003; // clear two low bits (status bits)
    return result;
}