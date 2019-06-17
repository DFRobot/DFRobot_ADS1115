/*
 * file ADS1115_ComparatorVoltage.ino
 *
 * @ https://github.com/DFRobot/DFRobot_ADS1115
 *
 * connect ADS1115 I2C interface with your board (please reference board compatibility)
 *
 * Through the serial port to see the voltage difference between the two channels.
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
    ads.setAddr_ADS1115(ADS1115_IIC_ADDRESS0);   // 0x48
    ads.setGain(eGAIN_TWO);          // 2x gain
    ads.setMode(eMODE_SINGLE);       // single-shot mode
    ads.setRate(eRATE_128);          // 128SPS (default)
    ads.setOSMode(eOSMODE_SINGLE);   // Start a single-conversion (default)
    ads.setCompMode(eCOMPMODE_TRAD);     // Traditional comparator with hysteresis (default)
    ads.setCompPol(eCOMPPOL_LOW);        // Comparator polarity: Active low (default)
    ads.setCompLat(eCOMPLAT_LATCH);   // Latching comparator
    ads.setCompQue(eCOMPQUE_ONE);        // Comparator queue: Assert after one conversion
    // ADC Range: 2x gain (1 bit = 0.0625mV)");
    // Serial.println("Comparator High Threshold: 32000 (2.000V)");
    ads.setHighThreshold(32000);
    ads.init();
    delay(1000);
}

void loop(void)
{
    if (ads.checkADS1115())
    {
        int16_t result01, result03, result13, result23;
        Serial.println("Get the voltage difference between two channels");
        Serial.println(" ");
        result01 = ads.ComparatorVoltage(01);
        Serial.print("The voltage difference between A0 and A1 ");
        Serial.print(result01);
        Serial.println("mV");
        result03 = ads.ComparatorVoltage(03);
        Serial.print("The voltage difference between A0 and A3 ");
        Serial.print(result03);
        Serial.println("mV");
        result13 = ads.ComparatorVoltage(13);
        Serial.print("The voltage difference between A1 and A3 ");
        Serial.print(result13);
        Serial.println("mV");
        result23 = ads.ComparatorVoltage(23);
        Serial.print("The voltage difference between A2 and A3 ");
        Serial.print(result23);
        Serial.println("mV ");
    }else
    {
        Serial.println("ADS1115 Disconnected!");
    }

    delay(1000);
}
