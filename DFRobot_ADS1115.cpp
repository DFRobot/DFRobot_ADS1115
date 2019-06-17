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
 *Sets the Operational status/single-shot conversion start
 *This determines the operational status of the device
 */
void DFRobot_ADS1115::setOSMode(eADSOSMode_t osmode)
{
    ads_osmode = osmode;
}
/*
 *Gets the Operational status/single-shot conversion start
 */
eADSOSMode_t DFRobot_ADS1115::getOSMode()
{
    return ads_osmode;
}
/*
 *Sets the gain and input voltage range
 *This configures the programmable gain amplifier
 */
void DFRobot_ADS1115::setGain(eADSGain_t gain)
{
    ads_gain = gain;
    switch(gain){
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

/*
 *Gets a gain and input voltage range
 */
eADSGain_t DFRobot_ADS1115::getGain()
{
    return ads_gain;
}

/*
 *Sets the Device operating mode
 *This controls the current operational mode of the ADS1115
 */
void DFRobot_ADS1115::setMode(eADSMode_t mode)
{
    ads_mode = mode;
}

/*
 *Gets the Device operating mode
 */
eADSMode_t DFRobot_ADS1115::getMode()
{
    return ads_mode;
}

/*
 *Sets the Date Rate
 *This controls the data rate setting
 */
void DFRobot_ADS1115::setRate(eADSRate_t rate)
{
    ads_rate = rate;
}

/*
 *Gets the Date Rate
 */
eADSRate_t DFRobot_ADS1115::getRate()
{
    return ads_rate;
}

/*
 *Sets the Comparator mode
 *This controls the comparator mode of operation
 */
void DFRobot_ADS1115::setCompMode(eADSCompMode_t compmode)
{
    ads_compmode = compmode;
}

/*
 *Gets the Comparator mode
 */
eADSCompMode_t DFRobot_ADS1115::getCompMode()
{
    return ads_compmode;
}

/*
 *Sets the Comparator polarity
 *This controls the polarity of the ALERT/RDY pin
 */
void DFRobot_ADS1115::setCompPol(eADSCompPol_t comppol)
{
    ads_comppol = comppol;
}

/*
 *Gets the Comparator polarity
 */
eADSCompPol_t DFRobot_ADS1115::getCompPol()
{
    return ads_comppol;
}

/*
 *Sets the Latching comparator
 *This controls whether the ALERT/RDY pin latches once asserted
 *or clears once conversions are within the
 *margin of the upper and lower threshold values
 */
void DFRobot_ADS1115::setCompLat(eADSCompLat_t complat)
{
    ads_complat = complat;
}

/*
 *Gets the Latching comparator
 */
eADSCompLat_t DFRobot_ADS1115::getCompLat()
{
    return ads_complat;
}

/*
 *Sets the Comparator queue and disable
 *This perform two functions. 
 *It can disable the comparator function and put the
 *ALERT/RDY pin into a high state.
 *It also can control the number of successive
 *conversions exceeding the upper or lower thresholds 
 *required before asserting the ALERT/RDY pin
 */
void DFRobot_ADS1115::setCompQue(eADSCompQue_t compque)
{
    ads_compque = compque;
}


/*
 *Gets the Comparator queue and disable
 */
eADSCompQue_t DFRobot_ADS1115::getCompQue()
{
    return ads_compque;
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

/*
 *Reads the conversion results, measuring the voltage
 *for a single-ended ADC reading from the specified channel
 *Negative voltages cannot be applied to this circuit because the
 *ADS1115 can only accept positive voltages
 */
uint16_t DFRobot_ADS1115::readVoltage(uint8_t channel)
{
    if (channel > 3)
    {
        return 0;
    }
    // Start with default config values
    uint16_t config =   DFROBOT_ADS1115_COMP_QUE_NONE    |   // Disable the comparator (default value)
                        DFROBOT_ADS1115_COMP_LAT_NONLAT  |   // Non-latching (default value)
                        DFROBOT_ADS1115_COMP_POL_ACTVLOW |   // Alert/Rdy active low   (default value)
                        DFROBOT_ADS1115_COMP_MODE_TRAD;      // Traditional comparator (default value)
    // Set Operational status/single-shot conversion start
    config |= ads_osmode;
    // Set PGA/voltage range
    config |= ads_gain;
    // Set Device operating mode
    config |= ads_mode;
    // Set Data rate
    config |= ads_rate;
    // Set single-ended input channel
    switch (channel)
    {
        case (0):
            config |= DFROBOT_ADS1115_MUX_5;
            break;
        case (1):
            config |= DFROBOT_ADS1115_MUX_6;
            break;
        case (2):
            config |= DFROBOT_ADS1115_MUX_7;
            break;
        case (3):
            config |= DFROBOT_ADS1115_MUX_8;
            break;
    }
    // Write config register to the ADC
    writeAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_CONFIG, config);
    // Wait for the conversion to complete
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
int16_t DFRobot_ADS1115::ComparatorVoltage(uint8_t channel)
{
    // Start with default values
    uint16_t config;
    // Set Operational status/single-shot conversion start
    config |= ads_osmode;
    // Set PGA/voltage range
    config |= ads_gain;
    // Set Device operating mode
    config |= ads_mode;
    // Set Data rate
    config |= ads_rate;
    // Set Comparator mode
    config |= ads_compmode;
    // Set Comparator polarity
    config |= ads_comppol;
    // Set Latching comparator
    config |= ads_complat;
    // Set Comparator queue and disable
    config |= ads_compque;
    // Set Differential input channel
    switch (channel)
    {
        case (01):
            config |= DFROBOT_ADS1115_MUX_1;  // AIN0 = P, AIN1 = N
            break;
        case (03):
            config |= DFROBOT_ADS1115_MUX_2;  // AIN0 = P, AIN3 = N
            break;
        case (13):
            config |= DFROBOT_ADS1115_MUX_3;  // AIN1 = P, AIN3 = N
            break;
        case (23):
            config |= DFROBOT_ADS1115_MUX_4;  // AIN2 = P, AIN3 = N
            break;
    }
    
    // Write config register to the ADC
    writeAdsReg(ads_i2cAddress, DFROBOT_ADS1115_POINTER_CONFIG, config);
    
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
