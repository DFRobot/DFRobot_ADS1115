/*!
 * @file DFRobot_ADS1115.cpp
 * @brief Provides an Arduino library to read ADS1115 data over I2C. Use this library to read analog voltage values.
 *
 * @copyright   Copyright (c) 2010 DFRobot Co.Ltd (http://www.dfrobot.com)
 * @license     The MIT License (MIT)
 * @author [luoyufeng](yufeng.luo@dfrobot.com),
 * @version  V1.0
 * @date  2019-06-19
 * @url https://github.com/DFRobot/DFRobot_ADS1115
 */
#include "Arduino.h"
#include <Wire.h>
#include <math.h>

#include "DFRobot_ADS1115.h"
float coefficient = 0.0625;

/*
 *Instantiates a new ADS1115 class with appropriate properties
 */
void DFRobot_ADS1115::setAddr_ADS1115(uint8_t i2cAddress)
{
    ads_i2cAddress = i2cAddress;
    ads_conversionDelay = DFROBOT_ADS1115_CONVERSIONDELAY;
}

/*
 *Sets up the Hardware
 */
void DFRobot_ADS1115::init()
{
  Wire.begin();
}


bool DFRobot_ADS1115::checkADS1115()
{
    uint8_t error;
    ads_i2cAddress;
    Wire.beginTransmission(ads_i2cAddress);
    error = Wire.endTransmission();
    if(error == 0){
        return true;
    }else{
        return false;
    }
    
}

/*
 *Sets the low threshold value
 */
void DFRobot_ADS1115::setLowThreshold(int16_t threshold)
{
    ads_lowthreshold = threshold;
    writeAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_LOWTHRESH, ads_lowthreshold);
}

/*
 *Gets the low threshold value
 */
int16_t DFRobot_ADS1115::getLowThreshold()
{
    return ads_lowthreshold;
}

/*
 *Sets the high threshold value
 */
void DFRobot_ADS1115::setHighThreshold(int16_t threshold)
{
    ads_highthreshold = threshold;
    writeAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_HITHRESH, ads_highthreshold);
}

/*
 *Gets the high threshold value
 */
int16_t DFRobot_ADS1115::getHighThreshold()
{
    return ads_highthreshold;
}

void DFRobot_ADS1115::setCompQue(eADSCompQue_t value){
    int16_t    conf;
    conf = readAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_CONFIG);
    conf &= ~((uint16_t) 0x03);
    conf |= (uint16_t) value;
    writeAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_CONFIG, conf);
}

void DFRobot_ADS1115::setCompLat(eADSCompLat_t value){
    int16_t    conf;
    conf = readAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_CONFIG);
    conf &= ~((uint16_t) 0x01 << 2);
    conf |= (uint16_t) value << 2;
    writeAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_CONFIG, conf);
}

void DFRobot_ADS1115::setCompPol(eADSCompPol_t value){
    int16_t    conf;
    conf = readAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_CONFIG);
    conf &= ~((uint16_t) 0x01 << 3);
    conf |= (uint16_t) value << 3;
    writeAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_CONFIG, conf);
}

void DFRobot_ADS1115::setCompMode(eADSCompMode_t value){
    int16_t    conf;
    conf = readAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_CONFIG);
    conf &= ~((uint16_t) 0x01 << 4);
    conf |= (uint16_t) value << 4;
    writeAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_CONFIG, conf);
}

void DFRobot_ADS1115::setRate(eADSRate_t value){
    int16_t    conf;
    conf = readAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_CONFIG);
    conf &= ~((uint16_t) 0x07 << 5);
    conf |= (uint16_t) value << 5;
    writeAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_CONFIG, conf);
}

void DFRobot_ADS1115::setMode(eADSMode_t value){
    int16_t    conf;
    conf = readAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_CONFIG);
    conf &= ~((uint16_t) 0x01 << 8);
    conf |= (uint16_t) value << 8;
    writeAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_CONFIG, conf);
}

void DFRobot_ADS1115::setGain(eADSGain_t value){
    int16_t    conf;
    conf = readAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_CONFIG);
    conf &= ~((uint16_t) 0x07 << 9);
    conf |= (uint16_t) value << 9;
    writeAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_CONFIG, conf);
    switch(value){
        case eGAIN_TWO:
            coefficient = 0.0625;
            break;
        case eGAIN_TWOTHIRDS:
            coefficient = 0.1875;
            break;
        case eGAIN_ONE:
            coefficient = 0.125;
            break;
        case eGAIN_FOUR:
            coefficient = 0.03125;
            break;
        case eGAIN_EIGHT:
            coefficient = 0.015625;
            break;
        case eGAIN_SIXTEEN:
            coefficient = 0.0078125;
            break;
        default:
            coefficient = 0.0625;
            break;
    }
}

void DFRobot_ADS1115::setMux(eADSMux_t value){
    int16_t    conf;
    conf = readAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_CONFIG);
    conf &= ~((uint16_t) 0x07 << 12);
    conf |= (uint16_t) value << 12;
    writeAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_CONFIG, conf);
}

void DFRobot_ADS1115::setOSMode(eADSOSMode_t value){
    int16_t    conf;
    conf = readAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_CONFIG);
    conf &= ~((uint16_t) 0x01 << 15);
    conf |= (uint16_t) value << 15;
    writeAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_CONFIG, conf);
}

/*
 *Reads the conversion results, measuring the voltage
 *for a single-ended ADC reading from the specified channel
 *Negative voltages cannot be applied to this circuit because the
 *ADS1115 can only accept positive voltages
 */
uint16_t DFRobot_ADS1115::readVoltage(uint8_t channel)
{
    if (channel > 3)
        return 0;
    // Start with default config values
    setCompQue(eCOMPQUE_NONE);
    setCompLat(eCOMPLAT_NONLAT);
    setCompPol(eCOMPPOL_LOW);
    setCompMode(eCOMPMODE_TRAD);
    if (channel == 0)
        setMux(eADSMUX_5);
    else if (channel == 1)
        setMux(eADSMUX_6);
    else if (channel == 2)
        setMux(eADSMUX_7);
    else if (channel == 3)
        setMux(eADSMUX_8);
    // Wait for the conversion to complete

    uint16_t config = readAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_CONFIG);
    delay(ads_conversionDelay);
    // Read the conversion results
    // 16-bit unsigned results for the ADS1115
    int16_t Voltage = 0;
    Voltage = (int16_t)readAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_CONVERT)*coefficient;
    return Voltage;
}
/*
 *Sets up the comparator causing the ALERT/RDY pin to assert 
 *(go from high to low) when the ADC value exceeds the 
 *specified  upper or lower threshold
 *ADC is Differential input channel
 */
/**************************************************************************/
int16_t DFRobot_ADS1115::comparatorVoltage(uint8_t channel)
{
    // Start with default values
    uint16_t config;
    // Set Comparator mode
    setCompMode(eCOMPMODE_TRAD);
    // Set Comparator polarity
    setCompPol(eCOMPPOL_LOW);
    // Set Latching comparator
    setCompLat(eCOMPLAT_NONLAT);
    // Set Comparator queue and disable
    setCompQue(eCOMPQUE_NONE);
    // Set Differential input channel
    if (channel == 01)
        setMux(eADSMUX_1);  // AIN0 = P, AIN1 = N
    else if (channel == 03)
        setMux(eADSMUX_2);  // AIN0 = P, AIN3 = N
    else if (channel == 13)
        setMux(eADSMUX_3);  // AIN1 = P, AIN3 = N
    else if (channel == 23)
        setMux(eADSMUX_4);  // AIN2 = P, AIN3 = N
    
    // Wait for the conversion to complete
    delay(ads_conversionDelay);
    
    // Read the conversion results
    int16_t Voltage = 0;
    Voltage = (int16_t)readAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_CONVERT)*coefficient;
    return Voltage;
}

void DFRobot_ADS1115::writeReg(uint8_t i2cAddress, uint8_t reg, uint8_t *pBuf, uint16_t len)
{
    _pWire->begin();
    _pWire->beginTransmission(i2cAddress);
    _pWire->write(reg);
    for(uint16_t i = 0; i < len; i ++)
        _pWire->write(pBuf[i]);
    _pWire->endTransmission();
}

void DFRobot_ADS1115::readReg(uint8_t i2cAddress, uint8_t reg, uint8_t *pBuf, uint16_t len)
{
    _pWire->begin();
    _pWire->beginTransmission(i2cAddress);
    _pWire->write(reg);
    if(_pWire->endTransmission() != 0)
        return;
    _pWire->requestFrom(i2cAddress, (uint8_t) len);
    for(uint16_t i = 0; i < len; i ++) {
        pBuf[i] = _pWire->read();
    }
    _pWire->endTransmission();
}

int16_t DFRobot_ADS1115::readAdsReg(uint8_t i2cAddress, uint8_t reg)
{
    uint8_t buf[2] = {0};
    
    readReg(i2cAddress, reg, buf, sizeof(buf));
    return (buf[0] << 8) | buf[1];
}

void DFRobot_ADS1115::writeAdsReg(uint8_t i2cAddress, uint8_t reg, uint16_t value)
{
    uint8_t buffer[2] = {(value >> 8), value & 0xff};
    writeReg(i2cAddress, reg, buffer, 2);
}
