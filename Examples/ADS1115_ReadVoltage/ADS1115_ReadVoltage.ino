/*
 * file ADS1115_ReadVoltage.ino
 *
 * @ https://github.com/DFRobot/DFRobot_ADS1115
 *
 * connect ADS1115 I2C interface with your board (please reference board compatibility)
 *
 * The voltage value read by A0 A1 A2 A3 is printed through the serial port.
 *
 * Copyright   [DFRobot](http://www.dfrobot.com), 2016
 * Copyright   GNU Lesser General Public License
 *
 * version  V1.0
 * date  2018-01-21
 */

#include <Wire.h>
#include <DFRobot_ADS1115.h>

DFRobot_ADS1115 ads(&Wire);

void setup(void) 
{
    Serial.begin(115200);
    ads.setAddr_ADS1115(ADS1115_IIC_ADDRESS1);   // 0x48
    ads.setGain(eGAIN_TWOTHIRDS);   // 2/3x gain
    ads.setMode(eMODE_SINGLE);       // single-shot mode
    ads.setRate(eRATE_128);          // 128SPS (default)
    ads.setOSMode(eOSMODE_SINGLE);   // Set to start a single-conversion
    ads.init();
}

void loop(void) 
{
    if (ads.checkADS1115())
    {
        int16_t adc0, adc1, adc2, adc3;
        adc0 = ads.readVoltage(0);
        Serial.print("A0:");
        Serial.print(adc0);
        Serial.print("mV,  ");
        adc1 = ads.readVoltage(1);
        Serial.print("A1:");
        Serial.print(adc1);
        Serial.print("mV,  ");
        adc2 = ads.readVoltage(2);
        Serial.print("A2:");
        Serial.print(adc2);
        Serial.print("mV,  ");
        adc3 = ads.readVoltage(3);
        Serial.print("A3:");
        Serial.print(adc3);
        Serial.println("mV");
    }
    else
    {
        Serial.println("ADS1115 Disconnected!");
    }

    delay(1000);
}
